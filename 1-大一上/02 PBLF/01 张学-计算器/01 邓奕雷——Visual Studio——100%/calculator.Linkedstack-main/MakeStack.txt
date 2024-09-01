OBJS= Stack.o main.o 
calculator:$(OBJS)
	cc $(OBJS) -o calculator -lreadline -lhistory -lm

main.o:main.c Stack.h common.h
	cc -c main.c -o main.o
	
Stack.o:Stack.c Stack.h common.h
	cc -c Stack.c -o Stack.o
	
.PHONY:clean
clean:
	rm $(OBJS) calculator

