#include <cstdio>
#include <climits>
struct stuff {
    char id[20];
    int SigninTime;
    int SignoutTime;
};
int main() {
    int n,min=INT_MAX,max=-1;
    int min_flag=-1,max_flag=-1;
    scanf("%d",&n);
    struct stuff a[n];
    for(int i=0; i<n; i++) {
        int h1,m1,s1,h2,m2,s2;
        scanf("%s %d:%d:%d %d:%d:%d",a[i].id,&h1,&m1,&s1,&h2,&m2,&s2);
        a[i].SigninTime=h1*3600+m1*60+s1;
        a[i].SignoutTime=h2*3600+m2*60+s2;
        if(a[i].SigninTime<min) {
            min_flag=i;
            min=a[i].SigninTime;
        }
        if(a[i].SignoutTime>max) {
            max_flag=i;
            max=a[i].SignoutTime;
        }
    }
    printf("%s %s",a[min_flag].id,a[max_flag].id);
}