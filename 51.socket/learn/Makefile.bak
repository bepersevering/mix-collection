
CC = gcc

CFLAGS = -Wall -g

TABLE_TARGET = hash_table_main

SRCS = hash_table.c hash_table_test.c 

OBJS = $(SRCS:.c=.o)

hash_table_all: $(TABLE_TARGET)

# 链接目标文件
$(TABLE_TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TABLE_TARGET) $(OBJS)

# 编译源文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成文件
clean: 
	rm -f $(TABLE_TARGET) $(OBJS)

# 伪目标
.PHONY: all clean
