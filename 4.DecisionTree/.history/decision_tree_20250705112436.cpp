#include<bits/stdc++.h>
using namespace std;

float getEntropy(vector<vector<string>>& dataset,unordered_set<string>& decisions)
{
    float entropy=0;
    for(string decision:decisions)
    vector<string> decisions_vect;
    vector<int> probability(decisions.size(),0);
    for(string decision : decisions){
        decisions_vect.push_back(decision);
    }
    for (int i=0;i<dataset.size();i++){
        for (int j=0;j<decisions_vect.size();j++){
            if(dataset[i][dataset[i].size()-1] == decisions_vect[j]){
                probability[i]++;
            }
        }
    }
    for(int i=0;i<decisions.size();i++){
        cout<<decisions_vect[i]<<" -> "<<probability[i]<<endl;
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
        int i=0;
        while(getline(ss,value,',')) {
            row.push_back(value);
            values[i].insert(value);
            i++;
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

    // for(int i=0;i<values.size();i++){
    //     cout<<attributes[i]<<" -> ";
    //     for(string value : values[i]){
    //         cout<<value<<", ";
    //     }
    //     cout<<endl;
    // }

    getEntropy(dataset,values[values.size()-1]);

    return 0;
}