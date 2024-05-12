CC=gcc
CFLAGS=-g -Wall -Wextra
LDFLAGS=

all: broadcast_sender broadcast_receiver

broadcast_sender: broadcast_sender.o
	$(CC) $(LDFLAGS) -o $@ $^

broadcast_receiver: broadcast_receiver.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f broadcast_sender broadcast_receiver *.o
