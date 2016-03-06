#include "LinkedList.h"
#include <fstream>
#include <iostream>

using namespace std;

void LinkedList::append(string category, Queue &orderQueue){
    if(this->headptr == nullptr){
        Node *firstNode = new Node(nullptr, nullptr, category, orderQueue);
        headptr = firstNode;
        tailptr = firstNode;
        length = 1;
    }else{
        Node *appendedNode = new Node(tailptr, nullptr, category, orderQueue);
        tailptr->nextNode = appendedNode;
        tailptr = appendedNode;
        length++;
    }
}

Queue & LinkedList::getQueueByCat(string cat){
    Node *searchedNode = headptr;
    while(searchedNode != nullptr){
        if(searchedNode->category.compare(cat) == 0){
            return searchedNode->orderQueue;
        }else{
            searchedNode = searchedNode->nextNode;
        }
    }
    cout << "REturning epty node" << endl;
    Queue *emptyQueue = new Queue();
    return *emptyQueue;
}

Node LinkedList::getQueueNodeByCat(string cat){
    Node *searchedNode = headptr;
    while(searchedNode != nullptr){
        if(searchedNode->category.compare(cat) == 0){
            return *searchedNode;
        }else{
            searchedNode = searchedNode->nextNode;
        }
    }
    
    return *searchedNode;
}

void LinkedList::setOrderCount(string cat, int count){
    Node *searchedNode = headptr;
    while(searchedNode != nullptr){
        if(searchedNode->category.compare(cat) == 0){
            searchedNode->orderCount = count;
            break;
        }else{
            searchedNode = searchedNode->nextNode;
        }
    }
}

const int LinkedList::size() const{
    return length;
}

