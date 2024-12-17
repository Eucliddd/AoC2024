#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct instruction{
    char opcode;
    char operand;
    instruction(char opcode, char operand) : opcode(opcode), operand(operand) {}
};

vector<instruction> program;
ll A = 0, B = 0, C = 0;

inline ll combo_operand(char operand){
    if (operand >= 0 && operand <= 3) return operand;
    if (operand == 4) return A;
    if (operand == 5) return B;
    if (operand == 6) return C;
    return -1;
}
inline ll literal_operand(char operand){
    return operand;
}

void read_input(string file_path){
    ifstream file(file_path);
    string line;
    getline(file, line);
    A = stoll(line.substr(line.find(':') + 2));
    getline(file, line);
    B = stoll(line.substr(line.find(':') + 2));
    getline(file, line);
    C = stoll(line.substr(line.find(':') + 2));
    getline(file, line);
    getline(file, line);
    for (int i = line.find(':') + 2; i < line.size(); i += 4){
        program.emplace_back(line[i] - '0', line[i + 2] - '0');
    }
    // cout << "A: " << A << ", B: " << B << ", C: " << C << endl;
    // cout << "Program size: " << program.size() << endl;
    // for (auto instr : program){
    //     cout << (int)instr.opcode << " " << (int)instr.operand  << endl;
    // }
    file.close();
}

void solve(){
    int ip = 0;
    while (ip < program.size()){
        auto [opcode, operand] = program[ip];
        switch (opcode)
        {
        case 0:
            A >>= combo_operand(operand);
            ip += 1;
            break;
        case 1:
            B ^= literal_operand(operand);
            ip += 1;
            break;
        case 2:
            B = combo_operand(operand) & 7;
            ip += 1;
            break;
        case 3:
            if (A == 0) ++ip;
            else ip = literal_operand(operand);
            break;
        case 4:
            B ^= C;
            ip += 1;
            break;
        case 5:
            cout << (combo_operand(operand) & 7) << ",";
            ip += 1;
            break;
        case 6:
            B = A >> combo_operand(operand);
            ip += 1;
            break;
        case 7:
            C = A >> combo_operand(operand);
            ip += 1;
            break;
        default:
            break;
        }
    }
}

int main(int argc, char** argv){
    read_input(argv[1]);
    solve();
    return 0;
}