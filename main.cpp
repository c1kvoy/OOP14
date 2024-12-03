#include <iostream>
#include "graph.h"
#include <cassert>


int main() {
    // тут тест взятия из файлов и тест оператора []
    Graph graph;
    graph.graphFromFile("input.txt");
    std::vector<std::vector<int> > expected = {{4, 7}};
    assert(graph[2] == expected);


    // тут тест оператора == и remove
    Graph graph2;
    graph2.addRoute(2, 4, 7);
    graph2.addRoute(1, 2, 3);
    graph2.addRoute(5, 2, 3);
    graph2.removeByIndex(1);
    assert(graph==graph2);
    assert(graph2.checkValue(2)==true);
    assert(graph2.checkValue(1)==false);

    // тут тест оператора &&
    graph2.addRoute(1, 2, 3);
    Graph graph3 = graph && graph2;
    assert(graph == graph3);

    //тут тест выгрузки в файл
    graph3.graphToFile("output.txt");


    Graph graph4;
    graph4.graphFromFile("output.txt");
    assert(graph4 == graph3);

    // проверка removeAll
    graph4.removeAll();
    graph3.removeAll();
    std::vector<std::vector<int> > expected2 = {{2, 3}};
    assert(graph4[2] != expected);
    assert(graph4[5] != expected2);
    assert(graph4 == graph3);

    //тут тест дийкстры
    Graph diGraph;
    diGraph.addRoute(1,2,2);
    diGraph.addRoute(1,3,6);
    diGraph.addRoute(2,3,3);
    diGraph.addRoute(2,4,5);
    diGraph.addRoute(3,4,1);
    diGraph.dijkstra(1,4);

    return 0;
}
