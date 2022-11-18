CC = gcc
CFLAGS = -Wall
PROJECTS = helloworld tcpsvr
SUB_SRC_DIR := ./net
OBJS += $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c $(SUB_SRC_DIR)/*.c))

all: 	${PROJECTS}

helloworld: helloworld.o
		${CC} ${CFLAGS} -o $@ helloworld.o
# aprsock.o: ./net/aprsock.c ./net/aprsock.h
#         ${CC} ${CFLAGS} -c ./net/aprsock.c
tcpsvr: tcpsvr.c $(OBJS)
		${CC} ${CFLAGS} -o $@ $^
# $@ 指 tcopsvr，$^ 指 OBJS 中，所有的 .o 目标文件

.PHONY: 	clean
clean:
	-rm *.o ${PROJECTS} ${OBJS}
