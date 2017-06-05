#include "include/ihm/gridview.h"

#include <QPainter>
#include <QMouseEvent>
#include <deque>
#include <iostream>
#include <topology/priorityfile.h>
#include <time.h>


GridView::GridView(QWidget *parent) :
    QOpenGLWidget(parent), m_grid(30,30),m_maxCost(100000)
{
    m_beginer = m_grid.get(0,m_grid.sy()/2);
    m_end = m_grid.get(m_grid.sx()-1,m_grid.sy()/2);

    //    for(int y=m_grid.sy()/3;y<m_grid.sy()-m_grid.sy()/3;y++){
    //        for(int x=5;x<29;x+=3)
    //            m_grid.get(x,y)->cout(m_maxCost);
    //    }

    for(int x=m_grid.sx()/3;x<m_grid.sx()-m_grid.sx()/3;x++){
        m_grid.get(x,m_grid.sy()/4)->weight(m_maxCost);
    }

    for(int y=m_grid.sy()/4;y<m_grid.sy()-m_grid.sy()/3;y++){
        m_grid.get(m_grid.sx()-m_grid.sx()/3,y)->weight(m_maxCost);
    }
}

GridView::~GridView()
{

}

void GridView::initializeGL(){
    QOpenGLWidget::initializeGL();

}

void GridView::paintEvent(QPaintEvent *e)
{
    makeCurrent();


    QPainter painter;
    painter.begin(this);

    painter.save();


    const float w = width();
    const float h = height();
    const int xSize = w/m_grid.sx();
    const int ySize = h/m_grid.sy();
    painter.fillRect(0,0,w,h, Qt::white);

    for(int x=0;x<m_grid.sx();x++)
        for(int y=0;y<m_grid.sy();y++){
            const int posx = x*xSize;
            const int posy = y*ySize;
            int cost = m_grid.get(x,y)->cout();

            if(m_grid.get(x,y)==m_end && m_end->cout()<=0){
                painter.fillRect(posx,posy,xSize,ySize, Qt::red);
                painter.drawEllipse(QPoint(posx+xSize/2,posy+ySize/2),xSize/4,ySize/4);
            }
            if(m_grid.get(x,y)==m_beginer){
                painter.fillRect(posx,posy,xSize,ySize, Qt::green);
                painter.drawEllipse(QPoint(posx+xSize/2,posy+ySize/2),xSize/4,ySize/4);
            }else if(cost == m_maxCost){
                painter.fillRect(posx,posy,xSize,ySize, QColor(50,50,50));
            }else if(m_grid.get(x,y)->inFilnalPath()){
                painter.fillRect(posx,posy,xSize,ySize, QColor(50,200,50));
            }else if(m_grid.get(x,y)->inCloseList()){
                painter.fillRect(posx,posy,xSize,ySize,Qt::red);
            }else if(m_grid.get(x,y)->inOpenList()){
                painter.fillRect(posx,posy,xSize,ySize, Qt::blue);
            }

            //            painter.fillRect(x*xSize,y*ySize,x*xSize+xSize,y*ySize+ySize, col);
            if(m_showHeuristique && m_grid.sx()*m_grid.sy()<50*50)
                painter.drawText(x*xSize+xSize/4,y*ySize+ySize/4,x*xSize+xSize,y*ySize+ySize,0,QString::number(int(m_grid.get(x,y)->heuristique())));


        }

    painter.setPen(QPen(Qt::black, 2));
    for(int x=0;x<=m_grid.sx();x++){
        painter.drawLine(x*xSize,0,x*xSize,m_grid.sy()*ySize);
    }
    for(int y=0;y<=m_grid.sy();y++){
        painter.drawLine(0,y*ySize,m_grid.sx()*xSize,y*ySize);
    }


    painter.restore();
    painter.end();
}

void GridView::setGrid(Grid g)
{
    m_grid = g;
}

void GridView::compute(const int sleepTime)//Node *begin, Node *end)
{
#define dist(x,y,a,b) (sqrtf((a-x)*(a-x)+(b-y)*(b-y)))
    std::vector<Node*> closedList;
    PriorityFile file;
    file.push(m_beginer);
    std::map<Node*, Node*> comFrom;

    while (!file.empty()) {
        if(sleepTime>0){
            repaint();
            Sleep(sleepTime);
        }
        Node* n = file.pop();
        if(m_end->x()==n->x() && m_end->y()==n->y()){
            std::cout << "End !" << std::endl;
            reconstructPath(comFrom,n);
            repaint();
            return;
        }
        for(Node* v : n->neighbors()){
            bool inOpen = false;
            bool costLess = v->cout() <= n->cout();
            if(costLess){
                bool inClose = false;
                for(Node* c : closedList){
                    if(c->x()==v->x() && c->y()==v->y()){
                        inClose = true;
                        break;
                    }
                }
                if(inClose)continue;
                for(Node* c : file){
                    if(c->x()==v->x() && c->y()==v->y()){
                        inOpen = true;
                        break;
                    }
                }
            }else{
                continue;
            }

            if(!inOpen){
                comFrom.insert(std::pair<Node*,Node*>(v,n));
                v->cout(n->cout()+dist(v->x(),v->y(),n->x(),n->y()));
                v->heuristique(v->cout()+dist(v->x(),v->y(),m_end->x(),m_end->y()));
                file.push(v);
                v->inOpenList(true);
            }
        }
        closedList.push_back(n);
        n->inCloseList(true);
    }
    std::cerr  << "error computing less cost path" << std::endl;
}


void GridView::reconstructPath(std::map<Node*, Node*> comFromMap, Node* current){
    Node* beg = current;
    while(comFromMap.find(beg)!=comFromMap.end()){
        beg->inFilnalPath(true);
        beg = comFromMap.at(beg);
    }
}


Node* GridView::getNodeFromMousePos(QPoint mPos){
    const float w = width();
    const float h = height();
    const int xSize = w/m_grid.sx();
    const int ySize = h/m_grid.sy();
    if(mPos.x()/xSize<m_grid.sx() && mPos.y()/ySize<m_grid.sy())
        return m_grid.get(mPos.x()/xSize, mPos.y()/ySize);
    return NULL;
}


void GridView::reset(const int nbx, const int nby){
    m_grid.newGrid(nbx, nby);
    m_beginer = m_grid.get(0,nby/2);
    m_end = m_grid.get(nbx-1,nby/2);
    repaint();
}
void GridView::clean(){
    m_grid.clean();
    repaint();
}

void GridView::mousePressEvent(QMouseEvent *e){
    Qt::MouseButton but = e->button();

}

void GridView::mouseMoveEvent(QMouseEvent *e){
    Qt::MouseButton but = e->button();
    QPoint mousePos = getMousePosition();
    Node* node = getNodeFromMousePos(mousePos);
    if(node){
        if(e->modifiers() & Qt::ControlModifier)
            node->weight(0);
        else
            node->weight(m_maxCost);
        repaint();
    }
}

void GridView::mouseReleaseEvent(QMouseEvent *e){
    Qt::MouseButton but = e->button();
    QPoint mousePos = getMousePosition();
    Node* node = getNodeFromMousePos(mousePos);
    if(node){
        if(e->modifiers() & Qt::ControlModifier)
            node->weight(0);
        else
            node->weight(m_maxCost);
        repaint();
    }
}
