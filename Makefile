GXX = gcc

lab0: lab0.h lab0.c
	$(GXX) lab0.c -o lab0

check: lab0.h lab0.c
	$(GXX) -g lab0.c -o lab0
	echo "hello world" > testfile
	./lab0 --input=testfile --output=testcopy
	cat testcopy
	-./lab0 --input=testfile --output=testcopy --catch --segfault
	-./lab0 --input=testfile --output=testcopy --segfault	
	-./lab0 --input=testfile --output
	-./lab0 --input= --output=testcopy

clean:
	-rm testcopy
	-rm testfile
	-rm lab0

dist:
	# tar example used:
	# http://osxdaily.com/2012/04/05/create-tar-gzip/
	tar -cvzf lab0-040161840.tar.gz lab0.h lab0.c README.md img/* Makefile
