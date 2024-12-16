#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
int start_x, start_y;
int end_x, end_y;
int n, m;
enum direction{
    UP, RIGHT, DOWN, LEFT
};
array<int, 4> dx = {-1, 0, 1, 0};
array<int, 4> dy = {0, 1, 0, -1};
struct point{
    int x, y;
    direction dir;
    point(int x, int y, direction dir): x(x), y(y), dir(dir){}
};
struct cmp{
    bool operator()(const pair<int, point> &a, const pair<int, point> &b){
        return a.first > b.first;
    }
};
void read_input(string filename){
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        grid.push_back(line);
        if (line.find('S') != string::npos){
            start_x = grid.size() - 1;
            start_y = line.find('S');
        }
        if (line.find('E') != string::npos){
            end_x = grid.size() - 1;
            end_y = line.find('E');
        }
    }
    n = grid.size();
    m = grid[0].size();
}

int solve(){
    priority_queue<pair<int, point>, vector<pair<int, point>>, cmp> pq;
    pq.push({0, point(start_x, start_y, RIGHT)});
    vector<vector<vector<int>>> visited(n, vector<vector<int>>(m, vector<int>(4, 0)));
    vector<vector<vector<int>>> dists(n, vector<vector<int>>(m, vector<int>(4, INT_MAX)));
    while(!pq.empty()){
        auto [dist, p] = pq.top();
        pq.pop();
        if (visited[p.x][p.y][p.dir]) continue;
        visited[p.x][p.y][p.dir] = 1;
        dists[p.x][p.y][p.dir] = dist;
        if (p.x == end_x && p.y == end_y){
            return dist;
        }
        for (int i = 0; i < 4; i++){
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (grid[nx][ny] == '#' || visited[nx][ny][i] || (p.dir + 2) % 4 == i) continue;
            // go straight forward
            if (i == p.dir){
                if (dist + 1 < dists[nx][ny][i]){
                    pq.push({dist + 1, point(nx, ny, direction(i))});
                    dists[nx][ny][i] = dist + 1;
                }   
            }
            // turn at same point
            else{
                if (dist + 1000 < dists[p.x][p.y][i]){
                    pq.push({dist + 1000, point(p.x, p.y, direction(i))});
                    dists[p.x][p.y][i] = dist + 1000;
                }
            }
        }
    }
    return -1;
}

int main(int argc, char *argv[]){
    read_input(argv[1]);
    cout << solve() << endl;
    return 0;
}