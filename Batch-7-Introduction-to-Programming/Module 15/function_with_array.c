#include<stdio.h>

void fun(int a[])
{
    a[2] = 300;
}

int main()
{
    int a[5] = {10,20,30,40,50};
    printf("%d\n",a[2]);
    fun(a);
    printf("%d\n",a[2]);
    return 0;
}