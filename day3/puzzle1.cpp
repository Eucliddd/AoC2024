#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(string& str){
    ll sum = 0;
    regex re(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch match;
    while (regex_search(str, match, re)) {
        ll a = stoll(match[1]);
        ll b = stoll(match[2]);
        str = match.suffix().str();
        sum += a * b;
    }
    return sum;
}

int main(){
    ifstream fin("input.txt");
    string s((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    cout << solve(s) << endl;
    return 0;
}