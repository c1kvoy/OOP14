#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <vector>

class Graph {
private:
    std::unordered_map<int, std::vector<std::vector<int>>> adjList;
public:
    Graph();
    Graph(const Graph &g);
    ~Graph();

    void addRoute(int from, int to, int cost);
    void removeByIndex(int idx);
    void removeAll();
    bool checkValue(int val) const ;
    void dijkstra(int from, int to) const;
    int getSize() const;


    bool operator==(const Graph &g) const;
    Graph operator&&(const Graph& other) const;
    std::vector<std::vector<int>> operator[](int idx) const;

    void graphFromFile(const std::string& filename);
    void graphToFile(const std::string& filename) const ;
};

#endif
