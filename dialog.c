#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "func.h"
#include "dialog.h"
#include "toFile.h"

int dialog(const char *msgs[], int N) {
	char *errmsg = "";
        int rc;
        int i, n;
        do{
                puts(errmsg);
                errmsg = "You are wrong. Repeate, please!";
                for(i = 0; i < N; ++i)
                        puts(msgs[i]);
                puts("Make your choice: --> ");
                n = scan(&rc);
                if(n == 1)
                        rc = 0;
        } while(rc < 0 || rc >= N);
        return rc;
}


int Dfile(FILE **iofile){
	char *file = "file.txt";
	FILE *fp;
	int key;
	char *str = NULL;
	OpenRead(file, &fp);
       	while (1){
		if (Read(fp, &key, &str)){
			if (simkey(*iofile, key)){
				free(str);
				continue;
			}
			add(*iofile, key, str);
			free(str);
		} else {
			break;
		}
	}
	fclose(fp);
	return 0;
}

int Dshow(FILE **iofile){
        print(*iofile);
        return 0;
}

int Dadd(FILE **iofile){
        int key, incor;
        printf("Put a key :");
        if (scan(&key)) return 1;
        if (simkey(*iofile, key)){
                printf("Put another key\n");
                if (Dadd(iofile)){
                        return 1;
                }
                return 0;

        }
        char *str = readline("Put an info: ");
        while (str==0){
                return 1;
        }
        add(*iofile, key, str);
	free(str);
        return 0;
}


int Ddelete(FILE **iofile){
        printf("Put key to delete\n");
        int key, ind = -1, n;
        if (scan(&key)) return 1;
        if (delete(iofile, key)){
                printf("There is no such key\n");
        }
        return 0;
}


int Dfind(FILE **iofile){
	char *str;
        printf("Put key to find an elem\n");
        int key;
        if (scan(&key)){
                printf("no elem\n");
                return 1;
        }
	str = find(*iofile, key);
        printf("%s\n", str);
	free(str);
        return 0;
}


int Dtask(FILE **iofile){
        FILE *file;
	file = fopen("mytask.bin", "w+b");
        printf("Put range of keys in format int-int\n");
        int begin, end, size = 0;
        scanf("%d%*c%d", &begin, &end);
        myFunc(*iofile, file, begin, end);
        print(file);
	fclose(file);
        return 0;
}
