#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(string& str){
    ll sum = 0;
    // regex mul(R"(mul\((\d{1,3}),(\d{1,3})\))");
    bool isEnabled = true;
    for (size_t i = 0; i < str.size(); ++i){
        if (i + 4 <= str.size() && str.substr(i, 4) == "do()"){
            isEnabled = true;
            i += 3;
        }
        else if (i + 7 <= str.size() && str.substr(i, 7) == "don't()"){
            isEnabled = false;
            i += 6;
        }
        else if (isEnabled && i + 4 <= str.size() && str.substr(i, 4) == "mul("){
            ll a = 0, b = 0;
            size_t j = i + 4;
            bool valid = true;
            while (j < str.size() && isdigit(str[j])){
                a = a * 10 + str[j] - '0';
                j++;
                if (a > 999){
                    valid = false;
                    break;
                }
            }
            if (j == str.size() || str[j] != ','){
                valid = false;
            }
            j++;
            while (j < str.size() && isdigit(str[j])){
                b = b * 10 + str[j] - '0';
                j++;
                if (b > 999){
                    valid = false;
                    break;
                }
            }
            if (j == str.size() || str[j] != ')'){
                valid = false;
            }
            if (valid){
                sum += a * b;
            }
            i = j;
        }
    }
    return sum;
}

int main(){
    ifstream fin("input.txt");
    string s((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    cout << solve(s) << endl;
    return 0;
}