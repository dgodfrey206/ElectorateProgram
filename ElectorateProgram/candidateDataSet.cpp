/*	
 *	Logan M. Wunder
 *	
 *	CANDIDATE DATA SET - A container class for lists of candidates
 *	
 */	

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "candidate.hpp"
#include "candidateDataSet.hpp"
#include "functions.hpp"

/* I'm lazy and want to save some typing */
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ios;

/*
**
**		C O N S T R U C T O R S  /  D E S T R U C T O R S
**
*/
candidateDataSet::candidateDataSet()
{
	setValidity( false );
	setModified( false );
	setListName( "Default" );
	setTotalVotes( 0 );
}
candidateDataSet::candidateDataSet( vector<candidate> &in_list, string &in_name )
{
	if( in_name.empty() )
		setListName( "Default" );
	else
		setListName( in_name );

	// Copy the elements from the input vector into the internal vector...
	for( decltype(in_list.size()) i = 0; i < in_list.size(); i++ )
	{
		addTotalVotes( in_list[i].getVotes() );
		v_Candidate.push_back( in_list[i] );
	}
	setValidity( true );
	setModified( true );
}

candidateDataSet::~candidateDataSet()
{
	// Destroy Reptar
}

/*
**
**		A C C E S S O R S
**
*/
bool candidateDataSet::isValid() const
{
	return b_isValid;
}

bool candidateDataSet::isModified() const
{
	return b_isModified;
}

string candidateDataSet::getListName() const
{
	return s_listName;
}

unsigned candidateDataSet::getTotalVotes() const
{
	return i_totalVotes;
}

candidate candidateDataSet::getListItem( unsigned i_ID ) const
{
	return v_Candidate[i_ID];
}

unsigned candidateDataSet::getListSize() const
{
	return v_Candidate.size();
}

/*
**
**		M U T A T O R S
**
*/
void candidateDataSet::setValidity( bool b_setValidState )
{
	b_isValid = b_setValidState;
}

void candidateDataSet::setModified( bool b_setModifiedState )
{
	b_isModified = b_setModifiedState;
}

void candidateDataSet::setListName( string is_name )
{
	s_listName = is_name;
}

void candidateDataSet::setTotalVotes( unsigned i_Votes )
{
	i_totalVotes = i_Votes;
}

void candidateDataSet::addTotalVotes( unsigned i_Votes )
{
	i_totalVotes += i_Votes;
}

void candidateDataSet::addListItem()
{
	candidate* p_bufCandidate = new candidate();
	string* p_bufName = new string("Default");
	unsigned* p_bufVotes = new unsigned(0);
	bool okToGo = false;

	do
	{
		cout << "Please type the name of your candidate:" << endl;
		cout << "=>";
		getline( cin, *p_bufName);

		do
		{
			cin.sync();
			cin.clear();

			cout << "Type in the number of votes " << *p_bufName << " has:" << endl;
			cout << "=>";
			cin >> *p_bufVotes;
			if( cin.bad() )
			{
				cin.sync();
				cout << "Error: Invalid input was detected. Try again!" << endl;
			}
			else
			{
				cin.clear();
				cin.sync();
			}
		}
		while( cin.bad() );

		cout << "You're about to add the following:" << endl;
		cout << "Name: " << *p_bufName << " Votes: " << *p_bufVotes << endl;
		cout << "Is this information correct? [ Y / N ]" << endl;
		cout << "=>";
		okToGo = getYesNoOption();

		if( okToGo )
		{
			cout << "Ok To Go; Inserting into list..." << endl;

			p_bufCandidate->setFullName( *p_bufName );
			delete p_bufName;
			p_bufName = NULL;

			p_bufCandidate->setVotes( *p_bufVotes );
			addTotalVotes( *p_bufVotes );
			delete p_bufVotes;
			p_bufVotes = NULL;

			v_Candidate.push_back( *p_bufCandidate );
			delete p_bufCandidate;
			p_bufCandidate = NULL;

			setModified( true );

			// Sort the newly added candidate in the vector
			if( v_Candidate.size() > 1 )
				sort();
		}
		else
			cout << "Information is not correct... Returning to questions!" << endl;
	}
	while( !okToGo );
}

