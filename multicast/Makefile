CC=gcc
CFLAGS=-g -Wall -Wextra
LDFLAGS=

all: multicast_sender multicast_receiver

multicast_sender: multicast_sender.o
	$(CC) $(LDFLAGS) -o $@ $^

multicast_receiver: multicast_receiver.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f multicast_sender multicast_receiver *.o
