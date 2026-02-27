#include<stdio.h>
#include<string.h>
int main(){
    int n,m;
    scanf("%d %d",&n, &m);
    int a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }

    int fre[100001] = {0};


    for(int i=0;i<n;i++)
    {
        int val = a[i];
        fre[val]++;
    }
    for(int i=0;i<=m;i++)
    {
        printf("%d -> %d\n",i,fre[i]);
    }
    return 0;
}