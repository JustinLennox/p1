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

string *categoriesPointer;
int categoriesLength = 0;
string *ordersPointer;
int ordersLength = 0;
string *dispatchPointer;
int dispatchLength = 0;
string *dispatchCategoriesPointer;
string dispatchCategoriesArray[1000];
int dispatchCategoriesLength = 0;

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
    for(int i = (int)dispatchCategoriesLength - 1; i >= 0; i--){
        dispatchOrder(*queueList, *(dispatchCategoriesPointer+i));
    }
    printLabel(*orderStack);
    
    return EXIT_SUCCESS;
}

void parseInputFile(ifstream& inputFile){
    string line;
    bool readingCategories = false;
    string categoryArray[1000];
    categoriesPointer = categoryArray;
    bool readingOrders = false;
    string orderArray[1000];
    ordersPointer = orderArray;
    bool readingDispatch = false;
    string dispatchArray[1000];
    dispatchPointer = dispatchArray;
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
            categoryArray[categoriesLength] = line;
            categoriesLength++;
        }else if(readingOrders){
            orderArray[ordersLength] = line;
            ordersLength++;
        }else if(readingDispatch){
            dispatchArray[dispatchLength] = line;
            dispatchLength++;
        }
    }
    inputFile.close();
    
    queueList = new LinkedList();
    
    for(int i = 0; i < categoriesLength; i++){
        createQueueWithCategory(*(categoriesPointer + i));
    }
    
    for(int i = 0; i < ordersLength; i++){
        parseOrderFromString(i+1, *(ordersPointer + i));
    }
    
    for(int i = 0; i < dispatchLength; i++){
        parseDispatchFromString(*(dispatchPointer + i));
    }
    for(int i = 0; i < categoriesLength; i++){
        Queue tempQueue = queueList->getQueueByCat(*(categoriesPointer + i));
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
    dispatchCategoriesPointer = dispatchCategoriesArray;
    int numberOfItemsToDispatch = 0;
    
    for(int i = 0; i < 2; i++){
        getline(dispatchStream, dispatchSection, ' ');
        dispatchSection = dispatchSection.erase(dispatchSection.find_last_not_of("\n\r") + 1);
        if(i == 0){
            categoryName = dispatchSection;
            dispatchCategoriesArray[dispatchCategoriesLength] = categoryName;
            dispatchCategoriesLength++;
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
    if(outputFile.good()){
        for(int i = 0; i < myStack.size; i++){
            outputFile << myStack.pop().orderString();
        }
    }
}

