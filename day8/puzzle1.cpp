#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

vector<string> grid;
unordered_map<char, vector<Point>> antennas;

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            if (isalpha(grid[i][j]) || isdigit(grid[i][j])){
                antennas[grid[i][j]].emplace_back(i, j);
            }
        }
    }
}

int solve(){
    int ans = 0;
    int n = grid.size();
    int m = grid[0].size();
    //vector<string> temp(n, string(m, '.'));
    for (auto& [c, points] : antennas){
        for (int i = 0; i < points.size() - 1; i++){
            for (int j = i + 1; j < points.size(); j++){
                int x1 = points[i].x;
                int y1 = points[i].y;
                int x2 = points[j].x;
                int y2 = points[j].y;
                int x3 = 2 * x2 - x1;
                int y3 = 2 * y2 - y1;
                if (x3 >= 0 && x3 < n && y3 >= 0 && y3 < m && grid[x3][y3] != '#'){
                    ans++;
                    grid[x3][y3] = '#';
                }
                x3 = 2 * x1 - x2;
                y3 = 2 * y1 - y2;
                if (x3 >= 0 && x3 < n && y3 >= 0 && y3 < m && grid[x3][y3] != '#'){
                    ans++;
                    grid[x3][y3] = '#';
                }
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

