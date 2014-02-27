
/*	
 *	Logan M. Wunder
 *	
 *	CANDIDATE - Definition and Interface
Description: The Candidate class represents a candidate in the electorate. Only data regarding the candidate's name and vote count are stored, making this a simple class.
 *	
 */

#ifndef CANDIDATE
#define CANDIDATE

#include <string>

/*
**	Headers should not include using declarations to eliminate
**	namespace conflicts...
*/

class candidate
{
private: std::string fullName;
private: unsigned votes;

/*
**
**		C O N S T R U C T O R S  /  D E S T R U C T O R S
**
*/
public: candidate();
public: candidate( std::string, unsigned );
public: candidate( const candidate& );
public: ~candidate();

/*
**
**		A C C E S S O R S
**
*/
public: std::string getFullName() const;
		// Fetches the candidate's full name
public: unsigned getVotes() const;
		// Fetches the number of votes a candidate posesses

/*
**
**		M U T A T O R S
**
*/
public: void setFullName( std::string );
		// Changes the name of the candidate via assignment
public: void setVotes( unsigned );
		// Changes the number of votes a candidate possesses

/*
**
**		O P E R A T I O N S   &   O V E R L O A D S
**		When overloading operators, use const to ensure no data changes
**		and use the & reference operator to eliminate redundant copying
*/
public: void operator=( const candidate& );
		// Assignment Operator
public: bool operator==( const candidate& );
		// Relational - Equality Operator
public: bool operator!=( const candidate& );
		// Relational - Negation
public: bool operator<( const candidate& );
		// Relational - Less Than
public: bool operator>( const candidate& );
		// Relational - Greater Than
public: void printStats( unsigned ) const;
// Prints out the name, votes, and % of total votes a candidate posesses. Accepts a reference to a single unsigned as an argument for % of total vote calculation.
};
#endif