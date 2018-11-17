//
// Created by mateo on 28/10/18.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <list>
#include <vector>
#include <map>
#include <queue>
#include <cmath>

struct Point {
    float X, Y, Z;

    float distanceTo(const Point& b) const
    {
        float x = X - b.X;
        float y = Y - b.Y;
        float z = Z - b.Z;
        return ( std::sqrt(( x * x ) + ( y * y ) + ( z * z )));
    }
};

template<class V, class C>
class Graph {
public:
    typedef std::tuple<double, double, double> Point;

    Graph();
    virtual ~Graph();
    std::list<V> Preorder(V seed);
    std::list<V> Levels(V seed);
    long AddNode(V v);
    void AddArc(long a, long b, float c);
    bool HasArc(V a, V b);
    V GetNode(long a);
    long GetIndex(V a);
    double GetCost(V a, V b);
    std::vector<long> Dijkstra (long seed);
    double EuclideanDist( Point a, Point b);
    long Size();
    std::deque<long> Path(long a, long b);

protected:
    std::vector<V> m_Vertices;
    std::map<long, std::map<long, C>> m_Matrix;

};

#include "Graph.hxx"

#endif //GRAPH_GRAPH_H
