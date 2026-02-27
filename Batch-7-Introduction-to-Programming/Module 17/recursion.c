#include<stdio.h>
void hello()
{
    printf("Hello\n");
    hello();
}
int main()
{
    printf("Hi\n");
    hello();
    return 0;
}