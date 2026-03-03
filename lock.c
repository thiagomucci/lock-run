#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	int fd;

	if(argc != 2)
	{
		write(STDERR_FILENO ,"try: ./prog <file>", sizeof("try: ./prog <file>") -1);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR | O_CREAT, 0644)) < 0)
	{
		perror("open");
		exit(1);
	}

	 if (lock_reg(fd, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0) < 0) {
        perror("lock");
        exit(1);
    }

	 printf("file locked\n");
	 printf("press enter to unlock file\n");
	 getchar();

	lock_reg(fd, F_SETLK, F_UNLCK, 0, SEEK_SET, 0);

	printf("file unlocked\n");

	close(fd);
	return 0;

}
