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
	if(!*ul)
		return;
	char **argv = malloc(sizeof(*argv) * (POCDUZ + 1));
	int i, fd;
	for(i = 0; i<POCDUZ; i++)
		argv[i] = NULL;
	int argc = 0, stvduz = POCDUZ;
	argv[argc] = NULL;
	char *prg;

	char *tok = strtok(ul, delm);
	if((tok[0] == '.') && (tok[1] == '/')) {
		prg = strdup(tok);
		dbgprint((1, "prg(./): %s\n", prg));
	} else {
		prg = malloc(sizeof(*prg) * (strlen(put) + strlen(tok) + 1));
		*prg = 0;
		strcpy(prg, put);
		strcat(prg, tok);
		dbgprint((1, "prg: %s\n", prg));
	}
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

			dbgprint((1, "%s\n", tok));
			tok = strtok(NULL, delm);
		}

		if(!**argv)
			goto kraj;

		if(fork() == 0)
			exec(prg, argv);
		else
			nwait();
	} else {
		if((tok[0] == 'c') && (tok[1] == 'd') && (tok[2] == 0)) {
			tok = strtok(NULL, delm);

			if(chdir(tok) < 0)
				nprintf(2, "cannot cd %s\n", tok);
		} else {
			nprintf(2, "Can't open %s; no such file\n", prg);
		}
	}

	/*================= KRAJ =================*/

kraj:
	for(i = 0; i<argc; i++)
		free(argv[i]);
	free(argv);
	free(prg);
}

int main() {
	for(;;) {
		nprintf(1, "> ");
		//ngets(ul, DUZ);
		if(!fgets(ul, DUZ, stdin))
			break;
		eval(ul, DUZ);
	}
	nexit();
}
