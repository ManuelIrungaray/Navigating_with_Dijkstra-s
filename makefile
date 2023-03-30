build:
	rm -f program
	g++ -O2 -std=c++11 -Wall main.cpp distance.cpp osm.cpp tinyxml2.cpp -o program

run:
	./program

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program
