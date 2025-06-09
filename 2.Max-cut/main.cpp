#include<bits/stdc++.h>
#include "Algorithms.cpp"
using namespace std;

int main()
{
    ofstream csv_file("output.csv");
    if (!csv_file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    csv_file << ",Problem,,,Constructive algorithm,,Localsearch,,GRASP,,Known best solution\n";
    csv_file << "Name,|V| or n,|E| or m,Simple Randomized,Simple Greedy,Semi-greedy,No. of iterations,Average value,No.of iterations,Best value\n";
    int iterations = 50;
    vector<string> best_solutions = {"12078","12084","12077","N/A","N/A","N/A","N/A","N/A","N/A","N/A","627","621","645","3187","3169","3172","N/A","N/A","N/A","N/A","N/A","14123","14129","14131","N/A","N/A","N/A","N/A","N/A","N/A","N/A","1560","1537","1541","8000","7996","8009","N/A","N/A","N/A","N/A","N/A","7027","7022","7020","N/A","N/A","6000","6000","5988","N/A","N/A","N/A","N/A"};

    for(int k=1;k<=1;k++){
        string input_file = "graph_GRASP/set1/g"+to_string(k)+".rud";
        freopen(input_file.c_str(),"r",stdin);

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

        int random = RandomizedMaxCut(graph,n,iterations);
        pair<set<int>,set<int>> temp;
        temp = GreedyMaxCut(edges,n,graph);
        int greedy = CalculateCutWeight(graph,temp.first,temp.second);
        temp = SemiGreedyMaxCut(n,graph);
        int semi_greedy = CalculateCutWeight(graph,temp.first,temp.second);
        pair<int,int> temp2;
        temp2 = GRASP(iterations,n,graph);
        int local_search = temp2.first;
        int grasp = temp2.second;
        csv_file << "G"<<k<<","<<n<<","<<m<<","<<random<<","<<greedy<<","<<semi_greedy<<","<<iterations<<","<<local_search<<","<<iterations<<","<<grasp<<","<<best_solutions[k-1]<<"\n";
        cout<<"input "<<k<<" has been processed"<<endl;
    }

    return 0;
}