#include "incl.h"

#define DUZ 200
#define POCDUZ 8
//#define DBG

#ifdef DBG
# define dbgprint(x) nprintf x
#else
# define dbgprint(x) do {} while (0)
#endif

char ul[DUZ] = {0};
char delm[] = " \n\t";
const char put[] = "/usr/bin/";

void eval(char *ul, int duz) {
	char **argv = malloc(sizeof(*argv) * (POCDUZ + 1));
	int i, fd;
	for(i = 0; i<POCDUZ; i++)
		argv[i] = NULL;
	int argc = 0, stvduz = POCDUZ;
	argv[argc] = NULL;
	char *prg;

	char *tok = strtok(ul, delm);
	prg = malloc(sizeof(*prg) * (strlen(put) + strlen(tok) + 1));
	*prg = 0;
	strcpy(prg, put);
	strcat(prg, tok);
	dbgprint(("prg: %s\n", prg));

	if((fd = open(prg, 0)) >= 0){

		while(tok) {
			argv[argc++] = strdup(tok);
			argv[argc] = NULL;
			if(argc == stvduz) {
				stvduz *= 2;
				char **t = malloc(sizeof(*t) * (stvduz + 1));
				for(i = 0; i<= argc; i++)
					t[i] = argv[i];
				free(argv);
				argv = t;
			}

			dbgprint(("%s\n", tok));
			tok = strtok(NULL, delm);
		}

		if(fork() == 0)
			exec(prg, argv);
		else
			nwait();
	} else {
		nprintf(1, "Can't open %s; no such file\n", prg);
	}

	/*================= KRAJ =================*/

	for(i = 0; i<argc; i++)
		free(argv[i]);
	free(argv);
	free(prg);
}

int main() {
	for(;;) {
		nprintf(1, "> ");
		ngets(ul, DUZ);
		eval(ul, DUZ);
	}
	nexit();
}
