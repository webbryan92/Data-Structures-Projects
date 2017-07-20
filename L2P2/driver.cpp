#include "wrapper.h"
#include "RestaurantRecord.h"
#include "List\List1.hpp"

typedef List1<RestaurantRecord> RestaurantList;

void doLoadData(RestaurantList& s)
{
   Text filename = "Restaurant5.dat";
   Integer size;
   File input;
   Boolean successful;
   RestaurantRecord r;
   input.openFile(filename, File::openForRead, successful);

   if (!successful) {
		cout << "Could not successfully open file" << endl;
	}
   // Note: in this code, the order of the data stored in the file
   // is assumed to be in the same order that the data members are
   // listed in PersonClass. This may not always be the case.
   else {
	input.read(size, successful);
	for(int i = 0; i < size; i++) {
		input.read(r.name, successful);
		input.read(r.restaurantID, successful);
		input.read(r.type, successful);
		input.read(r.street, successful);
		input.read(r.city, successful);
		input.read(r.state, successful);
		input.read(r.zip, successful);
		input.read(r.phone, successful);
		s.addRightFront(r);
		s.advance();
	}
	s.moveToStart();
	input.closeFile(successful);
   }
} // inputOneFromFile
void displayRestaurants(RestaurantList& s){
	RestaurantList sTemp;

	s.moveToStart();
	for(int i = 0, z = s.rightLength(); i < z; i++){
		RestaurantRecord x;
		s.removeRightFront(x);
		cout << x  << endl;
		sTemp.addRightFront(x);
		sTemp.advance();
	}
	sTemp.moveToStart();
	s.transferFrom(sTemp);
}

int main(int argc, char* argv[])
{
	RestaurantList rList;
	doLoadData(rList);
	displayRestaurants(rList);
}