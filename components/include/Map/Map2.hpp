#pragma once

//
// realization # 1 of PartialMapTemplate layered on Chain Position
// author: Dr. Holly
//

#include "List\List1.hpp"


//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
class Map2
	//! Map2 is modeled by PARTIAL_FUNCTION
	//! math subtype PARTIAL_FUNCTION is finite set of
	//!                  key: K
	//!                  value: V
	//!             exemplar m
	//!             constraint
	//!                for all   key: K, r1, r2: V
	//!                          where (key, r1) is in m
	//!                          and   (key, r2) is in m then (r1 = r2)
	//! 
	//!          math operation DEFINED_IN (
	//!                   m: PARTIAL_FUNCTION
	//!                   key: K
	//!                ): boolean
	//! 
	//!          definition   DEFINED_IN (m, key)  iff
	//!                            there exists value: V, ((key, value) is in m)
	//! exemplar self
{
public: // standard Operations
	Map2 ();
		//! alters self
		//! ensures: self = { }
	~Map2 ();
	void clear (void);
		//! alters self
		//! ensures: self = { }
	void transferFrom(Map2& source);
	//! alters self, source
	//! ensures self = #source  and  source = { }
	Map2& operator = (Map2& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// Map2 Specific Operations
	void add (K& key, V& value);
		//! alters   self
		//! consumes key,  value
		//! requires:  not DEFINED_IN (self, key)
		//! ensures: self = #self  union  {(#key, #value)}
	void remove (K& key, K& keyFromMap, V& valueFromMap);
		//! alters    self
		//! preserves key
		//! produces  keyFromMap, valueFromMap
		//! requires:  DEFINED_IN (self, key)
		//! ensures: (key, valueFromMap) is in #self  and
		//!       self = #self - {(keyFromMap, valueFromMap)}  and  keyFromMap = key
	V& value (K& key);
		//! preserves self, key
		//! requires:  DEFINED_IN (self, key)
		//! ensures: (key, value) is in self
	void removeAny (K& key, V& value);
		//! alters   self
		//! produces key, value
		//! requires:  self /= { }
		//! ensures: (key, value) is in #self  and  self = #self - {(key, value)}
	Boolean hasKey (K& key);
		//! preserves  self
		//! preserves key
		//! ensures: hasKey = true  iff  DEFINED_IN (self, key)
	Integer size (void);
		//! preserves self
		//! ensures: size = |self|

	friend ostream & operator<< <K, V, TCompare>(ostream &os, Map2& m);
	//! alters os
	//! preserves q

private: // representation
	class MapPairRecord {
	public:
		K keyItem; 
		V valueItem;

		void transferFrom(MapPairRecord& source) 
		{
			keyItem.transferFrom(source.keyItem);
			valueItem.transferFrom(source.valueItem);
		};

		friend ostream& operator << (ostream &os, MapPairRecord& r)
		{
			os << "(" << r.keyItem << "," << r.valueItem << ")";
			return os;
		}
	};

private: // internal representation
	#ifdef NDEBUG
		typedef List1 <MapPairRecord> ListOfMapPair;
	#else
	#include "List\ListChecking.hpp"
		typedef ListChecking1 <List1, MapPairRecord> ListOfMapPair;
	#endif

	ListOfMapPair s;
	Integer mapSize;

private: // disallowed Map2 Operations
	Map2 (const Map2& s);
	Map2* operator & (void) {return (this);};
	const Map2* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

// convention: chain == smartPosition

template <class K, class V, class TCompare>
Map2<K, V, TCompare>::Map2 ()
{
}	// Map2

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Map2<K, V, TCompare>::~Map2 ()
{
}	// ~Map2

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map2<K, V, TCompare>::transferFrom(Map2& source)
{
	s.transferFrom(source.s);
	mapSize.transferFrom(source.mapSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Map2<K, V, TCompare>& Map2<K, V, TCompare>::operator = (Map2& rhs)
{
	s = rhs.s;
	mapSize = rhs.mapSize;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map2<K, V, TCompare>::clear (void)
{
	s.clear();
	mapSize = 0;
}	// clear

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map2<K, V, TCompare>::add (
			K& key,
			V& value
		)
{
	MapPairRecord newPair;

	newPair.keyItem.transferFrom(key);
	newPair.valueItem.transferFrom(value);
	
	s.addRightFront(newPair);

	mapSize++;
}	// add

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map2<K, V, TCompare>::remove (
			K& key,
			K& keyFromMap,
			V& valueFromMap
		)
{
	MapPairRecord existingPair;

	while (!TCompare::areEqual (key, s.rightFront().keyItem)) {
		s.advance();
	}  // end while
	s.removeRightFront(existingPair);
	s.moveToStart();

	keyFromMap.transferFrom(existingPair.keyItem);
	valueFromMap.transferFrom(existingPair.valueItem);

	mapSize--;
}	// remove

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
V& Map2<K, V, TCompare>::value (preserves K& key)
{

	while (!TCompare::areEqual (key, s.rightFront().keyItem)) {
		s.advance();
	}  // end while
	s.moveToStart();
	return (s.rightFront().valueItem);
}  // value

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map2<K, V, TCompare>::removeAny (
			K& key,
			V& value
		)
{
	MapPairRecord existingPair;
	s.removeRightFront(existingPair);
	key.transferFrom(existingPair.keyItem);
	value.transferFrom(existingPair.valueItem);

	mapSize--;
}	// removeAny

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Boolean Map2<K, V, TCompare>::hasKey (
			K& key
		)
{
	int z;
	boolean keyFound = false;
	z = s.rightLength();
	int i = 0;
	while (!keyFound && i < z) {
		if(TCompare::areEqual (key, s.rightFront().keyItem))
			keyFound = true;
		else
			s.advance();
		i++;
	}	// end while
	s.moveToStart();
	return (keyFound);
}	// hasKey

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Integer Map2<K, V, TCompare>::size (void)
{
	return (mapSize);
}	// size

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
ostream & operator<<(ostream &os, Map2<K, V, TCompare>& m)
{
	Map2<K, V, TCompare> temp;

	os << "{";
	for (int i = 0, z = m.size(), lastItem = z - 1; i < z; i++) {
		K key;
		V value;

		m.removeAny (key, value);
		os << "(" << key << "," << value << ")";
		if (i < lastItem) {
			os << ",";
		} // end if
		temp.add (key, value);
	}	// end for
	os << "}";
	m.transferFrom(temp);

#ifndef NDEBUG
	os << endl;
	os << m.mapSize << endl;
	os << m.s;
#endif

	return (os);
} // operator<<
