CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS = -Wall -g
LFLAGS = -l sqlite3

all: suricatastat

suricatastat: main.o file.o db.o gestionStruct.o stats.o
	gcc $(CFLAGS) $(LFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm *.o

cleanall:
	rm *.o
	rm suricatastat
