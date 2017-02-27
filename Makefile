cc = gcc
cflags = -Wall -Werror -Wextra -pedantic -ansi
executable=hospital

all: hospital

debug: cflags += -g
debug: executable=hospital.dbg
debug: hospital

.PHONY: force
compiler_flags: force
	echo '$(cflags)' | cmp -s - $@ || echo '$(cflags)' > $@

hospital: compiler_flags hospital.o parse.o structure.o
	$(cc) -o $(executable) $(cflags) hospital.o parse.o structure.o

structure.o: compiler_flags structure.c structure.h
	$(cc) -c $(cflags) structure.c

parse.o: compiler_flags parse.c parse.h
	$(cc) -c $(cflags) parse.c

hospital.o: compiler_flags hospital.c
	$(cc) -c $(cflags) hospital.c

clean :
	rm hospital.o parse.o structure.o hospital hospital.dbg compiler_flags
