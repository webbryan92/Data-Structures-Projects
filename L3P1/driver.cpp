#include "wrapper.h"
#include "RestaurantRecord.h"
#include "RestaurantSorter.h"
#include "RestaurantList.h"
#include "List\List1.hpp"

void doLoadData(RestaurantList& s)
{
   Text filename = "Restaurant56.dat";
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

void sortData (alters RestaurantList& s)
   // requires s.left = < >
   // ensures s.left = < >  and  s.right is sorted
{
   RestaurantRecordSorter restaurantSorter;

   for (int i = 0, z = s.rightLength(); i < z; i++) {
      RestaurantRecord r;

      s.removeRightFront(r);
      restaurantSorter.add(r);
   } // end for

   restaurantSorter.changeToExtractionMode();
   
   for (int i = 0, z = restaurantSorter.size(); i < z; i++) {
      RestaurantRecord r;

      restaurantSorter.removeFirst(r);
      s.addRightFront(r);
      s.advance();
   } // end for
   s.moveToStart();
} // sortData

int main(int argc, char* argv[])
{
	RestaurantList rList;
	doLoadData(rList);
	cout << "Unsorted Restaurants" << endl;
	cout << rList << endl;
	sortData(rList);
	cout << "Sorted Restaurants" << endl;
	cout << rList << endl;

	return 0;
}