compile:  rectangles.o
	g++ rectangles.o -o sfml_rectangles -lsfml-graphics -lsfml-window -lsfml-system

rectangles.o: rectangles.cpp
	g++ -c rectangles.cpp

run: compile
	./sfml_rectangles.exec