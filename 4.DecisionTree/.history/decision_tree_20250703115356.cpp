#include<bits/stdc++.h>
using namespace std;

int getEntropy(int attributes, vector<int> top, vector<int> bottom)
{
    int entropy=0;
    for (int i=0;i<attributes;i++){
        float p = static_cast<float> (top[i])/bottom[i];
        entropy -= log2(p) * p;
    }
}

int main()
{
    vector<vector<string>>
}