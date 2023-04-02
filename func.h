#ifndef _func_h_
#define _func_h_

int scan(int *);

void print(FILE *);

int simkey(FILE *, int);

//void endfile(FILE *);

int add(FILE *, int, char *);

int delete(FILE **, int);

char* find(FILE *, int);

int findkeys(FILE *, int, int);

void myFunc(FILE *, FILE *, int, int);

#endif
