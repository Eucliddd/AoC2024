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
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if (matrix[i][j] == 'X'){
                if (j + 3 < m && matrix[i][j + 1] == 'M' && matrix[i][j + 2] == 'A' && matrix[i][j + 3] == 'S'){
                    res++;
                }
                if (j - 3 >= 0 && matrix[i][j - 1] == 'M' && matrix[i][j - 2] == 'A' && matrix[i][j - 3] == 'S'){
                    res++;
                }
                if (i + 3 < n && matrix[i + 1][j] == 'M' && matrix[i + 2][j] == 'A' && matrix[i + 3][j] == 'S'){
                    res++;
                }
                if (i - 3 >= 0 && matrix[i - 1][j] == 'M' && matrix[i - 2][j] == 'A' && matrix[i - 3][j] == 'S'){
                    res++;
                }
                if (i + 3 < n && j + 3 < m && matrix[i + 1][j + 1] == 'M' && matrix[i + 2][j + 2] == 'A' && matrix[i + 3][j + 3] == 'S'){
                    res++;
                }
                if (i - 3 >= 0 && j - 3 >= 0 && matrix[i - 1][j - 1] == 'M' && matrix[i - 2][j - 2] == 'A' && matrix[i - 3][j - 3] == 'S'){
                    res++;
                }
                if (i + 3 < n && j - 3 >= 0 && matrix[i + 1][j - 1] == 'M' && matrix[i + 2][j - 2] == 'A' && matrix[i + 3][j - 3] == 'S'){
                    res++;
                }
                if (i - 3 >= 0 && j + 3 < m && matrix[i - 1][j + 1] == 'M' && matrix[i - 2][j + 2] == 'A' && matrix[i - 3][j + 3] == 'S'){
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