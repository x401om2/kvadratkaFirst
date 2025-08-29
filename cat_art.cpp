#include <stdio.h>
#include "cat_art.h"




void poltoraIIIka(const char *name) {
    printf(" ");
    printf(" \n");
    printf(BLUE "       ....／＞　 フ.....\n" RESET);
    printf(BLUE "　　　　　| 　_　 _|\n" RESET);
    printf(BLUE "　 　　　／`ミ _* 彡 -- %s!!\n" RESET ,name);
    printf(BLUE "　　 　 /　　　 　 |\n" RESET);
    printf(GREEN "　　　 /　 ヽ　　 ﾉ\n" RESET);
    printf(GREEN "　／￣|　　 |　|　|\n" RESET);
    printf(YELLOW "　| (￣ヽ＿_ヽ_)_)\n" RESET);
    printf(YELLOW "　＼二つ\n" RESET);
    printf(" \n");
    printf(" ");
    sleep(2);
}
