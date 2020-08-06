all:
	gcc *.c -o nsh

run: all
	./nsh

_dbg: all
	gcc *.c -g -o nsh

dbg: _dbg
	gdb ./nsh

val: _dbg
	valgrind ./nsh


clean:
	rm -vf nsh
	rm -rvf *.o
