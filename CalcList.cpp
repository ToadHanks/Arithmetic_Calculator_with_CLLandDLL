/*
	Author of this file:		Mihir K Patel
	Purpose:			Following is a source file for CalcList.hpp. It implements the definitions for
					constructors and destructors and abstract functions.

*/
#include "CalcList.hpp"

/*Constructor that makes a cursor node object*/
CalcList::CalcList() :CalcListInterface() { 
	cursor = new CalcNode;
	cursor->nodes_operator = ADDITION;
	cursor->nodes_operand = 0.0;
	cursor->nodes_total = 0.0;
	cursor->next = cursor;
}
/*Destroys the CalcList objects*/
CalcList::~CalcList() {
	while (!is_empty()) { remove_node(); } /*Recursive call*/
}
/*Adds a node in the beginning*/
void CalcList::add_node(const double& element_para) {
	++steps;/*Increment the operation counter*/
	CalcNode* before_crsr = new CalcNode; /*Temprory node which will get added in beginning*/

	before_crsr->next = nullptr;
	before_crsr->nodes_total = 0.0;
	before_crsr->nodes_operand = 0.0;
	before_crsr->nodes_operator = ADDITION;

	if (cursor == nullptr) { /*If the list is empty, make a node, set its next to itself*/
		before_crsr->nodes_total = element_para;
		cursor = before_crsr;
		cursor->next = before_crsr;
	}
	else { /*Or just put the node and make it cursor's next*/
		before_crsr->next = cursor->next;
		before_crsr->nodes_total = cursor->next->nodes_total;
		cursor->next = before_crsr;
	}
}
/*remove a node, if no node in the list, throws an error*/
void CalcList::remove_node(){ 
	if (is_empty()) { throw ("Remove function is not valid since no node present in the list.");  }
	else {
		--steps; /*Decrement an operation*/
		CalcNode* old = cursor->next; /*Get the node-to-be-removed in a temprory pointer object*/
		if (old == cursor) { cursor = nullptr; } /*if happens to be the cursor itself, jst set to null*/
		else { 
			cursor->next = old->next;  
		}
		delete old; /*Remove the temprory*/
	}
}
/*Returns the total till it's called*/
double CalcList::total() const{
	return cursor->next->nodes_total; /*Gets the total from a particular node*/
}
/*Adds a node, then allows an operation on it*/
void CalcList::newOperation(const FUNCTIONS func, const double operand) {

	add_node(0); /*Add a default node first*/
	
	switch (func) { /*then update the newly default node with operator, its unique total, & operand*/
	case ADDITION:
		cursor->next->nodes_operator = ADDITION;
		cursor->next->nodes_operand = operand;
		cursor->next->nodes_total += operand;
		break;
	case SUBTRACTION:
		cursor->next->nodes_operator = SUBTRACTION;
		cursor->next->nodes_operand = operand;
		cursor->next->nodes_total -= operand;
		break;
	case MULTIPLICATION:
		cursor->next->nodes_operator = MULTIPLICATION;
		cursor->next->nodes_operand = operand;
		cursor->next->nodes_total *= operand;
		break;
	case DIVISION: /*Throw an error if divison is bad*/
		if (operand >= 0 && operand < 1.00) { removeLastOperation(); throw("Divide by zero."); }
		else {
			cursor->next->nodes_operator = DIVISION;
			cursor->next->nodes_operand = operand;
			cursor->next->nodes_total /= operand;
			break; 
		}
	default: /*Throw if enum is missing*/
		throw ("Bad arithmetic operation. Use Addition, Substraction, Multiplication, or Divison.");
		break;
	}
}
/*nested function that removes the last node*/
void CalcList::removeLastOperation() { 
	remove_node();
}
/*Converts past operations to string and returns it*/
std::string CalcList::toString(unsigned short precision) const {
	
	std::stringstream ss; /*String stream will get past operation in string buffer*/
	std::string node_data_to_string = ""; /*This variable will get the converted buffer data*/
	int step_back = steps; /*Temprory variable that holds the number of steps*/
	CalcNode* node_ptr = new CalcNode; /*Temprory variable that holds cursor->next data*/
	node_ptr = cursor->next;

	ss.precision(precision); /*sets the numerical into decimal points*/
	/*Simple output that mimics the example in pdf of PP1*/
	while(node_ptr->nodes_total != 0){ 
		ss << step_back << ": "; 

		ss << std::fixed << node_ptr->next->nodes_total; /*one before that*/

		if (node_ptr->nodes_operator == ADDITION) {
			ss << "+";
		}
		else if (node_ptr->nodes_operator == SUBTRACTION) {
			ss << "-";
		}
		else if (node_ptr->nodes_operator == MULTIPLICATION) {
			ss << "*";
		}
		else if (node_ptr->nodes_operator == DIVISION) {
			ss << "/";
		}
		ss << node_ptr->nodes_operand;
		ss << "=";
		ss << node_ptr->nodes_total; /*One at that*/
		ss << std::endl;
		
		node_ptr = node_ptr->next;
		--step_back;
	}
	node_data_to_string = ss.str();/*Convert and return*/
	return node_data_to_string;
}
