#pragma once
//
// merge Sort Realization of SortingMachineTemplate using List
// author: Ryan Webb
//

#include "List\List1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, class TCompare>
class SortingMachine2
	//! SortingMachine2 is modeled by tuple of
	//!             contents:  FiniteMultiSet(T)
	//!             inserting: boolean
	//! exemplar self

	//! math operation IS_FIRST (
	//!          s: FiniteMultiSet(T),
	//!          x: T
	//!      ): boolean
	//!      definition
	//!          x is in s  and
	//!          for all y: Item where (y is in s)
	//!              (areOrdered (x, y))

	//! TCompare required to have an areOrdered operation:
	//! 
	//! Boolean areOrdered (T& lhs, T& rhs)
	//! preserves lhs, rhs
	//!   areOrdered returns true iff the two items compared
	//!      are in order relative to each other.
	//!   lhs stands for left hand side
	//!   rhs stands for right hand side

{
public: // standard Operations
	SortingMachine2 ();
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true
	~SortingMachine2 ();
	void clear (void);
   		//! alters self
   		//! ensures: self.contents = { }  and  self.inserting = true
	void transferFrom(SortingMachine2& source);
		//! alters self, source
		//! ensures self = #source  and  source = self.contents = { }  and  self.inserting = true
	SortingMachine2& operator = (SortingMachine2& rhs);
   		//! alters self
   		//! preserves rhs
   		//! ensures: self = rhs

	// SortingMachine2 Specific Operations
	void add (T& x);
   		//! alters    self
   		//! consumes x
   		//! requires:  self.inserting
   		//! ensures: self.contents = #self.contents  union  {#x}  and
   		//!       self.inserting = true
	void changeToExtractionMode (void);
   		//! alters self
   		//! requires:  self.inserting
   		//! ensures: self.inserting = false  and  self.contents = #self.contents
	void removeFirst (T& x);
   		//! alters self
   		//! produces x
   		//! requires:  not self.inserting  and  self.contents != {}
   		//! ensures: IS_FIRST (#self.contents, x)  and
   		//!       self.contents = #self.contents - {x}  and
   		//!       self.inserting = false
	Integer size (void);
   		//! preserves  self
   		//! ensures: size = |self.contents|
	Boolean isInInsertionMode (void);
   		//! preserves  self
   		//! ensures:    isInInsertionMode = self.inserting

	friend ostream & operator<< <T, TCompare>(ostream &os, SortingMachine2& s);
	//! alters os
	//! preserves s

private: // representation
	typedef List1 <T> ListOfT;

	Boolean insertionMode;
	ListOfT itemKeeper;

private: // local Operations
	void mergeSort (alters ListOfT& s);
	void split (
         consumes ListOfT& s, 
         produces ListOfT& h1, 
         produces ListOfT& h2
      );
	void merge (
         produces ListOfT& s, 
         consumes ListOfT& h1, 
         consumes ListOfT& h2
      );
private: // disallowed SortingMachine2 Operations
	SortingMachine2 (const SortingMachine2& s);
	SortingMachine2* operator & (void) {return (this);};
	const SortingMachine2* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

// convention
// itemKeeper.left = < >
//

//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine2<T, TCompare>::mergeSort (ListOfT& s)
{
	ListOfT h1;
	ListOfT h2;
	if(s.rightLength() == 1){
	}
	else{
		split(s, h1, h2);
		mergeSort(h1);
		mergeSort(h2);
		merge(s, h1, h2);
	}
}	// mergeSort
template <class T, class TCompare>
void SortingMachine2<T, TCompare>::split (ListOfT& s, ListOfT& h1, ListOfT& h2){
		 T x;

		 for(int i = 0, z = s.rightLength() / 2; i < z; i++){
			 s.removeRightFront(x);
			 h1.addRightFront(x);
		 }
		 for(int i = 0, z = s.rightLength(); i < z; i++){
			s.removeRightFront(x);
			h2.addRightFront(x);
		 }
}
template <class T, class TCompare>
void SortingMachine2<T, TCompare>::merge (ListOfT& s, ListOfT& h1, ListOfT& h2){
		T x;
		T y;
		 while(h1.rightLength() > 0 && h2.rightLength() > 0){			 
			 h1.removeRightFront(x);
			 h2.removeRightFront(y);
			 if(TCompare::areOrdered(x, y)){
				 s.addRightFront(x);
				 s.advance();
				 h2.addRightFront(y);
			 }
			 else{
				 s.addRightFront(y);
				 s.advance();
				 h1.addRightFront(x);
			 }
		 }
		 if(h1.rightLength() > 0){
			 s.swapRights(h1);
		 }
		 else {
			 s.swapRights(h2);
		 }
		 s.moveToStart();
}
//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------

template <class T, class TCompare>
SortingMachine2<T, TCompare>::SortingMachine2 ()
{
	insertionMode = true;
}	// SortingMachine2

//----------------------------------------------------------------

template <class T, class TCompare>
SortingMachine2<T, TCompare>::~SortingMachine2 ()
{
}	// ~SortingMachine2

//-----------------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine2<T, TCompare>::transferFrom(SortingMachine2& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, class TCompare>
SortingMachine2<T, TCompare>& 
SortingMachine2<T, TCompare>::operator = (SortingMachine2& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	return (*this);
} // operator =

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine2<T, TCompare>::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
}	// clear

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine2<T, TCompare>::add (T& x)
{
	itemKeeper.addRightFront(x);
}	// add

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine2<T, TCompare>::changeToExtractionMode (void)
{
	mergeSort(itemKeeper);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, class TCompare>
void SortingMachine2<T, TCompare>::removeFirst (T& x)
{
	itemKeeper.removeRightFront(x);
}	// removeFirst

//----------------------------------------------------------------

template <class T, class TCompare>
Integer SortingMachine2<T, TCompare>::size (void)
{
   return (itemKeeper.rightLength());
}	// size

//----------------------------------------------------------------

template <class T, class TCompare>
Boolean SortingMachine2<T, TCompare>::isInInsertionMode (void)
{
   return (insertionMode);
}	// isInInsertionMode

//-----------------------------------------------------------------------

template <class T, class TCompare>
ostream & operator<<(ostream &os, SortingMachine2<T, TCompare>& sm)
{
	Boolean inInsertionPhase;
	SMachine temp;

	inInsertionPhase = sm.isInInsertionMode();
	if (inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	os << "({";
	for (int i = 0, z = sm.size(), lastItem = z - 1; i < z; i++) {
		T x;

		sm.removeFirst(x);
		os << x;
		temp.add(x);
		if (i < lastItem) {
			os << ",";
		} // end if
	}	// end for
	os << "},";
	os << inInsertionPhase << ")";

	sm.transferFrom(temp);
	if (!inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if

#ifndef NDEBUG
	os << endl;
	os << sm.itemKeeper;
#endif
	return (os);
} // operator<<