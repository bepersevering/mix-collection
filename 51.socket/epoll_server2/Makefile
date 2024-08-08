#此功能是编译当前所有文件的c或cpp的文件。
CC      = gcc
CPP     = g++
RM      = rm -rf
 
DBG_ENABLE   = 1
 
## source file path
        SRC_PATH   := .
 
## get all source files
SRCS         += $(wildcard $(SRC_PATH)/*.c)
 
## target exec file name
TARGET     := httpd
#TARGET = $(patsubst %.cpp, %, ${SRCS})
 
## all .o based on all .c
OBJS        := $(SRCS:.c=.o)
 
## need libs, add at here
#LIBS := pthread mysqlclient hiredis
LIBS := pthread 
#LIBS := pthread  hiredis event
 
## used headers  file path
# 先备份
INCLUDE_PATH := . /usr/local/include/
 
 
#-I./指定出ae.h头文件的位置
LIBRARY_PATH := . /usr/local/lib 
 
## debug for debug info, when use gdb to debug
#-Wl,--no-as-needed  -lm 解决cjson编译选项问题
ifeq (1, ${DBG_ENABLE})
	CFLAGS += -D_DEBUG -O0 -g -DDEBUG=1  -Wl,--no-as-needed  -lm
endif
 
## get all include path
CFLAGS  += $(foreach dir, $(INCLUDE_PATH), -I$(dir))
 
## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))
 
## get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))
 
all: clean build
build:
	$(CC) -c $(CFLAGS) $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
	$(RM) $(OBJS)
 
clean:
	$(RM) $(OBJS) $(TARGET)
 