#include <bits/stdc++.h>
#include <ranges>
using namespace std;
using ll = long long;
array<vector<ll>, 2> read_input(){
    ifstream file("input.txt");
    string line;
    array<vector<ll>, 2> res;
    while(getline(file, line)){
        ll x, y;
        stringstream ss(line);
        ss >> x >> y;
        res[0].push_back(x);
        res[1].push_back(y);
    }
    return res;
}

ll solve(vector<ll>& x, vector<ll>& y){
    std::ranges::sort(x);
    std::ranges::sort(y);
    ll n = x.size();
    ll res = 0;
    for(ll i = 0; i < n; i++){
        res += abs(x[i] - y[i]);
    }
    return res;
}

int main()
{
    auto [x, y] = read_input();
    cout << solve(x, y) << endl;
    return 0;
}