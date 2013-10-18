CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -l sqlite3

all: suricatastat

suricatastat: main.o file.o
	gcc $(CFLAGS) $(LFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) $(LFLAGS) -c $< -o $@

clean:
	rm *.o
