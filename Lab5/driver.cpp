//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "List\List3.hpp"


#ifdef NDEBUG
// When NDEBUG is defined, that means: Compiling in Not Debug configuration = Release Configuration
typedef List3<Text> TextList;
#else
// Compiling in Debug configuration
#include "List\ListChecking.hpp"
typedef ListChecking1 <List3, Text> TextList;
#endif

//-------------------------------------------------------------------
// program constants
//-------------------------------------------------------------------

void displayMenu (void)
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

void holdScreen (void)
{
	Text x;

	cout << "Type Return to continue." << endl;
	cin >> x;
}	// holdScreen

//-------------------------------------------------------------------

void getCommand (
		produces Character& command
	)
{
	cin >> command;
	cout << endl;
}	// getCommand

//-------------------------------------------------------------------

Integer getIndex (void)
{
	Integer index;

	do {
		cout << "which List? 1 or 2:";
		cin >> index;
	} while ((index < 1) || (index > 2));
	cout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void doRemoveRightFrontOnCopy(TextList s)
	// requires |s.right| > 0
	// this operation is for exercising List3's copy constructor
	// that is why 's' is passed to this operation by value
{
	Text x;

	cout << "Start of doRemoveRightFrontOnCopy - s = " << s << endl;
	s.removeRightFront(x);	
	cout << "  End of doRemoveRightFrontOnCopy - s = " << s << endl;
} // doRemoveRightFrontOnCopy

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	TextList s1, s2;

	Integer i, z;
	Text x;
	Character command;

	do {
		if (showMenu) {
			displayMenu();
		}	// end if
		getCommand(command);

		switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'C':
			{
				const int bufferSize = 5;
				char cString[bufferSize];
				for (i = 4; i >= 0; i--) {
					sprintf_s (cString, bufferSize, "#%d", (int)i);
					x = cString;
					s2.addRightFront(x);
				} // end for
				s2.advance();
				s2.advance();
				cout << "  Before doRemoveRightFrontOnCopy - s = " << s2 << endl;
				doRemoveRightFrontOnCopy(s2);
				cout << "   After doRemoveRightFrontOnCopy - s = " << s2 << endl;
			}
			break;
		case 'e':
			cout << "Add right to ";
			i = getIndex();
			cout << "Enter text string:"; 
			cin >> x;
			if (i == 1) {
				s1.addRightFront(x);
			} else {
				s2.addRightFront(x);
			}	// end if
			cout << endl << "Executed s" << i << ".addRightFront(x);" << endl;
			cout << "x = " << x << endl;
			break;
		case 'd':
			cout << "Remove right from ";
			i = getIndex();
			if (i == 1) {
				s1.removeRightFront(x);
			} else {
				s2.removeRightFront(x);
			}	// end if
			cout << endl << "Executed s" << i << ".removeRightFront(x);" << endl;
			cout << "x = " << x << endl;
			break;
		case 'r':
			cout << "Replace right front of ";
			i = getIndex();
			cout << "Enter text string:"; 
			cin >> x;
			if (i == 1) {
				s1.replaceRightFront(x);
			} else {

				s2.replaceRightFront(x);
			}	// end if
			cout << endl << "Executed s" << i << ".replaceRightFront(x);" << endl;
			cout << "x = " << x << endl;
			break;
		case 'f':
			cout << "Access right front ";
			i = getIndex();
		   if (i == 1) {
			cout << "s1.rightFront() = " << s1.rightFront() << endl;
		   } else {
			cout << "s2.rightFront() = " << s2.rightFront() << endl;
		   } // end if
		   break;
		case 'a':
			cout << "Advance ";
			i = getIndex();
			if (i == 1) {
				s1.advance();
			} else {
				s2.advance();
			}	// end if
			cout << "Executed s" << i << ".advance();" << endl;
			break;
		case '<':
			cout << "Move to start ";
			i = getIndex();
			if (i == 1) {
				s1.moveToStart();
			} else {
				s2.moveToStart();
			}	// end if
			cout << "Executed s" << i << ".moveToStart();" << endl;
			break;
		case '>':
			cout << "Move to finish ";
			i = getIndex();
			if (i == 1) {
				s1.moveToFinish();
			} else {
				s2.moveToFinish();
			}	// end if
			cout << "Executed s" << i << ".moveToFinish();" << endl;
			break;
		case 's':
			s1.swapRights(s2);
			cout << endl << "Executed s1.swapRights(s2);" << endl;
			break;
		case '(':
			cout << "Left length of ";
			i = getIndex();
			if (i == 1) {
				z = s1.leftLength();
			} else {
				z = s2.leftLength();
			}	// end if
			cout << "|s" << i << ".left| = " << z << endl;
			break;
		case ')':
			cout << "Right length of ";
			i = getIndex();
			if (i == 1) {
				z = s1.rightLength();
			} else {
				z = s2.rightLength();
			}	// end if
			cout << "|s" << i << ".right| = " << z << endl;
			break;
		case 'x':
			cout << "Transfer from ";
			i = getIndex();
			if (i == 1) {
				s2.transferFrom(s1);
				cout << endl << "Executed s2.transferFrom(s1);" << endl;
			} else {
				s1.transferFrom(s2);
				cout << endl << "Executed s1.transferFrom(s2);" << endl;
			} // end if
			break;
		case '=':
			cout << "Copy ";
			i = getIndex();
			if (i == 1) {
				s2 = s1;
				cout << "Executed s2 = s1;" << endl;
			} else {
				s1 = s2;
				cout << "Executed s1 = s2;" << endl;
			}	// end if
			break;
		case 'l':
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
					for (int i = 0; i < size; i++) {
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
			}
			break;
		case 'o':
			{
				Boolean successful;
				Integer lz, z, index;
				Text filename;
				File output;
				TextList s;

				cout << "Enter data file name: ";
				cin >> filename;
				cout << endl;
				output.openFile(filename, File::openForWrite, successful);

				if (!successful) {
					cout << "Could not successfully open file" << endl;
				} else {
					cout << "Output from ";
					index = getIndex();

					if (index == 1) {
						s.transferFrom(s1);
					} else {
						s.transferFrom(s2);
					}	// end if

					lz = s.leftLength();
					s.moveToStart();
					z = s.rightLength();
					output.write(z, successful);
					for (int i = 0; i < z; i++) {
						output.write(s.rightFront(), successful);
						s.advance();
					}	// end for
					output.closeFile(successful);

					s.moveToStart();
					for (int i = 0; i < lz; i++) {
						s.advance();
					}	// end for

					if (index == 1) {
						s1.transferFrom(s);
					} else {
						s2.transferFrom(s);
					}	// end if
				}  // end if
			}
			break;
		case 'p':
			cout << "Display ";
			i = getIndex();
			cout << "s" << i << " = ";
			if (i == 1) {
				cout << s1 << endl;
			} else {
				cout << s2 << endl;
			}	// end if
			cout << endl;
			break;
		case 'c':	
			cout << "Clear ";
			i = getIndex();
			if (i == 1) {
				s1.clear();
			} else {
				s2.clear();
			}	// end if
			cout << endl << "s" << i << ".clear();" << endl;
			break;
		case '@':
			cout << "Driver supplied by Dr. Holly" << endl;
			break;
		case 'q':
			cout << "Quit Command Interpreter" << endl;
			break;
		default:
			cout << "Unknown command: " << command << endl;
			cout << "Please reenter your command" << endl;
			break;
		}	// end switch
	} while (command != 'q' && command != 'Q');
	cout << "end program" << endl;
	return 0;
}	// end main
