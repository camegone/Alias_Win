#ifndef ALI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALI_H
// enums for storing type of quotes
enum quot
{
    none = '\n',
    sing = '\'',
    doub = '"'
};

// show a short help message
void quick_help()
{
    printf("Usage: walias <NAME>=<COMMAND> <ARGS>\n");
    printf("Examples: walias np=notepad.exe\n");
    printf("          walias edge=\"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe\"\n");
    printf("          walias ls=dir /b /d\n");
}

// show quick_help and throw error
void refuse()
{
    printf("!!invalid arguments!!\n");
    quick_help();
    exit(1);
}

// strcpy with calloc. need to be freed
char *strcallocpy(char source[])
{
    char *ret;
    ret = calloc(strlen(source) + 1, sizeof(char));
    strcpy(ret, source);

    return ret;
}

// strcopy only specified range
char *strcallocpyr(char source[], int start_id, int end_id)
{
    int i, j, size;
    char *ret;

    size = (end_id - start_id) + 2;
    ret = calloc(size, sizeof(char));

    j = 0;
    for (i = start_id; i <= end_id; i++)
        ret[j++] = source[i];

    return ret;
}
// strcat with calloc. need to be freed
char *strcallocat(char strto[], char strfrom[])
{
    char *ret;
    ret = calloc(strlen(strto) + strlen(strfrom) + 1, sizeof(char));
    sprintf(ret, "%s%s", strto, strfrom);

    return ret;
}

// do strcallocat, then free specified buffer(0x01 is first one, 0x02 is second one).
char *strcallocat_wf(char strto[], char strfrom[], char bit_mask)
{
    char *ret;
    ret = strcallocat(strto, strfrom);

    if (bit_mask & 0x01)
    {
        free(strto);
    }
    if (bit_mask & 0x02)
    {
        free(strfrom);
    }
    return ret;
}

// returns the path containing aliases created
char *get_alipath()
{
    char *user, *path;
    user = getenv("USERPROFILE");
    path = strcallocat_wf(user, "\\Aliases\\", 1);

    return path;
}

// show list of aliases
void show_list()
{
    char *path, *cmd, *cmd1;
    // show where aliases are
    path = get_alipath();
    printf("Aliases are stored at> %s\n---\n", path);

    // show what inside
    cmd = strcallocat_wf("dir ", path, 2);
    cmd1 = strcallocat_wf(cmd, " /b /d", 1);
    system(cmd1);

    free(cmd1);
}

int make_ali(char name[], char com[])
{
    char *path;
    FILE *fp;
    printf("%s, %s\n", name, com);
    // determine file name
    path = strcallocat_wf(get_alipath(), name, 1);
    path = strcallocat_wf(path, ".cmd", 1);
    printf("try to save in %s\n", path);
    // open file
    fp = fopen(path, "w");
    if (fp == NULL)
        return 1;
    // write file
    fprintf(fp, "@echo off\n\n%s %%*\n", com);

    return fclose(fp);
}

// make a string quoted
char *quote(char str[])
{
    str = strcallocat_wf("\"", str, 2);
    str = strcallocat_wf(str, "\"", 1);

    return str;
}

// check if a string should be quoted (contains spaces)
char should_quoted(char str[])
{
    for (; *str != '\0'; str++)
        if (*str == ' ')
            return 1;

    return 0;
}
#endif
