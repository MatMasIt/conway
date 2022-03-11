/**
 * @file main.c
 * @author MatMasIt
 * @brief The Conway game of life in ANSI C
 * @version 0.1
 * @date 2022-03-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <inttypes.h>
#define bool uint8_t
#define TRUE 1
#define FALSE 0
#define ALIVE TRUE
#define DEAD FALSE
#include "args.c"
#include "conway.c"
#include "display.c"
/**
 * @brief The main function
 *
 * @param argc argument count
 * @param argv arguments pointer
 * @return int program result
 */
int main(int argc, char **argv)
{
    args ar = parseArgs(argc, argv);
    char t;
    bool error;
    Game g = gameFromArgs(ar, &error);
    if (error)
    {
        printf("Initialization error: check arguments\n");
        exit(1);
    }
    uint64_t i = 0;
    if (ar.cells == NULL)
    {
        randomPopulate(&g);
    }
    else
    {
        const char *curLine = ar.cells;
        while (curLine)
        {
            const char *nextLine = strchr(curLine, '.');
            uint64_t x, y;
            int curLineLen = nextLine ? (nextLine - curLine) : strlen(curLine);
            char *tempStr = (char *)malloc(curLineLen + 1);
            if (tempStr)
            {
                memcpy(tempStr, curLine, curLineLen);
                tempStr[curLineLen] = '\0'; // NUL-terminate!
                sscanf(tempStr, "%" PRIu64 ",%" PRIu64 "", &x, &y);
                setCell(&g, x, y, ALIVE);
                free(tempStr);
            }
            else
                printf("Memory allocation error\n");

            curLine = nextLine ? (nextLine + 1) : NULL;
        }
    }
    while (TRUE)
    {
        if (ar.requestedGen != 0)
        {
            if (i == ar.requestedGen)
            {
                printScreen(&g, ar);
                break;
            }
        }
        else
        {
            printScreen(&g, ar);
        }
        if (ar.interactive)
            scanf("%c", &t);
        progress(&g);
        i++;
    }
    return 0;
}
