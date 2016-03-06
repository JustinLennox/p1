/**
 * Order class
 */

#ifndef _ORDER_H
#define _ORDER_H
#include <string>
using namespace std;

class Order {
	public:
	int orderNumber = -1;
    string name = "";
	string item = "";
    string category = "";
    string shipArea = "";
    
    Order *nextNode = nullptr;
    Order *previousNode = nullptr;
    
    string orderString(int orderNum);
	
	/**
    * Default Constructor
    */
    Order() = default;

	
	/**
	* Constructor
	*/
	Order(const int orderNumber, const string &name, const string &item,const string &category, const string &shipArea);
	
	/**
	* copy constructor
	*/
    Order(const Order &copied){
        this->orderNumber = copied.orderNumber;
        if(!copied.name.empty()){
            this->name = copied.name;
        }
        this->item = copied.item;
        this->category = copied.category;
        this->shipArea = copied.shipArea;
        this->nextNode = copied.nextNode;
        this->previousNode = copied.previousNode;
    }
	
	/**
	* copy operator
	*/
    Order & operator = (const Order &){
        return *this;
    }
	
	/**
//	* Destructor
//	*/
//    ~Order(void){
//        if(nextNode != nullptr){
//            nextNode->previousNode = nullptr;
//            nextNode->nextNode = nullptr;
//            delete nextNode;
//        }else{
//            delete nextNode;
//        }
//        if(previousNode != nullptr){
//            previousNode->previousNode = nullptr;
//            previousNode->nextNode = nullptr;
//            delete previousNode;
//        }else{
//            delete previousNode;
//        }
//    }
    
};

#endif 
