/*	
 *	Logan M. Wunder
 *	
 *	CANDIDATE DATA SET - A container class for lists of candidates
 *	
 */	

#ifndef CAND_DATAFILE
#define CAND_DATAFILE

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "candidate.hpp"

/*
**	Headers should not include using declarations to eliminate
**	namespace conflicts...
*/

/*
**		C A N D I D A T E - D A T A - S E T - C L A S S
**
**		The Candidate Data Set Class stores a list of all electorates along
**		with the name and metadata for that list
**
*/
class candidateDataSet
{
private: bool b_isValid;
private: bool b_isModified;
private: std::string s_listName;
private: unsigned i_totalVotes;
private: std::vector<candidate> v_Candidate;

// Constructors and Destructors
public: candidateDataSet();						// Default
public: candidateDataSet( std::vector<candidate>&, std::string& );	// Copying a list
public: ~candidateDataSet();

// Accessors
public: bool isValid() const;
public: bool isModified() const;
public: std::string getListName() const;
public: unsigned getTotalVotes() const;
public: candidate getListItem( unsigned ) const;
public: unsigned getListSize() const;

// Mutators
public: void setValidity( bool );
public: void setModified( bool );
public: void setListName( std::string );
public: void setTotalVotes( unsigned );
public: void addTotalVotes( unsigned );
public: void addListItem();
public: bool modifyListItem( std::string& );
public: bool deleteListItem( std::string& );
public: void calculateTotalVotes();

// Member Operations
public: void sort();
public: std::vector<candidate>::iterator find( std::string& );
public: bool readElectorateFile( std::ifstream& );
public: void writeElectorateFile( std::ofstream& );
public: void printList();

		/*
		Mr. Bouchard - 2/24/2014 5:00 pm
		Be smart about your decisions with scholarships
		Let others know what you have on the table!!!
		PTK; 14000 scholarship, Computer Club, etc...
		*/
};

#endif