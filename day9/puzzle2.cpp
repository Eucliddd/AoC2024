#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> strip;
struct fileblock{
    int id;
    int size;
    int idx;
    fileblock(int id, int size, int idx) : id(id), size(size), idx(idx) {}
};
struct freeblock{
    int size;
    int idx;
    freeblock(int size, int idx) : size(size), idx(idx) {}
};
vector<fileblock> files;
vector<freeblock> freeblocks;

void read_input(const string &filename) {
    ifstream file(filename);
    string line;
    file >> line;
    for (int i = 0; i < line.size(); i++){
        if (i % 2 == 0){
            files.emplace_back(i / 2, line[i] - '0', strip.size());
            for (int j = 0; j < line[i] - '0'; j++)
                strip.push_back(i / 2);
        }
        else{
            freeblocks.emplace_back(line[i] - '0', strip.size());
            for (int j = 0; j < line[i] - '0'; j++)
                strip.push_back(-1);
        }
    }
    file.close();
}

ll solve(){
    int n = strip.size();
    // int l = 0, r = n - 1;
    ll ans = 0;
    for (auto it = files.rbegin(); it != files.rend(); ++it){
        int id = it->id;
        int size = it->size;
        int idx = it->idx;
        for (auto& block : freeblocks){
            if (block.idx > idx) break;
            if (block.size >= size){
                for(int i = idx; i < idx + size; i++) strip[i] = -1;
                for(int i = block.idx; i < block.idx + size; i++) strip[i] = id;
                block.size -= size;
                block.idx += size;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (strip[i] != -1){
            ans += (ll) i * (ll) strip[i];
            //cout << strip[i];
        }
        //else cout << '.';
    }
    //cout << endl;
    return ans;
}

int main(int argc, char* argv[]){
    read_input(argv[1]);
    cout << solve() << endl;
    return 0;
}