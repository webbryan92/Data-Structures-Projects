#pragma once
// File: RestaurantSorter.h
// Date: 09/13

#include "wrapper.h"
#include "RestaurantRecord.h"
#include "SortingMachine\SortingMachine2.hpp"

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

//----------------------------------
//
// Create a Sorting Machine for EmployeeRecord
//

#ifdef NDEBUG
typedef SortingMachine2<RestaurantRecord, nameComparer> RestaurantRecordSorter;
#else
#include "SortingMachine\SortingMachineChecking.hpp"
typedef SortingMachineChecking1<SortingMachine2, RestaurantRecord, nameComparer> RestaurantRecordSorter;
#endif