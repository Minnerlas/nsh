#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void nprintf(int fd, const char *fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	vprintf(fmt, arg);
	va_end(arg);
}

void nexit() {
	exit(0);
}

unsigned long strlen(const char *ul) {
	unsigned long i;
	char *t;
	for(i = 0, t = (char*)ul; *ul; ul++, i++);
	return i;
}

static int in(char c, const char *str) {
	char *t;
	for(t = (char *)str; *t; t++)
		if(c == *t)
			return 1;
	return 0;
}

char *strcpy(char *dest, const char *src) {
	char *t1 = dest, *t2 = (char*)src;

	while(*t1++ = *t2++);

	return dest;
}

char *strtok(char *ul, const char *delim) {
	static char *tren = NULL;
	char *t = NULL, *t1 = NULL;

	if((ul == NULL) && (tren == NULL))
		return NULL;

	if(ul)
		tren = ul;
	for(t = t1 = tren; *t; t++)
		if(in(*t, delim))
			break;
	//printf(1, "test: %s, \"%s\"\n", ul, delim);

	while(*t && in(*t, delim))
		*t++ = 0;
	tren = *t ? t : NULL;
	return t1;
}

char *strcat(char *dest, const char *src) {
	strcpy(dest + strlen(dest), src);
	return dest;
}

char *strdup(char *ul) {
	char *t = malloc(sizeof(*t) * (strlen(ul) + 1));
	return strcpy(t, ul);
}

void ngets(char *buf, int duz) {
	fgets(buf, duz, stdin);
}

int exec(const char* path, char *const argv[]) {
	return execve(path, argv, NULL);
}

int nwait() {
	return wait(NULL);
}
