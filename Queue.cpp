#include "Queue.h"
#include <fstream>
#include <iostream>

using namespace std;

Queue::Queue(string category){
    this->category = category;
}

void Queue::enqueue(Order &order){
    if(this->headptr == nullptr){
        cout << "head ptr" << order.category << endl;
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
    
    cout << "Queue count: " << order.category << ":: " << queueCount;
    cout << "TailPTR: " << tailptr->item << endl;
}

Order & Queue::dequeue(void){
    cout << tailptr;
    if(tailptr != nullptr){
        cout << "TAILPTR !+ nullptr" << endl;
        Order *tailOrder = tailptr;
        tailptr = tailOrder->previousNode;
        this->queueCount -= 1;
        return *tailOrder;
    }else{
        cout << "TAILPTR == nullptr" << endl;
        Order *blankOrder = new Order();
        return *blankOrder;
    }
}


int Queue::queueSize(void){
    cout << "Queuecount: " << to_string(queueCount) << endl;
    return queueCount;
}

