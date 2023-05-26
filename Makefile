default: build

build:
	c99 urss.c -o urss

install: build
	rm -f /usr/local/bin/urss
	cp urss /usr/local/bin/
	cp urss.1 /usr/local/man/man1/
