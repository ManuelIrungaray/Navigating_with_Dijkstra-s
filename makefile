build:
	rm -f program
	g++ -O2 -std=c++11 -Wall main.cpp disancet.cpp osm.cpp tinyxml2.cpp -o program

run:
	./program

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program
