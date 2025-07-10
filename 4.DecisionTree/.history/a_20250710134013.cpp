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
        if(children.find(edge) != children.end()){
            return children[edge];
        }
        return NULL;
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
    int start=0,end = str.size();
    while(str[start] == ' ') start++;
    while(str[end] == ' ') end--;
    return str.substr(start, end-start);
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
        float probability = static_cast <float> (count)/dataset_size;
        entropy -= (probability * log2(probability));
    }
    return entropy;
}

float getInformationGain(vector<vector<string>>& dataset, vector<unordered_set<string>>& values, unordered_map<string,int>& decisions,int attribute_num,float threshold=0)
{
    float ig= getEntropy(dataset.size(),decisions);
    if(is_digit(*values[attribute_num].begin())){
        int temp1_size=0,temp2_size=0;
        unordered_map<string,int>temp_decisions1,temp_decisions2;
        for(int i=0;i<dataset.size();i++){
            if(stof(dataset[i][attribute_num]) < threshold){
                temp1_size++;
                temp_decisions1[dataset[i][values.size()-1]]++;
            }
            else{
                temp2_size++;
                temp_decisions2[dataset[i][values.size()-1]]++;
            }
        }
        float entropy1 = getEntropy(temp1_size,temp_decisions1);
        float entropy2 = getEntropy(temp2_size,temp_decisions2);
        ig -= (static_cast <float> (temp1_size)/dataset.size())*entropy1;
        ig -= (static_cast <float> (temp2_size)/dataset.size())*entropy2;
    }
    else{
        for(string value : values[attribute_num]){
            int temp=0;
            unordered_map<string,int> temp_decisions;
            for(int i=0;i<dataset.size();i++){
                if(dataset[i][attribute_num] == value){
                    temp++;
                    temp_decisions[dataset[i][values.size()-1]]++;
                }
            }
            float entropy = getEntropy(temp,temp_decisions);
            ig -= (static_cast <float> (temp)/dataset.size())*entropy;
        }
    }
    return ig;
}

void calculateMaxThreshold(vector<vector<string>>& dataset,vector<unordered_set<string>>& values,unordered_map<string,int>& decisions,vector<pair<float,bool>>& used)
{
    for(int i=0;i<values.size();i++){
        if(!is_digit(*values[i].begin())) continue;
        float max_ig = INT_MIN;
        float max_threshold = 0;
        int j = 0;
        for(string val: values[i]){
            float ig = getInformationGain(dataset,values,decisions,i,stof(val));
            if(ig>max_ig){
                max_ig = ig;
                max_threshold = stof(val);
            }
            cout<<i<<" "<<j<<endl;
            j++;
        }
        used[i].first = max_threshold;
    }
}


