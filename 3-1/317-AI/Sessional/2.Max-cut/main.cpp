#include<bits/stdc++.h>
using namespace std;

int is_in_partition(int vertex, set<int> partition){
    return partition.find(vertex) != partition.end();
}


// Computing the potential increase in weight if the vertex is inserted in one of the partitions
int ComputeWeight(int vertex, set<int>& partition, unordered_map<int,vector<pair<int,int>>>& graph) {
    int total = 0;
    for (auto& [v, weight] : graph[vertex]) {
        if (partition.count(v)) {
            total += weight;
        }
    }
    return total;
}

// Calculating total cut weight given two final partitions
int CalculateCutWeight(unordered_map<int,vector<pair<int,int>>>& graph, set<int>& partition_x, set<int>& partition_y){
    int cut_weight=0;
    for(int u: partition_x){
        for(auto& [v,w] : graph[u]){
            if(partition_y.find(v) != partition_y.end()){
                cut_weight+=w;
            }
        }
    }
    return cut_weight;
}


//Algorithms


// Local search for the max cut
void LocalSearchMaxCut(int n, unordered_map<int,vector<pair<int,int>>>& graph, set<int>& partition_x, set<int>& partition_y){
    list<int> changed_partition_x,changed_partition_y;
    changed_partition_x.assign(partition_x.begin(),partition_x.end());
    changed_partition_y.assign(partition_y.begin(),partition_y.end());

    for (int i=1;i<=n;i++){
        if (is_in_partition(i,partition_x)){
            changed_partition_x.remove(i);
            int sigma_x = ComputeWeight(i,partition_y,graph);
            int sigma_y = ComputeWeight(i,partition_x,graph);
            if (sigma_x>sigma_y){
                changed_partition_x.push_back(i);
            }
            else{
                changed_partition_y.push_back(i);
            }
        }
        else if (is_in_partition(i,partition_y)){
            changed_partition_y.remove(i);
            int sigma_x = ComputeWeight(i,partition_y,graph);
            int sigma_y = ComputeWeight(i,partition_x,graph);
            if (sigma_x>sigma_y){
                changed_partition_x.push_back(i);
            }
            else{
                changed_partition_y.push_back(i);
            }
        }
    }
    set<int> new_partition_x,new_partition_y;
    new_partition_x.insert(changed_partition_x.begin(),changed_partition_x.end());
    new_partition_y.insert(changed_partition_y.begin(),changed_partition_y.end());
    partition_x = new_partition_x;
    partition_y = new_partition_y;
}

//Randomized heuristic for the max cut
int RandomizedMaxCut(unordered_map<int,vector<pair<int,int>>>& graph,int n){
    int total_cut_weight = 0;
    for (int i=1;i<=n;i++){
        set<int> partition_x;
        set<int> partition_y;
        for (int j=1;j<=n;j++){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(0,1);
            int probability = dist(gen);
            if (probability==1){
                partition_x.insert(j);
            }
            else{
                partition_y.insert(j);
            }
        }
        total_cut_weight+=CalculateCutWeight(graph,partition_x,partition_y);
    }
    int avg_cut_weight = total_cut_weight/n;
    return avg_cut_weight;
}

// Greedy heuristic for the max cut
pair<set<int>,set<int>> GreedyMaxCut(vector<pair<pair<int,int>,int>>& edges, int n, unordered_map<int,vector<pair<int,int>>>& graph){
    pair<pair<int,int>,int> max_edge=edges[0];
    for (int i=0;i<edges.size();i++){
        if (edges[i].second > max_edge.second){
            max_edge = edges[i];
        }
    }
    set<int> partition_x,partition_y;
    partition_x.insert(max_edge.first.first);
    partition_y.insert(max_edge.first.second);
    list<int> candidates;
    for (int i=1;i<=n;i++){
        candidates.push_back(i);
    }
    candidates.remove(max_edge.first.first);
    candidates.remove(max_edge.first.second);
    for (int i : candidates){
        int wx = ComputeWeight(i,partition_y,graph);
        int wy = ComputeWeight(i,partition_x,graph);
        if(wx>wy){
            partition_x.insert(i);
        }
        else{
            partition_y.insert(i);
        }
    }
    return make_pair(partition_x,partition_y);
}

