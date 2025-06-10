#include <bits/stdc++.h>
using namespace std;

#define DEPTH 2

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
    if(target.get_orb_num() >= target.get_critical_mass()) {
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


int main()
{
    vector<vector<Cell>> grid(9,vector<Cell>(6));
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            grid[i][j].set_color('B');
        }
    }
    grid[2][5].set_color('W');
    grid[3][1].set_color('W');
    grid[3][4].set_color('W');
    grid[5][5].set_color('W');
    grid[7][1].set_color('W');
    grid[7][3].set_color('W');
    grid[8][0].set_color('R');
    grid[8][1].set_color('R');
    grid[8][2].set_color('W');

    grid[0][0].set_orb_num()
}