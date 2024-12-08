#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<pair<ll, vector<ll>>> equations;

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<ll> equation;
        ll num = stoll(line.substr(0, line.find(":")));
        line.erase(0, line.find(":") + 2);
        string temp;
        stringstream ss(line);
        while (getline(ss, temp, ' ')){
            equation.push_back(stoll(temp));
        }
        equations.emplace_back(num, equation);
    }
    file.close();
}

bool dfs(const vector<ll>& equation, int idx, ll cur, const ll sum){
    if (idx == equation.size()){
        return cur == sum;
    }
    if (cur > sum){
        return false;
    }
    ll combination = cur;
    ll n = equation[idx];
    while (n > 0){
        combination *= 10;
        n /= 10;
    }
    combination += equation[idx];
    return dfs(equation, idx + 1, cur + equation[idx], sum) || dfs(equation, idx + 1, cur * equation[idx], sum)
        || dfs(equation, idx + 1, combination, sum);
}

ll solve(){
    ll ans = 0;
    for (auto& [num, equation] : equations){
        if (dfs(equation, 1, equation[0], num)){
            ans += num;
        }
    }
    return ans;
}

int main(){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}