// Semi greedy heuristic for the max cut
pair<set<int>,set<int>> SemiGreedyMaxCut(int n,unordered_map<int,vector<pair<int,int>>>& graph){
    set<int> partition_x, partition_y;
    list<int> candidates;

    for (int i = 1; i <= n; i++) {
        candidates.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    while (!candidates.empty()) {
        vector<int> rcl;
        int w_min = INT_MAX, w_max = INT_MIN;
        vector<int> greedy_values;
        greedy_values.push_back(0);

        for (int i : candidates) {
            int sigma_x = ComputeWeight(i, partition_y, graph);
            int sigma_y = ComputeWeight(i, partition_x, graph);
            int greedy_value = max(sigma_x, sigma_y);
            greedy_values.push_back(greedy_value);
            w_min = min(w_min, min(sigma_x, sigma_y));
            w_max = max(w_max, max(sigma_x, sigma_y));
        }

        float alpha = 0.5;
        float mu = w_min + alpha * (w_max - w_min);

        for (int i : candidates) {
            if (greedy_values[i] >= mu) {
                rcl.push_back(i);
            }
        }

        if (rcl.empty()) {
            rcl.assign(candidates.begin(), candidates.end());
        }

        uniform_int_distribution<> dist(0, rcl.size() - 1);
        int vertex = rcl[dist(gen)];

        int sigma_x = ComputeWeight(vertex, partition_y, graph);
        int sigma_y = ComputeWeight(vertex, partition_x, graph);

        if (sigma_x > sigma_y) {
            partition_x.insert(vertex);
        } else {
            partition_y.insert(vertex);
        }
        candidates.remove(vertex);
    }

    return make_pair(partition_x,partition_y);
}

// GRASP for the max cut
pair<set<int>,set<int>> GRASP(int maxiterations,int n, unordered_map<int,vector<pair<int,int>>>& graph){
    pair<set<int>,set<int>> final_partitions;
    int final_cut_weight=0;
    for (int i=1;i<=maxiterations;i++){
        pair<set<int>,set<int>> temp_partitions;
        temp_partitions = SemiGreedyMaxCut(n,graph);
        LocalSearchMaxCut(n,graph,temp_partitions.first,temp_partitions.second);
        int cut_weight = CalculateCutWeight(graph,temp_partitions.first,temp_partitions.second);
        if(i==1){
            final_partitions = temp_partitions;
            final_cut_weight = cut_weight;
        }
        else if (cut_weight>final_cut_weight){
            final_partitions = temp_partitions;
            final_cut_weight = cut_weight;
        }
    }
    return final_partitions;
}


int main()
{
    int n,m;
    cin>>n>>m;
    vector <pair<pair<int,int>,int>> edges;
    unordered_map<int, vector<pair<int, int>>> graph;

    for (int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        pair<pair<int,int>,int> state = make_pair(make_pair(u,v),w);
        edges.push_back(state);

        graph[u].emplace_back(make_pair(v,w));
        graph[v].emplace_back(make_pair(u,w));
    }

    // float avg_cut_weight = RandomizedMaxCut(graph,n);
    // cout<<avg_cut_weight<<endl;
    pair<set<int>,set<int>> temp;
    // temp = GreedyMaxCut(edges,n,graph);
    // cout<<CalculateCutWeight(graph,temp.first,temp.second)<<endl;
    // LocalSearchMaxCut(n,graph,temp.first,temp.second);
    // cout<<"After Local search: "<<CalculateCutWeight(graph,temp.first, temp.second);
    // temp = SemiGreedyMaxCut(n,graph);
    // cout<<CalculateCutWeight(graph,temp.first,temp.second)<<endl;
    // LocalSearchMaxCut(n,graph,temp.first,temp.second);
    // cout<<"After Local search: "<<CalculateCutWeight(graph,temp.first, temp.second);
    temp = GRASP(5,n,graph);
    cout<<CalculateCutWeight(graph,temp.first,temp.second);

    return 0;
}