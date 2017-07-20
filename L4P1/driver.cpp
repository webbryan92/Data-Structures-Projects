//-------------------------------------------------------------------
// file: driver.cpp
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// obtain classes and operations from Include files
//-------------------------------------------------------------------

#include "wrapper.h"
#include "IntTextMap.h"

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
	cout << "        d - add" << endl;
	cout << "        u - remove" << endl;
	cout << "        1 - removeAny" << endl;
	cout << "        v - value" << endl;
	cout << "        ? - hasKey" << endl;
	cout << "        z - size" << endl;
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
		cout << "which Map? 1 or 2:";
		cin >> index;
	} while ((index < 1) || (index > 2));
	cout << endl;
	return (index);
}	// getIndex

//-------------------------------------------------------------------

void getInteger (produces Integer& x)
{
	cout << "Enter a key value (integer):";
	cin >> x;
}	// getInteger

//-------------------------------------------------------------------

void getText (produces Text& s)
{
	cout << "Enter text string:";
	cin >> s;
}	// getText

//-------------------------------------------------------------------

void doAdd (alters ITMap& m1, alters ITMap& m2)
   // Note: this client does not check 'add' requires clause
{
	Integer i, key;
	Text value;

	cout << "Add to ";
	i = getIndex ();
	getInteger (key);
	getText (value);

	if (i == 1) {
		m1.add (key, value);
	} else {
		m2.add (key, value);
	}	// end if
	cout << endl << "m" << i << ".add (key, value); executed." << endl;
	cout << "key = " << key <<"   value = " << value << endl;
}	// doAdd

//-------------------------------------------------------------------

void doRemove (alters ITMap& m1, alters ITMap& m2)
   // Note: this client does not check 'remove' requires clause
{
	Integer i, key, keyFromMap;
	Text value;

	cout << "Remove from ";
	i = getIndex ();
	getInteger (key);
	if (i == 1) {
		m1.remove (key, keyFromMap, value);
	} else {
		m2.remove (key, keyFromMap, value);
	}	// end if
	cout << endl << "m" << i << ".remove (key, keyFromMap, value); executed." << endl;
	cout << "key = " << key << endl;
	cout << "keyFromMap = " << keyFromMap << endl;
	cout << "value = " << value << endl;
}	// doRemove

//-------------------------------------------------------------------

void doRemoveAny (alters ITMap& m1, alters ITMap& m2)
   // Note: this client does not check 'removeAny' requires clause
{
	Integer i, key;
	Text value;

	cout << "Remove any from ";
	i = getIndex ();
	if (i == 1) {
		m1.removeAny (key, value);
	} else {
		m2.removeAny (key, value);
	}	// end if
	cout << endl << "m" << i << ".removeAny (key, value); executed." << endl;
	cout << "key = " << key <<"   value = " << value << endl;
}	// doRemoveAny

//-------------------------------------------------------------------

void doValue (preserves ITMap& m1, preserves ITMap& m2)
   // Note: this client does not check 'removeAny' requires clause
{
	Integer i, key;

	cout << "Access value in ";
	i = getIndex ();
	getInteger (key);
	if (i == 1) {
		cout << "m1.value(" << key << ") = " << m1.value(key) << endl;
	} else {
		cout << "m2.value(" << key << ") = " << m2.value(key) << endl;
	}	// end if
}	// doValue

//-------------------------------------------------------------------

void doSize (preserves ITMap& m1, preserves ITMap& m2)
{
	Integer i, z;

	cout << "Size of ";
	i = getIndex ();
	if (i == 1) {
		z = m1.size ();
	} else {
		z = m2.size ();
	}	// end if
	cout << "|m" << i << "| = " << z << endl;
}	// doSize

//-------------------------------------------------------------------

void doHasKey (preserves ITMap& m1, preserves ITMap& m2)
{
	Boolean b;
	Integer i, key;

	cout << "Has key in ";
	i = getIndex ();
	getInteger (key);
	if (i == 1) {
		b = m1.hasKey (key);
	} else {
		b = m2.hasKey (key);
	}	// end if
	cout << key << " is";
	if (!b) {
		cout << " not";
	}   // end if
	cout << " in m" << i << endl;
}	// doHasKey


//-------------------------------------------------------------------

void doTransferFrom(alters ITMap& m1, alters ITMap& m2)
{
	Integer index;

	cout << "Transfer from ";
	index = getIndex();
	if (index == 1) {
		m2.transferFrom(m1);
		cout << endl << "m2.transferFrom(m1); executed." << endl;
	} else {
		m1.transferFrom(m2);
		cout << endl << "m1.transferFrom(m2); executed." << endl;
	} // end if
}	// doTransferFrom

//-------------------------------------------------------------------

void doCopy (alters ITMap& m1, alters ITMap& m2)
{
	Integer i;

	cout << "Copy ";
	i = getIndex ();
	if (i == 1) {
		m2 = m1;
		cout << "m2 = m1; executed." << endl;
	} else {
		m1 = m2;
		cout << "m1 = m2; executed." << endl;
	}	// end if
}	// doCopy

