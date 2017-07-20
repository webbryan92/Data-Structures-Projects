#pragma once

/*
	Realization of QueueTemplate using ChainPosition
	Author: Dr. Holly
*/

#include "ChainPosition\ChainPosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class Queue1
	//! is modeled by string(T)
	//!   exemplar self
{
public: // standard Operations
	Queue1();
		//! alters self
		//! ensures: self = < >
	~Queue1();
	void clear(void);
		//! alters self
		//! ensures: self = < >
	void transferFrom(Queue1& source);
		//! alters self, source
		//! ensures self = #source  and  source = < >
	Queue1& operator =(Queue1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// Queue1 Specific Operations
	void enqueue(T& x);
		//! alters self
		//! consumes x
		//! ensures: self = #self * <#x>
	void dequeue(T& x);
		//! alters self
		//! produces x
		//! requires: self /= < >
		//! ensures: #self = <x> * self
	void replaceFront(T& x);
		//! alters self, x
		//! requires: self /= < >
		//!  ensures: there exists rem: string(T) such that #self = <x> * rem  and  
		//!           self = <#x> * rem
	T& front(void);
		//! preserves self
		//! requires: self /= < >
		//!  ensures: there exists rem: string(T) such that self = <front> * rem
	Integer length(void);
		//! preserves self
		//! ensures: length = |self|

	friend ostream& operator << <T>(ostream &os, Queue1& q);
	//! alters os
	//! preserves q

private: // internal representation
	
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT preFront;
	ChainPositionOfT rear;
	Integer lengthOfQueue;

private: // disallowed Queue1 Operations
	Queue1(const Queue1& s);
	Queue1* operator &(void) {return (this);};
	const Queue1* operator &(void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Queue1<T>::Queue1 ()
{
	T temp;

	preFront.labelNew(temp);
	rear = preFront;
}	// queue1

//-----------------------------------------------------------------------

template <class T>
Queue1<T>::~Queue1 ()
{
}	// ~Queue1

//-----------------------------------------------------------------------

template <class T>
void Queue1<T>::transferFrom (Queue1& source)
{
	preFront.transferFrom(source.preFront);
	rear.transferFrom(source.rear);
	lengthOfQueue.transferFrom(source.lengthOfQueue);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
Queue1<T>& Queue1<T>::operator = (Queue1& rhs)
{
	T x;
	ChainPositionOfT newPos, existingPos;

	preFront.labelNew(x);
	rear = preFront;

	existingPos = rhs.preFront;
	existingPos.applyTarget();
	while (!existingPos.isZero()) {
		x = existingPos.label();
		newPos.labelNew(x);
		rear.swapWithTarget(newPos);
		rear.applyTarget();
		existingPos.applyTarget();
	} // end while
	lengthOfQueue = rhs.lengthOfQueue;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Queue1<T>::clear (void)
{
	T temp;

	preFront.labelNew(temp);
	rear = preFront;
	lengthOfQueue = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Queue1<T>::enqueue (T& x)
{
	ChainPositionOfT newPos;

	newPos.labelNew(x);
	rear.swapWithTarget(newPos);
	rear.applyTarget();
	lengthOfQueue++;
}	// enqueue

//-----------------------------------------------------------------------

template <class T>
void Queue1<T>::dequeue( T& x)
{
	preFront.applyTarget();
	preFront.replaceLabel(x);
	lengthOfQueue--;
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void Queue1<T>::replaceFront (T& x)
{
	ChainPositionOfT pos;
	pos = preFront;
	pos.applyTarget();
	pos.replaceLabel(x);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& Queue1<T>::front (void)
{
	ChainPositionOfT pos;
	pos = preFront;
	pos.applyTarget();
	return (pos.label());
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer Queue1<T>::length (void)
{
	return (lengthOfQueue);
}	// length

//-----------------------------------------------------------------------

template <class T>
ostream& operator<< (ostream &os, Queue1<T>& q)
{
	os << "<";
	for (int i = 0, z = q.length(), lastItem = z - 1; i < z; i++) {
		T x;

		q.dequeue(x);
		os << x;
		q.enqueue(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	} // end for
	os << ">";

#ifndef NDEBUG
	os << endl;
	os << q.preFront;
#endif
	return (os);
} // operator<<



