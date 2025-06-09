#include <bits/stdc++.h>
using namespace std;

class cell {
    int orb_num;
    int critical_mass;
    char color;

public:

    cell() {
        this->orb_num = 0;
        this->color = 'B';
        this->critical_mass = 4;
    }

    // cell(int orb_num, char color) {
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

bool isValidMove(vector<vector<cell>>& grid,char user_color,int row,int column) {
    if(grid[row][column].get_color() == 'B') return true;
    if(grid[row][column].get_color() == user_color) return true;
    return false;
}

int userMove(vector<vector<cell>>& grid,char user_color,int row,int column) {
    if(!isValidMove) return -1;
    grid[row][column].set_color(user_color);
    grid[row][column].inc_orb_count();
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

    vector<vector<cell>> grid(m,vector<cell>(n));
    for(int i=0;i<m;i++){
        grid[i][0]
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            grid[i][j].printCell();
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


