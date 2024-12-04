#include <bits/stdc++.h>
using namespace std;

vector<string> read_input(){
    ifstream fin("input.txt");
    vector<string> res;
    string s;
    while (getline(fin, s)){
        res.push_back(s);
    }
    return res;
}

int solve(const vector<string>& matrix){
    int n = matrix.size();
    int m = matrix[0].size();
    int res = 0;
    for(int i = 1; i < n - 1; ++i){
        for(int j = 1; j < m - 1; ++j){
            if (matrix[i][j] == 'A'){
                if (((matrix[i - 1][j - 1] == 'M' && matrix[i + 1][j + 1] == 'S') || (matrix[i - 1][j - 1] == 'S' && matrix[i + 1][j + 1] == 'M'))
                    && ((matrix[i - 1][j + 1] == 'M' && matrix[i + 1][j - 1] == 'S') || (matrix[i - 1][j + 1] == 'S' && matrix[i + 1][j - 1] == 'M'))){
                    res++;
                }
            }
        }
    }
    return res;
}

int main(){
    vector<string> matrix = read_input();
    cout << solve(matrix) << endl;
    return 0;
}