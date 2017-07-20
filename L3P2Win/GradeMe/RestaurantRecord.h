#pragma once
#include "wrapper.h"

class RestaurantRecord {
   public:
      Text name;
      Integer restaurantID;
      Text type;
      Text street;
	 Text city;
	 Text state;
	 Integer zip;
	 Text phone;

      void clear(void)
      {
         name.clear();
         restaurantID.clear();
         type.clear();
         street.clear();
	    city.clear();
	    state.clear();
	    zip.clear();
	    phone.clear();
      } // clear

      RestaurantRecord& operator = (RestaurantRecord& rhs)
      {
         name = rhs.name;
         restaurantID = rhs.restaurantID;
         type = rhs.type;
         street = rhs.street;
	    city = rhs.city;
	    state = rhs.state;
	    zip = rhs.zip;
	    phone = rhs.phone;

         return (*this);
      } // operator =

      void transferFrom(RestaurantRecord& source) 
      {
         name.transferFrom(source.name);
         restaurantID.transferFrom(source.restaurantID);
         type.transferFrom(source.type);
         street.transferFrom(source.street);
	    city.transferFrom(source.city);
	    state.transferFrom(source.state);
	    zip.transferFrom(source.zip);
	    phone.transferFrom(source.phone);
      } // transferFrom

      friend ostream& operator << (ostream &os, RestaurantRecord& r)
      {
         os << "(" << r.name << "," << r.restaurantID << "," << r.type << "," << r.street << "," << r.city << "," << r.state << "," << r.zip << "," << r.phone << ")";
         return os;
      } // operator <<
};