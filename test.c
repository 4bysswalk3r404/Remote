#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "codes.h"
#include "../lib/lib.h"
#include <windows.h>

char* locLow;
char* locHigh;

void RunCode(int num, char* buffer, struct timespec* carrier, struct timespec* tim)
{
    buffer = locHigh;
    *buffer = '\0';
    for (int k = 0; k < 16; k++)
    {
        buffer--;
        *buffer = ((num >> k) & 1) + '0';
    }
    buffer = locLow;
    for (int k = 0; k < 16; k++)
    {
        printf("%c", *buffer);
        buffer++;
        nanosleep(carrier, tim);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    int code;
    char* buffer = (char*)malloc(sizeof(char) * 18);
    locLow = buffer;
    for (int i = 0; i < 16; i++)
        buffer++;
    locHigh = buffer;
    buffer = locLow;

    struct timespec carrier;
    struct timespec tim;

    carrier.tv_sec  = 0;
    carrier.tv_nsec = atoi(argv[1]);

    for (int i = 0; i < sizeof(codes) / sizeof(codes[0]); i++)
    {
        for (int j = 0; codes[i][j] != '\0'; j++)
        {
            RunCode(codes[i][j], buffer, &carrier, &tim);
        }
        printf("\n");
    }
    return 1;
}
