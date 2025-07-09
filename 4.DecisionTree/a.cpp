#include<bits/stdc++.h>
using namespace std;

class Node {
    int column_num;
    string label;
    unordered_map<string,Node*> children;
    Node* parent;
    float threshold;
    
public:
    Node(int column_num){
        this->column_num = column_num;
        this->parent = NULL;
        this->label = "";
        this->threshold = 0;
    }

    Node(string label){
        column_num = 0;
        this->label = label;
        this->parent = NULL;
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

    void setParent(Node* parent){
        this->parent = parent;
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


int main()
{

    return 0;
}