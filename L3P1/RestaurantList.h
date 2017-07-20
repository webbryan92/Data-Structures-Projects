#pragma once
// File: RestaurantList.h
// Date: 09/13

#include "wrapper.h"
#include "RestaurantRecord.h"
#include "List\List1.hpp"

//----------------------------------
//
// Create a List for EmployeeRecord
//

#ifdef NDEBUG
typedef List1<RestaurantRecord> RestaurantList;
#else
#include "List\ListChecking.hpp"
typedef ListChecking1<List1, RestaurantRecord> RestaurantList;
#endif