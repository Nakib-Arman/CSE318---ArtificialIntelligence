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

string trim(string str)
{
    int start=0,end = ;
    while(str[start == ' ']) start++;

}

bool is_digit(string str)
{
    for(int i=0;i<str.size();i++){
        if(str[i] == '.') continue;
        if(!isdigit(str[i])) return false;
    }
    return true;
}

float getEntropy(int dataset_size,unordered_map<string,int>& decisions)
{
    float entropy=0;
    for(auto& [val,count] : decisions){
        // if (count[i] == 0) continue;
        float probability = static_cast <float> (count)/dataset_size;
        entropy -= (probability * log2(probability));
    }
    return entropy;
}

float getInformationGain(vector<vector<string>>& dataset, vector<unordered_set<string>>& values, unordered_map<string,int>& decisions,int attribute_num,float threshold=0)
{
    float ig= getEntropy(dataset.size(),decisions);
    cout<<ig<<endl;
    if(is_digit(*values[attribute_num].begin())){
        int temp1_size=0,temp2_size=0;
        unordered_map<string,int>temp_decisions;
        cout<<values[attribute_num].size()<<endl;
        for(string val: values[attribute_num]){
            cout<<val<<endl;
        }
        for(int i=0;i<values[attribute_num].size();i++){
            if(stof(dataset[i][attribute_num]) < threshold){
                temp1_size++;
            }
            else{
                temp2_size++;
            }
        }
        // float entropy1 = getEntropy(temp1_size++,values[values.size()-1]);
        // float entropy2 = getEntropy(temp2,values[values.size()-1]);
        // ig -= (static_cast <float> (temp1.size())/dataset.size())*entropy1;
        // ig -= (static_cast <float> (temp2.size())/dataset.size())*entropy2;
    }
    // else{
    //     for(string value : values[attribute_num]){
    //         vector<vector<string>> temp;
    //         for(int i=0;i<dataset.size();i++){
    //             if(dataset[i][attribute_num] == value){
    //                 temp.push_back(dataset[i]);
    //             }
    //         }
    //         float entropy = getEntropy(temp,values[values.size()-1]);
    //         ig -= (static_cast <float> (temp.size())/dataset.size())*entropy;
    //     }
    // }
    return ig;
}


int main()
{
    ifstream file("test.txt");
    string line;
    if(!file.is_open()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    
    vector<vector<string>> dataset;
    vector<pair<float,bool>> used;
    
    getline(file,line);
    stringstream ss(line);
    string attribute;
    int i = 1;
    while(getline(ss,attribute,',')){
        used.push_back(make_pair(INT_MIN,false));
        i++;
    }
    vector<unordered_set<string>> values(used.size());
    unordered_map<string,int> decisions;
    // vector<vector<float>> numeric_values(used.size()); 

    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        int i=0;
        while(getline(ss,value,',')) {
            row.push_back(value);
            // if(!is_digit(value)) 
            values[i].insert(trim(value));
            if(i==values.size()-1){
                decisions[value]++;
            }
            // else numeric_values[i].push_back(stof(value));
            i++;
        }
        dataset.push_back(row);
    }

    // for(int i=0;i<values.size();i++){
    //     cout<<i+1<<" -> ";
    //     for(string val: values[i]){
    //         cout<<val<<endl;
    //     }
    //     cout<<endl;
    // }

    // for(auto& [val,count] : decisions){
    //     cout<<val<<" "<<count<<endl;
    // }

    getInformationGain(dataset,values,decisions,1,1);

    // for(int i=0;i<values.size();i++){
    //     if(!is_digit(*values[i].begin())) continue;
    //     float max_ig = INT_MIN;
    //     int max_index = 0;
    //     int j=0;
    //     for(string val: values[i]){
    //         cout<<val<<endl;
    //         float ig = getInformationGain(dataset,values,i,stof(val));
    //         cout<<ig<<endl;
    //         if(ig>max_ig){
    //             max_ig = ig;
    //         }
    //         cout<<i<<" "<<j<<endl;
    //         j++;
    //     }
        // values[i].insert(to_string(numeric_values[i][max_index]));
    // }
    
    return 0;
}