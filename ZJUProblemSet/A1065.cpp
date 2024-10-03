// A+B必须存放到long long型变量中才可与C进行比较，而不可以在if的条件中直接相加与C比较，否则会造成后两组数据错误
// Why?????
#include <cstdio>
int main() {
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++) {
        printf("Case #%d: ",i+1);
        long long a,b,c,res;
        scanf("%lld%lld%lld",&a,&b,&c);
        res=a+b;
        if(a>0&&b>0&&res<0) {
            printf("true\n");
        }
        else if(a<0&&b<0&&res>0) {
            printf("false\n");
        }
        else if(res>c) printf("true\n");
        else printf("false\n");
    }
}