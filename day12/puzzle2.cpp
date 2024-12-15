#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<int>> visited;
int n, m;
// 0: right, 1: down, 2: left, 3: up
array<int, 4> dx = {0, 1, 0, -1};
array<int, 4> dy = {1, 0, -1, 0};
// 0: up-right, 1: right-down, 2: down-left, 3: left-up
array<pair<int, int>, 4> corners = {{{3, 0}, {0, 1}, {1, 2}, {2, 3}}};

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

bool is_valid(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool is_in_region(int x, int y, char c){
    return is_valid(x, y) && grid[x][y] == c;
}

pair<int, int> dfs(int x, int y, char c){
    if (!is_valid(x, y) || visited[x][y] || grid[x][y] != c) return {0, 0};
    visited[x][y] = 1;
    int area = 1;
    int perimeter = 0;
    for (int i = 0; i < 4; i++){
        auto [d1, d2] = corners[i];
        if (!is_in_region(x + dx[d1], y + dy[d1], c) 
            && !is_in_region(x + dx[d2], y + dy[d2], c)) 
            perimeter++;
        if (is_in_region(x + dx[d1], y + dy[d1], c) 
            && is_in_region(x + dx[d2], y + dy[d2], c)
            && !is_in_region(x + dx[d1] + dx[d2], y + dy[d1] + dy[d2], c))
            perimeter++;
    }
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!is_valid(nx, ny) || grid[nx][ny] != c) continue;
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

