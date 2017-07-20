#pragma once

//
// realization # 1 of PartialMapTemplate layered on Chain Position
// author: Dr. Holly
//

#include "ChainPosition\ChainPosition.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
class Map1
	//! Map1 is modeled by PARTIAL_FUNCTION
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
	Map1 ();
		//! alters self
		//! ensures: self = { }
	~Map1 ();
	void clear (void);
		//! alters self
		//! ensures: self = { }
	void transferFrom(Map1& source);
	//! alters self, source
	//! ensures self = #source  and  source = { }
	Map1& operator = (Map1& rhs);
		//! alters self
		//! preserves rhs
		//! ensures: self = rhs

	// Map1 Specific Operations
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

	friend ostream & operator<< <K, V, TCompare>(ostream &os, Map1& m);
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
	typedef ChainPosition1 <MapPairRecord> ChainPositionOfMapPair;

	ChainPositionOfMapPair chain;
	Integer mapSize;

private: // disallowed Map1 Operations
	Map1 (const Map1& s);
	Map1* operator & (void) {return (this);};
	const Map1* operator & (void) const {return (this);};
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

// convention: chain == smartPosition

template <class K, class V, class TCompare>
Map1<K, V, TCompare>::Map1 ()
{
	ChainPositionOfMapPair smartPosition;
	MapPairRecord label;

	smartPosition.labelNew (label);
	chain.transferFrom(smartPosition);
}	// Map1

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Map1<K, V, TCompare>::~Map1 ()
{
}	// ~Map1

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map1<K, V, TCompare>::transferFrom(Map1& source)
{
	chain.transferFrom(source.chain);
	mapSize.transferFrom(source.mapSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Map1<K, V, TCompare>& Map1<K, V, TCompare>::operator = (Map1& rhs)
{
	ChainPositionOfMapPair newPos, oldPos, current;
	MapPairRecord x;

	current.labelNew (x);
	chain = current;

	oldPos = rhs.chain;
	oldPos.applyTarget ();
	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		current.swapWithTarget (newPos);
		current.applyTarget ();
		oldPos.applyTarget ();
	} // end while
	mapSize = rhs.mapSize;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map1<K, V, TCompare>::clear (void)
{
	ChainPositionOfMapPair smartPosition;
	MapPairRecord label;

	chain.clear ();
	smartPosition.labelNew (label);
	chain.transferFrom(smartPosition);
	mapSize = 0;
}	// clear

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map1<K, V, TCompare>::add (
			K& key,
			V& value
		)
{
	MapPairRecord newPair;
	ChainPositionOfMapPair newPosition;
	ChainPositionOfMapPair firstPosition;

	newPair.keyItem.transferFrom(key);
	newPair.valueItem.transferFrom(value);

	chain.swapWithTarget (firstPosition);

	newPosition.labelNew (newPair);
	newPosition.swapWithTarget (firstPosition);
	chain.swapWithTarget (newPosition);

	mapSize++;
}	// add

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map1<K, V, TCompare>::remove (
			K& key,
			K& keyFromMap,
			V& valueFromMap
		)
{
	ChainPositionOfMapPair trailingPosition;
	ChainPositionOfMapPair currentPosition;
	MapPairRecord existingPair;

	trailingPosition = chain;
	currentPosition = trailingPosition;
	currentPosition.applyTarget ();

	while (!TCompare::areEqual (key, currentPosition.label().keyItem)) {
		trailingPosition = currentPosition;
		currentPosition.applyTarget ();
	}  // end while
	currentPosition.replaceLabel (existingPair);

	currentPosition.applyTarget ();
	trailingPosition.swapWithTarget (currentPosition);

	keyFromMap.transferFrom(existingPair.keyItem);
	valueFromMap.transferFrom(existingPair.valueItem);

	mapSize--;
}	// remove

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
V& Map1<K, V, TCompare>::value (preserves K& key)
{
	ChainPositionOfMapPair currentPosition;

	currentPosition = chain;
	currentPosition.applyTarget ();

	while (!TCompare::areEqual (key, currentPosition.label().keyItem)) {
		currentPosition.applyTarget ();
	}  // end while
	return (currentPosition.label().valueItem);
}  // value

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
void Map1<K, V, TCompare>::removeAny (
			K& key,
			V& value
		)
{
	ChainPositionOfMapPair position;
	MapPairRecord existingPair;

	position = chain;
	position.applyTarget ();

	position.replaceLabel (existingPair);
	position.applyTarget ();
	chain.swapWithTarget (position);

	key.transferFrom(existingPair.keyItem);
	value.transferFrom(existingPair.valueItem);

	mapSize--;
}	// removeAny

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Boolean Map1<K, V, TCompare>::hasKey (
			K& key
		)
{
	ChainPositionOfMapPair position;

	position = chain;
	position.applyTarget ();

	while (!position.isZero () && !TCompare::areEqual (key, position.label().keyItem)) {
		position.applyTarget ();
	}	// end while

	return (!position.isZero ());
}	// hasKey

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
Integer Map1<K, V, TCompare>::size (void)
{
	return (mapSize);
}	// size

//-----------------------------------------------------------------------

template <class K, class V, class TCompare>
ostream & operator<<(ostream &os, Map1<K, V, TCompare>& m)
{
	Map1<K, V, TCompare> temp;

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
	os << m.chain;
#endif

	return (os);
} // operator<<
