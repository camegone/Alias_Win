#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ali.h"

// making alias
int main(int argc, char **argv)
{
    int i, name_len, com_len, name_end, com_start;
    enum quot q_type;
    char *name, *com;
    // if no arguments, list up aliases
    if (argc == 1)
    {
        show_list();
        printf("---\n");
        quick_help();
        exit(0);
    }

    // count the number of characters before equal sign
    i = 0;
    for (name_len = 0; argv[1][i] != '\0'; ++i)
    {
        // printf("%c\n", argv[1][i]);
        name_len++;
        if (argv[1][i] == '=')
            break;
    }
    // if no equal sign, error
    if (argv[1][i] != '=')
    {
        refuse();
    }
    name_end = i - 1;
    i++;
    // start checking command
    com_start = i;
    q_type = none;
    for (com_len = 0; argv[1][i] != '\0'; i++)
    {
        com_len++;
    }

    name = strcallocpyr(argv[1], 0, name_end);
    com = strcallocpyr(argv[1], com_start, i - 1);
    // if name has spaces, refuse
    if (should_quoted(name))
        refuse();
    // if containing spaces, quote the app name
    if (should_quoted(com))
        com = quote(com);
    // join the arguments
    for (i = 2; i < argc; i++)
    {
        char *buf = strcallocpy(argv[i]);
        if (should_quoted(buf))
            buf = quote(buf);
        com = strcallocat_wf(com, " ", 1);
        com = strcallocat_wf(com, buf, 1);
        free(buf);
    }

    if (make_ali(name, com))
    {
        printf("Error!!\n");
        quick_help();
        exit(1);
    }
    free(name);
    free(com);

    printf("alias created successfully\n");
    return 0;
}
