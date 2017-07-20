#pragma once
// File: RestaurantSorter.h
// Date: 09/13

#include "wrapper.h"
#include "RestaurantRecord.h"
#include "SortingMachine\SortingMachine1.hpp"

//----------------------------------
//
// Create Comparer class
//

class nameComparer
{
public:
   static Boolean areOrdered (
         preserves RestaurantRecord& lhs,
         preserves RestaurantRecord& rhs
      )
   {
      return (lhs.name <= rhs.name);
   }; // areOrdered
};
class typeComparer
{
public:
   static Boolean areOrdered (
         preserves RestaurantRecord& lhs,
         preserves RestaurantRecord& rhs
      )
   {
      return (lhs.type <= rhs.type);
   }; // areOrdered
};
//----------------------------------
//
// Create a Sorting Machine for EmployeeRecord
//

#ifdef NDEBUG
typedef SortingMachine1<RestaurantRecord, nameComparer> RestaurantRecordSorterName;
typedef SortingMachine1<RestaurantRecord, typeComparer> RestaurantRecordSorterType;
#else
#include "SortingMachine\SortingMachineChecking.hpp"
typedef SortingMachineChecking1<SortingMachine1, RestaurantRecord, nameComparer> RestaurantRecordSorterName;
typedef SortingMachineChecking1<SortingMachine1, RestaurantRecord, typeComparer> RestaurantRecordSorterType;
#endif