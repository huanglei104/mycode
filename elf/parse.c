#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int fd = -1;

int open_elf(const char *path)
{
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	return fd;
}

int parse_elf_head()
{
	int len;
	Elf32_Ehdr e;

	len = read(fd, &e, sizeof(e));
	if (len == -1) {
		perror("read");
		return -1;
	}

	printf("elf file length is %d\n", len);

	printf("Magic:\n");

	for (int i = 0; i < 16; i++) {
		printf("%x ", e.e_ident[i]);
	}

	printf("\n");

	printf("file type is %d\n", e.e_type);
	printf("machine type is %d\n", e.e_machine);
	printf("version is %d\n", e.e_version);


	return 0;
}

int main(int argc, char *argv[])
{
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	if (parse_elf_head() == -1) {
		printf("parse_elf_head errorr\n");
		return -1;
	}

	return 0;
}
