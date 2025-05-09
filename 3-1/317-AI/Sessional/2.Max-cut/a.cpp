#include<bits/stdc++.h>
using namespace std;

int ComputeWeightFast(int vertex, const set<int>& other_partition, const unordered_map<int, vector<pair<int, int>>>& adj) {
    int total = 0;
    for (auto& [neighbor, weight] : adj.at(vertex)) {
        if (other_partition.count(neighbor)) {
            total += weight;
        }
    }
    return total;
}

// Calculating total cut weight given two final partitions
int CalculateCutWeight(unordered_map<int,vector<pair<int,int>>> graph, set<int> partition_x, set<int> partition_y){
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

void SemiGreedyMaxCut(vector<pair<pair<int,int>,int>> edges, int n, unordered_map<int,vector<pair<int,int>>> adj){
    set<int> partition_x, partition_y;
    list<int> candidates;
    // unordered_map<int, vector<pair<int, int>>> adj;

    // Preprocessing
    // for (auto& edge : edges) {
    //     int u = edge.first.first;
    //     int v = edge.first.second;
    //     int w = edge.second;
    //     adj[u].emplace_back(v, w);
    //     adj[v].emplace_back(u, w);
    // }

    for (int i = 1; i <= n; i++) {
        candidates.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());

    while (!candidates.empty()) {
        vector<int> rcl;
        int w_min = INT_MAX, w_max = INT_MIN;
        vector<int> greedy_values;
        vector<int> vertex_list(candidates.begin(), candidates.end());

        for (int j : vertex_list) {
            int sigma_x = ComputeWeightFast(j, partition_y, adj);
            int sigma_y = ComputeWeightFast(j, partition_x, adj);
            int greedy_value = max(sigma_x, sigma_y);
            greedy_values.push_back(greedy_value);
            w_min = min(w_min, min(sigma_x, sigma_y));
            w_max = max(w_max, max(sigma_x, sigma_y));
        }

        float alpha = 0.5;
        float mu = w_min + alpha * (w_max - w_min);

        for (int i = 0; i < vertex_list.size(); ++i) {
            if (greedy_values[i] >= mu) {
                rcl.push_back(vertex_list[i]);
            }
        }

        if (rcl.empty()) {
            rcl = vertex_list;
        }

        uniform_int_distribution<> dist(0, rcl.size() - 1);
        int vertex = rcl[dist(gen)];

        int sigma_x = ComputeWeightFast(vertex, partition_y, adj);
        int sigma_y = ComputeWeightFast(vertex, partition_x, adj);

        if (sigma_x > sigma_y) {
            partition_x.insert(vertex);
        } else {
            partition_y.insert(vertex);
        }
        candidates.remove(vertex);
        cout<<vertex<<endl;
    }

    int temp = CalculateCutWeight(adj, partition_x, partition_y);
    cout << temp << endl;
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

    SemiGreedyMaxCut(edges,n,graph);

    return 0;
}