Node* makeDecisionTree(vector<vector<string>>& dataset, vector<unordered_set<string>>& values, unordered_map<string,int>& decisions,vector<pair<float,bool>>& used,int depth)
{   
    int count = 0;
    for(auto& [val,cnt] : decisions){
        if(cnt>0) count++;
    }
    if(count == 1){
        return new Node(dataset[0][dataset[0].size()-1]);
    }
    count = 0;
    for(int i=0;i<used.size();i++){
        if(!used[i].second){
            count++;
        }
    }
    if(count == 1){
        int max_count = 0;
        string label;
        for(auto& [val,cnt] : decisions){
            if(cnt>max_count){
                max_count = cnt;
                label = val;
            }
        }
        return new Node (label);
    }
    if(depth == 0){
        int max_count = 0;
        string label;
        for(auto& [val,cnt] : decisions){
            if(cnt>max_count){
                max_count = cnt;
                label = val;
            }
        }
        return new Node (label);
    }

    float max_ig = INT_MIN;
    int max_i=0;
    for (int i=0;i<used.size()-1;i++){
        if(used[i].second){
            continue;
        }
        float temp = 0;
        float ig = getInformationGain(dataset,values,decisions,i,used[i].first);
        if(ig>max_ig){
            max_ig = ig;
            max_i = i;
        }
    }
    bool check = false;
    for(string val : values[max_i]){
        if(is_digit(val)) check = true;
        break;
    }
    if(!check) used[max_i].second = true;
    cout<<max_i+1<<" selected"<<endl;
    Node* root = new Node(max_i+1);
    for(string val: values[max_i]){
        cout<<val<<endl;
        if(is_digit(val)){
            vector<vector<string>> temp_dataset1,temp_dataset2;
            unordered_map<string,int> temp_decisions1,temp_decisions2;
            vector<unordered_set<string>> temp_values1(used.size()),temp_values2(used.size());
            for(int i=0;i<dataset.size();i++){
                if(stof(dataset[i][max_i]) < used[max_i].first){
                    temp_dataset1.push_back(dataset[i]);
                    temp_decisions1[dataset[i][values.size()-1]]++;
                    for(int j=0;j<dataset[i].size();j++){
                        temp_values1[j].insert(dataset[i][j]);
                    }
                }
                else{
                    temp_dataset2.push_back(dataset[i]);
                    temp_decisions2[dataset[i][values.size()-1]]++;
                    for(int j=0;j<dataset[i].size();j++){
                        temp_values2[j].insert(dataset[i][j]);
                    }
                }
            }
            int max_count = 0;
            string label;
            for(auto& [value,cnt] : decisions){
                if(cnt>max_count){
                    max_count = cnt;
                    label = value;
                }
            }
            string curr_thresh = to_string(used[max_i].first);
            if(temp_dataset1.size() == 0) {
                root->addChild("lt "+to_string(used[max_i].first),new Node (label));
            }
            else{
                calculateMaxThreshold(temp_dataset1,temp_values1,temp_decisions1,used);
                Node* child1 = makeDecisionTree(temp_dataset1,temp_values1,temp_decisions1,used,depth-1);
                root->addChild("lt "+curr_thresh,child1);
            }
            if(temp_dataset2.size() == 0){
                root->addChild("geq "+to_string(used[max_i].first),new Node (label));
            }
            else{
                calculateMaxThreshold(temp_dataset2,temp_values2,temp_decisions2,used);
                Node* child2 = makeDecisionTree(temp_dataset2,temp_values2,temp_decisions2,used,depth-1);
                root->addChild("geq "+curr_thresh,child2);
            }
            break;
        }
        else{
            vector<vector<string>> temp_dataset;
            unordered_map<string,int> temp_decisions;
            vector<unordered_set<string>> temp_values(used.size());
            cout<<dataset.size()<<endl;
            for(int i=0;i<dataset.size();i++){
                cout<<val<<" "<<dataset[i][max_i]<<endl;
                if(dataset[i][max_i] == val){
                    temp_dataset.push_back(dataset[i]);
                    temp_decisions[dataset[i][values.size()-1]]++;
                    for(int j=0;j<dataset[i].size();j++){
                        temp_values[j].insert(dataset[i][j]);
                    }
                } 
            }
            cout<<temp_dataset.size()<<endl;
            calculateMaxThreshold(temp_dataset,temp_values,temp_decisions,used);
            Node* child = makeDecisionTree(temp_dataset,temp_values,temp_decisions,used,depth-1);
            root->addChild(val,child);
        }
    }
    root->print();
    used[max_i].second = false;
    return root;
}


string testDecisionTree(Node* root,vector<string>& data)
{
    while(root->getLabel() == ""){
        if(root->getThreshold() == 0){
            string edge = data[root->getColumnNum()-1];
            root = root->getChild(edge);
            if(root == NULL) return "";
        }
        else{
            float threshold = root->getThreshold();
            float edge = stof(data[root->getColumnNum()-1]);
            if(edge < threshold) {
                root = root->getChild("lt "+to_string(threshold));
                if(root == NULL) return "";
            }
            else{
                root = root->getChild("geq "+to_string(threshold));
                if(root == NULL) return "";
            }
        }
    }
    return root->getLabel();
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
    vector<vector<string>> test_data;
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

    random_device rd;
    mt19937 gen(rd());
    int j = 0;
    while(getline(file,line)) {
        uniform_int_distribution<> dist(1,5);
        int p = dist(gen);
        stringstream ss(line);
        string val;
        vector<string> row;
        if(p<5){
            int i=0;
            int count = 0;
            while(getline(ss,val,',')){
                string value = trim(val);
                if(value == "?") count++;
                row.push_back(value);
                values[i].insert(value);
                if(i==values.size()-1){
                    decisions[value]++;
                }
                i++;
            }
            if(count == 0) dataset.push_back(row);
        }
        else{
            int count = 0;
            while(getline(ss,val,',')){
                string value = trim(val);
                if(value == "?") count++;
                row.push_back(value);
            }
            if(count == 0) test_data.push_back(row);
        }
        j++;
    }

    calculateMaxThreshold(dataset,values,decisions,used);
    
    // for(int i=0;i<used.size();i++){
    //     cout<<used[i].first<<endl;
    // }
    Node* root = makeDecisionTree(dataset,values,decisions,used,5);
    int count = 0;
    // cout<<testDecisionTree(root,test_data[0])<<endl;
    for(int i=0;i<test_data.size();i++){
        // vector<string> data = dataset[i];
        // cout<<i+2<<" "<<testDecisionTree(root,data)<<endl;
        if(testDecisionTree(root,test_data[i]) == test_data[i][used.size()-1]){
            count++;
        }
    }
    cout<<static_cast<float>(count)/test_data.size()<<endl;
    
    return 0;
}