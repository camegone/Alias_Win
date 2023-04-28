#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ali.h"

int main(int argc, char **argv)
{
    char *path;
    int stat;
    if (argc != 2)
    {
        printf("!!invalied arguments!!\nUsage: unwalias <name>");
        exit(1);
    }
    path = strcallocat_wf(get_alipath(), argv[1], 1);
    path = strcallocat_wf(path, ".cmd", 1);

    stat = remove(path);
    if (stat == 0)
        printf("alias %s removed.\n", argv[1]);
    else
        printf("error: %s cannot be removed, may it be wrong name?\n", argv[1]);
    return stat;
}
