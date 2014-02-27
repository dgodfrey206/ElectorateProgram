/*	
 *	Logan M. Wunder
 *	
 *	CANDIDATE - Implementation
Description: None
 *	
 */

#include <string>
#include <iostream>
#include <iomanip>
#include "candidate.hpp"

using std::string;
using std::setprecision;
using std::setw;
using std::cout;
using std::cin;
using std::getline;
using std::endl;

/*
**
**		C O N S T R U C T O R S  /  D E S T R U C T O R S
**
*/
candidate::candidate()
{
	// Call Function to Prompt for Name
	fullName = "Frank Underwood";
	votes = 9001;
}

candidate::candidate( string argName, unsigned argVotes )
{
	fullName = argName;
	votes = argVotes;
}

candidate::candidate( const candidate &orig )
{
	setFullName( orig.getFullName());
	setVotes( orig.getVotes());
}

candidate::~candidate()
{
	// No dangling pointers here to delete so far...
}

/*
**
**		A C C E S S O R S
**
*/
string candidate::getFullName() const
{
	return fullName;
}

unsigned candidate::getVotes() const
{
	return votes;
}

/*
**
**		M U T A T O R S
**
*/
void candidate::setFullName( string argName )
{
	fullName = argName;
}
	// Accepts a candidate's name as a string

void candidate::setVotes( unsigned argVotes )
{
	votes = argVotes;
}
	// Accepts a candidate's vote count

/*
**
**		O P E R A T I O N S   &   O V E R L O A D S
**
*/
void candidate::operator=( const candidate &rhs_input )
{
	setFullName( rhs_input.getFullName() );
	setVotes( rhs_input.getVotes() );
}

bool candidate::operator==( const candidate &rhs_comp )
{
	bool b_NamesAreEqual = ( getFullName() == rhs_comp.getFullName() );
	bool b_VotesAreEqual = ( getVotes() == rhs_comp.getVotes() );

	if( b_NamesAreEqual && b_VotesAreEqual )
		return true;
	else
		return false;
}

bool candidate::operator!=( const candidate &rhs_comp )
{
	bool b_NamesAreEqual = ( getFullName() == rhs_comp.getFullName() );
	bool b_VotesAreEqual = ( getVotes() == rhs_comp.getVotes() );

	if( b_NamesAreEqual || b_VotesAreEqual )
		return false;
	else
		return true;
}

bool candidate::operator<( const candidate &rhs_comp )
{
	bool b_rhsNameLarger = ( getFullName() < rhs_comp.getFullName() );
	bool b_rhsVoteLarger = ( getVotes() < rhs_comp.getVotes() );

	if( b_rhsNameLarger && b_rhsVoteLarger )
		return true;
	else
		return false;
}

bool candidate::operator>( const candidate &rhs_comp )
{
	bool b_lhsNameLarger = ( getFullName() > rhs_comp.getFullName() );
	bool b_lhsVoteLarger = ( getVotes() > rhs_comp.getVotes() );

	if( b_lhsNameLarger && b_lhsVoteLarger )
		return true;
	else
		return false;
}

void candidate::printStats( unsigned i_totalVotes ) const
{
	if( i_totalVotes < 1 )
		cout << "Error: Total votes cannot be 0!" << endl;

	// Pad the full name of the candidate up to 3 characters
	short unsigned padding = 3 - ( fullName.length() % 3 );

	cout << setw( fullName.length() + padding );
	cout << fullName << " | ";
	cout << setw( 10 );	// Same length as "Vote Count"
	cout << votes << " | ";
	cout << setprecision( 4 );
	// Cast both values as doubles, then multiply by 100 to get the % points
	cout << ( ( (double)votes / (double)i_totalVotes ) * 100 ) << " %";
	cout << endl;

}