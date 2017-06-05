#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <topology/grid.h>

#include <QOpenGLWidget>
#include <QPoint>
#include <map>

class GridView : public QOpenGLWidget
{
    Q_OBJECT

private :
    Grid m_grid;
    Node* m_beginer, *m_end;
    int m_maxCost;
    bool m_showHeuristique;

public:
    explicit GridView(QWidget *parent = 0);
    ~GridView();

    void initializeGL();

    QPoint getMousePosition() const
    {
        QPoint tmp = QCursor::pos();
        tmp = mapFromGlobal(tmp);
        QPoint res(tmp.x(),tmp.y());
        return res;
    }

    Node* getNodeFromMousePos(QPoint mPos);

protected:

    void paintEvent(QPaintEvent *e);

    void setGrid(Grid g);

    void reconstructPath(std::map<Node*, Node*> comFromMap, Node* current);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    // should have done this in the Grid class
    void compute(const int sleepTime);//Node* begin=m_beginer, Node* end=m_end);
    void reset(const int nbx, const int nby);
    void clean();
    void includeDiag(const bool b){m_grid.includeDiag(b);}
    void showHeuristique(const bool b){m_showHeuristique = b;repaint();}

};

#endif // GRIDVIEW_H
