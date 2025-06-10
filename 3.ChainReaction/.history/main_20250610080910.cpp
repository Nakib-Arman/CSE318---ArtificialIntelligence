#include <bits/stdc++.h>
using namespace std;

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

void inc_cell_orbs(vector<vector<Cell>>& grid, char color,int row,int column) {
    if(row<0 || row>=grid.size()) return;
    if(column<0 || column>=grid[0].size()) return;
    grid[row][column].inc_orb_count();
    Cell target = grid[row][column];
    if(target.get_orb_num() == target.get_critical_mass()) {
        grid[row][column].set_orb_num(0);
        grid[row][column].set_color('W');
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

int minimax(vector<vector<Cell>>& grid,char color,int depth,int alpha,int beta,char user_color,char ai_color) {
    if(depth == 0 || foundWinner(grid) != 'W') return evaluate(grid,color);
    if(color == user_color) {
        int max = INT_MIN;
        vector<vector<Cell>>
    }
}

void getBestMove(vector<vector<Cell>>& grid,char ai_color,char user_color,int depth) {
    int best_value = INT_MIN;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(!isValidMove(grid,ai_color,i,j)) continue;

        }
    }
}

int aiMove(vector<vector<Cell>>& grid,char ai_color,int row,int column) {
    
}


int main() {
    int m = 9,n = 6;
    // cin>>m>>n;

    char user_color,ai_color;
    char color;
    cin>>color;
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

    for(int k=0;k<5;k++){
        int row,col;
        cin>>row>>col;
        userMove(grid,user_color,row,col);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                grid[i][j].printCell();
                cout<<" ";
            }
            cout<<endl;
        }
    }
}


