CFLAGS = -Wall -Wstrict-aliasing=2 -fstrict-aliasing -std=c99 -fPIC

all: good bad
	./good
	./bad

good:
	gcc-4.3 $(CFLAGS) -O0 pool.c -o good

bad:
	gcc-4.3 $(CFLAGS) -O2 pool.c -o bad

clean:
	rm -vf ./good ./bad