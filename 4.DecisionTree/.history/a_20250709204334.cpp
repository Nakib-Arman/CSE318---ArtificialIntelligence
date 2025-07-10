#include<bits/stdc++.h>
using namespace std;

class Node {
    int column_num;
    string label;
    unordered_map<string,Node*> children;
    float threshold;
    
public:
    Node(int column_num){
        this->column_num = column_num;
        this->label = "";
        this->threshold = 0;
    }

    Node(string label){
        column_num = 0;
        this->label = label;
        this->threshold = 0;
    }

    int getColumnNum(){
        return column_num;
    }

    string getLabel(){
        return label;
    }

    float getThreshold(){
        return threshold;
    }

    Node* getChild(string edge){
        return children[edge];
    }

    void addChild(string edge, Node* child){
        stringstream ss(edge);
        string first,second;
        ss>>first>>second;
        if(!second.empty()){
            this->threshold = stof(second);
        }
        this->children[edge] = child;
    }
    
    void print(){
        cout<<column_num<<" -> ";
        for(auto& [val,node] : children){
            cout<<"("<<val<<","<<node->getColumnNum()<<","<<node->getLabel()<<"), ";
        }
        cout<<endl;
    }
};

bool is_digit(string str)
{
    for(int i=0;i<str.size();i++){
        if(str[i] == '.' || str[i] == ' ') continue;
        if(!isdigit(str[i])) return false;
    }
    return true;
}

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

float getInformationGain(vector<vector<string>>& dataset, unordered_set<string>& decisions, int attribute_num, unordered_set<string>& values,float threshold=0)
{
    float ig= getEntropy(dataset,decisions);
    if(threshold!=0){
        vector<vector<string>> temp1,temp2;
        for(int i=0;i<dataset.size();i++){
            if(stof(dataset[i][attribute_num]) < threshold){
                temp1.push_back(dataset[i]);
            }
            else{
                temp2.push_back(dataset[i]);
            }
        }
        float entropy1 = getEntropy(temp1,decisions);
        float entropy2 = getEntropy(temp2,decisions);
        ig -= (static_cast <float> (temp1.size())/dataset.size())*entropy1;
        ig -= (static_cast <float> (temp2.size())/dataset.size())*entropy2;
    }
    else{
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
    }
    return ig;
}


int main()
{
    ifstream file("adult.txt");
    string line;
    if(!file.is_open()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    
    vector<vector<string>> dataset;
    vector<bool> used;
    
    getline(file,line);
    stringstream ss(line);
    string attribute;
    int i = 1;
    while(getline(ss,attribute,',')){
        used.push_back(false);
        i++;
    }
    vector<unordered_set<string>> values(used.size());
    // vector<vector<float>> numeric_values(used.size()); 

    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        int i=0;
        while(getline(ss,value,',')) {
            row.push_back(value);
            // if(!is_digit(value)) 
            values[i].insert(value);
            // else numeric_values[i].push_back(stof(value));
            i++;
        }
        dataset.push_back(row);
    }

    for(int i=0;i<values.size();i++){
        cout<<i+1<<" -> ";
        for(string val : values[i]){
            cout<<val<<",";
        }
        cout<<endl;
    }

    for(int i=0;i<values.size();i++){
        auto str = values[i]
        if(is_digit(values[i].begin())) continue;
        float max_ig = INT_MIN;
        int max_index = 0;
        for(int j=0;j<dataset.size();j++){
            float ig = getInformationGain(dataset,values[values.size()-1],i,values[i],numeric_values[i][j]);
            if(ig>max_ig){
                max_ig = ig;
                max_index = j;
            }
            cout<<i<<" "<<j<<endl;
        }
        values[i].insert(to_string(numeric_values[i][max_index]));
    }
    
    return 0;
}