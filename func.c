#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "func.h"
#include "dialog.h"

int scan(int *elem){
        int n;
        while ((n=scanf("%d", elem))!=1 || (*elem)<0){
                if (n==-1){
                        scanf("%*[^\n]");
                        return 1;
                }
                printf("Sorry, again..\n");
                scanf("%*[^\n]");
        }
        scanf("%*[^\n]");
        return 0;
}


void print(FILE *iofile){
        rewind(iofile);
        int counter, num, len, is;
        char str[80];
        do {
                is = fread(&num, sizeof(int), 1, iofile);
                if (is==0){
                        break;
                }
                printf("key: [%d] ", num);
                fread(&len, sizeof(int), 1, iofile);
                fread(str, 1, len, iofile);
                str[len] = '\0';
                printf("info: [%s]\n", str);
        } while (1);
}


int simkey(FILE *iofile, int key){
	rewind(iofile);
	int len, filekey, is, index = 0;
	do {
		is = fread(&filekey, sizeof(int), 1, iofile);
		index+=1;
		if (is==0)
			break;
		if (filekey==key){
			return index;
		}
		fread(&len, sizeof(int), 1, iofile);
		fseek(iofile, len, SEEK_CUR);
		index+=len+1;
	} while (1);
	return 0;
}

int add(FILE *iofile, int key, char *str){
        fwrite(&key, sizeof(int), 1, iofile);
        unsigned int len = strlen(str);
        fwrite(&len, sizeof(unsigned), 1, iofile);
        fwrite(str, 1, len, iofile);
        return 1;
}


int delete(FILE **iofile, int key){
	rewind(*iofile);
	FILE *file;
	int filekey, is, len;
	file = fopen("func.bin", "w+b");
	char str[80];
	if (file==NULL){
		printf("Error to open file\n");
		return 1;
	}
	do {
		is = fread(&filekey, sizeof(int), 1, (*iofile));
		if (is==0){
			break;
		}
		if (filekey==key){
			fread(&len, sizeof(int), 1, (*iofile));
			fseek((*iofile), len, SEEK_CUR);
			continue;
		}
		fread(&len, sizeof(int), 1, (*iofile));
		fread(str, 1, len, (*iofile));
		str[len] = '\0';
		add(file, filekey, str);
	} while (1);
	if (-1 == remove ("numbers.bin")){
		printf ("Error remove\n");
	}
	if (-1 == rename ("func.bin","numbers.bin")){
		printf ("Error rename\n");
	}
	(*iofile) = file;
	return 0;
}


char* find(FILE *iofile, int key){
	if (!simkey(iofile, key)){
		char utr[] = "no elem";
		char *urt1 = strdup(utr);
		return urt1;
	}
	int len;
	char str[80];
	char *stri;
	fread(&len, sizeof(int), 1, iofile);
	fread(str, 1, len, iofile);
	str[len] = '\0';
	stri = strdup(str);
	return stri;
}

int findkeys(FILE *iofile, int begin, int end){
	int len, filekey, is;
	do {
		is = fread(&filekey, sizeof(int), 1, iofile);
		if (is==0)
			break;
		if (filekey>=begin && filekey<=end){
			return filekey;
		}
		fread(&len, sizeof(int), 1, iofile);
		fseek(iofile, len, SEEK_CUR);
	} while (1);
	return 0;
}


void myFunc(FILE *iofile, FILE *file, int begin, int end){
	rewind(iofile);
	int len, filekey;
	char str[80];
	do {
		filekey = findkeys(iofile, begin, end);
		if (filekey==0)
			break;
		fread(&len, sizeof(int), 1, iofile);
		fread(str, 1, len, iofile);
		str[len] = '\0';
		add(file, filekey, str);
	} while (1);
	return;
}






