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
    vector<unordered_map<string,string>> dataset;
    
    ifstream file("test.txt");
    string line;
    if(!file.is_open()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        unordered_map <string,string> row;
        while(getline(ss,value,',')) {
            row.e
        }
        dataset.push_back(temp);
    }

    // for(int i=0;i<dataset.size();i++){
    //     for(int j=0;j<dataset[0].size();j++){
    //         cout<<dataset[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    
    return 0;
}