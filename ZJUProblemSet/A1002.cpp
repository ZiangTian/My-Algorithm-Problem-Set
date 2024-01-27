#include <cstdio>
int main() {
    double a[1001]={0}, b[1001]={0}, c[1001]={0};
    int m,n,count=0;
    scanf("%d",&m);
    for(int i=0; i<m; i++) {
        int exp; double co;
        scanf("%d %lf",&exp,&co);
        a[exp]=co;
    }
    scanf("%d",&n);
    for(int i=0; i<n; i++) {
        int exp; double co;
        scanf("%d %lf",&exp,&co);
        b[exp]=co;
    }
    for(int i=0; i<1001; i++) {
        c[i]=a[i]+b[i];
        if(c[i]!=0)    count++;
    }
    printf("%d",count);
    for(int i=1000; i>=0; i--) {
        if(c[i]!=0) {
            printf(" %d %.1f",i,c[i]);
        }
    }
}