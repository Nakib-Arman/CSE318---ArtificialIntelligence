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
        // if (count[i] == 0) continue;
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
            // if(j==1000) break;
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
        // vector<pair<string,int>> labels(values[values.size()-1].size());
        // int i=0;
        // for (auto& [val,cnt] : decisions){
        //     labels[i].first = val;
        //     labels[i].second = 0;
        //     for(int j=0;j<dataset.size();j++){
        //         if(dataset[j][dataset[j].size()-1] == val){
        //             labels[i].second++;
        //         }
        //     }
        //     i++;
        // }
        int max_count = 0;
        string label;
        // for(int i=0;i<labels.size();i++){
        //     if(labels[i].second>max_count){
        //         max_count = labels[i].second;
        //         max = i;
        //     }
        // }
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
        // if(values[i].size() == 1){
        //     for(string val:values[i]){
        //         temp = stof(val);
        //     }
        // }
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
        // cout<<val<<endl;
        // cout<<"hi"<<endl;
        // cout<<used[max_i].first<<endl;
        if(is_digit(val)){
            // cout<<used[max_i].first<<endl;
            vector<vector<string>> temp_dataset1,temp_dataset2;
            unordered_map<string,int> temp_decisions1,temp_decisions2;
            vector<unordered_set<string>> temp_values1(used.size()),temp_values2(used.size());
            // vector<vector<float>> temp_numeric_values1(numeric_values.size()),temp_numeric_values2(numeric_values.size());
            for(int i=0;i<dataset.size();i++){
                if(stof(dataset[i][max_i]) < used[max_i].first){
                    temp_dataset1.push_back(dataset[i]);
                    // for(int j=0;j<numeric_values.size();j++){
                    //     if(numeric_values[j].empty()) continue;
                    //     temp_numeric_values1[j].push_back(numeric_values[j][i]);
                    // }
                    temp_decisions1[dataset[i][values.size()-1]]++;
                    for(int j=0;j<dataset[i].size();j++){
                        temp_values1[j].insert(dataset[i][j]);
                    }
                }
                else{
                    temp_dataset2.push_back(dataset[i]);
                    // for(int j=0;j<numeric_values.size();j++){
                    //     if(numeric_values[j].empty()) continue;
                    //     temp_numeric_values2[j].push_back(numeric_values[j][i]);
                    // }
                    temp_decisions2[dataset[i][values.size()-1]]++;
                    for(int j=0;j<dataset[i].size();j++){
                        temp_values2[j].insert(dataset[i][j]);
                    }
                }
            }
            // cout<<temp_dataset1.size()<<" "<<temp_dataset2.size()<<endl;
            // vector<pair<string,int>> labels(values[values.size()-1].size());
            // int i=0;
            // for (string val : values[values.size()-1]){
            //     labels[i].first = val;
            //     labels[i].second = 0;
            //     for(int j=0;j<dataset.size();j++){
            //         if(dataset[j][dataset[j].size()-1] == val){
            //             labels[i].second++;
            //         }
            //     }
            //     i++;
            // }
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
                // for(int i=0;i<temp_numeric_values1.size();i++){
                //     if(temp_numeric_values1[i].empty()) continue;
                //     values[i].clear();
                //     float max_ig = INT_MIN;
                //     int max_index = 0;
                //     for(int j=0;j<temp_dataset1.size();j++){
                //         float ig = getInformationGain(temp_dataset1,values[values.size()-1],i,values[i],temp_numeric_values1[i][j]);
                //         if(ig>max_ig){
                //             max_ig = ig;
                //             max_index = j;
                //         }
                //     }
                //     values[i].insert(to_string(temp_numeric_values1[i][max_index]));
                // }
                // cout<<"before"<<endl;
                // for(int i=0;i<used.size();i++){
                //     cout<<used[i].first<<endl;
                // }
                calculateMaxThreshold(temp_dataset1,temp_values1,temp_decisions1,used);
                // cout<<"after"<<endl;
                // for(int i=0;i<used.size();i++){
                //     cout<<used[i].first<<endl;
                // }
                // for(int i=0;i<used.size();i++){
                //     cout<<used[i].first<<" "<<used[i].second<<endl;
                // }
                Node* child1 = makeDecisionTree(temp_dataset1,temp_values1,temp_decisions1,used,depth-1);
                root->addChild("lt "+curr_thresh,child1);
            }
            if(temp_dataset2.size() == 0){
                root->addChild("geq "+to_string(used[max_i].first),new Node (label));
            }
            else{
                // for(int i=0;i<temp_numeric_values2.size();i++){
                //     if(temp_numeric_values2[i].empty()) continue;
                //     values[i].clear();
                //     float max_ig = INT_MIN;
                //     int max_index = 0;
                //     for(int j=0;j<temp_dataset2.size();j++){
                //         float ig = getInformationGain(temp_dataset2,values[values.size()-1],i,values[i],temp_numeric_values2[i][j]);
                //         if(ig>max_ig){
                //             max_ig = ig;
                //             max_index = j;
                //         }
                //     }
                //     values[i].insert(to_string(temp_numeric_values2[i][max_index]));
                // }
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
            // vector<vector<float>> temp_numeric_values(numeric_values.size());
            for(int i=0;i<dataset.size();i++){
                if(dataset[i][max_i] == val){
                    temp_dataset.push_back(dataset[i]);
                    // for(int j=0;j<numeric_values.size();j++){
                    //     if(numeric_values[j].empty()) continue;
                    //     temp_numeric_values[j].push_back(numeric_values[j][i]);
                    // }
                    temp_decisions[dataset[i][values.size()-1]]++;
                    for(int j=0;j<dataset[i].size();j++){
                        temp_values[j].insert(dataset[i][j]);
                    }
                } 
            }
            // for(int i=0;i<temp_numeric_values.size();i++){
            //     if(temp_numeric_values[i].empty()) continue;
            //     values[i].clear();
            //     float max_ig = INT_MIN;
            //     int max_index = 0;
            //     for(int j=0;j<temp_dataset.size();j++){
            //         float ig = getInformationGain(temp_dataset,values[values.size()-1],i,values[i],temp_numeric_values[i][j]);
            //         if(ig>max_ig){
            //             max_ig = ig;
            //             max_index = j;
            //         }
            //     }
            //     values[i].insert(to_string(temp_numeric_values[i][max_index]));
            // }
            // for(int i=0;i<temp_dataset.size();i++){
            //     for(int j=0;j<temp_dataset[i].size();j++){
            //         cout<<temp_dataset[i][j]<<" ";
            //     }
            //     cout<<endl;
            // }
            // for(int i=0;i<temp_values.size();i++){
            //     for(string val: temp_values[i]) cout<<val<<" ";
            //     cout<<endl;
            // }
            // for(auto& [val,cnt] : temp_decisions){
            //     cout<<val<<" "<<cnt;
            // }
            // for(int i=0;i<used.size();i++){
            //     cout<<used[i].first<<" "<<used[i].second<<endl;
            // }
            // string curr_thresh = to_string(used[max_i].first);
            cout<<"hi"
            calculateMaxThreshold(temp_dataset,temp_values,temp_decisions,used);
            // for(int k=0;k<used.size();k++){
            //     cout<<used[k].first<<" "<<used[k].second<<endl;
            // }
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
        }
        else{
            float threshold = root->getThreshold();
            float edge = stof(data[root->getColumnNum()-1]);
            if(edge < threshold) {
                root = root->getChild("lt "+to_string(threshold));
            }
            else{
                root = root->getChild("geq "+to_string(threshold));
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
        string value;
        vector<string> row;
        if(p<5){
            int i=0;
            int count = 0;
            while(getline(ss,value,',')){
                if(value == "?") count++;
                row.push_back(value);
                values[i].insert(trim(value));
                if(i==values.size()-1){
                    decisions[value]++;
                }
                i++;
            }
            if(count == 0) dataset.push_back(row);
        }
        else{
            int count = 0;
            while(getline(ss,value,',')){
                if(value == "?") count++;
                row.push_back(value);
            }
            if(count ==0) test_data.push_back(row);
        }
        j++;
        if(j==1000) break;
    }

    calculateMaxThreshold(dataset,values,decisions,used);
    
    // for(int i=0;i<used.size();i++){
    //     cout<<used[i].first<<endl;
    // }
    Node* root = makeDecisionTree(dataset,values,decisions,used,5);
    int count = 0;
    for(int i=0;i<test_data.size();i++){
        // vector<string> data = dataset[i];
        // cout<<i+2<<" "<<testDecisionTree(root,data)<<endl;
        if(testDecisionTree(root,test_data[i]) == test_data[i][used.size()-1]){
            count++;
        }
    }
    cout<<static_cast<float>(count)/test_data.size();
    
    return 0;
}