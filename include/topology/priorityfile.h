#ifndef PRIORITYFILE_H
#define PRIORITYFILE_H

#include<topology/node.h>
#include <vector>

class PriorityFile
{
private:
    std::vector<Node*> file;
public:
    PriorityFile();
    ~PriorityFile();

    void push(Node* n);
    Node* pop();
    inline bool empty(){return file.empty();}

    std::vector<Node*>::iterator begin(){return file.begin();}
    std::vector<Node*>::iterator end(){return file.end();}
};

#endif // PRIORITYFILE_H
