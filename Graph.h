//
// Created by shervitch on 2023/6/2.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "DSU.h"
#include<algorithm>

struct Edge {
    int from, to, w;
};

class Graph {
private:
    int N;
    vector<vector<Edge> > edges;
public:
    explicit Graph(int n) {
        this->N = n;
        edges.resize(n);
    }

    inline void addDirectedEdge(int from, int to, int w) {
        edges[from].push_back({from, to, w});
    }

    inline void addUndirectedEdge(int u, int v, int w) {
        addDirectedEdge(u, v, w);
        addDirectedEdge(v, u, w);
    }

    //Implemented by Kruskal algorithm
    vector<Edge> genMinimumSpanningTree() {
        vector<Edge> edgesCopy, tree;
        for (vector<Edge> &edgeVec: edges) {
            for (Edge edge: edgeVec) {
                edgesCopy.push_back(edge);
            }
        }
        sort(edgesCopy.begin(), edgesCopy.end(), [](Edge &e1, Edge &e2) {
            return e1.w < e2.w;
        });
        DSU dsu(N);
        for (auto &edge: edgesCopy) {
            if (dsu.union_(edge.from, edge.to)) {
                tree.push_back(edge);
            }
            if (tree.size() == N - 1) break;
        }
        return tree;
    }

    //Implemented by Kruskal algorithm
    int getMinimumSpanningTreeWeightSum() {
        int weights = 0;
        vector<Edge> edgesCopy, tree;
        for (vector<Edge> &edgeVec: edges) {
            for (Edge edge: edgeVec) {
                edgesCopy.push_back(edge);
            }
        }
        sort(edgesCopy.begin(), edgesCopy.end(), [](Edge &e1, Edge &e2) {
            return e1.w < e2.w;
        });
        DSU dsu(N);
        for (auto &edge: edgesCopy) {
            if (dsu.union_(edge.from, edge.to)) {
                weights += edge.w;
                tree.push_back(edge);
            }
            if (tree.size() == N - 1) break;
        }
        return weights;
    }
};

#endif //GRAPH_H
