/*
	Author of this file:	Mihir K Patel
	Purpose:				Following is a header file which overrides the abstract class of CalcListInterface.hpp. This class
							also creates nodes for a doubly linked list. This class has prototypes for arithmetic
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
	/*class of a Bidirectional list node*/
	friend class CalcList;
	CalcNode* prev = nullptr;
	CalcNode* next = nullptr;
	FUNCTIONS nodes_operator;
	double nodes_total = 0.0;
	double nodes_operand = 0.0;
};

class CalcList: public CalcListInterface
{
private:
	/*Sentinels*/
	CalcNode* header;
	CalcNode* trailer;
protected:
	/*Utility functions*/
	void add_node(CalcNode* node_para, const double& element_para);/*Adds a node before trailer*/
	void remove_node(CalcNode* node_para);/*Removes the node before trailer*/
	/*Helper function that returns if there is any node in the list*/
	bool is_empty() const { return header->next == trailer; } /*Returns true if sentinels are at each other*/
public:
	int steps = 0;/*Counts the number of operation*/
	/*Constructor and destructor*/
	CalcList();
	~CalcList();
	
	/*General functions*/
	double total() const;
	void newOperation(const FUNCTIONS func, const double operand); 
	void removeLastOperation();
	std::string toString(unsigned short precision) const;
};
#endif //!CALCLIST_H