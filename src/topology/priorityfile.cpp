#include "include/topology/priorityfile.h"

PriorityFile::PriorityFile()
{

}

PriorityFile::~PriorityFile(){
    file.clear();
}


void PriorityFile::push(Node* n){
    std::vector<Node*>::iterator it = file.begin();
    for( ;it!=file.end();it++){
        if( (*(*it)<(*n)) ){
            break;
        }
    }
    file.insert(it,n);
}

Node* PriorityFile::pop(){
    Node* n = file.back();
    file.pop_back();
    return n;
}
