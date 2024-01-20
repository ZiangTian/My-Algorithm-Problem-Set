#include <cstdio>
int main() {
    int n,a[55],b[55],c[55]={0};
    for(int i=0; i<55; i++) {
        a[i]=i;
        b[i]=i;
    }
    scanf("%d",&n);
    for(int i=0; i<54; i++) {
        scanf("%d",&c[i+1]);
    }
    for(int i=1; i<=n; i++) {
        if(i%2==1) {
            for(int j=1; j<=54; j++)
                a[c[j]]=b[j];
        }
        else {
            for(int j=1; j<=54; j++)
                b[c[j]]=a[j];
        }
    }
    if(n%2==0) {
        for(int i=1; i<=54; i++) {
            //printf("%d ",b[i]);
            if(b[i]>=1&&b[i]<=13) printf("S%d",b[i]);
            if(b[i]>=14&&b[i]<=26) printf("H%d",b[i]-13);
            if(b[i]>=27&&b[i]<=39) printf("C%d",b[i]-26);
            if(b[i]>=40&&b[i]<=52) printf("D%d",b[i]-39);
            if(b[i]==53) printf("J1");
            if(b[i]==54) printf("J2");
            if(i!=54) printf(" ");
        }
    }
    else {
        for(int i=1; i<=54; i++) {
            if(a[i]>=1&&a[i]<=13) printf("S%d",a[i]);
            if(a[i]>=14&&a[i]<=26) printf("H%d",a[i]-13);
            if(a[i]>=27&&a[i]<=39) printf("C%d",a[i]-26);
            if(a[i]>=40&&a[i]<=52) printf("D%d",a[i]-39);
            if(a[i]==53) printf("J1");
            if(a[i]==54) printf("J2");
            if(i!=54) printf(" ");
        }
    }
}