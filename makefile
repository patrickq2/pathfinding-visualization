make:
	g++ -c -g main.cpp 
	g++ -g main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app