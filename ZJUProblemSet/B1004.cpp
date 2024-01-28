#include <cstdio>
#include <cstring>
struct stu{
    char name[15];
    char id[15];
    int grade;
};
int main() {
    int n,min=101,max=-1,min_flag=-1,max_flag=-1;
    scanf("%d",&n);
    struct stu a[n];
    for(int i=0; i<n; i++) {
        scanf("%s%s%d",a[i].name,a[i].id,&a[i].grade);
        if(a[i].grade>max) {
            max=a[i].grade;
            max_flag=i;
        }
        if(a[i].grade<min) {
            min=a[i].grade;
            min_flag=i;
        }
    }
    printf("%s %s\n%s %s\n",a[max_flag].name,a[max_flag].id,a[min_flag].name,a[min_flag].id);
}