#include<bits/stdc++.h>
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

char foundWinner(vector<vector<Cell>>& grid) {
    char winner = 'W';
    int count = 0;
    for(int i=0;i<grid.size();i++){
        for(int j=0; j<grid[0].size();j++){
            if(grid[i][j].get_color() != 'W' && grid[i][j].get_color() != winner) {
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


int main() 
{
    vector<vector<Cell>> grid(m,vector<Cell>(n));
    for(int i=0;i<m;i++){
        grid[i][0].dec_critical_mass();
        grid[i][n-1].dec_critical_mass();
    }
    for(int i=0;i<n;i++){
        grid[0][i].dec_critical_mass();
        grid[m-1][i].dec_critical_mass();
    }
    cout<<foundWinner(grid)
}