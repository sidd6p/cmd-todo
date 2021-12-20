todo_start: task.cpp implementation.cpp implementation.h
	@g++ -c implementation.cpp
	@g++ -o task implementation.o task.cpp
