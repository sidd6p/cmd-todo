
# cmd Todo

This cmd Todo is very handy in following the task. It allow to add task to pending task list, delete them, mark them as done and also help the completed in a seperate list


## Authors

- [@sidd6p](https://github.com/sidd6p)


## Features

- Add task with priority
- Mark task as done
- View all pending task, highest priority first 
- Delete any task
- Get all available cmd details
- Report of all pending as well as completed task



## Directory stracture

    |--cmd-todo
        |--implementation.cpp
        |--implementation.h
        |--makefile
        |--README.md
        |--task.cpp

## Run Locally

Clone the project

```bash
  git clone https://github.com/sidd6p/cmd-todo.git
```

Go to the project directory

```bash
  cd cmd-todo
```

Install dependencies

```bash
  choco install make
```

build the project

```bash
  make
```


## Demo

#### cmd-todo>task
```cmd
Usage :-
$ ./task add 2 hello world    # Add a new item with priority 2 and text "hello world" to the list
$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order
$ ./task del INDEX            # Delete the incomplete item with the given index
$ ./task done INDEX           # Mark the incomplete item with the given index as complete
$ ./task help                 # Show usage
$ ./task report               # Statistics
```
#### cmd-todo>task help
```cmd
Usage :-
$ ./task add 2 hello world    # Add a new item with priority 2 and text "hello world" to the list
$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order
$ ./task del INDEX            # Delete the incomplete item with the given index
$ ./task done INDEX           # Mark the incomplete item with the given index as complete
$ ./task help                 # Show usage
$ ./task report               # Statistics
```

#### cmd-todo>task add 1 "task with priority 1"
```cmd
Added task: "task with priority 1" priority 1
```

#### cmd-todo>task add 3 "task with priority 3"
```cmd
Added task: "task with priority 3" priority 3
```

#### cmd-todo>task add 0 "task with priority 0"
```cmd
Added task: "task with priority 0" priority 0
```

#### cmd-todo>task ls
```cmd
1. task with priority 0 [0]
2. task with priority 1 [1]
3. task with priority 3 [3]
```

#### cmd-todo>task del 1
```cmd
Deleted item with index 1
```

#### cmd-todo>task done 2
```cmd
Marked item as done.
```

#### cmd-todo>task report
```cmd
Pending : 1
1. task with priority 1 [1]

Completed : 1
1. task with priority 3
```
## Appendix

#### It will create three txt file

    1. task.txt, for storing all pending task
    2. complete.txt, for storing all complete task
    3. meta.txt, for storing the priority of all pending task

