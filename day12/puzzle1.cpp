#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<int>> visited;
int n, m;
array<int, 4> dx = {0, 1, 0, -1};
array<int, 4> dy = {1, 0, -1, 0};

void read_input(const string& file) {
    ifstream in(file);
    string line;
    while (getline(in, line)) {
        grid.push_back(line);
    }
    n = grid.size();
    m = grid[0].size();
    visited = vector<vector<int>>(n, vector<int>(m, 0));
}

pair<int, int> dfs(int x, int y, char c){
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] != c) return {0, 0};
    visited[x][y] = 1;
    int area = 1;
    int perimeter = 0;
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] != c) perimeter++;
        else{
            auto [a, b] = dfs(nx, ny, c);
            area += a;
            perimeter += b;
        }
    }
    return {area, perimeter};
}

int solve(){
    int ans = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (!visited[i][j]){
                auto [area, perimeter] = dfs(i, j, grid[i][j]);
                ans += area * perimeter;
            }
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    read_input("input.txt");
    cout << solve() << endl;
}

