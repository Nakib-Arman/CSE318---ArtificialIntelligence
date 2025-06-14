#include <bits/stdc++.h>
using namespace std;

#define DEPTH 3

class Cell {
    int orb_num;
    int critical_mass;
    char color;

public:

    Cell() {
        this->orb_num = 0;
        this->color = 'W';
        this->critical_mass = 4;
    }

    // Cell(int orb_num, char color) {
    //     this->orb_num = orb_num;
    //     this->color = color;
    // }

    void set_orb_num(int orb_num) {
        this->orb_num = orb_num;
    }

    void set_color(char color) {
        this->color = color;
    }

    int get_orb_num() {
        return orb_num;
    }

    char get_color() {
        return color;
    }

    int get_critical_mass(){
        return critical_mass;
    }

    void inc_orb_count() {
        if(orb_num<4) orb_num++;
    }

    void dec_critical_mass() {
        this->critical_mass--;
    }

    void printCell() {
        cout<<orb_num;
        if(color!='W') cout<<color;
    }

};

bool isValidMove(vector<vector<Cell>>& grid,char user_color,int row,int column) {
    if(grid[row][column].get_color() == 'W') return true;
    if(grid[row][column].get_color() == user_color) return true;
    return false;
}

char foundWinner(vector<vector<Cell>>& grid) {
    char winner = 'W';
    int count = 0;
    for(int i=0;i<grid.size();i++){
        for(int j=0; j<grid[0].size();j++){
            if(grid[i][j].get_color() == 'W') continue;
            if(winner != 'W' && grid[i][j].get_color() != winner) {
                return 'W';
            }
            else if(grid[i][j].get_color() != 'W') {
                winner = grid[i][j].get_color();
                count++;
            }
        }
    }
    if(count ==1) return 'W';
    return winner;
}

void inc_cell_orbs(vector<vector<Cell>>& grid, char color,int row,int column) {
    if(row<0 || row>=grid.size()) return;
    if(column<0 || column>=grid[0].size()) return;
    grid[row][column].inc_orb_count();
    Cell target = grid[row][column];
    if(target.get_orb_num() >= target.get_critical_mass()) {
        grid[row][column].set_orb_num(0);
        grid[row][column].set_color('W');
        if(foundWinner(grid) == color) {
            grid[row][column].set_orb_num(target.get_orb_num());
            grid[row][column].set_color(color);
            return;
        }
        inc_cell_orbs(grid,color,row+1,column);
        inc_cell_orbs(grid,color,row-1,column);
        inc_cell_orbs(grid,color,row,column+1);
        inc_cell_orbs(grid,color,row,column-1);
    }
    else{
        grid[row][column].set_color(color);
    }
}

int userMove(vector<vector<Cell>>& grid,char user_color,int row,int column) {
    if(!isValidMove(grid,user_color,row,column)) return -1;
    inc_cell_orbs(grid,user_color,row,column);
    return 0;
}

int evaluate(vector<vector<Cell>>& grid, char ai_color) {
    int ai_orbs = 0, user_orbs = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j< grid[0].size(); j++) {
            if (grid[i][j].get_color() == ai_color)
                ai_orbs += grid[i][j].get_orb_num();
            else{
                user_orbs += grid[i][j].get_orb_num();
            }
        }
    }
    return ai_orbs - user_orbs;
}


int minimax(vector<vector<Cell>>& grid,char color,int depth,int alpha,int beta,char user_color,char ai_color) {
    // for(int i=0;i<grid.size();i++){
    //     for(int j=0;j<grid[0].size();j++){
    //         grid[i][j].printCell();
    //         cout<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    if(depth == 0 || foundWinner(grid) != 'W'){
        return evaluate(grid,ai_color);
    }
    if(color == ai_color) {
        int max_value = INT_MIN;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(!isValidMove(grid,color,i,j)) continue;
                vector<vector<Cell>> temp = grid;
                inc_cell_orbs(temp,color,i,j);
                int value = minimax (temp,user_color,depth-1,alpha,beta,user_color,ai_color);
                max_value = max(value,max_value);
                alpha = max(value,alpha);
                if (beta<=alpha) break;
            }
            if(beta<=alpha) break;
        }
        return max_value;
    }
    else{
        int min_value = INT_MAX;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(!isValidMove(grid,color,i,j)) continue;
                vector<vector<Cell>> temp = grid;
                inc_cell_orbs(temp,color,i,j);
                int value = minimax (temp,ai_color,depth-1,alpha,beta,user_color,ai_color);
                min_value = min(value,min_value);
                beta = min(value,beta);
                if (beta<=alpha) break;
            }
            if(beta<=alpha) break;
        }
        return min_value;
    }
}

