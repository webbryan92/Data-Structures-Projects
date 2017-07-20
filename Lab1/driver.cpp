//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"

#include "List\List1.hpp"
#include "List\ListChecking.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef List1<Text> TextList;
#else
// Compiling in Debug configuration
#include "QUEUE\QueueChecking.hpp"
typedef ListChecking1 <List1, Text> TextList;
#endif

//-------------------------------------------------------------------
// program constants
//-------------------------------------------------------------------

void displayMenu(void)
{
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;
	cout << "     Command -  Result" << endl;
	cout << "        g - toggle display menu" << endl;
	cout << "        e - addRightFront" << endl;
	cout << "        d - removeRightFront" << endl;
	cout << "        r - replaceRightFront" << endl;
	cout << "        f - rightFront" << endl;
	cout << "        a - advance" << endl;
	cout << "        < - moveToStart" << endl;
	cout << "        > - moveToFinish" << endl;
	cout << "        s - swapRights" << endl;
	cout << "        ( - leftLength" << endl;
	cout << "        ) - rightLength" << endl;
	cout << "        x - transferFrom" << endl;
	cout << "        = - copy" << endl;
	cout << "        l - load from file" << endl;
	cout << "        o - output to file" << endl;
	cout << "        p - display" << endl;
	cout << "        c - clear" << endl;
	cout << "        q - quit program" << endl;
	cout << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl << "        command:";
}	// showMenu

//-------------------------------------------------------------------

