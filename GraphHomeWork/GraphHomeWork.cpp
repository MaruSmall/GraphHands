#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
    // создаём объект
    Graph g;

    // добавляем вершины
    g.addVertex("Oleg");
    g.addVertex("Masha");
    g.addVertex("Sasha");
    g.addVertex("Klava");
    g.addVertex("Misha");
    g.addVertex("Dasha");
    g.addVertex("Leha");
    g.addVertex("Jeka");


    // добавляем ребра
    g.addEdge("Oleg", "Masha");
    g.addEdge("Masha", "Sasha");
    g.addEdge("Sasha", "Klava");
    g.addEdge("Misha", "Sasha");
    g.addEdge("Dasha", "Masha");
    g.addEdge("Masha", "Jeka");
    g.addEdge("Leha", "Klava");
    g.addEdge("Misha", "Jeka");
   
    
    


    g.traversal();

}


