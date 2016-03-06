//
//  main.cpp
//  p1
//
//  Created by Justin Lennox on 2/25/16.
//  Copyright © 2016 Justin Lennox. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Order.h"
#include "Queue.h"
#include "Stack.h"

using std::ifstream;
using namespace std;

LinkedList *queueList;
Stack *orderStack = new Stack();

vector<string> categories;
vector<string> orders;
vector<string> dispatch;
vector<string> dispatchCategories;
void createQueueWithCategory(string categoryName);
void parseInputFile(ifstream& inputFile);
void parseOrderFromString(int orderNumber, string orderLine);
void addOrderToQueue(Order &orderToAdd);
void parseDispatchFromString(string dispatchLine);
void dispatchOrder(LinkedList &myList, string category);
void printLabel(Stack &myStack);

int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc < 2) {
        std::cerr << "Error: Please pass a text input file to parse." << std::endl;
    }else{
        ifstream inputFile;
        inputFile.open(argv[1]); // open a file
        
        if(inputFile.is_open()){
            parseInputFile(inputFile);
        }else{
            std::cerr << "Error: Couldn't open the input file." << std::endl;
        }
    }
    for(int i = (int)dispatchCategories.size() - 1; i >= 0; i--){
        dispatchOrder(*queueList, dispatchCategories.at(i));
    }
    printLabel(*orderStack);
    
    return EXIT_SUCCESS;
}

void parseInputFile(ifstream& inputFile){
    string line;
    bool readingCategories = false;
    bool readingOrders = false;
    bool readingDispatch = false;
    while(getline(inputFile, line))
    {
        line = line.erase(line.find_last_not_of("\n\r") + 1);
        if(line.compare("CATEGORIES") == 0){
            readingCategories = true;
            readingOrders = false;
            readingDispatch = false;
        }else if(line.compare("ORDERS") == 0){
            readingCategories = false;
            readingOrders = true;
            readingDispatch = false;
        }else if(line.compare("DISPATCH") == 0){
            readingCategories = false;
            readingOrders = false;
            readingDispatch = true;
        }else if(readingCategories){
            categories.push_back(line);
        }else if(readingOrders){
            orders.push_back(line);
        }else if(readingDispatch){
            dispatch.push_back(line);
        }
    }
    inputFile.close();
    
    queueList = new LinkedList();
    
    for(int i = 0; i < categories.size(); i++){
        createQueueWithCategory(categories.at(i));
    }
    
    for(int i = 0; i < orders.size(); i++){
        parseOrderFromString(i+1, orders.at(i));
    }
    
    for(int i = 0; i < dispatch.size(); i++){
        parseDispatchFromString(dispatch.at(i));
    }
    for(int i = 0; i < categories.size(); i++){
        Queue tempQueue = queueList->getQueueByCat(categories.at(i));
        cout << "TEMP QUEUE CATEGORY: " << tempQueue.category << endl;
        cout << "DEQUEUEING: " << tempQueue.dequeue().item << endl;
    }

}

void createQueueWithCategory(string categoryName){
    Queue *categoryQueue = new Queue(categoryName);
    queueList->append(categoryName, *categoryQueue);
}

void parseOrderFromString(int orderNumber, string orderLine){
    stringstream orderStream(orderLine);
    string orderSection;
    string name;
    string item;
    string category;
    string shipArea;
    
    for(int i = 0; i < 4; i++){
        getline(orderStream, orderSection, ',');
        if(i != 0){
            orderSection.erase(std::remove_if(orderSection.begin(), orderSection.end(), ::isspace), orderSection.end());
        }
        if(i == 0){
            name = orderSection;
        }else if(i == 1){
            item = orderSection;
        }else if(i == 2){
            category = orderSection;
        }else if(i == 3){
            shipArea = orderSection;
        }
    }
    Order *myOrder = new Order(orderNumber, name, item, category, shipArea);
    addOrderToQueue(*myOrder);
}

void parseDispatchFromString(string dispatchLine){
    stringstream dispatchStream(dispatchLine);
    string dispatchSection;
    string categoryName;
    int numberOfItemsToDispatch = 0;
    
    for(int i = 0; i < 2; i++){
        getline(dispatchStream, dispatchSection, ' ');
        dispatchSection = dispatchSection.erase(dispatchSection.find_last_not_of("\n\r") + 1);
        if(i == 0){
            categoryName = dispatchSection;
            dispatchCategories.push_back(categoryName);
        }else if(i == 1){
            numberOfItemsToDispatch = stoi(dispatchSection);
        }
    }
    queueList->setOrderCount(categoryName, numberOfItemsToDispatch);
}

void addOrderToQueue(Order &orderToAdd){
    queueList->getQueueByCat(orderToAdd.category).enqueue(orderToAdd);
}

void dispatchOrder(LinkedList &myList, string category){
    for(int j = 0; j < myList.getQueueNodeByCat(category).orderCount; j++){
        orderStack->push(myList.getQueueByCat(category).dequeue());
    }
}



void printLabel(Stack &myStack){
    ofstream outputFile("output.txt");
    cout << "Stack size: " << myStack.size;
    if(outputFile.good()){
        for(int i = 0; i < myStack.size; i++){
            outputFile << myStack.pop().orderString(i);
        }
    }
}

