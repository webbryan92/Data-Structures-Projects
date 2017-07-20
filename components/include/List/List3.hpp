#pragma once
#pragma warning( disable : 4172 )
/*
	Realization of OneWayListTemplate using ChainPosition
	Author: Dr. Holly
*/

#ifdef NDEBUG
#define checked(CHECKED_T) CHECKED_T
#else
#include "dereferee.h"
#endif



//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class List3
	//! is modeled by tuple of
	//!   left: string(T)
	//!   right: string(T)
	//! exemplar self
{
public: // standard Operations
	List3 ();
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	List3 (List3& actual);
		//! alters self
		//! preserves actual
		//! ensures: self = actual
	~List3 ();
	void clear (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = < >
	void transferFrom(List3& source);
		//! alters self, source
		//! ensures self = #source  and  source = < > < >
	List3& operator = (List3& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// List3 Specific Operations
	void moveToStart (void);
		//! alters self
		//! ensures: self.left = < >  and  self.right = #self.left * #self.right
	void moveToFinish (void);
		//! alters self
		//! ensures: self.right = < >  and  self.left = #self.left * #self.right
	void advance (void);
		//! alters self
		//! requires: self.right /= < >
		//! ensures: there exists x: T 
		//!       (self.left = #self.left * <x>  and  #self.right = <x> * self.right)
	void addRightFront (T& x);
		//! alters self
		//! consumes x
		//! ensures: self.left = #self.left  and  self.right = <#x> * #self.right
	void removeRightFront (T& x);
		//! alters self
		//! produces x
		//! requires: self.right /= < >
		//! ensures: self.left = #self.left  and  #self.right = <x> * self.right
	T& rightFront(void);
		//! preserves self
		//! requires: self.right /= < >
		//!  ensures: there exists rem: string(T) such that self.right = <rightFront> * rem
	void replaceRightFront (T& x);
		//! alters self, x
		//! requires: self.right /= < >
		//!  ensures: there exists rem: string(T) such that #self.right = <x> * rem  and  
		//!           self.right = <#x> * rem  and  self.left = #self.left
	void swapRights (List3& s);
		//! alters self, other_s
		//! ensures: self.left = #self.left  and  s.left = #s.left  and
		//!       s.right = #self.right  and  self.right = #s.right
	Integer leftLength (void);
		//! preserves self
		//! ensures: leftLength = |self.left|
	Integer rightLength (void);
		//! preserves self
		//! ensures: rightLength = |self.right|

	friend ostream & operator<< <T>(ostream &os, List3<T>& s);
		//! alters os
		//! preserves s

private: // representation
	class NodeRecord {
	public:
		T value;
		checked(NodeRecord*) next;
	};

	checked(NodeRecord*) head;
	Integer lengthOfLeft;
	Integer lengthOfRight;

private: // local operations
	void displayRep(void);

	void reclaimAllNodes (checked(NodeRecord*) p);
	void copyNodes (checked(NodeRecord*)& toP, checked(NodeRecord*) fromP);

private: // disallowed List3 Operations
	List3* operator & (void) {return (this);};
	const List3* operator & (void) const {return (this);};
};
//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void List3<T>::reclaimAllNodes (checked(NodeRecord*) initialP)
{
	//DONE: reclaimAllNodes
	checked(NodeRecord*) p;
	while(initialP != NULL){
		p = initialP;
		initialP = initialP->next;
		delete p;
	}
} // reclaimAllNodes

template <class T>
void List3<T>::copyNodes (checked(NodeRecord*)& toP, checked(NodeRecord*) fromP)
{
	//TODO: copyNodes
	checked(NodeRecord*) temp;
	checked(NodeRecord*) newNode;
	
	reclaimAllNodes(toP);
	if(fromP == NULL){
		toP = NULL;
	}
	else{
		toP.head = newNode;
		temp = fromP;
		newNode = new NodeRecord;
		newNode->value = temp->value;
		newNode->next = temp->next;
	}
} // copyNodes

//-----------------------------------------------------------------------

template <class T>
void List3<T>::displayRep(void)
{
	//DONE: displayRep
	checked(NodeRecord*) p;
	p = head;
	cout << endl << " lengthOfLeft: " << lengthOfLeft << endl;
	cout << "lengthOfRight: " << lengthOfRight << endl;
	cout << "         head: " << head << endl;
	while(p != NULL) {
		cout << "#" << p << "(" << p->value << "," << '#' << p->next << ")" << endl;
		p = p->next;		
	}
}

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
List3<T>::List3 ()
{
	//DONE: List3 - default constructor
	head = NULL;
}	// List3

//-----------------------------------------------------------------------
// This is the copy constructor
// It gets invoked when a List gets passed by value during a call to an operation
// It's job is to make an exact duplicate of the actual parameter and put that duplicate into the formal parameter
// Think of the call as follows:
//    formalParameterName.List3(acutalParameterName);
// So the object in front of the dot is the formal parameter, and the actual parameter gets passed in as the parameter to this operation.
// Note: the formal parameter is just now coming into existance, i.e., it is just now coming in from "out of scope", it is the job
//       of the copy constructor to make have an exact duplicate of what is in the actual parameter.
template <class T>
List3<T>::List3 (List3& actual)
{
	//TODO: List3 - copy constructor
}	// List3

//-----------------------------------------------------------------------

template <class T>
List3<T>::~List3 ()
{
	//DONE: ~List3 - destructor
	reclaimAllNodes(head);
	head = NULL;
}	// ~List3

//-----------------------------------------------------------------------

template <class T>
void List3<T>::transferFrom(List3& source)
{
	//DONE: transferFrom
	reclaimAllNodes(head);
	head = source.head;
	source.head = NULL;
	lengthOfLeft.transferFrom(source.lengthOfLeft);
	lengthOfRight.transferFrom(source.lengthOfRight);
}

//-----------------------------------------------------------------------

template <class T>
List3<T>& List3<T>::operator = (List3& rhs)
{
	//DONE: operator =
	reclaimAllNodes(head);
	copyNodes(head, rhs.head);
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void List3<T>::clear (void)
{
	//DONE: clear
	reclaimAllNodes(head);
	head = NULL;
	lengthOfLeft = 0;
	lengthOfRight = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void List3<T>::moveToStart (void)
{
	//DONE: moveToStart
	lengthOfRight += lengthOfLeft;
	lengthOfLeft = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void List3<T>::moveToFinish (void)
{
	//DONE: moveToFinish
	lengthOfLeft += lengthOfRight;
	lengthOfRight = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void List3<T>::advance (void)
{
	//DONE: advance
	lengthOfLeft++;
	lengthOfRight--;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void List3<T>::addRightFront (T& x)
{
	//DONE: addRightFront
	checked(NodeRecord*) newNode;
	checked(NodeRecord*) temp;

	newNode = new NodeRecord;
	newNode->value.transferFrom(x);
	newNode->next = NULL;

	if (head == NULL) {
		head = newNode;
	} else if(lengthOfLeft == 0){
		newNode->next = head;
		head = newNode;
	}else {
		checked(NodeRecord*) p;
		p = head;
		for(int i = 0, z = lengthOfLeft; i < z; i++){
			p = p->next;
		}
		temp = p->next;
		p->next = newNode;
		newNode->next = temp;
	}
	lengthOfRight++;
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void List3<T>::removeRightFront (T& x)
{
	//DONE: removeRightFront
	checked(NodeRecord*) trail;
	checked(NodeRecord*) p;
	p = head;
	for(int i = 0, z = lengthOfLeft; i < z; i++){
		trail = p;
		p = p->next;
	}
	trail->next = p->next;
	x = p->value;
	delete p;
	lengthOfRight--;
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& List3<T>::rightFront(void)
{
	//DONE: rightFront
	// note - in order for this operation to compile, a value must be returned
	// after correctly implementing this operation, delete this temporary variable.
	checked(NodeRecord*) p;
	p = head;
	for(int i = 0, z = lengthOfLeft; i < z; i++){
		p = p->next;
	}
	return (p->value);
}  // rightFront


//-----------------------------------------------------------------------

template <class T>
void List3<T>::replaceRightFront (T& x)
{
	//DONE: replaceRightFront
	T temp;
	checked(NodeRecord*) p;
	p = head;
	for(int i = 0, z = lengthOfLeft; i < z; i++){
		p = p->next;
	}
	temp = p->value;
	p->value = x;
	x = temp;
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void List3<T>::swapRights (List3& s)
{
	//DONE: swapRights
	checked(NodeRecord*) px;
	checked(NodeRecord*) py;	
	checked(NodeRecord*) temp;
	Integer intTemp;

	px = head;
	py = s.head;
	//if lefts are empty
	if(lengthOfLeft == 0 && s.lengthOfLeft == 0){
		temp = head;
		head = s.head;
		s.head = temp;
	}
	//if a left is empty
	else if(lengthOfLeft == 0 && s.lengthOfLeft != 0){
		for(int i = 0, z = s.lengthOfLeft-1; i < z; i++){
			py = py->next;
		}
		head = py->next;
		py->next = px;
	}
	else if(lengthOfLeft != 0 && s.lengthOfLeft == 0){
		for(int i = 0, z = lengthOfLeft-1; i < z; i++){
			px = px->next;
		}
		s.head = px->next;
		px->next = py;
	}
	//middle of the list on both
	else {	
		
		for(int i = 0, z = lengthOfLeft-1; i < z; i++){
			px = px->next;
		}	
		for(int i = 0, z = s.lengthOfLeft-1; i < z; i++){
			py = py->next;
		}

		temp = px->next;
		px->next = py->next;
		py->next = temp;
	}

	intTemp = lengthOfRight;
	lengthOfRight = s.lengthOfRight;
	s.lengthOfRight = intTemp;
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer List3<T>::leftLength (void)
{
	//DONE: leftLength
	return (lengthOfLeft);
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
inline Integer List3<T>::rightLength (void)
{
	//DONE: leftLength
	return (lengthOfRight);
}	// rightLength

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, List3<T>& s)
{
#ifdef NDEBUG
	os << "<";
	int lengthOfLeft = s.leftLength();

	s.moveToStart();
	for (int i = 0, lastItem = lengthOfLeft - 1; i < lengthOfLeft; i++) {
		os << s.rightFront();
		s.advance();
		if (i < lastItem) {
			os << ",";
		} // end if
	}
	os << "> <";

	int lengthOfRight = s.rightLength();
	for (int i = 0, lastItem = lengthOfRight - 1; i < lengthOfRight; i++) {
		os << s.rightFront();
		s.advance();
		if (i < lastItem) {
			os << ",";
		} // end if
	}
	os << ">";

	// reset fence to original location
	s.moveToStart();
	for (int i = 0; i < lengthOfLeft; i++) {
		s.advance();
	}

#else 
	s.displayRep();
#endif
	return (os);
}