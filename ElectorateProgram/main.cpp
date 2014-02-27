/*	
 *	Logan M. Wunder
 *	
 *	MAIN - User Front End to program
 *	
 */	

#include <iostream>
#include <string>

#include "candidate.hpp"
#include "candidateDataSet.hpp"
#include "functions.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
 *	Application Flags
 */
bool appStateFlags[3] =
{
	false,	// List - isLoaded
	true,	// List - isSaved
	false	// Program - exit
};

int main()
{
	cout << "-= Initializing Program =-" << endl;

	char menuOption = '\0';
	
	// Perhaps to save some trouble you should at least INITIALIZE IT!!!
	candidateDataSet *g_pList = new candidateDataSet();

	cout << "= Votes are In; Ready to Launch =" << endl;
	cout << endl;

	do
	{
		printMenu( appStateFlags, g_pList );

		menuOption = getOption();

		cout << "\n";

		switch( menuOption )
		{
		case 'V':
		case 'v':
			if( g_pList->isValid() )
			{
				viewElectorateList( g_pList );
			}
			else
			{
				cout << "There is no list to view!" << endl;
			}

			break;
		case 'A':
		case 'a':
			if( g_pList->isValid() )
			{
				addCandidate( g_pList );
			}
			else
			{
				cout << "You must load a list to add candidates to." << endl;
			}
			break;
		case 'E':
		case 'e':
			if( g_pList->isValid() )
			{
				editCandidate( g_pList );
			}
			else
			{
				cout << "You must load a list to edit candidates." << endl;
			}
			break;
		case 'R':
		case 'r':
			if( g_pList->isValid() )
			{
				removeCandidate( g_pList );
			}
			else
			{
				cout << "You must load a list to delete candidates from." << endl;
			}
			break;
		case 'N':
		case 'n':
			if( g_pList->isValid() )
			{
				cout << "Are you sure you wish to start a new candidate list?" << endl;
				if( g_pList->isModified() )
				{
					cout << "Note: This will overwrite your unsaved work..." << endl;
				}

				if( !getYesNoOption() )
				{
					break;		// The key here is evaluating getYesNoOption(), and then breaking out of the switch
				}
				
				createElectorate( g_pList );
			}
			else
			{
				g_pList = createElectorate( g_pList );
			}
			break;
		case 'S':
		case 's':
			if( g_pList->isValid() && g_pList->isModified() )
			{
				saveElectorateFile( g_pList );
			}
			else if( g_pList->isValid() && g_pList->isModified() )
			{
				cout << "There have been no changes since the last save." << endl;
			}
			else
			{
				cout << "There is no list to save!" << endl;
			}
			break;
		case 'L':
		case 'l':
			if( g_pList->isValid() )
			{
				cout << "Are you sure you wish to load a candidate list?" << endl;

				if( g_pList->isModified() )
					cout << "Note: You will lose any unsaved work..." << endl;

				if( !getYesNoOption() )	// No
				{
					break;
				}
				// Yes
			}
			loadElectorateFile( g_pList );

			break;
		case 'Q':
		case 'q':
			if( g_pList->isValid() && g_pList->isModified() )
			{
				cout << "Are you sure you want to quit with unsaved data?" << endl;

				appStateFlags[2] = getYesNoOption();
			}
			else
				appStateFlags[2] = true;
			break;

		case '\0':
		default:
			printOptionError( menuOption );
			break;
		}

	}
	while( appStateFlags[2] != true );

	if( g_pList != NULL )
	{
		delete g_pList;
		g_pList = NULL;
	}
	
	return EXIT_SUCCESS;
}