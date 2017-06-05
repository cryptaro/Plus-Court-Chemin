#ifndef NODE_H
#define NODE_H

#include <vector>
#define PRECISION_NODE 100
class Node
{
public:
    Node(const int x, const int y);
    Node(Node& n);
    ~Node();

    inline int x(){return m_x;}
    inline int x(const int x){m_x = x;}
    inline int y(){return m_y;}
    inline int y(const int y){m_y = y;}
    inline float weight(){return m_weight;}
    inline void weight(const float weight){m_weight = int((weight)*PRECISION_NODE)/PRECISION_NODE;} // round to remove computation errors
    inline float cout(){return m_cout+m_weight;}
    inline void cout(const float cout){m_cout = int((cout-m_weight)*PRECISION_NODE)/PRECISION_NODE;} // round to remove computation errors
    inline float heuristique(){return m_heuristique;}
    inline void heuristique(const float h){m_heuristique = int(h*PRECISION_NODE)/PRECISION_NODE;}

    inline bool inFilnalPath(){return m_inFilnalPath;}
    inline bool inFilnalPath(bool b){m_inFilnalPath = b;}
    inline bool inOpenList(){return m_inOpenList;}
    inline bool inOpenList(bool b){m_inOpenList = b;}
    inline bool inCloseList(){return m_inCloseList;}
    inline bool inCloseList(bool b){m_inCloseList = b;}

    inline void resetNeighbors(){m_neighbor.clear();}

    bool operator<(Node& b){return m_heuristique<b.m_heuristique;}
    bool operator>(Node& b){return m_heuristique>b.m_heuristique;}
    bool operator<=(Node& b){return m_heuristique<=b.m_heuristique;}
    bool operator>=(Node& b){return m_heuristique>=b.m_heuristique;}

    inline std::vector<Node*> neighbors(){return m_neighbor;}
    void addNeighbord(Node* n);

    void reset(); // clear all params and removes neighbors
    void clean(); // clear computed modified params but keep neighbors and weight

private:
    int m_x, m_y;
    float m_cout, m_heuristique, m_weight;
    std::vector<Node*> m_neighbor;
    bool m_inFilnalPath, m_inCloseList, m_inOpenList;
};

#endif // NODE_H
