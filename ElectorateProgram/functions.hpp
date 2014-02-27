/*	
 *	Logan M. Wunder
 *	
 *	FUNCTIONS - Contains general helper assistance functions
 *	
 */	

#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <string>

#include "candidate.hpp"
#include "candidateDataSet.hpp"

/*
**	Headers should not include using declarations to eliminate
**	namespace conflicts...
*/

/* 
 *  Global Function Definitions
 */
void printMenu( bool[], candidateDataSet* );
char getOption();
bool getYesNoOption();
std::string getFilePath();
void printOptionError( char& );
void printFileError();

candidateDataSet* createElectorate( candidateDataSet* );
void viewElectorateList( candidateDataSet* );
void loadElectorateFile( candidateDataSet* );
void saveElectorateFile( candidateDataSet* );
void addCandidate( candidateDataSet* );
void removeCandidate( candidateDataSet* );
void editCandidate( candidateDataSet* );

#endif
