#include <bits/stdc++.h>
using namespace std;
constexpr int N = 71;
constexpr int M = 71;
constexpr int T = 1024;
array<array<char, M>, N> grid;
array<int, 4> dx = {0, 0, 1, -1};
array<int, 4> dy = {1, -1, 0, 0};
vector<pair<int, int>> bytes;

void read_input(string file){
    ifstream in(file);
    string str;
    for (auto& row: grid) fill(row.begin(), row.end(), '.');
    for (int i = 0; i < T; i++){
        in >> str;
        int x = 0, y = 0;
        sscanf(str.c_str(), "%d,%d", &x, &y);
        //cout << x << " " << y << endl;
        grid[y][x] = '#';
    }
    while(in >> str){
        int x = 0, y = 0;
        sscanf(str.c_str(), "%d,%d", &x, &y);
        bytes.push_back({y, x});
    }
    in.close();
}


bool bfs(){
    //int res = 0;
    bool exit = false;
    queue<pair<int, int>> q;
    q.push({0, 0});
    bitset<N * M> vis(0);
    vis[0] = 1;
    array<array<pair<int, int>, M>, N> parent;
    while(!q.empty()){
        int sz = q.size();
        for (int i = 0; i < sz; i++){
            auto [x, y] = q.front();
            q.pop();
            vis[x * M + y] = 1;
            if (x == N - 1 && y == M - 1){
                exit = true;
                break;
            }
            for (int j = 0; j < 4; j++){
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx < 0 || nx >= N || ny < 0 || ny >= M || grid[nx][ny] == '#' || vis[nx * M + ny]){
                    continue;
                }
                q.push({nx, ny});
                vis[nx * M + ny] = 1;
                parent[nx][ny] = {x, y};
            }
        }
    }
    return exit;
}

string solve(){
    for (auto [x, y]: bytes){
        grid[x][y] = '#';
        if (!bfs()){
            stringstream ss;
            ss << y << "," << x;
            return ss.str();
        }
    }
    return "-1,-1";
}

int main(int argc, char** argv){
    read_input(argv[1]);
    cout << solve() << endl;
    return 0;
}
