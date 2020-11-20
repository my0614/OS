#include <stdio.h>
#include <string.h>

void dumpMsg(char *x, int size)
{
    printf("============================\n");
    printf(" 0123456701234567  0123456701234567 \n");
    printf("-------------------------------------------------");
    for(int k =0; k<size; k++, x++)
    {
        if((k)%16==0) printf("\n ");
        printf("%02X", (int)*x);
        if((k+1)%8==0) printf("  ");
    }
    printf("\n============================\n");
}

struct abc
{
    char x_c;
    long x_l;
    int  x_i;
};

int main()
{
    struct abc a;
    memset((char*)&a, 0, sizeof(struct abc));
    a.x_c = 0x01;
    a.x_l = 0x0102030405060708;
    a.x_i = 0x01020304;
    dumpMsg((char*)&a, sizeof(struct abc));
    printf("%ld\n", sizeof(struct abc));
    return 0;
}

