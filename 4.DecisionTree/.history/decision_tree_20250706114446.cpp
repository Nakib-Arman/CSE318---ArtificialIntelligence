#include<bits/stdc++.h>
using namespace std;

class Node {
    int column_num;
    string label;
    unordered_map<string,Node*> children;
    Node* parent;

public:
    Node(int column_num){
        this->column_num = column_num;
        this->parent = NULL;
    }

    Node(string label)

    int getColumnNum(){
        return column_num;
    }

    void setParent(Node* parent){
        this->parent = parent;
    }

    void addChild(string edge, Node* child){
        this->children[edge] = child;
    }

    void print(){
        cout<<column_num<<" -> ";
        for(auto& [val,node] : children){
            cout<<"("<<val<<","<<node->getColumnNum()<<"), ";
        }
        cout<<endl;
    }
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
        if (count[i] == 0) continue;
        float probability = static_cast <float> (count[i])/dataset.size();
        entropy -= (probability * log2(probability));
    }
    return entropy;
}

float getInformationGain(vector<vector<string>>& dataset, unordered_set<string>& decisions, int attribute_num, unordered_set<string>& values)
{
    // for(int i=0;i<dataset.size();i++){
    //     for(int j=0;j<dataset[0].size();j++){
    //         cout<<dataset[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
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

Node* makeDecisionTree(vector<vector<string>>& dataset, vector<pair<int,bool>>& attributes, vector<unordered_set<string>>& values)
{   
    float max_ig = INT_MIN;
    int max_i=0;
    int count = 0;
    for(int i=0;i<dataset.size();i++){
        if(dataset[i][dataset[i].size()-1] != dataset[0][dataset[0].size()-1]){
            // cout<<dataset[i][dataset[i].size()-1]<<" "<<dataset[i][dataset[i].size()-1]<<endl;
            count++;
        }
    }
    // cout<<count<<endl;
    if(count == 0){
        return new Node(dataset[0][dataset[0].size()-1]);
    }
    for (int i=0;i<attributes.size()-1;i++){
        if(attributes[i].second){
            // cout<<attributes[i].first<<attributes[i].second<<endl;
            continue;
        }
        float ig = getInformationGain(dataset,values[values.size()-1],i,values[i]);
        // cout<<ig<<endl;
        if(ig>max_ig){
            max_ig = ig;
            max_i = i;
        }
    }
    attributes[max_i].second = true;
    // cout<<attributes[max_i].first<<attributes[max_i].second<<" Selected"<<endl;
    Node* root = new Node(attributes[max_i].first);
    for(string val: values[max_i]){
        vector<vector<string>> temp_dataset;
        for(int i=0;i<dataset.size();i++){
            if(dataset[i][max_i] == val){
                temp_dataset.push_back(dataset[i]);
            } 
        }
        float ig = getInformationGain(temp_dataset,values[values.size()-1],1,values[1]);
        // cout<<ig<<endl;
        Node* child = makeDecisionTree(temp_dataset,attributes,values);
        root->addChild(val,child);
    }
    root->print();
    return root;
}

int main()
{
    vector<vector<string>> dataset;
    vector<pair<int,bool>> attributes;
    
    ifstream file("test.txt");
    string line;
    if(!file.is_open()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    getline(file,line);
    stringstream ss(line);
    string attribute;
    int i = 1;
    while(getline(ss,attribute,',')){
        // attributes.push_back(make_pair(attribute,false));
        attributes.push_back(make_pair(i,false));
        i++;
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
    makeDecisionTree(dataset,attributes,values);
    
    return 0;
}