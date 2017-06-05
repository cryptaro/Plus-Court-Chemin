#include <topology/grid.h>

Grid::Grid(const int nbx, const int nby):
    m_x(nbx),m_y(nby),
    m_includeDiag(false)
{
    for(int i=0;i<nbx;i++)
        for(int j=0;j<nbx;j++){
            m_grid.push_back(new Node(i,j));
        }
    computeNeighbor();
}

Grid::Grid(Grid &g)
{
    for(Node* n: m_grid){
        if(n)delete n;
    }
    m_grid.clear();

    m_x = g.m_x;
    m_y = g.m_y;
    m_includeDiag = g.m_includeDiag;
    for(int i=0;i<m_y*m_y;i++)
        m_grid.push_back(g.m_grid[i]);
    computeNeighbor();
}

Grid::~Grid(){
    for(Node* n: m_grid){
        if(n)delete n;
    }
    m_grid.clear();
}


Node* Grid::get(const int x, const int y)const{
    return m_grid[y*m_x+x];
}


void Grid::clean(){
    for(Node* n: m_grid){
        n->clean();
        n->resetNeighbors();
    }
    computeNeighbor();
}

void Grid::newGrid(const int nbx, const int nby){
    for(Node* n: m_grid){
        if(n)delete n;
    }
    m_grid.clear();

    m_x = nbx;
    m_y = nby;
    for(int i=0;i<nbx;i++)
        for(int j=0;j<nbx;j++){
            m_grid.push_back(new Node(i,j));
        }
    computeNeighbor();
}


void Grid::reset(const int nbx, const int nby){
    for(Node* n: m_grid){
        n->reset();
    }
    computeNeighbor();
}


void Grid::computeNeighbor(){
    for(int x=0;x<m_x;x++)
        for(int y=0;y<m_y;y++){
            if(x>0){
                get(x,y)->addNeighbord(get(x-1,y));
                if(m_includeDiag){
                    if(y>0)
                        get(x,y)->addNeighbord(get(x-1,y-1));
                    if(y<m_y-1)
                        get(x,y)->addNeighbord(get(x-1,y+1));
                }
            }
            if(x<m_x-1){
                get(x,y)->addNeighbord(get(x+1,y));
                if(m_includeDiag){
                    if(y>0)
                        get(x,y)->addNeighbord(get(x+1,y-1));
                    if(y<m_y-1)
                        get(x,y)->addNeighbord(get(x+1,y+1));
                }
            }
            if(y>0)
                get(x,y)->addNeighbord(get(x,y-1));
            if(y<m_y-1)
                get(x,y)->addNeighbord(get(x,y+1));
        }
}
