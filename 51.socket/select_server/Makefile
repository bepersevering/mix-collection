#####################################################################
## file        : test makefile for build current dir .c            ##
## author      : liujifeng                                         ##
## date-time   : 12/14/2019                                        ##
## 原文链接：https://blog.csdn.net/jenie/article/details/106893512
#####################################################################

# 此功能是编译当前所有文件的c或者cpp的文件
CC = gcc
CPP = g++
RM = rm -rf

DEBUG_ENABLE   = 1

SRC_PATH := .
SRCS += $(wildcard $(SRC_PATH)/*c)

TARGET := httpd

OBJS := $(SRCS:.c=.o)
LIBS:=pthread
INCLUDE_PATH := . /usr/local/include/

LIBRARY_PATH := . /usr/local/lib

ifeq (1, ${DEBUG_ENABLE})
	CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1 -Wl,--no-as-needed -lm
endif

## get all include path
CFLAGS += $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

##get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

all: clean build
build:
	$(CC) -c $(CFLAGS) $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	$(RM) $(OBJS)

clean: 
	$(RM) $(OBJS) $(TARGET)
