#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int first_digit = n%1000;
    printf("%d",first_digit);
    return 0;
}