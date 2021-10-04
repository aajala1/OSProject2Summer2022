p0: p0.cpp
	g++ -g p0.cpp -o p0

# Compile p01.cpp
OBJ =  account.o savings.o checking.o account_thread.o p1.o
p1:  ${OBJ}
	g++  ${OBJ} -lpthread -o p1

account.o: 		account.cpp account.h 
			g++ -c -g account.cpp 

savings.o: 		savings.cpp savings.h 
			g++ -c -g savings.cpp

checking.o: 	checking.cpp checking.h 
			g++ -c -g checking.cpp

account_thread.o: 		account_thread.cpp checking.h savings.h config.h account.h
			g++ -c -g account_thread.cpp

p1.o: 		p1.cpp checking.h savings.h config.h 
			g++ -c -g p1.cpp
			

clean:
	rm *.o p1 p2
