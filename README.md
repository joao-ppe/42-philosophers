<div align="center">
  <h1>42 PHILOSOPHERS</h1>
</div>
<p align="center">
	<a href="#about">About</a> •
	<a href="#how-to-use">How to use</a> •
	<a href="#examples">Examples</a> •
	<a href="/en.subject.pdf">Subject</a> •
	<a href="#norminette">Norminette</a>
</p>

## ABOUT ([Subject](/en.subject.pdf))

The project involves creating a C program to simulate a scenario with philosophers seated at a round table. These philosophers alternate between eating, thinking, and sleeping. To eat, they require two forks. If a philosopher doesn't start eating within a specified time, they will starve to death. The program takes various command-line arguments, including the number of philosophers, time limits for actions, and an optional limit on how many times each philosopher must eat. Philosophers cannot communicate with eachother, and global variables are not allowed. The program must log philosopher activities with timestamps and handle the simulation's termination conditions.

**Logging Requirements:**
- The program must log the state changes of each philosopher, including taking a fork, eating, sleeping, and thinking.
- Log entries must include a timestamp in milliseconds and the philosopher number.
- Messages about a philosopher's death should be displayed no more than 10 ms after the actual death.

**Implementation Rules:**
- The program should be implemented without global variables.
- A philosopher dies if they don't eat within a specified time.
- The simulation stops when a philosopher dies or when all philosophers have eaten a specified number of times.

In summary, this project involves creating a C program that simulates philosophers dining at a table while following specific rules and logging their actions and potential deaths.

<a href="/.github/en.subject.pdf">Click here</a> for the subject of this project.

<br>

## HOW TO USE
#### COMPILATION AND EXECUTION
#### 1º - Clone the repository
```bash
$ ./git clone git@github.com:joao-ppe/42-philosophers.git
```

#### 2º - Enter the project folder and run `make`
```bash
$ ./cd 42-Philosophers
$ ./make
```

#### 3º - Launch the program
> The last argument is optional for the execution of the program.
```bash
$ ./philo [n of philos] [time to die] [time to eat] [time to sleep] [n times each philo must eat]
```

<br>

#### MAKEFILE COMMANDS
`make` or `make all` - Compile program **mandatory** files.

`make clean` - Delete all .o (object files) files.

`make fclean` - Delete all .o (object file) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

#### TIPS
> Replace the "CFLAGS" in the Makefile file to use fsanitize to track data races and mutex errors:
```bash
CFLAGS = -Wall -Wextra -Werror
```
```bash
CFLAGS = -g -Wall -Wextra -Werror -L. -lpthread -g3 -fsanitize=thread -O3 -march=native
```

<br>

## EXAMPLES
 > The performance will change if you use `-fsanitize`, `valgrind` or both together.
 
| Example | Expected Result |
| :-- | :-- |
| `./philo 4 500 200 1.2`           | Invalid argument.                                              |
| `./philo 4 0 200 200`             | Invalid argument.                                              |
| `./philo 4 -500 200 200`          | Invalid argument.                                              |
| `./philo 4 214748364732 200 200`  | Invalid argument.                                              |
| `./philo 1 200 200 200`           | Philosopher 1 takes a fork and dies after 200 ms.              |
| `./philo 4 500 200 2147483647`    | A philosopher dies after 500 ms                                |
| `./philo 4 200 210 200`           | A philosopher dies, it should display the death before 210 ms. |
| `./philo 4 310 200 200`           | A philosopher dies.                                            |
| `./philo 5 800 200 200 7`         | The program stops when each philosopher has eaten 7 times.     |
| `./philo 5 800 200 200`           | No philosopher dies.                                           |
| `./philo 4 2147483647 200 200`    | No philosopher dies.                                           |
| `./philo 5 800 200 150`           | No philosopher dies.                                           |
| `./philo 3 610 200 80`            | No philosopher dies.                                           |
| `./philo 2 800 200 200`           | No philosopher dies.                                           |
| `./philo 4 410 200 200`           | No philosopher dies.                                           |
 > Examples provided by [jotavare](https://github.com/jotavare)

<br>

## NORMINETTE
At 42 School, projects are generally expected to adhere to the Norm, the school's coding standard:

```
- No for, do while, switch, case or goto are allowed
- No more than 25 lines per function and 5 functions per file
- No assigns and declarations in the same line (unless static)
- No more than 5 variables in 1 function
... 
```
