#include <stdio.h>

struct abc
{
        char x_c;
};

struct abc2
{
        char x_c;
        long x_1;

};

struct abc3
{
        char x_c;
        long x_1;
        int x_i;

};

int main()
{
        printf("%d\n",sizeof(struct abc));
        printf("%d\n", sizeof(struct abc2));
        printf("%d\n", sizeof(struct abc3));

}
