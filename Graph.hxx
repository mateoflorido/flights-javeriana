//
// Created by mateo on 28/10/18.
//

#include "Graph.h"
#include <deque>

template<class V, class C>
Graph<V, C>::Graph()
{
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
Graph<V, C>::~Graph()
{
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
double Graph<V, C>::
EuclideanDist(Graph<V, C>::Point a, Graph<V, C>::Point b)
{
    return (( std::get<0>(a) + std::get<0>(b)) * ( std::get<0>(a) + std::get<0>(b)) +
            ( std::get<1>(a) + std::get<1>(b)) * ( std::get<1>(a) + std::get<1>(b)) +
            ( std::get<2>(a) + std::get<2>(b)) * ( std::get<2>(a) + std::get<2>(b)));
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
long Graph<V, C>::GetIndex(V a)
{
    for (int i = 0; i < this->m_Vertices.size(); i++) {
        if ( this->m_Vertices[ i ] == a )
            return i;
    }
    return -1;
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
long Graph<V, C>::AddNode(V v)
{
    this->m_Vertices.push_back(v);
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
void Graph<V, C>::AddArc(long a, long b, float c)
{
    if ( a != -1 && b != -1 ) {
        this->m_Matrix[ a ][ b ] = c;
    }
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
bool Graph<V, C>::HasArc(V a, V b)
{
    int aIndex = GetIndex(a);
    int bIndex = GetIndex(b);

    if ( aIndex != -1 && bIndex != -1 ) {
        auto ItA = this->m_Matrix.find(aIndex);
        if ( ItA != this->m_Matrix.end()) {
            auto ItB = ItA->second.find(bIndex);
            if ( ItB != ItA->second.end())
                return true;
            else
                return false;
        }
        else
            return false;
    }
    return false;
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
V Graph<V, C>::GetNode(long a)
{
    return this->m_Vertices[ a ];
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
std::list<V> Graph<V, C>::Levels(V seed)
{
    std::list<V> res;
    std::vector<bool> marks(this->m_Vertices.size(), false);
    std::queue<int> q;
    int Index = GetIndex(seed);

    q.push(Index);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if ( marks[ node ] )
            continue;
        marks[ node ] = true;
        res.push_back(this->m_Vertices[ node ]);

        for (int i = 0; i < this->m_Vertices.size(); ++i) {
            if ( this->HasArc(this->m_Vertices[ node ], this->m_Vertices[ i ]))
                q.push(i);
        }
    }
    return res;
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
std::vector<long> Graph<V, C>::Dijkstra(long seed)
{

    typedef std::tuple<long,long, unsigned int> TNode;
    typedef std::map<long, std::map<long, unsigned int>>::iterator RowIterator;
    typedef std::map<long, unsigned int>::iterator ColIterator;

    struct {
        bool operator()(TNode a, TNode b)
        {
            return ( std::get<2>(b) < std::get<2>(a));
        }
    } cmp;

    std::vector<bool> marks(this->m_Vertices.size(), false); //Mark Nodes
    std::vector<long> mst(this->m_Vertices.size(), -1);
    TNode n(seed,seed, 0); // Seed
    std::vector<TNode> q; // Priority Queue

    q.push_back(n); // Seed PQ.
    std::make_heap(q.begin(), q.end(), cmp); //Make heap with PQ

    while (!q.empty()) {

        //std::make_heap(q.begin(), q.end(), cmp);
        std::pop_heap(q.begin(), q.end(), cmp); //Send min to back
        TNode current = q.back(); //Get min
        q.pop_back(); //Delete node from PQ

        if ( marks[ std::get<0>(current) ] ) //Check visited Node
        {
            continue;
        }

        //Path.push_back(std::get<0>(current)); //Add to path
        marks[ std::get<0>(current) ] = true; //Mark actual Node
        mst[ std::get<0>(current) ]=std::get<1>(current);//Add Parent

        RowIterator ItA = this->m_Matrix.find(std::get<0>(current)); // Iterator row
        if ( ItA != this->m_Matrix.end()){
            ColIterator ItB = ItA->second.begin(); // Iterator Column
            for (;ItB != ItA->second.end();ItB++) {
                /*if ( !marks[ ItB->first ] ) {
                    q.push_back(std::make_pair(ItB->first, ItB->second + std::get<1>(current)));
                    Path[ ItB->first ] = ItA->first;
                }*/
                TNode NewNode(ItB->first,std::get<0>(current),std::get<2>(current)+ItB->second);
                q.push_back(NewNode);
                std::push_heap(q.begin(),q.end(),cmp);
            }

        }
    }
    return mst;

}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
long Graph<V, C>::Size()
{
    return this->m_Vertices.size();
}

//------------------------------------------------------------------------------------------------------
template<class V, class C>
std::deque<long> Graph<V, C>::Path(long a, long b)
{
    auto l = this->Dijkstra(a);
    std::deque<long> response;
    long pos = b;

    while (pos != l[pos]) {
        response.push_front(pos);
        pos = l[ pos ];
    }
    response.push_front(pos);

    return response;

}
template<class V, class C>
std::vector<long> Graph<V,C>::FloydWarshall(){
    typedef std::map<long, std::map<long, unsigned int>>::iterator RowIterator;
    typedef std::map<long, unsigned int>::iterator ColIterator;
    RowIterator ItR=this->m_Matrix.begin();
    std::vector<std::vector<long>(this->m_Vertices.size(),9223372036854775)> dist(this->m_Vertices.size(),9223372036854775);
    std::vector<std::vector<long>> next;
    for(int i=0;i<this->m_Vertices;i++){
        for(int j=0;j<this->m_Vertices;j++){
            if(this->m_Matrix.find(i)!=this->m_Matrix.end()){
                ItR=this->m_Matrix.find(i);
                if((*ItR).second.find(j)!=(*ItR).second.end()){
                    ColIterator ItC=(*ItR).second.find(j);
                    dist[i][j]=(*ItC).second;
                };
            }
        }
    }

}