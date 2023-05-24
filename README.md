# Simple Shell

## Description :pen:

A simple UNIX command interpreter written as part of the low-level programming and algorithm track at [ALX Software engineering program] (https://www.alxafrica.com/software-engineering-cert/).In this project we are tasked with creating our own simple UNIX command interpreter. The program must have the exact same output as sh (/bin/sh) as well as the exact same error output. The only difference is when you print an error, the name of the program must be equivalent to your fnargv[0].

## General Requirements

* Allowed editors:``` vi```, ```vim```, ```emacs```
* All your files will be compiled on```Ubuntu 20.04 LTS``` using ```gcc```, using the options ```-Wall -Werror -Wextra -pedantic -std=gnu89```
* All your files should end with a new line
* A ```README.md``` file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using ```betty-style.pl``` and ```betty-doc.pl```
* Your shell should not have any memory leaks
* No more than ```5``` functions per file
* All your header files should be include guarded
* Use system calls only when you need to (why?)

### List of allowed functions and system calls

   - ```access``` (man 2 access)
   - ```chdir``` (man 2 chdir)
   - ```close``` (man 2 close)
   - ```closedir``` (man 3 closedir)
   - ```execve``` (man 2 execve)
   - ```exit``` (man 3 exit)
   - ```_exit``` (man 2 _exit)
   - ```fflush``` (man 3 fflush)
   - ```fork``` (man 2 fork)
   - ```free``` (man 3 free)
   - ```getcwd``` (man 3 getcwd)
   - ```getline``` (man 3 getline)
   - ```getpid``` (man 2 getpid)
   - ```isatty``` (man 3 isatty)
   - ```kill``` (man 2 kill)
   - ```malloc``` (man 3 malloc)
   - ```open``` (man 2 open)
   - ```opendir``` (man 3 opendir)
   - ```perror``` (man 3 perror)
   - ```read``` (man 2 read)
   - ```readdir``` (man 3 readdir)
   - ```signal``` (man 2 signal)
   - ```stat``` (__xstat) (man 2 stat)
   - ```lstat``` (__lxstat) (man 2 lstat)
   - ```fstat``` (__fxstat) (man 2 fstat)
   - ```strtok``` (man 3 strtok)
   - ```wait``` (man 2 wait)
   - ```waitpid``` (man 2 waitpid)
   - ```wait3``` (man 2 wait3)
   - ```wait4``` (man 2 wait4)
   - ```write``` (man 2 write)

## Compilation

```gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh```

### How to use it
#### In order to use this shell, in a terminal, first run the program:
``prompt$ ./hsh``
#### It wil then display a simple prompt and wait for commands.
``$``
**List of built-ins**
#### Currently the list of built-ins I wrote is:
- cd [directory]
#### Switch to the specified directory (fnpath).
- fnenv
#### Displays the environment variable
- exit [exitstatus]
#### Exit from the program with exitstatus value. 0 by default.
- getenv NAME
#### Return the value of the NAME variable if it is in the environment
- help [command]
#### Displays the syntax for the command, or all commands.
- fnhistory
#### Displays the last typed user.
- echo [$$] or [$?] or [$PATH] Return pid and exit statue and PATH.
**Command**
Basicly Every Program in $PATH It Support Single Word like ls

- It Handle Path ls /tmp
- it Handle Options Like ls -l
- it Handle All Three Togther Like ls -l /var
- it Handle Command Path Also Like /bin/ls And All The Option And Path Like /bin/ls -l /var
- it Handle Comments #
## Examples Command
**Example 1**
- Username@your-regular-prompt:~$ ./hsh
- $ pwd
/home/username/
- $ ^D
- Username@your-regular-prompt:~$

## Example 2

- Username@your-regular-prompt:~$ ./hsh
- $ ls -l /tmp 
- -rw------- 1 username username    0 Nov  1 12:09 config-err-aAMZrR
- drwx------ 3 root   root   4096 Nov  1 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
- drwx------ 3 root   root   4096 Nov  1 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
- drwx------ 3 root   root   4096 Nov  1 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
- -rw-rw-r-- 1 username username    0 Nov  1 12:09 unity_support_test.0
- $ ^D
``Username@your-regular-prompt:~$``

### For More Info About It Check The Man Page by
```Username@your-regular-prompt:~$ man ./man_1_simple_shell```
