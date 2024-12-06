#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
array<array<int, 2>, 4> dir = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();
}

int solve(){
    int n = grid.size();
    int m = grid[0].size();
    int x, y;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (grid[i][j] == '^'){
                x = i;
                y = j;
                break;
            }
        }
    }

    int d = 0, cnt = 0;
    while(x >= 0 && x < n && y >= 0 && y < m){
        if (grid[x][y] == '.' || grid[x][y] == '^'){
            cnt++;
        }
        grid[x][y] = 'X';
        x += dir[d][0];
        y += dir[d][1];
        if (x < 0 || x >= n || y < 0 || y >= m){
            break;
        }
        if (grid[x][y] == '#'){
            x -= dir[d][0];
            y -= dir[d][1];
            d = (d + 1) % 4;
            x += dir[d][0];
            y += dir[d][1];
        }
    }
    return cnt;
}

int main(){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}