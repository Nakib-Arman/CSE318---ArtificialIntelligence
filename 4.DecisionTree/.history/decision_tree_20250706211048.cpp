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
        this->label = "";
    }

    Node(string label){
        column_num = 0;
        this->label = label;
        this->parent = NULL;
    }

    int getColumnNum(){
        return column_num;
    }

    string getLabel(){
        return label;
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
            cout<<"("<<val<<","<<node->getColumnNum()<<","<<node->getLabel()<<"), ";
        }
        cout<<endl;
    }
};

bool is_digit(string str)
{
    for(int i=0;i<str.size();i++){
        if(str[i] == '.') continue;
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

float getInformationGain(vector<vector<string>>& dataset, unordered_set<string>& decisions, int attribute_num, unordered_set<string>& values)
{
    // for(int i=0;i<dataset.size();i++){
    //     for(int j=0;j<dataset[0].size();j++){
    //         cout<<dataset[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    float ig= getEntropy(dataset,decisions);
    for(string value : values){
        if(is_digit(value)){
            vector<vector<string>> temp1,temp2;
            for(int i=0;i<dataset.size();i++){
                if(stof(dataset[i][attribute_num]) < stof(value)){
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

Node* makeDecisionTree(vector<vector<string>>& dataset, vector<pair<int,bool>>& attributes, vector<unordered_set<string>>& values, vector<vector<float>> numeric_values)
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
    count = 0;
    for(int i=0;i<attributes.size();i++){
        if(!attributes[i].second){
            // cout<<"hi"<<endl;
            count++;
        }
    }
    if(count == 1){
        vector<pair<string,int>> labels(values[values.size()-1].size());
        int i=0;
        for (string val : values[values.size()-1]){
            labels[i].first = val;
            labels[i].second = 0;
            for(int j=0;j<dataset.size();j++){
                if(dataset[j][dataset[j].size()-1] == val){
                    labels[i].second++;
                }
            }
            i++;
        }
        int max_count = 0;
        int max=0;
        for(int i=0;i<labels.size();i++){
            if(labels[i].second>max_count){
                max_count = labels[i].second;
                max = i;
            }
        }
        return new Node (labels[max].first);
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
    // cout<<attributes[max_i].first<<" Selected"<<endl;
    // for(int i=0;i<dataset.size();i++){
    //     for(int j=0;j<dataset[i].size();j++){
    //         cout<<dataset[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    Node* root = new Node(attributes[max_i].first);
    for(string val: values[max_i]){
        if(is_digit(val)){
            vector<vector<string>> temp_dataset1,temp_dataset2;
            vector<vector<float>> temp_numeric_values1(numeric_values.size()),temp_numeric_values2(numeric_values.size());
            for(int i=0;i<dataset.size();i++){
                if(stof(dataset[i][max_i]) < stof(val)){
                    temp_dataset1.push_back(dataset[i]);
                    for(int j=0;j<numeric_values.size();j++){
                        if(numeric_values[j].empty()) continue;
                        temp_numeric_values1[j].push_back(numeric_values[j][i]);
                    }
                }
                else{
                    temp_dataset2.push_back(dataset[i]);
                    for(int j=0;j<numeric_values.size();j++){
                        if(numeric_values[j].empty()) continue;
                        temp_numeric_values2[j].push_back(numeric_values[j][i]);
                    }
                }
            }
            for(int i=0;i<temp_numeric_values1.size();i++){
                values[i].erase(to_string)
                if(temp_numeric_values1[i].empty()) continue;
                float max_ig = INT_MIN;
                int max_index = 0;
                for(int j=0;j<temp_dataset1.size();j++){
                    values[i].insert(to_string(numeric_values[i][j]));
                    float ig = getInformationGain(dataset,values[values.size()-1],i,values[i]);
                    if(ig>max_ig){
                        max_ig = ig;
                        max_index = j;
                    }
                    values[i].erase(to_string(numeric_values[i][j]));
                }
                values[i].insert(to_string(numeric_values[i][max_index]));
                // cout<<attributes[i].first<<" "<<numeric_values[i][max_index]<<endl;
            }
            // for(int i=0;i<temp_numeric_values1.size();i++){
            //     for(int j=0;j<temp_numeric_values1[i].size();j++){
            //         cout<<temp_numeric_values1[i][j]<<" ";
            //     }
            //     cout<<endl;
            // }
            // for(int i=0;i<temp_numeric_values2.size();i++){
            //     for(int j=0;j<temp_numeric_values2[i].size();j++){
            //         cout<<temp_numeric_values2[i][j]<<" ";
            //     }
            //     cout<<endl;
            // }
            int max=0;
            vector<pair<string,int>> labels(values[values.size()-1].size());
            int i=0;
            for (string val : values[values.size()-1]){
                labels[i].first = val;
                labels[i].second = 0;
                for(int j=0;j<dataset.size();j++){
                    if(dataset[j][dataset[j].size()-1] == val){
                        labels[i].second++;
                    }
                }
                i++;
            }
            int max_count = 0;
            for(int i=0;i<labels.size();i++){
                if(labels[i].second>max_count){
                    max_count = labels[i].second;
                    max = i;
                }
            }
            if(temp_dataset1.size() == 0) {
                // root->addChild("lt",new Node("No idea"));
                root->addChild("lt",new Node (labels[max].first));
            }
            else{
                Node* child1 = makeDecisionTree(temp_dataset1,attributes,values,temp_numeric_values1);
                root->addChild("lt",child1);
            }
            if(temp_dataset2.size() == 0){
                root->addChild("geq",new Node (labels[max].first));
            }
            else{
                Node* child2 = makeDecisionTree(temp_dataset2,attributes,values,temp_numeric_values2);
                root->addChild("geq",child2);
            }
        }
        else{
            vector<vector<string>> temp_dataset;
            vector<vector<float>> temp_numeric_values(numeric_values.size());
            for(int i=0;i<dataset.size();i++){
                if(dataset[i][max_i] == val){
                    temp_dataset.push_back(dataset[i]);
                    for(int j=0;j<numeric_values.size();j++){
                        if(numeric_values[j].empty()) continue;
                        temp_numeric_values[j].push_back(numeric_values[j][i]);
                    }
                } 
            }
            // float ig = getInformationGain(temp_dataset,values[values.size()-1],1,values[1]);
            // cout<<ig<<endl;
            Node* child = makeDecisionTree(temp_dataset,attributes,values,temp_numeric_values);
            root->addChild(val,child);
        }
    }
    root->print();
    attributes[max_i].second = false;
    return root;
}


int main()
{
    vector<vector<string>> dataset;
    vector<pair<int,bool>> attributes;
    
    ifstream file("Iris.csv");
    // freopen("output.txt","w",stdout);
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
    vector<vector<float>> numeric_values(attributes.size()); 
    while(getline(file,line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        int i=0;
        while(getline(ss,value,',')) {
            row.push_back(value);
            if(!is_digit(value)) values[i].insert(value);
            else numeric_values[i].push_back(stof(value));
            i++;
        }
        dataset.push_back(row);
    }

    // values[1].insert(to_string(numeric_values[1][10]));
    // cout<<getInformationGain(dataset,values[values.size()-1],1,values[1])<<endl;

    for(int i=0;i<numeric_values.size();i++){
        if(numeric_values[i].empty()) continue;
        float max_ig = INT_MIN;
        int max_index = 0;
        for(int j=0;j<dataset.size();j++){
            values[i].insert(to_string(numeric_values[i][j]));
            float ig = getInformationGain(dataset,values[values.size()-1],i,values[i]);
            if(ig>max_ig){
                max_ig = ig;
                max_index = j;
            }
            values[i].erase(to_string(numeric_values[i][j]));
        }
        values[i].insert(to_string(numeric_values[i][max_index]));
        // cout<<attributes[i].first<<" "<<numeric_values[i][max_index]<<endl;
    }

    // for(int i=0;i<values.size();i++){
    //     cout<<attributes[i].first<<" -> (";
    //     for(string val : values[i]){
    //         cout<<val<<",";
    //     }
    //     cout<<")"<<endl;
    // }

    // for(int i=0;i<numeric_values.size();i++){
    //     cout<<attributes[i].first<<" -> (";
    //     for(int j=0;j<numeric_values[i].size();j++){
    //         cout<<numeric_values[i][j]<<",";
    //     }
    //     cout<<")"<<endl;
    // }

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
    makeDecisionTree(dataset,attributes,values,numeric_values);
    
    return 0;
}