#ifndef GRID_H
#define GRID_H

#include <vector>
#include <topology/node.h>

class Grid {
protected:
    int m_x,m_y;
    std::vector<Node*> m_grid;
    bool m_includeDiag;

public:
    Grid(const int nbx, const int nby);
    Grid(Grid& g);
    ~Grid();

    Node* get(const int x, const int y)const;

    void reset(const int nbx, const int nby);
    void clean();

    void newGrid(const int nbx, const int nby);

    inline int sx()const{return m_x;}
    inline int sy()const{return m_y;}

    void computeNeighbor();


    std::vector<Node*>::iterator begin(){return m_grid.begin();}
    std::vector<Node*>::iterator end(){return m_grid.end();}

    void includeDiag(const bool b){m_includeDiag = b;clean();}

};

#endif // GRID_H
