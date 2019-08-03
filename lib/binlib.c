void ByteSplit(int num, unsigned char* buffer, short size)
{
    unsigned char bin;
    for (short i = size - 1; i >= 0; i--)
    {
        bin = 0;
        for (short j = 8; j > 0; j--)
        {
            bin |= ((num >> j) & 1);
            bin <<= 1;
        }
        if (num % 2 == 1)
            bin++;
        num >>= 8;
        buffer[i] = bin;
    }
}

int ByteJoin(unsigned char* bin, short size)
{
    int num = 0;
    for (int i = 0, j = size - 1; i < size; i++, j--)
        num |= (bin[i] << (8 * j));
    return num;
}
