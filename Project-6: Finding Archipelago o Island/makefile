Project6: proj6Base.o island.o fileNodeandList.o archologicy.o;
	g++ -o Project6 proj6Base.o island.o fileNodeandList.o archologicy.o

island.o: island.cpp file.h
	g++ -c island.cpp

Proj6Base.o: proj6Base.cpp file.h
	g++ -c proj6Base.cpp

archologicy.o: archologicy.cpp file.h
	g++ -c archologicy.cpp

fileNodeandList.o: fileNodeandList.cpp file.h
	g++ -c fileNodeandList.cpp

clean:
	rm proj6Base.o island.o archologicy.o fileNodeandList.o Project6