pair<int,pair<int,int>> getBestMove(vector<vector<Cell>>& grid,char ai_color,char user_color,int depth) {
    int best_value = INT_MIN;
    pair<int,int> best_move = make_pair(-1,-1);
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(!isValidMove(grid,ai_color,i,j)) continue;
            vector<vector<Cell>> temp = grid;
            inc_cell_orbs(temp,ai_color,i,j);
            int value = minimax(temp,user_color,depth,INT_MIN,INT_MAX,user_color,ai_color);
            if (value>best_value) {
                best_value = value;
                best_move = make_pair(i,j);
            }
        }
    }
    return make_pair(best_value,best_move);
}

void aiMove(vector<vector<Cell>>& grid,char ai_color,char user_color,int depth) {
    pair<int,pair<int,int>> best_move = getBestMove(grid,ai_color,user_color,depth);
    inc_cell_orbs(grid,ai_color,best_move.second.first,best_move.second.second);
}


int main(int argc, char *argv[]) {
    int m = 9,n = 6;
    // cin>>m>>n;

    char user_color,ai_color;
    char color = 'R';
    // cin>>color;
    if(color == 'R') {
        ai_color = 'B';
    }
    else {
        ai_color = 'R';
    }
    user_color = color;

    vector<vector<Cell>> grid(m,vector<Cell>(n));
    for(int i=0;i<m;i++){
        grid[i][0].dec_critical_mass();
        grid[i][n-1].dec_critical_mass();
    }
    for(int i=0;i<n;i++){
        grid[0][i].dec_critical_mass();
        grid[m-1][i].dec_critical_mass();
    }

    // for(int i=0;i<m;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<grid[i][j].get_critical_mass();
    //         cout<<" ";
    //     }
    //     cout<<endl;
    // }

    ifstream file("file.txt");
    if (!file.is_open()) {
        cerr << "File failed to open\n";
        return 1;
    }

    string line;
    getline(file,line);
    int move;
    if (line == "Human Move:") move = 0;
    else if (line == "Ai Move:") move = 1;
    else cout<<"Move not specified"<<endl;

    int i=0,j=0;
    while(getline(file,line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string token;
        while (iss >> token) {
            if (token != "0") {
                grid[i][j].set_orb_num(token[0]-'0');
                grid[i][j].set_color(token[1]);
            }
            j++;
        }
        i++;
        j=0;
    }
    file.close();

    ofstream file2("file.txt");
    if (!file2) {
        cerr << "File failed to open\n";
        return 1;
    }
    if (move == 0) {
        int ret = userMove(grid,user_color,stoi(argv[1]),stoi(argv[2]));
        if (ret == -1) file
        file2 << "Ai Move:\n";
        for (int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                file2 << grid[i][j].get_orb_num();
                if (grid[i][j].get_orb_num() != 0) file2 << grid[i][j].get_color();
                file2 << " ";
            }
            file2 << "\n";
        }
        char winner = foundWinner(grid);
        if(winner != 'W'){
            if(winner == user_color){
                file2 << "Human";
            }
            else file2 << "AI";
        }
    }
    else if (move == 1) {
        aiMove(grid,ai_color,user_color,3);
        file2 << "Human Move:\n";
        for (int i=0;i<m;i++){
            for (int j=0;j<n;j++){
                file2 << grid[i][j].get_orb_num();
                if (grid[i][j].get_orb_num() != 0) file2 << grid[i][j].get_color();
                file2 << " ";
            }
            file2 << "\n";
        }
        char winner = foundWinner(grid);
        if(winner != 'W'){
            if(winner == user_color){
                file2 << "Human";
            }
            else file2 << "AI";
        }
    }
}


