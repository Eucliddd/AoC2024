#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int width = 101;
const int height = 103;

struct Robot{
    int x, y;
    int vx, vy;
    Robot(int x, int y, int vx, int vy): x(x), y(y), vx(vx), vy(vy){}
};

vector<Robot> robots;
void read_input(string filename){
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        //cout << line << endl;
        regex pattern(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
        smatch match;
        if (regex_match(line, match, pattern)){
            robots.emplace_back(Robot{stoi(match[1]), stoi(match[2]), stoi(match[3]), stoi(match[4])});
        }
    }
}

inline int warp(int v, int w){
    return (v % w + w) % w;
}

ll solve(int T){
    string filename = "output.txt";
    ofstream file(filename);
    for (int t = 1; t <= T; t++){
        for (Robot &robot: robots){
            robot.x = warp(robot.x + robot.vx, width);
            robot.y = warp(robot.y + robot.vy, height);
        }
        vector<string> grid(height, string(width, '.'));
        for (const Robot &robot : robots){
            grid[robot.y][robot.x] = '#';
        }
        for (const string &row : grid){
            if (row.find("#############") != string::npos){
                for (const string &rrow : grid){
                    file << rrow << endl;
                }
                return t;
            }
        }
    }
    return -1;
}

int main(int argc, char *argv[]){
    read_input("input.txt");
    //cout << robots.size() << endl;
    // for (auto &robot: robots){
    //     cout << robot.x << " " << robot.y << " " << robot.vx << " " << robot.vy << endl;
    // }
    cout << solve(stoi(argv[1])) << endl;
    return 0;
}
