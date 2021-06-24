CFLAGS = -O
OBJS = dllist.o fields.o jval.o jrb.o

all: libfdr.a

libfdr.a: $(OBJS)
	ar ru libfdr.a $(OBJS)
	ranlib libfdr.a 

clean:
	rm -f core *.o libfdr.a