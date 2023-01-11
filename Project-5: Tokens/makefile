Project5: project5main.o myStack.o;
	g++ -o Project5 project5main.o myStack.o
myStack.o: myStack.cpp Infix.h
	g++ -c myStack.cpp
project5main.o: project5main.cpp Infix.h
	g++ -c project5main.cpp
clean:
	rm project5main.o myStack.o Project5