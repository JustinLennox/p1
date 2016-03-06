#include "Order.h"
#include <fstream>
#include <iostream>

using namespace std;

Order::Order(const int orderNumber, const string &name, const string &item,const string &category, const string &shipArea){
    this->name = name;
    this->item = item;
    this->category = category;
    this->shipArea = shipArea;
    this->orderNumber = orderNumber;
}

string Order::orderString(){
    string orderString = "------------------------------\n";
    orderString += "Order Number: " + to_string(this->orderNumber) + "\n";
    orderString += "Name: " + this->name + "\n";
    orderString += "Item: " + this->item + "\n";
    orderString += "Ship To: " + this->shipArea + "\n";
    orderString += "------------------------------\n";
    return orderString;
}