#include <stdio.h>
#include "cat_art.h"

#include <unistd.h>


void poltoraIIIka(const char *name) {
    printf(" ");
    printf(" \n");
    printf("       ....／＞　 フ.....\n");
    printf("　　　　　| 　_　 _|\n");
    printf("　 　　　／`ミ _* 彡 -- %s!!\n" ,name);
    printf("　　 　 /　　　 　 |\n");
    printf("　　　 /　 ヽ　　 ﾉ\n");
    printf("　／￣|　　 |　|　|\n");
    printf("　| (￣ヽ＿_ヽ_)_)\n");
    printf("　＼二つ\n");
    printf(" \n");
    printf(" ");
    sleep(2);
}
