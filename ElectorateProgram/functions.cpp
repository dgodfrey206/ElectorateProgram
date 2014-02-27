/*	
 *	Logan M. Wunder
 *	
 *	FUNCTIONS - Contains general helper assistance functions
 *	
 */	

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "candidate.hpp"
#include "candidateDataSet.hpp"
#include "functions.hpp"

/* I'm lazy and want to save some typing */
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;

extern bool appStateFlags[3];

/* 
 *  Global Function Declarations
 */
void printMenu( bool appStateFlags[], candidateDataSet* p_List )
{
	cout << " -=( M a i n   M e n u )=- " << endl;
	if( p_List->isValid() ) 
		cout << "-= File " << p_List->getListName() << " Loaded =- " << endl;
	else 
		cout << " -= No File Loaded =- " << endl;

	cout << "[ N ] Create Candidate List" << endl;

	if( p_List->isValid() && p_List->isModified() ) 
		cout << "[ S ] Save Candidate List" << endl;

	cout << "[ L ] Load Candidate List" << endl;

	if( p_List->isValid() ) 
		cout << "[ V ] View Candidate List" << endl;

	if( p_List->isValid() ) 
		cout << "[ A ] Add a Candidate" << endl;

	if( p_List->isValid() ) 
		cout << "[ E ] Edit a Candidate" << endl;

	if( p_List->isValid() ) 
		cout << "[ R ] Remove a Candidate" << endl;

	cout << "[ Q ] Quit" << endl;
	cout << "----------------------" << endl;

	return;
}

char getOption()
{
	char option;

	cout << "Choose Your Option:\n";
	cout << "=>";
	cin >> option;

	if( cin.fail() )
	{
		cin.clear();

		option = '\0';
	}

	cin.sync();

	return option;
}

bool getYesNoOption()
{
	char option;

	cout << "=>";
	cin >> option;

	if( cin.fail() )
	{
		cin.clear();
		cin.sync();
		cout << "Error: Invalid input detected..." << endl;
		return false;
	} 

	cin.sync();

	if( option == 'Y' || option == 'y' )
		return true;
	else
		return false;
}

string getFileName()
{
	bool flgError = true;
	string fileName = "";

	do
	{
		cout << "Please type the name of your file:" << endl;
		cout << "=>";
		getline( cin, fileName );

		if( cin.bad() )
		{
			cin.clear();
			cin.sync();
			cout << "Error: Bad input detected. Let's try that again..." << endl;
			continue;
		}

		flgError = false;
	}
	while( flgError == true );

	return fileName;
}

void printOptionError( char& menuOption )
{
	cout << "{ " << menuOption << " } is not a valid menu option." << endl;
	cout << "Please view the list of options from the menu again..." << endl;
	cout << endl;

	return;
}

candidateDataSet* createElectorate( candidateDataSet *p_List )
{
	if( p_List->isValid() )
	{
		delete p_List;
		p_List = NULL;
	}

	p_List = new candidateDataSet();
	bool b_sure = false;
	
	do
	{
		cout << "What would you like to name your candidate list?" << endl;
		cout << "=>";

		string listName;

		getline( cin, listName );

		if( listName == "q" || listName == "Q" )
			return p_List;

		cout << "Are you sure you want to name your list " << listName << "?" << endl;
		b_sure = getYesNoOption();

		if( b_sure )
			p_List->setListName( listName );

		cout << endl;
	}
	while( !b_sure );

	p_List->setValidity( true );
	p_List->setModified( true );

	return p_List;
}

void viewElectorateList( candidateDataSet* g_pList )
{
	if( g_pList == NULL ) 
	{
		cout << "You have not loaded or started a candidate list!" << endl;
		return;
	}

	else if( g_pList->getListSize() == 0 )
		cout << g_pList->getListName() << " has no candidates entered in the list!" << endl;

	else
	{
		cout << " --=( " << g_pList->getListName() << " Report )=--" << endl;
		if( g_pList->getTotalVotes() == 0 )
			g_pList->calculateTotalVotes();
		g_pList->printList();
	}

	cout << endl;
}

void loadElectorateFile( candidateDataSet* p_List )
{
	string loadFileName = getFileName();

	ifstream if_file( loadFileName );

	if( if_file.good() )
	{
		// Avoid people wondering why they can't load files on startup
		if( p_List == NULL )
			p_List = new candidateDataSet();	// Create space for reading in info

		p_List->readElectorateFile( if_file );
		p_List->setValidity( true );
	}
	else
	{
		cout << "Warning: " << loadFileName << " is inaccessible." << endl;
		if( p_List->isModified() )
			cout << "Note: No changes were made to your previously loaded file" << endl;
		cout << endl;
	}
	return;
}

void saveElectorateFile( candidateDataSet* p_List )
{
	string loadFileName = getFileName();
	ofstream of_file( loadFileName );

	if( of_file.good() )
	{
		p_List->writeElectorateFile( of_file );
		p_List->setModified( true );
	}
	else
		cout << "Error: Could not save data :-( Uh Oh )..." << endl;
	cout << endl;
}

void addCandidate( candidateDataSet* g_pList )
{
	g_pList->addListItem();
	g_pList->setModified( true );
}

void removeCandidate( candidateDataSet* g_pList )
{
	bool b_sure = false;

	do
	{
		cout << "Type the name of the candidate you are searching for:" << endl;
		cout << "=>";

		string* p_ListName = new string("");
		
		getline( cin, *p_ListName );

		if( *p_ListName == "q" )
		{
			cout << "Candidate removal aborted..." << endl;
			cout << endl;
			return;	// Get out of this loop and go home...
		}

		cout << "Is " << *p_ListName << " correct?" << endl;
		b_sure = getYesNoOption();

		if( b_sure )
		{
			g_pList->deleteListItem( *p_ListName );
		}

		delete p_ListName;
	}
	while( !b_sure );
	g_pList->setModified( true );
}

void editCandidate( candidateDataSet* g_pList )
{
	bool b_sure = false;

	do
	{
		cout << "Type the name of the candidate you are searching for:" << endl;
		cout << "=>";

		string* p_ListName = new string("");
		
		getline( cin, *p_ListName );

		if( *p_ListName == "q" )
		{
			cout << "Candidate editing aborted..." << endl;
			cout << endl;
			return;	// Get out of this loop and go home...
		}

		cout << "Is " << *p_ListName << " correct?" << endl;
		b_sure = getYesNoOption();

		if( b_sure )
		{
			g_pList->modifyListItem( *p_ListName );
		}

		delete p_ListName;
	}
	while( !b_sure );
	g_pList->setModified( true );
}