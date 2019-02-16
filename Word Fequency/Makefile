CFLAG =-c -Wall -g

all: wf

wf: wf.o reader.o dict.o
	gcc wf.o reader.o dict.o -o wf

wf.o: wf.c
	gcc $(CFLAG) wf.c

reader.o: reader.c
	gcc $(CFLAG) reader.c

dict.o: dict.c
	gcc $(CFLAG) dict.c


clean:
	rm -f *.o wf
