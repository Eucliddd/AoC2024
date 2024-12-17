#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> code;

void read_input(string file){
    ifstream in(file);
    string str;
    for (int i = 0; i < 4; i++){
        getline(in, str);
    }
    getline(in, str);
    stringstream ss(str.substr(str.find(':') + 2));
    while(getline(ss, str, ',')){
        code.push_back(stoi(str));
    }
    in.close();
}

ll solve(){
    queue<ll> q;
    q.push(0);
    for (auto it = code.rbegin(); it != code.rend(); ++it){
        int cst = *it;
        int sz = q.size();
        for(int i = 0; i < sz; ++i){
            ll cur = q.front();
            q.pop();
            for (int x = 0; x < 8; ++x){
                ll A = (cur << 3) | x;
                ll B = x ^ 2;
                ll C = A >> B;
                B ^= C;
                B ^= 7;
                if ((B & 7) == cst){
                    q.push(A);
                }
            }
        }
        // res = (res << 3) | cst;
    }
    ll mi = LLONG_MAX;
    while(!q.empty()){
        mi = min(mi, q.front());
        q.pop();
    }
    return mi;
}

int main(int argc, char** argv){
    read_input(argv[1]);
    cout << solve() << endl;
    return 0;
}