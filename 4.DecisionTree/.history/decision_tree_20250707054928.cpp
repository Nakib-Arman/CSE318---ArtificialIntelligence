#include <bits/stdc++.h>
using namespace std;

class Node {
    int column_num;
    string label;
    unordered_map<string, Node*> children;
    Node* parent;

public:
    Node(int column_num) {
        this->column_num = column_num;
        this->parent = nullptr;
        this->label = "";
    }

    Node(string label) {
        this->column_num = 0;
        this->label = label;
        this->parent = nullptr;
    }

    int getColumnNum() {
        return column_num;
    }

    string getLabel() {
        return label;
    }

    void setParent(Node* parent) {
        this->parent = parent;
    }

    void addChild(string edge, Node* child) {
        this->children[edge] = child;
    }

    void print() {
        cout << column_num << " -> ";
        for (auto& [val, node] : children) {
            cout << "(" << val << "," << node->getColumnNum() << "," << node->getLabel() << "), ";
        }
        cout << endl;
    }
};

// Better test for numeric
bool is_numeric(const string& str) {
    if (str.empty()) return false;
    char* endptr = nullptr;
    strtod(str.c_str(), &endptr);
    return (*endptr == '\0');
}

float getEntropy(const vector<vector<string>>& dataset, const unordered_set<string>& decisions) {
    if (dataset.empty()) return 0.0f;
    float entropy = 0;
    vector<string> decisions_vect(decisions.begin(), decisions.end());
    vector<int> count(decisions.size(), 0);

    for (const auto& row : dataset) {
        for (int j = 0; j < decisions_vect.size(); j++) {
            if (row.back() == decisions_vect[j]) {
                count[j]++;
            }
        }
    }

    for (int i = 0; i < count.size(); i++) {
        if (count[i] == 0) continue;
        float p = static_cast<float>(count[i]) / dataset.size();
        entropy -= p * log2(p);
    }
    return entropy;
}

float getInformationGain(const vector<vector<string>>& dataset, const unordered_set<string>& decisions, int attribute_num, const unordered_set<string>& values) {
    float ig = getEntropy(dataset, decisions);

    for (const string& value : values) {
        if (is_numeric(value)) {
            vector<vector<string>> temp1, temp2;
            for (const auto& row : dataset) {
                if (stof(row[attribute_num]) < stof(value))
                    temp1.push_back(row);
                else
                    temp2.push_back(row);
            }

            if (!temp1.empty())
                ig -= (static_cast<float>(temp1.size()) / dataset.size()) * getEntropy(temp1, decisions);
            if (!temp2.empty())
                ig -= (static_cast<float>(temp2.size()) / dataset.size()) * getEntropy(temp2, decisions);
        }
        else {
            vector<vector<string>> temp;
            for (const auto& row : dataset) {
                if (row[attribute_num] == value)
                    temp.push_back(row);
            }
            if (!temp.empty())
                ig -= (static_cast<float>(temp.size()) / dataset.size()) * getEntropy(temp, decisions);
        }
    }
    return ig;
}

