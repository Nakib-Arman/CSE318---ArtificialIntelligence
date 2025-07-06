#include<bits/stdc++.h>
using namespace std;

float getEntropy(vector<vector<string>> dataset, string attribute)
{
    float entropy=0;
    for (int i=0;i<dataset.size();i++){
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
    getline(file,line);
    stringstream ss(line);
    string attribute;
    while(getline(ss,attribute,',')){
        attributes.push_back(attribute);
    }
    vector<unordered_set<string>> values(attributes.size());   
    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        while(getline(ss,value,',')) {
            row.push_back(value);
            values[i]
        }
        dataset.push_back(row);
    }

    for(int i=0;i<attributes.size();i++){
        cout<<attributes[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<dataset.size();i++){
        for(int j=0;j<dataset[0].size();j++){
            cout<<dataset[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}