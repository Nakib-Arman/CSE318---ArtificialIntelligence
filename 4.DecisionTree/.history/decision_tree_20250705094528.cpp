#include<bits/stdc++.h>
using namespace std;

float getEntropy(int attributes, vector<int> neumerator, vector<int> denomenator)
{
    float entropy=0;
    for (int i=0;i<attributes;i++){
        float p = static_cast<float> (neumerator[i])/denomenator[i];
        entropy -= log2(p) * p;
    }
    return entropy;
}

int main()
{
    vector<vector<string>> dataset;
    vector<string> attributes;
    
    ifstream file("test.txt");
    string line;
    if(!file.is_open()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    getline()
    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        while(getline(ss,value,',')) {
            row.push_back(value);
        }
        dataset.push_back(row);
    }

    for(int i=0;i<dataset.size();i++){
        for(int j=0;j<dataset[0].size();j++){
            cout<<dataset[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}