Node* makeDecisionTree(vector<vector<string>> dataset, vector<pair<int, bool>> attributes, vector<unordered_set<string>> values, vector<vector<float>> numeric_values) {
    // Check if all decisions are the same
    bool all_same = true;
    string first_label = dataset[0].back();
    for (const auto& row : dataset) {
        if (row.back() != first_label) {
            all_same = false;
            break;
        }
    }
    if (all_same) {
        return new Node(first_label);
    }

    // Check if no attributes left to split on
    bool all_used = true;
    for (int i = 0; i < attributes.size() - 1; i++) {
        if (!attributes[i].second) {
            all_used = false;
            break;
        }
    }
    if (all_used) {
        // Majority vote
        unordered_map<string, int> label_count;
        for (const auto& row : dataset) {
            label_count[row.back()]++;
        }
        string majority_label;
        int max_count = 0;
        for (const auto& [label, count] : label_count) {
            if (count > max_count) {
                max_count = count;
                majority_label = label;
            }
        }
        return new Node(majority_label);
    }

    // Choose best attribute
    float max_ig = -1e9;
    int best_attr = -1;
    for (int i = 0; i < attributes.size() - 1; i++) {
        if (attributes[i].second) continue;
        float ig = getInformationGain(dataset, values.back(), i, values[i]);
        if (ig > max_ig) {
            max_ig = ig;
            best_attr = i;
        }
    }

    if (best_attr == -1) {
        // Fallback: majority vote
        unordered_map<string, int> label_count;
        for (const auto& row : dataset) {
            label_count[row.back()]++;
        }
        string majority_label;
        int max_count = 0;
        for (const auto& [label, count] : label_count) {
            if (count > max_count) {
                max_count = count;
                majority_label = label;
            }
        }
        return new Node(majority_label);
    }

    attributes[best_attr].second = true;
    Node* root = new Node(attributes[best_attr].first);

    for (const string& val : values[best_attr]) {
        vector<vector<string>> subset;
        vector<vector<float>> subset_numeric_values(numeric_values.size());
        vector<unordered_set<string>> new_values = values;

        if (is_numeric(val)) {
            vector<vector<string>> temp1, temp2;
            vector<vector<float>> num1(numeric_values.size()), num2(numeric_values.size());

            for (int i = 0; i < dataset.size(); i++) {
                if (stof(dataset[i][best_attr]) < stof(val)) {
                    temp1.push_back(dataset[i]);
                    for (int j = 0; j < numeric_values.size(); j++)
                        if (!numeric_values[j].empty())
                            num1[j].push_back(numeric_values[j][i]);
                }
                else {
                    temp2.push_back(dataset[i]);
                    for (int j = 0; j < numeric_values.size(); j++)
                        if (!numeric_values[j].empty())
                            num2[j].push_back(numeric_values[j][i]);
                }
            }

            if (!temp1.empty()) {
                for (int i = 0; i < num1.size(); i++) {
                    if (num1[i].empty()) continue;
                    new_values[i].clear();
                    float best_split_ig = -1e9;
                    int best_split_idx = 0;
                    for (int j = 0; j < temp1.size(); j++) {
                        new_values[i].insert(to_string(num1[i][j]));
                        float ig = getInformationGain(temp1, new_values.back(), i, new_values[i]);
                        if (ig > best_split_ig) {
                            best_split_ig = ig;
                            best_split_idx = j;
                        }
                        new_values[i].erase(to_string(num1[i][j]));
                    }
                    new_values[i].insert(to_string(num1[i][best_split_idx]));
                }
                Node* child1 = makeDecisionTree(temp1, attributes, new_values, num1);
                root->addChild("lt " + val, child1);
            }
            else {
                unordered_map<string, int> label_count;
                for (const auto& row : dataset) {
                    label_count[row.back()]++;
                }
                string majority_label;
                int max_count = 0;
                for (const auto& [label, count] : label_count) {
                    if (count > max_count) {
                        max_count = count;
                        majority_label = label;
                    }
                }
                root->addChild("lt " + val, new Node(majority_label));
            }

            if (!temp2.empty()) {
                for (int i = 0; i < num2.size(); i++) {
                    if (num2[i].empty()) continue;
                    new_values[i].clear();
                    float best_split_ig = -1e9;
                    int best_split_idx = 0;
                    for (int j = 0; j < temp2.size(); j++) {
                        new_values[i].insert(to_string(num2[i][j]));
                        float ig = getInformationGain(temp2, new_values.back(), i, new_values[i]);
                        if (ig > best_split_ig) {
                            best_split_ig = ig;
                            best_split_idx = j;
                        }
                        new_values[i].erase(to_string(num2[i][j]));
                    }
                    new_values[i].insert(to_string(num2[i][best_split_idx]));
                }
                Node* child2 = makeDecisionTree(temp2, attributes, new_values, num2);
                root->addChild("geq " + val, child2);
            }
            else {
                unordered_map<string, int> label_count;
                for (const auto& row : dataset) {
                    label_count[row.back()]++;
                }
                string majority_label;
                int max_count = 0;
                for (const auto& [label, count] : label_count) {
                    if (count > max_count) {
                        max_count = count;
                        majority_label = label;
                    }
                }
                root->addChild("geq " + val, new Node(majority_label));
            }
        }
        else {
            for (int i = 0; i < dataset.size(); i++) {
                if (dataset[i][best_attr] == val) {
                    subset.push_back(dataset[i]);
                    for (int j = 0; j < numeric_values.size(); j++)
                        if (!numeric_values[j].empty())
                            subset_numeric_values[j].push_back(numeric_values[j][i]);
                }
            }
            if (subset.empty()) {
                unordered_map<string, int> label_count;
                for (const auto& row : dataset) {
                    label_count[row.back()]++;
                }
                string majority_label;
                int max_count = 0;
                for (const auto& [label, count] : label_count) {
                    if (count > max_count) {
                        max_count = count;
                        majority_label = label;
                    }
                }
                root->addChild(val, new Node(majority_label));
            }
            else {
                for (int i = 0; i < subset_numeric_values.size(); i++) {
                    if (subset_numeric_values[i].empty()) continue;
                    new_values[i].clear();
                    float best_split_ig = -1e9;
                    int best_split_idx = 0;
                    for (int j = 0; j < subset.size(); j++) {
                        new_values[i].insert(to_string(subset_numeric_values[i][j]));
                        float ig = getInformationGain(subset, new_values.back(), i, new_values[i]);
                        if (ig > best_split_ig) {
                            best_split_ig = ig;
                            best_split_idx = j;
                        }
                        new_values[i].erase(to_string(subset_numeric_values[i][j]));
                    }
                    new_values[i].insert(to_string(subset_numeric_values[i][best_split_idx]));
                }
                Node* child = makeDecisionTree(subset, attributes, new_values, subset_numeric_values);
                root->addChild(val, child);
            }
        }
    }

    root->print();
    return root;
}

