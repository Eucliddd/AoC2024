#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
array<array<int, 2>, 4> dir = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
vector<pair<int, int>> paths;
int start_x, start_y;

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();
}

bool looped(int xx, int yy){
    int n = grid.size();
    int m = grid[0].size();
    int x = start_x, y = start_y;
    int d = 0;
    
    set<pair<pair<int, int>, int>> visited;
    while(x >= 0 && x < n && y >= 0 && y < m){
        if (visited.find({{x, y}, d}) != visited.end()){
            return true;
        }
        visited.insert({{x, y}, d});
        int new_x = x + dir[d][0];
        int new_y = y + dir[d][1];
        if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m){
            return false;
        }
        if (grid[new_x][new_y] == '#' || grid[new_x][new_y] == 'O'){
            d = (d + 1) % 4;
        }
        else{
            x = new_x;
            y = new_y;
        }
    }
    return false;
}


int solve(){
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (grid[i][j] == '^'){
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    int x = start_x, y = start_y;
    auto _grid = grid;

    int d = 0;
    while(x >= 0 && x < n && y >= 0 && y < m){
        if (_grid[x][y] == '.' || _grid[x][y] == '^'){
            paths.emplace_back(x, y);
        }
        _grid[x][y] = 'X';
        x += dir[d][0];
        y += dir[d][1];
        if (x < 0 || x >= n || y < 0 || y >= m){
            break;
        }
        if (_grid[x][y] == '#'){
            x -= dir[d][0];
            y -= dir[d][1];
            d = (d + 1) % 4;
            x += dir[d][0];
            y += dir[d][1];
        }
    }

    int cnt = 0;
    for (auto [xx, yy] : paths){
        if (xx == start_x && yy == start_y){
            continue;
        }
        grid[xx][yy] = 'O';
        cnt += looped(xx, yy);
        //cout << "Path: " << xx << "," << yy << ": " << cnt << endl;
        grid[xx][yy] = '.';
    }
    return cnt;
}

int main(){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}