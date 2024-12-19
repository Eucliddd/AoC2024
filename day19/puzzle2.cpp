#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class trie{
public:
    trie* child[26];
    bool isEnd;
    trie(){
        isEnd = false;
        memset(child, 0, sizeof(child));
    }
    void insert(string s){
        trie* node = this;
        for (char c: s){
            if (!node->child[c - 'a']){
                node->child[c - 'a'] = new trie();
            }
            node = node->child[c - 'a'];
        }
        node->isEnd = true;
    }
};
trie* root;
vector<string> designs;

vector<string> split(string s, string delimeter){
    vector<string> res;
    size_t pos = 0;
    while((pos = s.find(delimeter)) != string::npos){
        res.push_back(s.substr(0, pos));
        s.erase(0, pos + delimeter.length());
    }
    res.push_back(s);
    return res;
}

void read_input(string file){
    ifstream in(file);
    string str;
    root = new trie();
    getline(in, str);
    for(const string& towel: split(str, ", ")){
        //cout << towel << endl;
        root->insert(towel);
    }
    getline(in, str);
    while(getline(in, str)){
        designs.push_back(str);
    }
    in.close();
}

ll combination_count(const string& design){
    vector<ll> dp(design.size() + 1, 0);
    dp[design.size()] = 1;
    for(int i = design.size() - 1; i >= 0; i--){
        trie* node = root;
        for (int j = i; j < design.size(); ++j){
            if (node->child[design[j] - 'a'] == nullptr)
                break;
            node = node->child[design[j] - 'a'];
            if (node->isEnd){
                dp[i] += dp[j + 1];
            }
        }
    }
    return dp[0];
}

ll solve(){
    ll res = 0;
    for (const string& design: designs){
        ll cnt = combination_count(design);
        //cout << design << " " << cnt << endl;
        res += cnt;
    }
    return res;
}

int main(int argc, char** argv){
    read_input(argv[1]);
    cout << solve() << endl;
    return 0;
}