//-------------------------------------------------------------------

void doDisplay (preserves ITMap& m1, preserves ITMap& m2)
{
	Integer i;

	cout << "Display ";
	i = getIndex ();
	cout << "m" << i << " = ";
	if (i == 1) {
		cout << m1 << endl;
	} else {
		cout << m2 << endl;
	}	// end if
}	// doDisplay

//-------------------------------------------------------------------

void doClear (alters ITMap& m1, alters ITMap& m2)
{
	Integer i;

	cout << "Clear ";
	i = getIndex ();
	if (i == 1) {
		m1.clear ();
	} else {
		m2.clear ();
	}	// end if
	cout << endl << "m" << i << ".clear ()  executed." << endl;
}	// doClear

//-------------------------------------------------------------------

void inputFromFile (
		alters ITMap& m1,
		alters ITMap& m2
	)
{
	Boolean successful;
	Integer i, size, index, key;
	Text filename, value;
	File input;
	ITMap m;

	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	
	input.openFile (filename, File::openForRead, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	} else {
		input.read (size, successful);
		for (i = 0; i < size; i++) {
			input.read (key, successful);
			input.read (value, successful);
			m.add (key, value);
		}	// end for
		input.closeFile (successful);

		cout << "Load file into ";
		index = getIndex ();
		if (index == 1) {
			m1.transferFrom(m);
		} else {
			m2.transferFrom(m);
		}	// end if
	}	// end if
}	// inputFromFile

//-------------------------------------------------------------------

void outputToFile (
		preserves ITMap& m1,
		preserves ITMap& m2
	)
{
	Boolean successful;
	Integer i, z, index, key;
	Text filename, value;
	File output;
	ITMap m, temp;

	// get file name from user
	// open file for writing
	cout << "Enter data file name: ";
	cin >> filename;
	cout << endl;
	output.openFile (filename, File::openForWrite, successful);

	if (!successful) {
		cout << "Could not successfully open file" << endl;
	} else {
		// find out from which PartialMap to output contents.
		cout << "Output from ";
		index = getIndex ();

		// swap contents of chosen PartialMap into local m.
		// note:   
		// &=   is an infix operator that swaps the values
		//      of two different PartialMap objects.
		if (index == 1) {
			m.transferFrom(m1);
		} else {
			m.transferFrom(m2);
		}	// end if

		// write to file:
		// 1) write an Integer telling how many items are in m
		// 2) write each item found in m
		// note: 
		// after loop has finished, m must contain
		// the same values as before, in same order.
		z = m.size ();
		output.write (z, successful);
		for (i = 0; i < z; i++) {
			m.removeAny (key, value);
			output.write (key, successful);
			output.write (value, successful);
			temp.add (key, value);
		}	// end for
		output.closeFile (successful);

		// swap the contents of local m back into original
		if (index == 1) {
			m1.transferFrom(temp);
		} else {
			m2.transferFrom(temp);
		}	// end if
	}  // end if
}	// outputToFile

//-------------------------------------------------------------------

void dispatchCommand (
		preserves Character command,
		alters Boolean& showMenu,
		alters ITMap& m1,
		alters ITMap& m2
	)
{
	switch (command) {
		case 'g':	// toggle display Menu
			showMenu = !showMenu;
			break;
		case 'd':
			doAdd (m1, m2);
			break;
		case 'u':
			doRemove (m1, m2);
			break;
		case '1':
			doRemoveAny (m1, m2);
			break;
		case 'v':
			doValue (m1, m2);
			break;
		case 'z':
			doSize (m1, m2);
			break;
		case '?':
			doHasKey (m1, m2);
			break;
		case 'x':
			doTransferFrom (m1, m2);
			break;
		case '=':
			doCopy (m1, m2);
			break;
		case 'l':
			inputFromFile (m1, m2);
			break;
		case 'o':
			outputToFile (m1, m2);
			break;
		case 'p':
			doDisplay (m1, m2);
			break;
		case 'c':	
			doClear (m1, m2);
			break;
		case 'q':
			cout << "Quit Command Interpreter" << endl;
			break;
		case '@':
			cout << "Authored by Dr. Holly" << endl;
			break;
		default:
			cout << "Unknown command: " << command << endl;
			cout << "Please reenter your command" << endl;
			break;
	}	// end switch
}	// dispatchCommand

//-------------------------------------------------------------------

void commandController (
		alters ITMap& m1,
		alters ITMap& m2,
		alters Boolean& showMenu
	)
{
	Character command;

	do {
		if (showMenu) {
			displayMenu ();
		}	// end if
		getCommand (command);
		dispatchCommand (command, showMenu, m1, m2);
	} while (command != 'q' && command != 'Q');
} // commandController

//-------------------------------------------------------------------
// main executable body
//-------------------------------------------------------------------

int main (int argc, char* argv[])
{
	Boolean showMenu = (argc == 1);
	ITMap m1, m2;

	commandController (m1, m2, showMenu);
	cout << "end program" << endl;
	return 0;
}	// end main
