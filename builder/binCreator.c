#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "codesFile.h"
#include "../lib/binlib.h"
#include <string.h>

char* locLow;
char* locHigh;

int main(int argc, char** argv)
{
    unsigned char binary[2];
    int code;

    FILE* outfile = fopen("codes.bin", "wb");

    for (int codeVecNum = 0; codeVecNum < sizeof(codes) / sizeof(codes[0]); codeVecNum++)
    {
        for (int codeNum = 0; codes[codeVecNum][codeNum] != '\0'; codeNum++)
        {
            code = codes[codeVecNum][codeNum];
            memset(binary, 0, sizeof(binary));
            ByteSplit(code, binary, 2);
            fwrite(binary, 2, 1, outfile);
        }
        fwrite("\0\0", 2, 1, outfile);
    }
    fclose(outfile);
    return 1;
}
