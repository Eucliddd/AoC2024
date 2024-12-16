#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
string instructions;
int start_x, start_y;
int n, m;
unordered_map<char, pair<int, int>> directions = {
    {'^', {-1, 0}},
    {'v', {1, 0}},
    {'<', {0, -1}},
    {'>', {0, 1}}
};

void read_input(string filename){
    ifstream file(filename);
    string line;
    while(getline(file, line) && !line.empty()){
        grid.push_back(line);
        if (line.find('@') != string::npos){
            start_x = grid.size() - 1;
            start_y = line.find('@');
        }
    }
    n = grid.size();
    m = grid[0].size();
    while(getline(file, line)){
        instructions.append(line);
    }
}

int solve(){
    for(auto inst: instructions){
        auto [dx, dy] = directions[inst];
        if (grid[start_x + dx][start_y + dy] == '.'){
            grid[start_x][start_y] = '.';
            start_x += dx;
            start_y += dy;
            grid[start_x][start_y] = '@';
        }
        else if (grid[start_x + dx][start_y + dy] == '#'){
            continue;
        }
        else if (grid[start_x + dx][start_y + dy] == 'O'){
            int x = start_x + dx, y = start_y + dy;
            for (; grid[x][y] != '#' && grid[x][y] != '.'; x += dx, y += dy);
            if (grid[x][y] == '#') continue;
            grid[start_x][start_y] = '.';
            start_x += dx;
            start_y += dy;
            grid[start_x][start_y] = '@';
            grid[x][y] = 'O';
        }
    }
    int res = 0;
    for(int i = 0; i < n; i++){
        //cout << grid[i] << endl;
        for(int j = 0; j < m; j++){
            if (grid[i][j] == 'O'){
                res += 100 * i + j;
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]){
    read_input("input.txt");
    cout << solve() << endl;
    return 0;
}