int main() {
    vector<vector<string>> dataset;
    vector<pair<int, bool>> attributes;

    ifstream file("adult.txt");
    string line;

    if (!file.is_open()) {
        cout << "File not found" << endl;
        return 1;
    }

    getline(file, line);
    stringstream ss(line);
    string attribute;
    int i = 1;
    while (getline(ss, attribute, ',')) {
        attributes.emplace_back(i, false);
        i++;
    }

    vector<unordered_set<string>> values(attributes.size());
    vector<vector<float>> numeric_values(attributes.size());

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> row;
        int i = 0;
        while (getline(ss, value, ',')) {
            row.push_back(value);
            if (!is_numeric(value))
                values[i].insert(value);
            else
                numeric_values[i].push_back(stof(value));
            i++;
        }
        dataset.push_back(row);
    }

    for (int i = 0; i < numeric_values.size(); i++) {
        if (numeric_values[i].empty()) continue;
    
        // Get unique sorted values
        set<float> unique_values(numeric_values[i].begin(), numeric_values[i].end());
        if (unique_values.size() <= 1) continue;
    
        vector<float> sorted_values(unique_values.begin(), unique_values.end());
        vector<float> candidate_splits;
    
        for (int k = 0; k < sorted_values.size() - 1; k++) {
            float mid = (sorted_values[k] + sorted_values[k+1]) / 2.0f;
            candidate_splits.push_back(mid);
        }
    
        float max_ig = -1e9;
        float best_split = sorted_values[0];
    
        for (float threshold : candidate_splits) {
            values[i].insert(to_string(threshold));
            float ig = getInformationGain(dataset, values.back(), i, values[i]);
            if (ig > max_ig) {
                max_ig = ig;
                best_split = threshold;
            }
            values[i].erase(to_string(threshold));
            cout<<i<<" "
        }
    
        values[i].insert(to_string(best_split));
    }
    

    makeDecisionTree(dataset, attributes, values, numeric_values);
    return 0;
}