bool candidateDataSet::modifyListItem( string &s_name )
{
	int position = find( s_name );
	if( position == -1 )
	{
		cout << "No candidate with the name " << s_name << " was found..." << endl;
		return false;
	}
	else
	{
		candidate* p_bufEdit = new candidate( v_Candidate[position] );
		string* p_bufName = new string("Frank Underwood");
		unsigned* p_bufVotes = new unsigned(0);
		bool okToGo = false;

		do
		{
			cout << "Found " << p_bufEdit->getFullName() << endl;
			cout << "Type " << p_bufEdit->getFullName() << "'s new name: " << endl;
			cout << "=>";
			getline( cin, *p_bufName );

			do
			{
				cin.sync();
				cin.clear();

				cout << "Type in the number of votes " << *p_bufName << " has:" << endl;
				cout << "=>";
				cin >> *p_bufVotes;
				if( cin.bad() )
				{
					cin.sync();
					cout << "Error: Invalid input was detected. Try again!" << endl;
				}
				else
				{
					cin.clear();
					cin.sync();
				}
			}
			while( cin.bad() );

			cout << "You're about to add the following:" << endl;
			cout << "Name: " << *p_bufName << " Votes: " << *p_bufVotes << endl;
			cout << "Is this information correct? [ Y / N ]" << endl;
			cout << "=>";
			okToGo = getYesNoOption();
			cout << endl;

			if( okToGo )
			{
				cout << "Modifying..." << endl;
				p_bufEdit->setFullName( *p_bufName );
				delete p_bufName;
				p_bufName = NULL;

				p_bufEdit->setVotes( *p_bufVotes );
				addTotalVotes( *p_bufVotes );
				delete p_bufVotes;
				p_bufVotes = NULL;

				v_Candidate.at(position) = *p_bufEdit;
				delete p_bufEdit;
				p_bufEdit = NULL;

				// Data has been changed
				setModified( true );
				cout << "Tallying votes..." << endl;
				calculateTotalVotes();

				// Sort the vector accordingly with the edits...
				cout << "Sorting candidates..." << endl;
				if( v_Candidate.size() > 1 )
					sort();

				cout << "Candidate sucessfully modified!" << endl;
			}
			else
				cout << "Information is not correct... Returning to questions!" << endl;
		}
		while( !okToGo );

		cout << endl;
		return true;
	}

	// Sort the newly added candidate in the vector
	if( v_Candidate.size() > 1 )
		sort();

	return false;	// Just in case!
}

bool candidateDataSet::deleteListItem( string &s_name )
{
	
	int position = find( s_name );
	if( position == -1 )
	{
		cout << "No candidate with the name " << s_name << " was found..." << endl;
		return false;
	}
	// Else it was true!

	v_Candidate.erase( position );

	// Sort the leftover candidates in the vector
	if( v_Candidate.size() > 1 )
		sort();

	return true;
}

void candidateDataSet::calculateTotalVotes()
{
	setTotalVotes( 0 );

	decltype( v_Candidate.size() ) i = 0;

	for( i; i < v_Candidate.size(); i++ )
	{
		addTotalVotes( v_Candidate[i].getVotes() );
	}

	// We may need to calculate total votes as part of another operation
	// setModified( true ); Must not exist then in this code...
}

/*
**
**		O P E R A T I O N S   &   O V E R L O A D S
**
*/
void candidateDataSet::sort()
{
	// A selection sort algorithm straight out of Starting out with C++, p470
	unsigned start, minIndex;
	candidate minValue;

	for( start = 0; start < ( v_Candidate.size() ); start++ )
	{
		minIndex = start;
		minValue = v_Candidate[start];

		for( unsigned i = ( start + 1 ); i < v_Candidate.size(); i++ )
		{
			if( v_Candidate[i] < minValue )
			{
				minValue = v_Candidate[i];
				minIndex = i;
			}
		}

		v_Candidate[minIndex] = v_Candidate[start];
		v_Candidate[start] = minValue;
	}
}

vector<candidate>::iterator candidateDataSet::find( string &s_name )
{
	
}

