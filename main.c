#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "dialog.h"

int main(){
//        int SIZE;
//        printf("Size: \n");
//        if (scan(&SIZE)) return 0;
        const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. File", "4. Delete", "5. Show", "6. Task"};
        const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
        int (*fptr[])(FILE **) = {NULL, Dadd, Dfind, Dfile, Ddelete, Dshow, Dtask};
	int msize = 8, incor;
        FILE *iofile;
        iofile = fopen("numbers.bin", "w+b");
        int input, choose, n, rc;
        while(rc = dialog(msgs, NMsgs))
                if(fptr[rc](&iofile))
                        break;
        printf("That's all. Bye!\n");
	fclose(iofile);
        return 0;
}
