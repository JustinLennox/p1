#include "Queue.h"
#include <fstream>
#include <iostream>

using namespace std;

Queue::Queue(string category){
    this->category = category;
}

void Queue::enqueue(Order &order){
    if(this->headptr == nullptr){
        headptr = &order;
        tailptr = &order;
        order.previousNode = nullptr;
        order.nextNode = nullptr;
        queueCount = 1;
    }else{
        tailptr->nextNode = &order;
        order.previousNode = tailptr;
        order.nextNode = nullptr;
        tailptr = &order;
        queueCount++;
    }
}

Order & Queue::dequeue(void){
    if(tailptr != nullptr){
        Order *tailOrder = tailptr;
        tailptr = tailOrder->previousNode;
        this->queueCount -= 1;
        return *tailOrder;
    }else{
        Order *blankOrder = new Order();
        return *blankOrder;
    }
}


int Queue::queueSize(void){
    return queueCount;
}

