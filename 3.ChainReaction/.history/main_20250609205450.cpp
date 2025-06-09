#include <bits/stdc++.h>
using namespace std;

class cell {
    int orb_num;
    char color;

public:

    cell() {
        this->orb_num = 0;
        this->color = 'B';
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

    void inc_orb_count() {
        if(orb_num<3) orb_num++;
    }

    void printCell() {
        cout<<orb_num<<color;
    }

};

void userMove(vector<vector<cell>>& grid,char user_color,int row,int column) {
    grid[row][column].set_color(user_color);
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
        for(int j=0;j<n;j++){
            grid[i][j].printCell();
            cout<<" ";
        }
        cout<<endl;
    }

    for(int i=0;i<5;i++){
        int row,col;
        cin>>row>>col;
        userMove()
    }
}


