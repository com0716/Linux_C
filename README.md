# Linux_C
将Linux下所有相关的编程知识记录下来，用于平时查询
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
