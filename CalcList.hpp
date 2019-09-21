/*
	Author of this file:	Mihir K Patel
	Purpose:		Following is a header file which overrides the abstract class of CalcListInterface.hpp. This class
				also creates nodes for a cicularly linked list. This class has prototypes for arithmetic
				operations for the list.
*/
#ifndef CALCLIST_H
#define CALCLIST_H

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "CalcListInterface.hpp"

class CalcNode {
	/*class of a circular list node*/
	friend class CalcList;
	CalcNode* next;
	FUNCTIONS nodes_operator;
	double nodes_total;
	double nodes_operand;
};

class CalcList: public CalcListInterface
{
private:
	CalcNode* cursor;/*Sort of tracker*/
protected:
	/*Utility functions*/
	void add_node(const double& element_para);/*Adds a node BEFORE cursor*/
	void remove_node();/*Removes the node after cursor*/
	int steps = 0;/*Counts the number od operation*/
public:
	/*Constructor and destructor*/
	CalcList();
	~CalcList();

	/*Helper functions*/
	bool is_empty() const { return (steps == 0); }/*Returns whether the list is empty*/
	
	/*general functions*/
	double total() const;
	void newOperation(const FUNCTIONS func, const double operand); //like add back
	void removeLastOperation();//like remove back
	std::string toString(unsigned short precision) const;
};
#endif //!CALCLIST_H
