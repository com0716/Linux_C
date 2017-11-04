/*
 * IO多路复用之select
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1 头文件
1.1 POSIX.1-2001
	#include <sys/select.h>
1.2 早期标准
	#include <sys/time.h>
 	#include <sys/types.h>
 	#include <unistd.h>

2 函数原型
 int select(int nfds, fd_set *readfds, fd_set *writefds,
             fd_set *exceptfds, struct timeval *timeout);
2.1 描述
	I/O多路复用
2.2 函数参数
	参数中的fds是file discriptor set的简写
	nfds：需要监测的文件描述符中最大文件描述符+1
	readfds：需要监测的可读文件描述符集合
	writefds：需要监测的可写文件描述符集合
	exceptfds：需要监测的出现异常情况的文件描述符集合
	timeout：1)NULL，select一直阻塞，直到有一个需要监测的文件描述符发生变化
			 2)timeval的两个值都为空，立即返回
			 3)timeval不为空，监测到文件描述符变化就立即返回，或者超时返回
2.3 函数返回值
	返回监测到文件描述符的总个数

3 其他
	void FD_CLR(int fd, fd_set *set);
	int  FD_ISSET(int fd, fd_set *set);
	void FD_SET(int fd, fd_set *set);
	void FD_ZERO(fd_set *set);

 */
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int nready = 0;
	int listen_fd = STDIN_FILENO;

	int nfds = 0;
	fd_set readfds;
	fd_set in_readfds;
	struct timeval timeout;

	char read_buf[100];
	int read_len = 0;

	FD_ZERO(&in_readfds);
	FD_SET(listen_fd, &in_readfds);
	nfds = listen_fd + 1;
	
	while (1)
	{
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		memcpy(&readfds, &in_readfds, sizeof(fd_set));

		nready = select(nfds, &readfds, NULL, NULL, &timeout);
		if (nready > 0)
		{
			//对多个文件描述符进行监测，这里就需要一个循环
			if (FD_ISSET(listen_fd, &readfds))
			{
				//printf("Data is available now.\n");
				//ps:如果不做下面的读取操作，只是打印printf
				//   会出现无限循环的情况
				//   这是因为程序不对其处理，select一直会上报
				read_len = read(listen_fd, read_buf, sizeof(read_buf));
				if (memcmp("quit", read_buf, 4) == 0)
				{
					return 1;
				}

				write(STDOUT_FILENO, read_buf, read_len);
			}
		}
	}
	
	return 0;
}

