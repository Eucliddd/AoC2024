#include <bits/stdc++.h>
using namespace std;
using ll = long long;

list<ll> stones;
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

void print_stones(){
    for (auto stone : stones) {
        cout << stone << " ";
    }
    cout << endl;
}

ll solve(int k = 25){
    for(int i = 0; i < k; i++){
        for (auto it = stones.begin(); it != stones.end(); it++) {
            if (*it == 0) *it = 1;
            else if(digits_len(*it) % 2 == 0){
                auto [left, right] = half_divide(*it);
                *it = right;
                stones.insert(it, left);
            }
            else{
                *it = *it * 2024;
            }
        }
        cout << "Round " << i+1 << ": " << stones.size() << endl;
    }
    return stones.size();
}

int main(int argc, char** argv) {
    read_input("input.txt");
    cout << solve(stoi(argv[1])) << endl;
    return 0;
}
