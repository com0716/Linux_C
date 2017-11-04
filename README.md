# Linux_C
将Linux下所有相关的编程知识记录下来，用于平时查询
0 CentOS的使用问题
0.1 vim中无法输入中文的问题
	set fileencodings=utf-8,gb2312,gbk,gb18030
	set termencoding=utf-8
	set fileformats=unix
	set encoding=prc
	这个原因是: 系统语言是英文，其编码不支持中文，在.vimrc中添加上面选项即可

1 Makefile中判断文件夹/文件是否存在的方法
1.1 shell
	OBJS_DIR = obj
	OBJS_DIR_EXIST = $(shell if [ ! -f  $(OBJS_DIR) ]; then echo "notexist"; fi;)

	all:
	ifneq ($(OBJS_DIR_EXIST), notexist)
	    @mkdir $(OBJS_DIR)
	endif

1.2 makefile函数
	OBJS_DIR = obj

	all:
	ifneq ($(OBJS_DIR), $(wildcard $(OBJS_DIR)))
		@mkdir $(OBJS_DIR)
	endif
	
1.3 总结
	建议多使用第二种
	OBJS_DIR_EXIST1 = $(shell if [ ! -f  $(OBJS_DIR) ]; then echo "notexist"; fi;)
	OBJS_DIR_EXIST2 = `if [ ! -f  $(OBJS_DIR) ]; then echo "notexist"; fi;`
	OBJS_DIR_EXIST1直接获得执行的结果，只执行一次；OBJS_DIR_EXIST2每次使用这个变量时都会执行shell指令，获取最新的执行结果

2 github远程提交
2.1 在本地创建git仓库，然后提交
	git remote add origin git@github.com:hanzichi/helloworld.git
	
2.2 本地修改后提交
	git push http://com0716@github.com/com0716/Linux_C.git
	直接修改.git/config中的url也可实现

3 I/O多路复用select poll epoll
	看这部分内容主要是为了更加学习nginx
	select poll 对于监测的IO不进行马上操作，后面还会再监测到
	epoll的默认形式也是这样的
