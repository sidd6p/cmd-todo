todo_start: main.cpp implementation.cpp implementation.h
	@g++ -c implementation.cpp
	@g++ -o task implementation.o main.cpp
