#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAXBUF 4096

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}

int
main(int argc, char *argv[])
{
	int type;
	ssize_t n;
	off_t offset;
	off_t len;;
	int whence;
	int fd;
	char buf[MAXBUF];

	if(argc != 6)
	{
		write(STDERR_FILENO ,"try: ./prog <file> <r/w> <offset> <set|cur|end> <len>", sizeof("try: ./prog <file> <r/w> <offset> <set|cur|end> <len>") -1);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) < 0)
	{
		perror("open");
		exit(1);
	}
	
	if (argv[2][0] == 'w')
	{
    type = F_WRLCK;
	}

	else if (argv[2][0] == 'r')
	{
    type = F_RDLCK;
	}
	
	else
	{
		perror("try: 'r' or 'w'");
		exit(1);
	}

	offset = strtoll(argv[3], NULL, 10);
	len = strtoll(argv[5], NULL, 10);

	if(strcmp(argv[4], "set") == 0)
	{
		whence = SEEK_SET;
	}
	else if(strcmp(argv[4], "cur") == 0)
	{
		whence = SEEK_CUR;
	}
	else if(strcmp(argv[4], "end") == 0)
	{
		whence = SEEK_END;
	}
	else{
		write(STDERR_FILENO,
				"whence: <set> || <cur> || <end>\n",
					sizeof("whence: <set> || <cur> || <end>\n") -1);
		exit(1);
	}

	if (lseek(fd, offset, whence) < 0) 
	{
    perror("lseek");
    exit(1);
	}

	 if((lock_reg(fd, F_SETLKW, type, offset, whence, len)) < 0) {
        perror("lock");
        exit(1);
    }

	printf("PID %d locked\n", getpid());

	 
	n = read(STDIN_FILENO, buf, MAXBUF);
	if (n < 0) 
	{
    perror("read");
    exit(1);
	}

	if (write(fd, buf, n) != n) 
	{
    perror("write");
    exit(1);
	}

	 printf("press enter to unlock file\n");
	 read(STDIN_FILENO, buf, 1);

	lock_reg(fd, F_SETLK, F_UNLCK, 0, SEEK_SET, 0);

	printf("file unlocked\n");

	close(fd);
	return 0;

}
