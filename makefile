# Compile p01.cpp
OBJ = p1.o
OBJ_0 = p0.o

p0: ${OBJ_0} 
	g++ ${OBJ_0} -lpthread -o p0

p1: ${OBJ} 
	g++ ${OBJ} -lpthread -o p1

account_thread.o: account_thread.cpp config.h
	g++ -g account_thread.cpp

p0.o: p0.cpp config.h 
		g++ -c -g p0.cpp

p1.o: p1.cpp config.h 
		g++ -c -g p1.cpp

test: test.o
		g++ -c -g test.o test.cpp

clean:
	rm *.o p1 p0 *.txt

