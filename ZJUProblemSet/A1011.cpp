#include <cstdio>
int max_of_3(double a,double b,double c) {
    if(a>=b)    return (a>=c)?0:2;
    else    return (b>=c)?1:2;
}
int main() {
    double odd[3],res=1;
    for(int i=0; i<3; i++) {
        scanf("%lf%lf%lf",&odd[0],&odd[1],&odd[2]);
        int flag=max_of_3(odd[0],odd[1],odd[2]);
        if(flag==0) printf("W ");
        else if(flag==1) printf("T ");
        else printf("L ");
        res*=odd[flag];
    }
    printf("%.2f",(res*0.65-1)*2);
}