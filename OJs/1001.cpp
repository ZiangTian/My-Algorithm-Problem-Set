#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include<cmath>
#include<string.h>

const int LEN = 1000;
int res[LEN] = {0};
std::vector<std::pair<int*, int>> inputs;

/* read inputs from std input */
std::vector<std::pair<float, int>> read()
{
    std::vector<std::pair<float, int>> numbers;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if(line.empty()) break;

        std::stringstream ss(line);
        float f;
        int i;
        if (ss >> f >> i)
        {
            numbers.push_back({f, i});
        }
        
    }
    return numbers;
}

std::vector<int> store(){
    static char s[LEN+1];
    int n = 0;
    int *input = new int[LEN];
    std::vector<int> poses;

    while (std::cin>>s>>n)
    {
        int len = strlen(s);
        int pos = 0;

        for(int i = 0; i < len; i++){
            char ch = s[i];
            if(ch == '.') pos = len - i; // if there is ., len should -1
            else input[len-i-1] = s[i] - '0';
        }
        inputs.push_back({input, n});
        poses.push_back(pos);
    }

}




void high_precision_power(int* r, int n){
    // 0 < r < 100; 0 < n <= 25

    // convert r to int
    double r_d = static_cast<double>(r);
    int dig_after_decimal_pt = 0;

    while(ceil(r_d)!=floor(r_d)){
        dig_after_decimal_pt++;
        r_d *= 10;
    }
    long long r_d = static_cast<long long>(r_d);

    int decimal_point_in_res = dig_after_decimal_pt * n;

    // high-precision int multiplication
    



}

int main()
{   
    store();
    // auto numbers = read();
    // int num_of_lines = numbers.size();

    for (auto input : inputs)
        high_precision_power(input.first, input.second);
    
}
