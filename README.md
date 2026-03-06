# lockrun
a small Unix-style utility written in C that demonstrates advisory file locking using the fcntl() system call this program allows a process to lock a specific region of a file and interactively write to it while the lock is held the program blocks until the requested lock becomes available and is part of my personal study of the book advanced programming in the unix enviroment (APUE)

# Compilation
gcc -Wall -Wextra -g lock.c -o lock

# Usage
./lock <file> <r|w> <offset> <set|cur|end> <len>

# Arguments:

| Argument | Description                   |
| -------- | ----------------------------- |
| file     | target file                   |
| r / w    | read lock or write lock       |
| offset   | starting byte                 |
| set      | relative to beginning of file |
| cur      | relative to current offset    |
| end      | relative to end of file       |
| len      | number of bytes to lock       |
# references

W. Richard Stevens, Advanced Programming in the UNIX Environment
