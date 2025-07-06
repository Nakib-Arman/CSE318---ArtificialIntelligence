#include<bits/stdc++.h>
using namespace std;

class node {
    string label;
    vector<node*> children;
    node* parent;

public:
    node(string label){
        this->label = label;
        this->parent = NULL;
    }

    void setParent(string)
};

float getEntropy(vector<vector<string>>& dataset,unordered_set<string>& decisions)
{
    float entropy=0;
    vector<string> decisions_vect;
    vector<int> count(decisions.size(),0);
    for(string decision : decisions){
        decisions_vect.push_back(decision);
    }
    for (int i=0;i<dataset.size();i++){
        for (int j=0;j<decisions_vect.size();j++){
            if(dataset[i][dataset[i].size()-1] == decisions_vect[j]){
                count[j]++;
            }
        }
    }
    for(int i=0;i<decisions_vect.size();i++){
        float probability = static_cast <float> (count[i])/dataset.size();
        if (probability == 0) continue;
        entropy -= (probability * log2(probability));
    }
    return entropy;
}

float getInformationGain(vector<vector<string>>& dataset, unordered_set<string>& decisions, int attribute_num, unordered_set<string>& values)
{
    float ig= getEntropy(dataset,decisions);
    vector<float> entropies(values.size());
    for(string value : values){
        vector<vector<string>> temp;
        for(int i=0;i<dataset.size();i++){
            if(dataset[i][attribute_num] == value){
                temp.push_back(dataset[i]);
            }
        }
        float entropy = getEntropy(temp,decisions);
        ig -= (static_cast <float> (temp.size())/dataset.size())*entropy;
    }
    return ig;
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

    // for(int i=0;i<attributes.size();i++){
    //     cout<<attributes[i]<<" ";
    // }
    // cout<<endl;
    // for(int i=0;i<dataset.size();i++){
    //     for(int j=0;j<dataset[0].size();j++){
    //         cout<<dataset[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // for(int i=0;i<values.size();i++){
    //     cout<<attributes[i]<<" -> ";
    //     for(string value : values[i]){
    //         cout<<value<<", ";
    //     }
    //     cout<<endl;
    // }
    getInformationGain(dataset,values[values.size()-1],0,values[0]);
    
    return 0;
}