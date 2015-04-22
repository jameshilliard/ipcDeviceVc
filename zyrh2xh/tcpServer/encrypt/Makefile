# Makefile
include ../Rules.make

SOURCES =$(wildcard *.c)
HEADERS =$(wildcard *.h)
OBJS = $(patsubst %.c, %.o, $(SOURCES))
#OBJS   	=$(SOURCES:%.c=objs/%.o)

#CROSS_COMPILE= arm-wrs-linux-gnueabi-armv5tel-uclibc_small-
ifeq ($(SUPPORT_DM6467), y)
CROSS_COMPILE= arm_v5t_le-
else
#CROSS_COMPILE= arm-hismall-linux-
CROSS_COMPILE= arm_v5t_le-
endif

CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
RANLIB = $(CROSS_COMPILE)ranlib

CFLAG	=
DFLAG	=-Wall -O2
CFLAGS	=$(CFLAG) $(DFLAG)

LIB =libencrypt.a

all : $(LIB) 

$(LIB):$(OBJS)
	$(AR) r $@ $(OBJS)
	$(RANLIB) $@
ifeq ($(SUPPORT_DM6467), y)
	cp $@ ../lib_DM6467/
else
	cp $@ ../lib
endif
	cp base64.h ../h/encrypt
	cp d3des.h ../h/encrypt
	cp md5.h ../h/encrypt
	cp hmac.h ../h/encrypt
	cp cryptomisc.h ../h/encrypt

#$(OBJS):objs/%.o:%.c
#	@mkdir -p objs 
#	@mkdir -p $(dir $@)
%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
clean :
	#-rm -rf objs
	-rm -f *.o *.bak $(LIB)

