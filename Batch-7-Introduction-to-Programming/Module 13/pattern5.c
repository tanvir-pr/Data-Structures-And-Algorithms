#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int val = 1;
    int space = n-1; 
    for(int i=1;i<=n;i++)   // for printing lines
    {
        for(int j=1;j<=space;j++)     // for printing space
        {
            printf(" ");
        }
        for(int j=1;j<=val;j++)  // for printing value
        {
            printf("* ");
        }
        printf("\n");
        val++;
        space--;
    }
    return 0;
}