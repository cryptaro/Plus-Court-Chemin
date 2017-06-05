#include "ihm/mainwindow.h"
#include <QApplication>
#include <topology/priorityfile.h>
#include <iostream>

int main(int argc, char *argv[])
{

//    PriorityFile file;
//    Node* n1 = new Node(0,0);
//    Node* n2 = new Node(0,0);
//    n2->heuristique(5);
//    Node* n3 = new Node(0,0);
//    n3->heuristique(3);
//    Node* n4 = new Node(0,0);
//    n4->heuristique(6);
//    file.push(n4);
//    file.push(n2);
//    file.push(n3);
//    file.push(n1);

//    while (!file.empty()) {
//        std::cout << file.pop()->heuristique() <<std::endl;
//    }
//    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
