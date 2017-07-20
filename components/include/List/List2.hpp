#pragma once
/*
	Realization of List using Stack
	Author: Ryan Webb
*/
#include "Stack\Stack1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class List2
	//! is modeled by tuple of
	//!   leftStack: string(T)
	//!   rightStack: string(T)
	//! exemplar self
{
public: // standard Operations
	List2 ();
		//! alters self
		//! ensures: self.leftStack = < >  and  self.rightStack = < >
	~List2 ();
	void clear (void);
		//! alters self
		//! ensures: self.leftStack = < >  and  self.rightStack = < >
	void transferFrom(List2& source);
		//! alters self, source
		//! ensures self = #source  and  source = < > < >
	List2& operator = (List2& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// List2 Specific Operations
	void moveToStart (void);
		//! alters self
		//! ensures: self.leftStack = < >  and  self.rightStack = #self.leftStack * #self.rightStack
	void moveToFinish (void);
		//! alters self
		//! ensures: self.rightStack = < >  and  self.leftStack = #self.leftStack * #self.rightStack
	void advance (void);
		//! alters self
		//! requires: self.rightStack /= < >
		//! ensures: there exists x: T 
		//!       (self.leftStack = #self.leftStack * <x>  and  #self.rightStack = <x> * self.rightStack)
	void addRightFront (T& x);
		//! alters self
		//! consumes x
		//! ensures: self.leftStack = #self.leftStack  and  self.rightStack = <#x> * #self.rightStack
	void removeRightFront (T& x);
		//! alters self
		//! produces x
		//! requires: self.rightStack /= < >
		//! ensures: self.leftStack = #self.leftStack  and  #self.rightStack = <x> * self.rightStack
	T& rightFront(void);
		//! preserves self
		//! requires: self.rightStack /= < >
		//!  ensures: there exists rem: string(T) such that self.rightStack = <rightFront> * rem
	void replaceRightFront (T& x);
		//! alters self, x
		//! requires: self.rightStack /= < >
		//!  ensures: there exists rem: string(T) such that #self.rightStack = <x> * rem  and  
		//!           self.rightStack = <#x> * rem  and  self.leftStack = #self.leftStack
	void swapRights (List2& s);
		//! alters self, other_s
		//! ensures: self.leftStack = #self.leftStack  and  s.leftStack = #s.leftStack  and
		//!       s.rightStack = #self.rightStack  and  self.rightStack = #s.rightStack
	Integer leftLength (void);
		//! preserves self
		//! ensures: leftLength = |self.leftStack|
	Integer rightLength (void);
		//! preserves self
		//! ensures: rightLength = |self.rightStack|

	friend ostream & operator<< <T>(ostream &os, List2<T>& s);
		//! alters os
		//! preserves s

private: // representation
	typedef Stack1<T> StackOfT;

	StackOfT leftStack;
	StackOfT rightStack;

private: // disallowed List2 Operations
	List2 (const List2& s);
	List2* operator & (void) {return (this);};
	const List2* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
List2<T>::List2 ()
{
	// DONE: List2
}	// List2

//-----------------------------------------------------------------------

template <class T>
List2<T>::~List2 ()
{
	// DONE: ~List2
}	// ~List2

//-----------------------------------------------------------------------

template <class T>
void List2<T>::transferFrom(List2& source)
{
	// Note: to see these "TODO:" tasks show up in Visual Studio follow the instructions in:
	// http://homepages.ius.edu/jholly/c343/labs/VSTaskList.htm 
	leftStack = source.leftStack;
	rightStack = source.rightStack;
	source.leftStack.clear();
	source.rightStack.clear();

	// DONE: transferFrom
}

//-----------------------------------------------------------------------

template <class T>
List2<T>& List2<T>::operator = (List2& rhs)
{
	leftStack = rhs.leftStack;
	rightStack = rhs.rightStack;
	// DONE: operator =
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void List2<T>::clear (void)
{
	leftStack.clear();
	rightStack.clear();
	// DONE: clear
}	// clear

//-----------------------------------------------------------------------

template <class T>
void List2<T>::moveToStart (void)
{
	Text x;
	for(int i = 0, z = leftStack.length(); i < z; i++){
		leftStack.pop(x);
		rightStack.push(x);
	}
	// DONE: moveToStart
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void List2<T>::moveToFinish (void)
{
	Text x;
	for(int i = 0, z = rightStack.length(); i < z; i++){
		rightStack.pop(x);
		leftStack.push(x);
	}
	// DONE: moveToFinish
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void List2<T>::advance (void)
{
	Text x;
	rightStack.pop(x);
	leftStack.push(x);
	// DONE: advance
}	// advance

//-----------------------------------------------------------------------

template <class T>
void List2<T>::addRightFront (T& x)
{
	// DONE: addRightFront
	rightStack.push(x);
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void List2<T>::removeRightFront (T& x)
{
	rightStack.pop(x);
	// DONE: removeRightFront
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& List2<T>::rightFront(void)
{
	// DONE: rightFront
	return(rightStack.top());
}  // rightFront


//-----------------------------------------------------------------------

template <class T>
void List2<T>::replaceRightFront (T& x)
{
	rightStack.replaceTop(x);
	// DONE: replaceRightFront
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void List2<T>::swapRights (List2& s)
{
	List2<T> Temp;
	Temp.rightStack = rightStack;
	rightStack = s.rightStack;
	s.rightStack = Temp.rightStack;
	// DONE: swapRights
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer List2<T>::leftLength (void)
{
	// DONE: leftLength
	return (leftStack.length());
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
inline Integer List2<T>::rightLength (void)
{
	// DONE: rightLength
	return (rightStack.length());
}	// rightLength

//-----------------------------------------------------------------------

template <class T>
ostream & operator<<(ostream &os, List2<T>& s)
{
	// ***********
	// Nothing to do here, this implementation is done.
	// ***********

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

#ifndef NDEBUG
	os << endl;
	os << "(" << s.leftStack << "," << s.rightStack << ")";
#endif
	return (os);
}