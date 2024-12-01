#include <bits/stdc++.h>
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
    unordered_map<ll, ll> mp1, mp2;
    for(ll i = 0; i < x.size(); i++){
        mp1[x[i]]++;
        mp2[y[i]]++;
    }
    ll res = 0;
    for (auto [key, value] : mp1){
        if(mp2.find(key) != mp2.end()){
            res += key * value * mp2[key];
        }
    }
    return res;
}

int main()
{
    auto [x, y] = read_input();
    cout << solve(x, y) << endl;
    return 0;
}