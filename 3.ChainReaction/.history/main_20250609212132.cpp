#include <bits/stdc++.h>
using namespace std;

class Cell {
    int orb_num;
    int critical_mass;
    char color;

public:

    Cell() {
        this->orb_num = 0;
        this->color = 'B';
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
        if(orb_num<3) orb_num++;
    }

    void dec_critical_mass() {
        this->critical_mass--;
    }

    void printCell() {
        cout<<orb_num<<color;
    }

};

bool isValidMove(vector<vector<Cell>>& grid,char user_color,int row,int column) {
    if(grid[row][column].get_color() == 'B') return true;
    if(grid[row][column].get_color() == user_color) return true;
    return false;
}

int userMove(vector<vector<Cell>>& grid,char user_color,int row,int column) {
    if(!isValidMove) return -1;
    Cell target = grid[row][column];
    grid[row][column].inc_orb_count();
    
    grid[row][column].set_color(user_color);
    return 0;
}


int main() {
    int m = 9,n = 6;
    // cin>>m>>n;

    // char user_color,ai_color;
    // char color;
    // cin>>color;
    // if(color == 'R') {
    //     ai_color = 'B';
    // }
    // else {
    //     ai_color = 'R';
    // }
    // user_color = color;

    vector<vector<Cell>> grid(m,vector<Cell>(n));
    for(int i=0;i<m;i++){
        grid[i][0].dec_critical_mass();
        grid[i][n-1].dec_critical_mass();
    }
    for(int i=0;i<n;i++){
        grid[0][i].dec_critical_mass();
        grid[m-1][i].dec_critical_mass();
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<grid[i][j].get_critical_mass();
            cout<<" ";
        }
        cout<<endl;
    }

    for(int k=0;k<5;k++){
        int row,col;
        cin>>row>>col;
        userMove(grid,'R',row,col);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                grid[i][j].printCell();
                cout<<" ";
            }
            cout<<endl;
        }
    }
}


