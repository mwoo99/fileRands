randtest: devrand.c
	gcc devrand.c -o randtest

run: randtest
	./randtest

clean:
	rm randFile.txt
	rm randtest
	rm *~
