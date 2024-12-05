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

// bool isTotalOrder(){
//     queue<int> q;
//     for(auto& [u, v] : indegree){
//         if (v == 0){
//             q.push(u);
//         }
//     }
//     int cnt = 0;
//     while(!q.empty()){
//         if (q.size() > 1){
//             return false;
//         }
//         int u = q.front();
//         q.pop();
//         cnt++;
//         cout << u << " ";
//         for(auto& v : adj[u]){
//             indegree[v]--;
//             if (indegree[v] == 0){
//                 q.push(v);
//             }
//         }
//     }
//     cout << endl;
//     return cnt == indegree.size();
// }

// check cycle
// bool dfs(int node, unordered_map<int, int>& visited) {
//     if (visited[node] == 1) {
//         return true;
//     }
//     if (visited[node] == 2) {
//         return false;
//     }

//     visited[node] = 1;
//     for (int neighbor : adj[node]) {
//         if (dfs(neighbor, visited)) {
//             return true;
//         }
//     }
//     visited[node] = 2;
//     return false;
// }

int solve(){
    int res = 0;
    for(auto& update : updates){
        if (isValidUpdate(update)){
            res += update[update.size() / 2];
            // for (auto x : update){
            //     cout << x << ",";
            // }
            // cout << endl;
        }
    }
    return res;
}

int main(){
    read_input("input.txt");
    // unordered_map<int, int> visited;
    // for (auto& [u, cnt] : indegree){
    //     visited[u] = 0;
    // }
    // for (auto& [u, v] : adj){
    //     if (dfs(u, visited)){
    //         cout << "Cycle detected!" << endl;
    //         return 0;
    //     }
    // }
    // for (auto& [u, v] : indegree){
    //     cout << u << ":" << v << endl;
    // }
    // cout << indegree.size() << endl;
    // cout << adj.size() << endl;
    // cout << isTotalOrder() << endl;
    cout << solve() << endl;
    return 0;
}