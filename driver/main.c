#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "codesFile.h"

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
        fprintf(stderr, *buffer);
        buffer++;
        nanosleep(carrier, tim);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    struct timespec carrierVec[7];
    struct timespec tim;

    for (int i = 0; i < 7; i++)
        carrierVec[i].tv_sec = 0;

    carrierVec[0].tv_nsec = 33333;
    carrierVec[1].tv_nsec = 30303;
    carrierVec[2].tv_nsec = 27777;
    carrierVec[3].tv_nsec = 27247;
    carrierVec[4].tv_nsec = 26315;
    carrierVec[5].tv_nsec = 25000;
    carrierVec[6].tv_nsec = 17857;

    int code;
    char* buffer = (char*)malloc(sizeof(char) * 18);
    locLow = buffer;
    for (int i = 0; i < 16; i++)
        buffer++;
    locHigh = buffer;
    buffer = locLow;

    while (1)
    {
        for (int carrierNum = 0; carrierNum <= 6; carrierNum++)
        {
            printf("carrier: %li\n", carrierVec[carrierNum].tv_nsec);
            for (int codeVecNum = 0; codeVecNum < sizeof(codes) / sizeof(codes[0]); codeVecNum++)
            {
                for (int codeNum = 0; codes[codeVecNum][codeNum] != '\0'; codeNum++)
                {
                    RunCode(codes[codeVecNum][codeNum], buffer, &carrierVec[carrierNum], &tim);
                }
                printf("\n");
            }
        }
    }
    return 1;
}
