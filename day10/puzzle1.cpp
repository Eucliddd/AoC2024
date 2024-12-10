#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> topomap;
array<int, 4> dx = {1, -1, 0, 0};
array<int, 4> dy = {0, 0, 1, -1};

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<int> temp;
        for(auto c : line) temp.push_back(c - '0');
        topomap.push_back(temp);
    }
    file.close();
}

int dfs(int x, int y, vector<vector<int>>& visited, int num){
    if (num == 9 && visited[x][y] == 0){
        visited[x][y] = 1;
        return 1;
    }
    int ans = 0;
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < topomap.size() && ny >= 0 && ny < topomap[0].size() && !visited[nx][ny] && topomap[nx][ny] == num + 1){
            ans += dfs(nx, ny, visited, num + 1);
        }
    }
    visited[x][y] = 0;
    return ans;
}

int solve(){
    int n = topomap.size();
    int m = topomap[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (topomap[i][j] == 0){
                vector<vector<int>> visited(n, vector<int>(m, 0));
                int d = dfs(i, j, visited, 0);
                //cout << d << endl;
                ans += d;
            }
        }
    }
    return ans;
}

int main(){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}