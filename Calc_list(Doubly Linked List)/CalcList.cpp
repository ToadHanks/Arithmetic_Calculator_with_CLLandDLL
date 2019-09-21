/*
	Author of this File:	Mihir K Patel
	Purpose:		Following is a source file for CalcList.hpp. It implements the definitions for
				constructors, destructors and abstract operations.

*/
#include "CalcList.hpp"

/*Constructor that makes a node object*/
CalcList::CalcList() :CalcListInterface() { 
	header = new CalcNode; /*Creates two nodes*/
	trailer = new CalcNode;
	header->next = trailer; /*Sentinels points to each other*/
	trailer->prev = header;
}
/*Destroys the CalcList objects*/
CalcList::~CalcList() {
	while (!is_empty()) { 
		remove_node(header->next);/*Removes the nodes with operations*/
	}
	delete header;/*Frees the heap*/
	delete trailer;
}
/*Adds a node in the before the trailer*/
void CalcList::add_node(CalcNode* node_para, const double& element_para) {
	++steps; /*Increments the operations counter*/
	CalcNode* before_trailer = new CalcNode; /*Creates a node before the trailer*/
	/*gives the newly created node default properties*/
	before_trailer->next = node_para;
	before_trailer->nodes_total = node_para->prev->nodes_total;/*gives the old total value*/
	before_trailer->prev = node_para->prev;
	node_para->prev->next = before_trailer;

	node_para->prev = before_trailer;
}
/*Removes the node before trailer*/
void CalcList::remove_node(CalcNode* node_para){
	if (is_empty()) { throw ("Remove function is not valid since no node present in the list."); /*throw header;*/  }
	else {
		--steps; /*Decrement for a removed operation*/
		CalcNode* before_para = node_para->prev; /*remove the node before trailer, and re-links it*/
		CalcNode* after_para = node_para->next;
		before_para->next = after_para;
		after_para->prev = before_para;
		delete node_para; /*then delete the selected node*/
	}
}
/*Returns the total till it's called*/
double CalcList::total() const{
	return trailer->prev->nodes_total;
}
/*Adds a node, then allows an operation on it*/
void CalcList::newOperation(const FUNCTIONS func, const double operand) {

	add_node(trailer, 0.00);/*Add an empty node on before trailer*/

	/*Updates the data members of a newly made node*/
	switch (func) {
	case ADDITION:
		trailer->prev->nodes_operator = ADDITION; /*after making a new node before trailer, we give it an operator*/
		trailer->prev->nodes_operand = operand; /*give it an operand*/
		trailer->prev->nodes_total += operand; /*give it a total which is total of old + operand*/
		break;
	case SUBTRACTION:
		trailer->prev->nodes_operator = SUBTRACTION;
		trailer->prev->nodes_operand = operand;
		trailer->prev->nodes_total -= operand;
		break;
	case MULTIPLICATION:
		trailer->prev->nodes_operator = MULTIPLICATION;
		trailer->prev->nodes_operand = operand;
		trailer->prev->nodes_total *= operand;
		break;
	case DIVISION: 
		if (operand >= 0 && operand < 1.00) { removeLastOperation(); throw("Divide by zero."); } /*check, and undo*/
		else {
			trailer->prev->nodes_operator = DIVISION;
			trailer->prev->nodes_operand = operand;
			trailer->prev->nodes_total /= operand;
			break; 
		}
	default:
		throw ("Bad arithmetic operation. Use Addition, Substraction, Multiplication, or Divison.");
		break;
	}
}
/*Removes the operation before trailer*/
void CalcList::removeLastOperation() {
	remove_node(trailer->prev);
}
/*Converts past operations to string and returns it*/
std::string CalcList::toString(unsigned short precision) const {
	
	std::stringstream ss; /*stringstream will take the data stream and convert */
	std::string node_data_to_string = ""; /*Blank variables that holds the past operations*/
	CalcNode* node_ptr = trailer;/*temp node*/
	int steps_temp = steps;

	ss.precision(precision); /*sets the precision of floats*/
	while (node_ptr->prev != header) { /*Simple load until header != [trailer]*/
		ss << steps_temp << ": ";

		ss << std::fixed << node_ptr->prev->prev->nodes_total;

		if (node_ptr->prev->nodes_operator == ADDITION) {
			ss << "+";
		}
		else if (node_ptr->prev->nodes_operator == SUBTRACTION) {
			ss << "-";
		}
		else if (node_ptr->prev->nodes_operator == MULTIPLICATION) {
			ss << "*";
		}
		else if (node_ptr->prev->nodes_operator == DIVISION) {
			ss << "/";
		}
		ss << node_ptr->prev->nodes_operand;
		ss << "=";
		ss << node_ptr->prev->nodes_total;
		ss << std::endl;

		node_ptr = node_ptr->prev;
		--steps_temp; 
	}
	node_data_to_string = ss.str();/*Now whole ss will be converted and set equal to the data member*/
	return node_data_to_string;
}
