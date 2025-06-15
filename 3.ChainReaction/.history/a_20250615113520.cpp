#include<bits/stdc++.h>
using namespace std;



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