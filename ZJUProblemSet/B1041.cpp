#include <cstdio>
#include <cstring>
struct student{
    //int test;
    int formal;
    char id[20];
};
int main() {
    int N,M;
    scanf("%d",&N);
    struct student a[N+1];
    for(int i=0; i<N; i++) {
        //scanf("%s %d %d",a[i].id,&a[i].test,&a[i].formal);
        char s[20]; int x,y;
        scanf("%s %d %d",s,&x,&y);
        a[x].formal=y;
        strcpy(a[x].id, s);
    }
    scanf("%d",&M);
    while(M--) {
        int check;
        scanf("%d",&check);
        printf("%s %d\n",a[check].id,a[check].formal);
    }
}