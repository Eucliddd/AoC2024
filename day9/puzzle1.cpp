#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> strip;

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    file >> line;
    for (int i = 0; i < line.size(); i++){
        if (i % 2 == 0){
            for (int j = 0; j < line[i] - '0'; j++)
                strip.push_back(i / 2);
        }
        else{
            for (int j = 0; j < line[i] - '0'; j++)
                strip.push_back(-1);
        }
    }
    file.close();
}

ll solve(){
    int n = strip.size();
    int l = 0, r = n - 1;
    ll ans = 0;
    while (l < r){
        while (l < r && strip[l] != -1) l++;
        while (l < r && strip[r] == -1) r--;
        swap(strip[l], strip[r]);
    }
    for (int i = 0; i < n; i++){
        if (strip[i] != -1){
            ans += (ll) i * (ll) strip[i];
        }
    }
    return ans;
}

int main(){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}