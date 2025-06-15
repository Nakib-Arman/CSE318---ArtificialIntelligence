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

// difference in number of controlled cells
int heuristic1(vector<vector<Cell>>& grid, char ai_color) {
    int ai_control = 0, user_control = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size();j++) {
            if (grid[i][j].get_color() == ai_color) {
                ai_control++;
            }
            else if (grid[i][j].get_color() != 'W') {
                user_control++;
            }
        }
    }
    return ai_control - user_control;
}

// difference in number of orbs
int heuristic2(vector<vector<Cell>>& grid, char ai_color) {
    int ai_orbs = 0, user_orbs = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j< grid[0].size(); j++) {
            if (grid[i][j].get_color() == ai_color) {
                ai_orbs += grid[i][j].get_orb_num();
            }
            else{
                user_orbs += grid[i][j].get_orb_num();
            }
        }
    }
    return ai_orbs - user_orbs;
}

// difference in number of controlled edge cells
int heuristic3(vector<vector<Cell>>& grid, char ai_color) {
    int ai_count = 0, user_count = 0;
    for (int i=0;i<grid.size();i++) {
        for(int j =0; j<grid[0].size();j++) {
            if (i!=0 || j!=0 || i!=grid.size()-1 || j!=grid[0].size()-1) continue;
            if (grid[i][j].get_color() == ai_color) {
                cout<<
                ai_count++;
            }
            else if (grid[i][j].get_color() != 'W') {
                user_count++;
            }
        }
    }
    return ai_count - user_count;
}

// difference in number of orbs in edge cells
int heuristic4(vector<vector<Cell>>& grid, char ai_color) {
    int ai_count = 0, user_count = 0;
    for (int i=0;i<grid.size();i++) {
        for(int j =0; j<grid[0].size();j++) {
            if (i!=0 || j!=0 || i!=grid.size()-1 || j!=grid[0].size()-1) continue;
            if (grid[i][j].get_color() == ai_color) {
                ai_count += grid[i][j].get_orb_num();
            }
            else if (grid[i][j].get_color() != 'W') {
                user_count += grid[i][j].get_orb_num();
            }
        }
    }
    return ai_count - user_count;
}

// proportion of critical mass
int heuristic5(vector<vector<Cell>>& grid, char ai_color) {
    float ai_count = 0, user_count = 0;
    for (int i=0;i<grid.size();i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (grid[i][j].get_color() == ai_color) {
                ai_count += static_cast<float>(grid[i][j].get_orb_num()) / grid[i][j].get_critical_mass();
            }
            else if (grid[i][j].get_color() != 'W') {
                user_count += static_cast<float>(grid[i][j].get_orb_num() / grid[i][j].get_critical_mass());
            }
        }
    }
    return ai_count - user_count;
}



int main()
{
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

    ifstream file("file.txt");
    if (!file.is_open()) {
        cerr << "File failed to open\n";
        return 1;
    }

    string line;
    getline(file,line);

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

    int a = heuristic3(grid,ai_color);
    cout<<a<<endl;
}