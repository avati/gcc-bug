all: good bad
	./good
	./bad

good:
	gcc-4.3 -Wall -O0 -fPIC pool.c -o good

bad:
	gcc-4.3 -Wall -O2 -fPIC pool.c -o bad
