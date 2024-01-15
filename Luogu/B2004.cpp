#include<iostream>
#include<iomanip>

/*
Intro about iomanip

a file to manipulate output formatting. 
e.g. the base used when formatting integers and precision of floating point values

std::setw(int n): sets the field width for the next insertion operation.
std::setprecision(int n): set the decimal precision to be used to format fp values
std::setfill(char c): fills the unused spaces of the field width with character c
std::fixed: use fp notation
std::showpos: force the output of the + sign for positive numbers
std::noshowops: self-explanatory
*/

int main(){
    int a, b, c;
    std::cin>>a>>b>>c;
    std::cout<<std::setw(8)<<a<<" "<<std::setw(8)<<b<<" "<<std::setw(8)<<c<<std::endl; // when the output exceeds the parameter, no effect; otherwise the output gets preceeded by blank space
}