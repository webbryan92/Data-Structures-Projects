// L3P2Win.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "L3P2Win.h"
#include "RestaurantRecord.h"
#include "RestaurantSorter.h"
#include "List\List1.hpp"
#include "resource.h"
#include "RestaurantList.h"
#include "ComFileDialog\ComFileDialog.hpp"

#ifdef NDEBUG
typedef List1<RestaurantRecord> RestaurantList;
#else
#include "List\ListChecking.hpp"
typedef ListChecking1<List1, RestaurantRecord> RestaurantList;
#endif

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
RestaurantList globalL;							// RestaurantList holder
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
				   _In_opt_ HINSTANCE hPrevInstance,
				   _In_ LPTSTR    lpCmdLine,
				   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_L3P2WIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_L3P2WIN));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
void sortDataType (alters RestaurantList& s)
   // requires s.left = < >
   // ensures s.left = < >  and  s.right is sorted
{
   RestaurantRecordSorterType restaurantSorter;

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
} // sortDataType

void sortData (alters RestaurantList& s)
   // requires s.left = < >
   // ensures s.left = < >  and  s.right is sorted
{
   RestaurantRecordSorterName restaurantSorter;

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
void doPaintData(HDC hdc, preserves RestaurantList& s){
	const int bufferSize = 10;
	char cString[bufferSize];
	RestaurantList sTemp;
	Integer yLoc, xLoc;
	Integer lineHeight;
	SIZE strSize;
	Text y;
	Integer inc;

	inc = 200;
	yLoc = 10;
	xLoc = 10;

	s.moveToStart();
	for(int i = 0, z = s.rightLength(); i < z; i++){
		RestaurantRecord x;
		s.removeRightFront(x);
		TextOut(hdc, xLoc, yLoc, x.name, x.name.size());
		sprintf_s(cString, bufferSize, "%d", (int)x.restaurantID);
		y = cString;
		xLoc += inc + 20;
		TextOut(hdc, xLoc, yLoc, y, y.size());
		xLoc += inc - 50;
		TextOut(hdc, xLoc, yLoc, x.type, x.type.size());
		xLoc += inc - 50;
		TextOut(hdc, xLoc, yLoc, x.street, x.street.size());
		xLoc += inc;
		TextOut(hdc, xLoc, yLoc, x.city, x.city.size());
		xLoc += inc - 50;
		TextOut(hdc, xLoc, yLoc, x.state, x.state.size());
		sprintf_s(cString, bufferSize, "%d", (int)x.zip);
		y = cString;
		xLoc += inc - 50;
		TextOut(hdc, xLoc, yLoc, y, y.size());
		xLoc += inc - 50;
		TextOut(hdc, xLoc, yLoc, x.phone, x.phone.size());
		GetTextExtentPoint32(hdc, x.name, x.name.size(), &strSize);
		lineHeight = strSize.cy;
		yLoc += lineHeight;
		xLoc = 10;
		sTemp.addRightFront(x);
		sTemp.advance();
	}
	sTemp.moveToStart();
	s.transferFrom(sTemp);
}

void doHandleOpen (
	preserves HWND hwnd, 
	produces RestaurantList& s
	)
{
	Boolean successful;
	Text fileToRead, fullPath;
	File input;
	CommonFileDialog fileDialog;
	Integer size;
	RestaurantRecord r;

	fileDialog.getOpenFilename (hwnd, fileToRead, fullPath, successful);
	if (successful) {
		input.openFile (fileToRead, File::openForRead, successful);
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
			input.closeFile (successful);
		} // end if
	} // doHandleOpen
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_L3P2WIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_L3P2WIN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT clientRect;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_OPEN:
			doHandleOpen (hWnd, globalL);			
			//Schedule a WM_Paint
			GetClientRect(hWnd, &clientRect);
               InvalidateRect(hWnd, &clientRect, true);
			break;
		case ID_SORTRESTAURANTS_BYNAME:
			sortData(globalL);
			GetClientRect(hWnd, &clientRect);
               InvalidateRect(hWnd, &clientRect, true);
			break;
		case ID_SORTRESTAURANTS_BYTYPE:
			sortDataType(globalL);
			GetClientRect(hWnd, &clientRect);
               InvalidateRect(hWnd, &clientRect, true);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		doPaintData(hdc, globalL);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