bool candidateDataSet::readElectorateFile( ifstream &in_file )
{
	if( in_file )
	{
		try
		{
			string* p_bufListName = new string("Default");
			unsigned* p_bufTotalVotes = new unsigned(0);
			string* p_bufFullName = new string("Frank Underwood");
			unsigned* p_bufVotes = new unsigned(9001);
			unsigned lineNo = 0;
			unsigned voteCheck = 0;

			// Let the input stream throw exceptions when these two flags are set
			in_file.exceptions( ios::badbit | ios::failbit );

			getline( in_file, *p_bufListName);	// Use getline to get whitespace up to \n
			cout << "Read List Name as : " << *p_bufListName << endl;
			setListName( *p_bufListName );
			delete p_bufListName;
			p_bufListName = NULL;

			in_file >> *p_bufTotalVotes;	// << automatically converts readable digits
			cout << "Read Total Votes as : " << *p_bufTotalVotes << endl;
			setTotalVotes( *p_bufTotalVotes );
			delete p_bufTotalVotes;
			p_bufTotalVotes = NULL;

			// The cake below is a lie 
			//in_file.ignore('\n');	// Throw away the newline separating the list from the total votes
	
			while( !in_file.eof() )	// Ensure that we're not running into the end of the file
			{
				lineNo++;
				getline( in_file, *p_bufFullName, '|');
				in_file >> *p_bufVotes;
				candidate buf_candidate( *p_bufFullName, *p_bufVotes );
				cout << "Read Line " << lineNo << ": ";
				cout << *p_bufFullName << " " << *p_bufVotes << endl;
			
				voteCheck += *p_bufVotes;
			
				v_Candidate.push_back( buf_candidate );
			}

			cout << "Validating votes..." << endl;
			if( getTotalVotes() != voteCheck )
			{
				cout << "Error: Vote check failed!" << endl;
				cout << "File: " << getTotalVotes();
				cout << " CheckList: " << voteCheck << endl;
				cout << "Using calculated votes..." << endl;
				setTotalVotes( voteCheck );
			}

			delete p_bufFullName;
			delete p_bufVotes;
			p_bufFullName = NULL;
			p_bufVotes = NULL;
			setValidity( true );
			setModified( false );
			cout << "File has been loaded. Ready." << endl;
			cout << endl;
			return true;
		}
		catch ( const ios::failure& error )
		{
			cout << "Error " << error.code() << ": " << error.what() << endl;
			cout << endl;
			return false;
		}
		catch (...)
		{
			cout << "Exception: Lions and tigers and bears oh my!" << endl;
			cout << endl;
			return false;
		}
	}
	else
	{
		cout << "Error: No file to load!\n" << endl;
		cout << endl;
		return false;
	}
	// Catch all
	return false;
}

void candidateDataSet::writeElectorateFile( ofstream &out_file )
{
	if( out_file.is_open() )
		cout << "File has been opened for writing..." << endl;

	if( out_file )
	{
		try
		{
			// Let the output stream throw exceptions on out_file operations
			out_file.exceptions( ios::badbit | ios::failbit );
			out_file << getListName() << endl;
			out_file << getTotalVotes() << endl;
			out_file << endl;

			if( !v_Candidate.empty() )
			{
				for( decltype( v_Candidate.size() ) i = 0; i < v_Candidate.size(); i++ )
				{
					candidate buf_Candidate = getListItem(i);
					out_file << buf_Candidate.getFullName();
					out_file << "|";
					out_file << buf_Candidate.getVotes();
					out_file << endl;
				}
			}
			else
			{
				cout << "Note:" << getListName();
				cout <<" has no candidates in the list..." << endl;
			}
			out_file.flush();

			cout << "Closing file; data sucessfully written." << endl;
			setModified( false );
			out_file.close();
		}
		catch( const ios::failure& error )
		{
			cout << "Error " << error.code() << ": " << error.what() << endl;
			cout << endl;
		}
		catch( ... )
		{
			cout << "Exception: Lions and tigers and bears oh my!" << endl;
		}
	}
	else
	{
		cout << "Error: Could not open file for writing..." << endl;
	}
}

void candidateDataSet::printList()
{
	cout << "Candidate Name" << " | ";
	cout << "Vote Count" << " | ";
	cout << "% of Total" << endl;

	for( decltype( v_Candidate.size() ) i = 0; i < v_Candidate.size(); i++ )
	{
		unsigned hobble = getTotalVotes();
		v_Candidate[i].printStats( hobble );
	}
}