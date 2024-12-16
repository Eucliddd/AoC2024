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
struct Box{
    int x;
    int y1, y2;
    Box(int x, int y1, int y2): x(x), y1(y1), y2(y2){}
};

void read_input(string filename){
    ifstream file(filename);
    string line;
    while(getline(file, line) && !line.empty()){
        string row;
        for(auto c : line){
            if (c == '#' || c == '.'){
                row.push_back(c);
                row.push_back(c);
            }
            else if (c == '@'){
                row.push_back('@');
                start_x = grid.size();
                start_y = row.size() - 1;
                row.push_back('.');
            }
            else if (c == 'O'){
                row.append("[]");
            }
        }
        //cout << row << endl;
        grid.push_back(row);
    }
    //cout << grid[start_x][start_y] << endl;
    //cout << endl;
    n = grid.size();
    m = grid[0].size();
    while(getline(file, line)){
        instructions.append(line);
    }
}

int solve(){
    for(auto inst: instructions){
        auto [dx, dy] = directions[inst];
        //cout << inst << endl;
        if (grid[start_x + dx][start_y + dy] == '.'){
            grid[start_x][start_y] = '.';
            start_x += dx;
            start_y += dy;
            grid[start_x][start_y] = '@';
        }
        else if (grid[start_x + dx][start_y + dy] == '#'){
            continue;
        }
        else if (grid[start_x + dx][start_y + dy] == '[' || grid[start_x + dx][start_y + dy] == ']'){
            int x = start_x + dx, y = start_y + dy;
            if (inst == '>' || inst == '<'){
                for (; grid[x][y] != '#' && grid[x][y] != '.'; x += dx, y += dy);
                if (grid[x][y] == '#') continue;
                for(int i = x, j = y; i != start_x || j != start_y; i -= dx, j -= dy){
                    grid[i][j] = grid[i - dx][j - dy];
                }
                grid[start_x][start_y] = '.';
                start_x += dx, start_y += dy;
            }
            else{
                vector<Box> boxes;
                queue<Box> q;
                if (grid[x][y] == '[') q.push(Box(x, y, y + 1));
                else q.push(Box(x, y - 1, y));
                bool can_move = true;
                // bfs
                while(!q.empty()){
                    auto [x, y1, y2] = q.front();
                    q.pop();
                    boxes.emplace_back(x, y1, y2);
                    if (grid[x + dx][y1] == '#' || grid[x + dx][y2] == '#'){
                        can_move = false;
                        break;
                    }
                    if (grid[x + dx][y1] == '['){
                        q.push(Box(x + dx, y1, y1 + 1));
                    }
                    else if (grid[x + dx][y1] == ']'){
                        q.push(Box(x + dx, y1 - 1, y1));
                    }
                    if (grid[x + dx][y2] == '['){
                        q.push(Box(x + dx, y2, y2 + 1));
                    }
                    else if (grid[x + dx][y2] == ']'){
                        q.push(Box(x + dx, y2 - 1, y2));
                    }
                }
                if (!can_move) continue;
                for(auto it = boxes.rbegin(); it != boxes.rend(); it++){
                    auto [x, y1, y2] = *it;
                    grid[x + dx][y1] = '[';
                    grid[x + dx][y2] = ']';
                    grid[x][y1] = '.';
                    grid[x][y2] = '.';
                }
                grid[start_x][start_y] = '.';
                start_x += dx;
                start_y += dy;
                grid[start_x][start_y] = '@';
            }
        }
        // for(auto row: grid){
        //     cout << row << endl;
        // }
        // cout << endl;
    }
    int res = 0;
    for(int i = 0; i < n; i++){
        //cout << grid[i] << endl;
        for(int j = 0; j < m; j++){
            if (grid[i][j] == '['){
                res += 100 * i + j;
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]){
    read_input(argv[1]);
    cout << solve() << endl;
    return 0;
}