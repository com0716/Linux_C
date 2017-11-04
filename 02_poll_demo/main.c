/*
 * 多路IO复用之poll
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1 头文件
	#include <poll.h>

2 函数原型
	int poll(struct pollfd *fds, nfds_t nfds, int timeout);
2.1 函数参数
	fds：文件描述符集合数组
	nfds：数组fds的长度
	timeout：超时时间，单位ms，负数表示无限等待，即阻塞

	struct pollfd {
		int   fd;         // file descriptor
		short events;     // requested events
		short revents;    // returned events
	};
	events：需要监测的事件，常用的有POLLIN、POLLOUT、POLLERR

3 返回值
	-1 出错
	0  超时或者没有监测到
	>0 监测到的文件描述符的个数
*/
#include <poll.h>
#include <unistd.h>

#define MAX_POLL_FD 5

int main(int argc, char *argv[])
{
	int nready = 0;
	int timeout = 5000;
	struct pollfd listen_fds[MAX_POLL_FD];
	int nfds = 0;

	int read_len = 0;
	char read_buf[1024];

	listen_fds[0].fd = STDIN_FILENO;
	listen_fds[0].events = POLLIN;
	nfds ++;

	while (1)
	{
		nready = poll(listen_fds, nfds, timeout);
		if (nready > 0)
		{
			memset(read_buf, 0, sizeof(read_buf));
			read_len = read(listen_fds[0].fd, read_buf, sizeof(read_buf));
			
			if (memcmp("quit", read_buf, 4) == 0)
			{
				return 1;
			}
			write(STDOUT_FILENO, read_buf, read_len);
		}
	}

	return 0;
}

