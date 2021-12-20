todo_start: task.cpp implementation.cpp implementation.h support.h
	@g++ -c implementation.cpp
	@g++ -o task implementation.o task.cpp
