#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Graph::Graph() = default;
Graph::Graph(const Graph &g) : adjList(g.adjList) {}
Graph::~Graph() = default;


void Graph::addRoute(int from, int to, int cost) {
    for (const auto &route: adjList[from]) {
        if (route[0] == to && route[1] == cost) {
            return;
        }
    }
    adjList[to];
    adjList[from].push_back({to, cost});
}
void Graph::removeByIndex(int idx) {
    adjList.erase(idx);
    for (auto &pair: adjList) {
        auto &routes = pair.second;
        routes.erase(
            std::remove_if(routes.begin(), routes.end(), [idx](const std::vector<int> &route) {
                return route[0] == idx;
            }),
            routes.end()
        );
    }
}
void Graph::removeAll() {
    for (auto it = adjList.begin(); it != adjList.end(); ) {
        it = adjList.erase(it);
    }
}
bool Graph::checkValue(int val) const  {
    auto it = adjList.find(val);
    return it != adjList.end();
}
int Graph::getSize() const { return adjList.size(); }


std::vector<std::vector<int> > Graph::operator[](int idx) const {
    auto iter = adjList.find(idx);
    if (iter != adjList.end() && !iter->second.empty()) {
        return iter->second;
    }
    return {};
}
bool Graph::operator==(const Graph &g) const {
    return adjList == g.adjList;
}
Graph Graph::operator&&(const Graph &other) const {
    Graph intersection;
    for (const auto &pair: adjList) {
        int from = pair.first;
        for (const auto &route: pair.second) {
            int to = route[0];
            int cost = route[1];

            auto it = std::find_if(other.adjList.at(from).begin(), other.adjList.at(from).end(),
                                   [to, cost](const std::vector<int> &r) { return r[0] == to && r[1] == cost; });
            if (it != other.adjList.at(from).end()) {
                intersection.addRoute(from, to, cost);
            }
        }
    }
    return intersection;
}


void Graph::graphFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "open error" << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int from, to, cost;

        if (iss >> from >> to >> cost) {
            addRoute(from, to, cost);
        } else {
            std::cout << "error in string: " << line << std::endl;
        }
    }

    file.close();
}
void Graph::graphToFile(const std::string &filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "error opening" << std::endl;
        return;
    }
    for (const auto &pair: adjList) {
        int from = pair.first;
        for (const auto &route: pair.second) {
            int to = route[0];
            int cost = route[1];

            outFile << from << " " << to << " " << cost << std::endl;
        }
    }
    outFile.close();
}


void Graph::dijkstra(int from, int to) const {
    if (adjList.find(from) == adjList.end() || adjList.find(to) == adjList.end()) {
        std::cout << "invalid points" << std::endl;
        return;
    }

    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;
    std::unordered_map<int, bool> visited;

    for (const auto& pair : adjList) {
        dist[pair.first] = INT_MAX;
        visited[pair.first] = false;
    }
    dist[from] = 0;

    while (true) {
        int u = -1;
        int minDist = INT_MAX;
        for (const auto& pair : adjList) {
            int vertex = pair.first;
            if (!visited[vertex] && dist[vertex] < minDist) {
                u = vertex;
                minDist = dist[vertex];
            }
        }

        if (u == -1) break;

        visited[u] = true;
        for (const auto& neighbor : adjList.at(u)) {
            int v = neighbor[0];
            int cost = neighbor[1];
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                prev[v] = u;
            }
        }
    }

    if (dist[to] == INT_MAX) {
        std::cout << "No path" << std::endl;
        return;
    }

    std::vector<int> path;
    for (int current = to; current != from; current = prev[current]) {
        path.push_back(current);
    }
    path.push_back(from);

    std::cout << "Shortest path from " << from << " to " << to << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i + 1 != path.size()) std::cout << " -> ";
    }
    std::cout << "\nPath cost: " << dist[to] << std::endl;
}
