GXX = gcc

lab0: lab0.h lab0.c
	$(GXX) lab0.c -o lab0

check: lab0.h lab0.c
	$(GXX) -g lab0.c -o lab0
	./lab0-test

clean:
	-rm testcopy
	-rm testfile
	-rm lab0
	-rm lab0-040161840.tar.gz

dist:
	# tar example used:
	# http://osxdaily.com/2012/04/05/create-tar-gzip/
	tar -cvzf lab0-040161840.tar.gz lab0.h lab0.c README.md img/* Makefile lab0-test

testfile:
	echo "hello world" > testfile
