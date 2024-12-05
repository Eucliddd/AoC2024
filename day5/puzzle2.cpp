#include <bits/stdc++.h>
using namespace std;
unordered_map<int, unordered_set<int>> adj;
vector<vector<int>> updates;

void read_input(string filename){
    ifstream fin(filename);
    string s;
    while(getline(fin, s) && s !=""){
        int u, v;
        sscanf(s.c_str(), "%d|%d", &u, &v);
        adj[u].insert(v);
    }
    while(getline(fin, s)){
        stringstream ss(s);
        vector<int> update;
        string token;
        while(getline(ss, token, ',')){
            update.push_back(stoi(token));
        }
        updates.push_back(update);
    }
}

bool isValidUpdate(const vector<int>& update){
    for (int i = 0; i < update.size(); ++i){
        for (int j = i + 1; j < update.size(); ++j){
            if (adj[update[j]].count(update[i])){
                return false;
            }
        }
    }
    return true;
}

int topoSort(const vector<int>& update){
    unordered_map<int, int> indegree;
    unordered_map<int, vector<int>> subgraph;
    unordered_set<int> subset(update.begin(), update.end());
    for (auto& u : update){
        if (indegree.find(u) == indegree.end()){
            indegree[u] = 0;
        }
        for (auto& v : adj[u]){
            if (subset.count(v)){
                subgraph[u].push_back(v);
                indegree[v]++;
            }
        }
    }

    queue<int> q;
    for(auto& [u, v] : indegree){
        if (v == 0){
            q.push(u);
        }
    }
    vector<int> res;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        res.push_back(u);
        for(auto& v : subgraph[u]){
            indegree[v]--;
            if (indegree[v] == 0){
                q.push(v);
            }
        }
    }
    if (res.size() != update.size()){
        return -1;
    }
    return res[res.size() / 2];
}

int solve(){
    int res = 0;
    for(auto& update : updates){
        if (!isValidUpdate(update)){
            res += topoSort(update);            
        }
    }
    return res;
}

int main(){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}