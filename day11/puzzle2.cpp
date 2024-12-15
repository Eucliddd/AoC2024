#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> stones;
map<pair<ll, int>, ll> memo;
//constexpr int k = 25;

void read_input(const string& file) {
    ifstream in(file);
    ll stone;
    while (in >> stone) {
        stones.push_back(stone);
    }
}

int digits_len(ll n){
    int len = 0;
    while (n) {
        len++;
        n /= 10;
    }
    return len;
}

pair<ll, ll> half_divide(ll n){
    int len = digits_len(n);
    ll half = 1;
    for (int i = 0; i < len/2; i++) {
        half *= 10;
    }
    return {n/half, n%half};
}

ll dfs(ll n, int k){
    if (k == 0) return 1;
    if (memo.find({n, k}) != memo.end()) return memo[{n, k}];
    ll ans = 0;
    if (n == 0) ans = dfs(1, k-1);
    else if(digits_len(n) % 2 == 0){
        auto [left, right] = half_divide(n);
        ans = dfs(left, k-1) + dfs(right, k-1);
    }
    else{
        ans = dfs(n * 2024, k-1);
    }
    return memo[{n, k}] = ans; 
}

ll solve(int k = 25){
    ll ans = 0;
    for (auto stone : stones) {
        ans += dfs(stone, k);
    }
    return ans;
}

int main(int argc, char** argv) {
    read_input("input.txt");
    cout << solve(stoi(argv[1])) << endl;
    return 0;
}
