#include <cstdio>
#include <cstring>
struct resident{
    char name[8];
    char birthday[15];
};
int main() {
    int N,count=0,young_flag=-1,old_flag=-1;
    char youngest[15]="1814/09/05", oldest[15]="2014/09/07";
    scanf("%d",&N);
    struct resident a[N];
    for(int i=0; i<N; i++) {
        scanf("%s%s",a[i].name,a[i].birthday);
        if(strcmp(a[i].birthday,"1814/09/06")>=0&&strcmp(a[i].birthday,"2014/09/06")<=0) {
            count++;
            if(strcmp(a[i].birthday,youngest)>0) {
                young_flag=i;
                strcpy(youngest,a[i].birthday);
            }
            if(strcmp(a[i].birthday,oldest)<0) {
                old_flag=i;
                strcpy(oldest,a[i].birthday);
            }
        }
    }
    if(count==0)
        printf("0");
    else
        printf("%d %s %s",count,a[old_flag].name,a[young_flag].name);
}