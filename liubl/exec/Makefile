
TARGET = benchmark
FILES += ./*.c
OBJS += ./*.o

SHELL= /bin/sh
CC_OSX = clang
CC_LINUX = gcc

UNAME=$(shell uname)
CC :=
ifeq ($(UNAME), Darwin)
	CC := $(CC_OSX)
else
	CC := $(CC_LINUX)
endif

TFLAGS=
DFLAGS=-g -Wall -o0
LINKS=

$(TARGET):
	$(CC) $(DFLAGS) $(TFLAGS) $(LINKS) -o $(TARGET) $(FILES)


.PHONY clean:
	rm -rf $(TARGET) $(OBJS) $(TARGET).dSYM 

