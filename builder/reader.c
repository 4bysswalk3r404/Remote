#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/lib.h"
#include <math.h>
#include "../lib/binlib.h"

unsigned char ToByte(int num)
{
    unsigned char bin = 0;
    for (int k = 8; k > 0; k--)
    {
        bin |= ((num >> k) & 1);
        bin <<= 1;
    }
    if (num % 2 == 1)
        bin++;
    return bin;
}

int main(int argc, char** argv)
{
    FILE* infile = fopen("codes.bin", "rb");

    fseek(infile, 0L, SEEK_END);
    unsigned int bufferSize = ftell(infile);
    rewind(infile);

    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * bufferSize);
    unsigned char* bufferLow = buffer;

    while (!(feof(infile)))
    {
        *buffer = getc(infile);
        buffer++;
    }

    fclose(infile);

    int num = 0;
    buffer = bufferLow;
    unsigned char bin[2];
    for (int i = 0; i < bufferSize; i++)
    {
        if ((*buffer == '\0') && (*(buffer + 1) == '\0')) {
            printf("\n");
            buffer += 2;
        } else {
            bin[0] = *buffer;
            buffer++;
            bin[1] = *buffer;
            buffer++;
            num = ByteJoin(bin, 2);
            printf("%i ", num);
        }
    }

    return 1;
}
