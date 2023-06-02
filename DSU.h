//
// Created by shervitch on 2023/6/2.
//

#ifndef DSU_H
#define DSU_H

#include<vector>

using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
public:
    explicit DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int index) {
        return index == parent[index] ? index : parent[index] = find(parent[index]);
    }

    bool union_(int u, int v) {
        int rootU = find(u), rootV = find(v);
        if (rootU == rootV) return false;
        else {
            if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else {
                parent[rootU] = rootV;
                ++rank[rootV];
            }
            return true;
        }
    }
};

#endif //DSU_H
