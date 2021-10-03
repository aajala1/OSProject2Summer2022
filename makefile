p0: p0.cpp
	g++ -g p0.cpp -o p0

# Compile p01.cpp
p1: p1.cpp 
	g++ -g p1.cpp -o p1

clean:
	rm p1 p2
