#include "include/topology/node.h"

Node::Node(const int x, const int y):
    m_x(x),m_y(y),
    m_cout(0), m_heuristique(0),m_weight(0),
    m_inFilnalPath(false), m_inCloseList(false), m_inOpenList(false)
{

}

Node::Node(Node& n){
    m_x = n.m_x;
    m_y = n.m_y;
    m_cout = n.m_cout;
    m_heuristique = n.m_heuristique;
}

Node::~Node(){
    m_neighbor.clear();
}


void Node::addNeighbord(Node* n){
    m_neighbor.push_back(n);
}

void Node::reset(){
    m_cout = 0;
    m_heuristique = 0;
    m_weight = 0;
    m_inFilnalPath = false;
    m_inCloseList = false;
    m_inOpenList = false;
    m_neighbor.clear();
}


void Node::clean(){
    m_cout = 0;
    m_heuristique = 0;
    m_inFilnalPath = false;
    m_inCloseList = false;
    m_inOpenList = false;
}
