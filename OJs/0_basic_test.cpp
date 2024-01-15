#include<iostream>
#include<limits>

int main(){
    long num1, num2;
    std::cin>>num1>>num2;
    std::cout<<(num1+num2);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}