#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int width = 101;
const int height = 103;
const int T = 100;

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

ll solve(){
    for (Robot &robot: robots){
        robot.x = warp(robot.x + robot.vx * T, width);
        robot.y = warp(robot.y + robot.vy * T, height);
    }
    ll q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (const Robot &robot : robots) {
        if (robot.x == width / 2 || robot.y == height / 2) {
            continue;
        }
        if (robot.x > width / 2 && robot.y < height / 2) q1++;
        else if (robot.x < width / 2 && robot.y < height / 2) q2++;
        else if (robot.x < width / 2 && robot.y > height / 2) q3++;
        else if (robot.x > width / 2 && robot.y > height / 2) q4++;
    }
    return q1 * q2 * q3 * q4;
}

int main(){
    read_input("input.txt");
    //cout << robots.size() << endl;
    // for (auto &robot: robots){
    //     cout << robot.x << " " << robot.y << " " << robot.vx << " " << robot.vy << endl;
    // }
    cout << solve() << endl;
    return 0;
}
