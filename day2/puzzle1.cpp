#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> read_input() {
    vector<vector<int>> input;
    ifstream fin("input.txt");
    string line;
    while (getline(fin, line)) {
        vector<int> row;
        istringstream iss(line);
        int token;
        while (iss >> token) {
            row.push_back(token);
        }
        input.push_back(row);
    }
    return input;
}

bool isSafe(const vector<int>& row){
    if(row.size() < 2) return true;
    if (abs(row[0] - row[1]) < 1 || abs(row[0] - row[1]) > 3) return false;
    bool isAscending = row[0] < row[1];
    for(int i = 1; i < row.size() - 1; i++){
        if (abs(row[i] - row[i+1]) < 1 || abs(row[i] - row[i+1]) > 3) return false;
        if(isAscending){
            if(row[i] > row[i+1]) return false;
        } else {
            if(row[i] < row[i+1]) return false;
        }
    }
    return true;
}

int solve(const vector<vector<int>>& input){
    int count = 0;
    for(auto row : input){
        if(isSafe(row)){
            count++;
        }
    }
    return count;
}

int main(){
    vector<vector<int>>&& input = read_input();
    cout << solve(input) << endl;
    return 0;
}