CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -ljansson

all: suricatastat

suricatastat: main.o
	gcc $(CFLAGS) $(LFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) $(LFLAGS) -c $< -o $@

clean:
	rm *.o