void getCommand(
		produces Character& command
	)
{
	cin >> command;
	cout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex(void)
{
	Integer index;

	do {
		cout << "which List? 1 or 2:";
		cin >> index;
	} while ((index < 1) ||(index > 2));
	cout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void getText(produces Text& s)
{
	cout << "Enter text string:";
	cin >> s;
}	// getText

//-------------------------------------------------------------------

void doAddRightFront(TextList & s1, TextList & s2)
{
	Integer index;
	Text x;

	cout <<  "Add right to ";
	index = getIndex();
	getText(x);
	if (index ==1) {
		s1.addRightFront(x);
	} else {
		s2.addRightFront(x);
	} //end if
	cout << endl << "s" << index << ".addRightFront(x); executed." << endl;
	cout << "x = " << x << endl;
	//doAddRightFront
}

//-------------------------------------------------------------------

void doAdvance(TextList & s1, TextList & s2)
{
	Integer index;

	cout << "Advance ";
	index = getIndex();
	if (index ==1) {
		s1.advance();
	} else {
		s2.advance();
	} //end if
	cout << "s" << index << ".advance(); executed." << endl;
	//doAdvance
}

//-------------------------------------------------------------------

void doRemoveRightFront(
		alters TextList& s1,
		alters TextList& s2
	)
{
	Integer index, z;
	Text x;

	cout << "Remove right from ";
	index = getIndex();
	if (index == 1) {
		z = s1.rightLength();
		if (z > 0) {
			s1.removeRightFront(x);
		} // end if
	} else {
		z = s2.rightLength();
		if (z > 0) {
			s2.removeRightFront(x);
		} // end if
	}	// end if
	if (z > 0) {
		cout << endl << "s" << index << ".removeRightFront(x); executed." << endl;
		cout << "x = " << x << endl;
	} else {
		cout << "Error: |s" << index << ".right| = 0 - cannot Remove right from an empty " << "s" << index << ".right." << endl;
	} // end if
}	// doRemoveRightFront

//-------------------------------------------------------------------

void doReplaceRightFront(
		alters TextList& s1,
		alters TextList& s2
	)
{
	Integer index, z;
	Text x;

	cout << "Replace right front of ";
	index = getIndex();
	if (index == 1) {
		z = s1.rightLength();
		getText(x);
		if (z > 0) {			
			s1.replaceRightFront(x);
		} // end if
	} else {
		z = s2.rightLength();
		getText(x);
		if (z > 0) {			
			s2.replaceRightFront(x);
		} // end if
	}	// end if
	if (z > 0) {
		cout << endl << "s" << index << ".replaceRightFront(x); executed." << endl;
		cout << "x = " << x << endl;
	} else {
		cout << "Error: |s" << index << ".right| = 0 - cannot replace right front from an empty " << "s" << index << ".right." << endl;
	} // end if
}	// doReplaceRightFront

//-------------------------------------------------------------------

void doRightFront(
		preserves TextList& s1,
		preserves TextList& s2
	)
{
	Integer index;

	cout << "Access right front ";
	index = getIndex();
	if (index == 1) {
		if (s1.rightLength() > 0) {
			cout << "s1.rightFront() = " << s1.rightFront() << endl;
		} else {
			cout << "Error: |s1| = 0 - cannot access front of an empty s1.rightFront." << endl;
		} // end if
	} else {
		if (s2.rightLength() > 0) {
			cout << "s2.rightFront() = " << s2.rightFront() << endl;
		} else {
			cout << "Error: |s2| = 0 - cannot access front of an empty s2.rightFront." << endl;
		} // end if
	}	// end if
}	// doRightFront

//-------------------------------------------------------------------

void doRightLength(
		preserves TextList& s1,
		preserves TextList& s2
	)
{
	Integer index, z;

	cout << "Right length of ";
	index = getIndex();
	if (index == 1) {
		z = s1.rightLength();
	} else {
		z = s2.rightLength();
	}	// end if
	cout << "|s" << index << ".right| = " << z << endl;
}	// doRightLength

//-------------------------------------------------------------------

void doLeftLength(
		preserves TextList& s1,
		preserves TextList& s2
	)
{
	Integer index, z;

	cout <<  "Left length of ";
	index = getIndex();
	if (index == 1) {
		z = s1.leftLength();
	} else {
		z = s2.leftLength();
	}	// end if
	cout << "|s" << index << ".left| = " << z << endl;
}	// doLength

//-------------------------------------------------------------------

void doMoveToFinish(TextList& s1, TextList& s2)
{
	Integer index;

	cout << "Move to finish ";
	index = getIndex();
	if(index == 1) {
		s1.moveToFinish();
	} else {
		s2.moveToFinish();
	}
	cout <<  "s" << index << ".moveToFinish(); executed." << endl;
}

//-------------------------------------------------------------------

void doMoveToStart(TextList& s1, TextList& s2)
{
	Integer index;

	cout << "Move to start ";
	index = getIndex();
	if(index == 1) {
		s1.moveToStart();
	} else {
		s2.moveToStart();
	}
	cout << "s" << index << ".moveToStart(); executed." << endl;
}

//-------------------------------------------------------------------

void doSwapRights(
		alters TextList& s1,
		alters TextList& s2
	)
{
	s1.swapRights(s2);
	cout << endl << "s1.swapRights(s2); executed." << endl;

}	// doSwapRights

//-------------------------------------------------------------------

void doTransferFrom(
		alters TextList& s1,
		alters TextList& s2
	)
{
	Integer index;

	cout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		s2.transferFrom(s1);
		cout << endl << "s2.transferFrom(s1); executed." << endl;
	} else {
		s1.transferFrom(s2);
		cout << endl << "s1.transferFrom(s2); executed." << endl;
	} // end if
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy(
		alters TextList& s1,
		alters TextList& s2
	)
{
	cout << "Copy ";
	if (getIndex() == 1) {
		s2 = s1;
		cout << "s2 = s1; executed." << endl;
	} else {
		s1 = s2;
		cout << "s1 = s2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void display(
		preserves TextList& s
	)
{
	TextList sTemp;
	Integer lftLngth;

	lftLngth = s.leftLength();
	s.moveToStart();
	cout << "<";
	for(int i = 0, z = lftLngth, lastItem = (z - 1); i < z; i++){
		Text x;
		s.removeRightFront(x);
		cout << x;
		sTemp.addRightFront(x);
		sTemp.advance();
		if (i < lastItem) {
			cout << ",";
		} // end if
	}
	cout << "> ";
	cout << "<";
	for(int i = 0, z = s.rightLength(), lastItem = (z - 1); i < z; i++) {
		Text x;
		s.removeRightFront(x);
		cout << x;
		sTemp.addRightFront(x);
		sTemp.advance();
		if (i < lastItem) {
			cout << ",";
		} // end if
	}	// end for
	cout << ">" << endl <<endl;
	sTemp.moveToStart();
	for(int i = 0, z = lftLngth; i < z; i++){
		sTemp.advance();
	}
	s.transferFrom(sTemp);
}	// display

//-------------------------------------------------------------------

void doDisplay(
		preserves TextList& s1,
		preserves TextList& s2
	)
{
	Integer index;

	cout << "Display ";
	index = getIndex();
	cout << "s" << index << " = ";
	if (index == 1) {
		display(s1);
	} else {
		display(s2);
	}	// end if
}	// doDisplay

//-------------------------------------------------------------------

void doClear(
		TextList& s1,
		TextList& s2
	)
{
	Integer index;

	cout << "Clear ";
	index = getIndex();
	if (index == 1) {
		s1.clear();
	} else {
		s2.clear();
	}	// end if
	cout << endl << "s" << index << ".clear(); executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile(
		alters TextList& s1,
		alters TextList& s2
	)
{
	Boolean successful;
	Integer size, index;
	Text filename, x;
	File input;
	TextList s;

	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	
	input.openFile(filename, File::openForRead, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	} else {
		input.read(size, successful);
		for(int i = 0; i < size; i++) {
			input.read(x, successful);
			s.addRightFront(x);
		}	// end for
		input.closeFile(successful);

		cout << "Load file into ";
		index = getIndex();
		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile(
		preserves TextList& s1,
		preserves TextList& s2
	)
{
	Boolean successful;
	Integer z, index, left;
	Text filename, x;
	File output;
	TextList s;

	// get file name from user
	// open file for writing
	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	output.openFile(filename, File::openForWrite, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	} else {
		// find out from which List to output contents.
		cout << "Output from ";
		index = getIndex();

		// transfer contents of chosen List into local s.
		if (index == 1) {
			s.transferFrom(s1);
		} else {
			s.transferFrom(s2);
		}	// end if

		// write to file:
		// 1) write an Integer telling how many items are in s
		// 2) write each item found in s
		// note: 
		// after loop has finished, s must contain
		// the same values as before, in same order.
		z = s.leftLength() + s.rightLength();
		left = s.leftLength();
		s.moveToStart();
		output.write(z, successful);
		for(int i = 0; i < z; i++) {
			s.removeRightFront(x);
			output.write(x, successful);
			s.addRightFront(x);
			s.advance();
		}	// end for
		output.closeFile(successful);
		s.moveToStart();
		for(int i = 0; i < left; i++) {
			s.advance();
		}
		// transfer the contents of local s back into original
		if (index == 1) {
			s1.transferFrom(s);
		} else {
			s2.transferFrom(s);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand(
		Character command,
	    Boolean& showMenu,
		TextList& s1,
		TextList& s2
	)
{
	switch(command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'e':
			doAddRightFront(s1, s2);
			break;
		case 'd':
			doRemoveRightFront(s1, s2);
			break;
		case 'r':
			doReplaceRightFront(s1, s2);
			break;
		case 'f':
			doRightFront(s1, s2);
			break;
		case 'a':
			doAdvance(s1, s2);
			break;
		case '<':
			doMoveToStart(s1, s2);
			break;
		case '>':
			doMoveToFinish(s1, s2);
			break;
		case 's':
			doSwapRights(s1, s2);
			break;
		case '(':
			doLeftLength(s1, s2);
			break;
		case ')':
			doRightLength(s1, s2);
			break;
		case 'x':
			doTransferFrom(s1, s2);
			break;
		case '=':
			doCopy(s1, s2);
			break;
		case 'l':
			inputFromFile(s1, s2);
			break;
		case 'o':
			outputToFile(s1, s2);
			break;
		case 'p':
			doDisplay(s1, s2);
			break;
		case 'c':	
			doClear(s1, s2);
			break;
		case 'q':
			cout << "Quit Command Interpreter" << endl;
			break;
		default:
			cout << "Unknown command: " << command << endl;
			cout << "Please reenter your command" << endl;
			break;
	}	// end switch
}	// dispatchCommand

//-------------------------------------------------------------------

void commandController(
		TextList & s1,
		TextList & s2,
		Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);
		dispatchCommand(command, showMenu, s1, s2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main(int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	TextList s1, s2;

	commandController(s1, s2, showMenu);
	cout << "end program" << endl;
	return 0;
}	// end main
