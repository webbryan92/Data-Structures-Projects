#include "Wrapper.h"
#include "Map\Map2.hpp"

class KeyComparer {
public:
	static Boolean areEqual (preserves Integer lhs, preserves Integer rhs)
	{return (lhs == rhs);};

	static Boolean areOrdered (preserves Integer lhs, preserves Integer rhs)
	{return (lhs <= rhs);};

	static Integer hashCode (preserves Integer key)
	{return (key);};
};

typedef Map2 <Integer, Text, KeyComparer> ITMap;

