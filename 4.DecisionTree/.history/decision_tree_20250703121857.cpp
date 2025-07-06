#include<bits/stdc++.h>
using namespace std;

/

int main()
{
    vector<vector<string>> dataset;
    
    ifstream file("test.txt");
    string line;
    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> temp;
        while(getline(ss,value,',')) {
            temp.push_back(value);
        }
        dataset.push_back(temp);
    }

    for(int i=0;i<dataset.size();i++){
        for(int j=0;j<dataset[0].size();j++){
            cout<<dataset[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}