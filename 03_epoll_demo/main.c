/*
 * IO多路复用之epoll
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1 头文件 
	#include <sys/epoll.h>
2 函数原型
2.1	int epoll_create(int size);
	size: 表示epoll要监测的个数
	return value: 文件描述符，用于描述epoll，需要使用close进行关闭
2.2 int  epoll_ctl(int  epfd,  int  op,  int  fd,  struct epoll_event *event);
	epfd: 描述epoll的文件描述符，也就是epoll_create的返回值
	op: 操作类型，主要有EPOLL_CTL_ADD，EPOLL_CTL_MOD，EPOLL_CTL_DEL
	fd: 加入epoll中的文件描述符
	event:
	typedef union epoll_data {
		void        *ptr;
		int          fd;
		__uint32_t   u32;
		__uint64_t   u64;
	} epoll_data_t;

	struct epoll_event {
		__uint32_t   events;      //Epoll events
		epoll_data_t data;        //User data variable
	};
	events表示事件，主要有EPOLLIN，EPOLLOUT，EPOLLRDHUP等
	returne value: 0表示成功，-1表示出错
2.3 int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
	epfd: 描述epoll的文件描述符，也就是epoll_create的返回值
	events: 用于接收监测的结果
	maxevents: events的最大长度
	timeout: 超时时间，单位ms，-1表示无限等待，即阻塞
	return value: 0表示没有，-1表示出错，>0表示填充events的个数

3 其他
*/
#include <sys/epoll.h>
#include <unistd.h>

#define EPOLL_MAX_EVENTS 10

int main(int argc, char *argv[])
{
	int listen_fd = STDIN_FILENO;
	int read_len = 0;
	char read_buf[1024] = {0};
	struct epoll_event event;

	int nready = 0;
	struct epoll_event listen_events[EPOLL_MAX_EVENTS];
	int timeout = 5000;

	int epfd = epoll_create(EPOLL_MAX_EVENTS);
	if (epfd < 0)
	{
		perror("[ERROR] epoll_create");
		return -1;
	}

	memset(&event, 0, sizeof(event));
	event.events = EPOLLIN;
	event.data.fd = listen_fd;

	epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event);

	while (1)
	{
		nready = epoll_wait(epfd, listen_events, EPOLL_MAX_EVENTS, timeout);
		if (nready > 0)
		{
			int i = 0;
			for (i = 0; i < nready; ++i)
			{
				if (listen_events[i].data.fd == listen_fd)
				{
					memset(read_buf, 0, sizeof(read_buf));
					read_len = read(listen_fd, read_buf, sizeof(read_buf));
					if (memcmp("quit", read_buf, 4) == 0)
					{
						close(epfd);
						return 1;
					}
					write(STDOUT_FILENO, read_buf, read_len);
				}
			}
		}
	}
	
	return 0;
}
