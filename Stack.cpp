#include "Stack.h"
#include <iostream>
using namespace std;

void Stack::push(Order & order){
    
    if(tailptr == nullptr){
        headptr = &order;
        tailptr = &order;
        order.previousNode = nullptr;
        order.nextNode = nullptr;
        size = 1;
        top = size - 1;
    }else{
        tailptr->nextNode = &order;
        order.previousNode = tailptr;
        tailptr = &order;
        size++;
        top = size-1;
        
    }
}

Order & Stack::pop(void){
    if(tailptr != nullptr){
        Order poppedOrder = *tailptr;
        if(poppedOrder.previousNode != nullptr){
            poppedOrder.previousNode->nextNode = nullptr;
        }
        tailptr = poppedOrder.previousNode;
        return poppedOrder;
    }else{
        cout << "NULL POP";
        Order *newOrder = new Order();
        return *newOrder;
    }
}

