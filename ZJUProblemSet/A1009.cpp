#include <cstdio>
struct item{
    int exp;
    double co;
};
int main() {
    int m,n,count=0;
    scanf("%d",&m);
    struct item a[m];
    for(int i=0; i<m; i++) {
        scanf("%d%lf",&a[i].exp,&a[i].co);
    }
    scanf("%d",&n);
    struct item b[n];
    for(int i=0; i<n; i++) {
        scanf("%d%lf",&b[i].exp,&b[i].co);
    }
    double res[2001]={0};
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++) 
            res[a[i].exp+b[j].exp]+=a[i].co*b[j].co;
    for(int i=0; i<2001; i++)
        if(res[i]!=0)
            count++;
    printf("%d",count);
    for(int i=2000; i>=0; i--)
        if(res[i]!=0)
            printf(" %d %.1f",i,res[i]);
}