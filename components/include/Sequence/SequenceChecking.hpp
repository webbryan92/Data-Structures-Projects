#pragma once

//
// checking Version for Sequence
// author: Dr. Holly
//


template <
	template <class> class Sequence,
	class T
>
class SequenceChecking1:
	public Sequence <T>
{
	typedef Sequence <T> SequenceOfT;
public:

//-----------------------------------------------------------------------

void add (
		preserves Integer pos,
		alters T& x
	)
{
	// assert that 0 <= pos <= s.length
	if (pos < 0) {
		OutputDebugString ("Operation: Add\n");
		OutputDebugString ("Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (pos > SequenceOfT::length ()) {
		OutputDebugString ("Operation: Add\n");
		OutputDebugString ("Assertion failed: pos <= |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::add (pos, x);
}	// add

//-----------------------------------------------------------------------

void remove (
		preserves Integer pos,
		alters T& x
	)
{
	// assert that 0 <= pos < s.length
	if (pos < 0) {
		OutputDebugString ("Operation: Remove\n");
		OutputDebugString ("Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (SequenceOfT::length () <= pos) {
		OutputDebugString ("Operation: Remove\n");
		OutputDebugString ("Assertion failed: pos < |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::remove (pos, x);
}	// remove

//-----------------------------------------------------------------------

void replaceEntry (
		preserves Integer pos,
		alters T& x
	)
{
	// assert that 0 <= pos < s.length
	if (pos < 0) {
		OutputDebugString ("Operation: replaceEntry\n");
		OutputDebugString ("Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (SequenceOfT::length () <= pos) {
		OutputDebugString ("Operation: replaceEntry\n");
		OutputDebugString ("Assertion failed: pos < |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::replaceEntry (pos, x);
}	// swapItem

//-----------------------------------------------------------------------

void split (
		preserves Integer pos,
		produces SequenceChecking1& otherS
	)
{
	// assert that 0 <= pos <= s.length
	if (pos < 0) {
		OutputDebugString ("Operation: Split\n");
		OutputDebugString ("Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (pos > SequenceOfT::length ()) {
		OutputDebugString ("Operation: Split\n");
		OutputDebugString ("Assertion failed: pos <= |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::split (pos, otherS);
}	// split

//-----------------------------------------------------------------------

T& entry (
			preserves Integer pos
		)
{
	// assert that 0 <= pos < s.length
	if (pos < 0) {
		OutputDebugString ("Operation: operator []\n");
		OutputDebugString ("Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (SequenceOfT::length () <= pos) {
		OutputDebugString ("Operation: operator []\n");
		OutputDebugString ("Assertion failed: pos < |s|\n");
		DebugBreak ();
	}	// end if 

	return (SequenceOfT::entry (pos));
}	// entry
};

