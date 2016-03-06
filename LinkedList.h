/**
* LinkedList class
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Queue.h"
#include <string>

using namespace std;
// forward declaration of LinkedList

class LinkedList;

/**
* Represents a node in a doubly-linked list.
* A node represent a category of product in the store.
* Each node stores information about the number of orders
* in that category that needs to be dispatched.
*/

class Node {
	friend class LinkedList;
private:
    string category = "";   // The category of products in this node.
	Queue &orderQueue; // The order queue reference for this category.
	Node * previousNode = nullptr;
	Node * nextNode = nullptr;
public:
	int orderCount; // The number of orders in this node/category of product to dispatch.
	
	/**
	* Parameterized Constructor
	*/
    Node(Node * prev, Node * next, string cat, Queue &orderQueueRef) : orderQueue(orderQueueRef) {
        previousNode = prev;
        nextNode = next;
        category = cat;
        orderQueue = orderQueueRef;
        orderCount = orderQueueRef.queueSize();
    }
	
}; // Node

/**
* A doubly-linked list data structure.
*/

class LinkedList {
private:
	Node * headptr = nullptr;
    Node * tailptr = nullptr;
public:
    
    /**
     * Default Constructor
     */
    LinkedList() = default;
    
	int length = 0;
	
	/**
	* Adds an item to the end of this list.
	*
	* @param category The category of the queue, the node having this queue is being appended
	* @param orderQueue The queue this node will have
	*/
	void append(string category, Queue &orderQueue);


	/**
	* Returns the queue for a given category.
	* Use this to quickly get the required queues
	* for enqueue and dequque operations.
	* @param cat the category for the required queue. 
	*/
	Queue & getQueueByCat(string cat);

	/**
	* Sets the value of orderCount for the given category.
	*
	* @param cat the category name
	* @param count the numbe of orders to dispatch
	*/
	void setOrderCount(string cat, int count);
    
    Node getQueueNodeByCat(string cat);

	/**
	* Returns the number of elements in this list.
	*/
	const int size() const;

	/**
	* Returns whether or not this linked list is empty. 
	*/
	const bool empty() const {
		return size() == 0;
	} // empty
}; // LinkedList
#endif /** LINKED_LIST_H */
