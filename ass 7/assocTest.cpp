// CS 302, Assignment #8
// Main program for testing hash table

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "assocArray.hpp"

using namespace std;

int main()
{

// *****************************************************************
//  Headers...

	string		bars, stars;

	bars.append(40, '-');
	stars.append(65, '*');

	cout << bars << endl << "CS 302 - Assignment #7" << endl;
	cout << "Associative Array Test Program." << endl;
	cout << endl;

// *****************************************************************
//  Very simple initial testing...

    {
	assocArray<double>	tstArr0;
	double			sum = 0.0;

	string	words0[10] = {"the", "a", "there", "answer", "any",
				"by", "bye", "their", "ball", "balloon" };
	int	len0 = 10;

	cout << stars << endl;

	for (int i=0; i<len0; i++)
		tstArr0[words0[i]] = static_cast<double>(i);

	for (int i=0; i<len0; i++) {
		if (!tstArr0.exists(words0[i])) {
			cout << "Error, array lost word " <<
				words0[i] << "." << endl;
		}
	}

	for (int i=0; i<len0; i++)
		sum += tstArr0[words0[i]];

	cout << endl << "Array Dump (for testing)" << endl;
	cout << bars << endl;

	for (string curr=tstArr0.begin(); curr != tstArr0.end();
		curr = tstArr0.next())
		cout << "Key: " << left << setw(8) << curr <<
			"    Value: " << tstArr0[curr] << endl;
	cout << endl << "Values Sum: " << sum << endl;
	cout << endl << endl;

	for (int i=0; i<len0; i++) {
		if (!tstArr0.erase(words0[i])) {
			cout << "Error, erase fail " <<
				words0[i] << "." << endl;
		}
	}

	// nothing should be displayed since array empty
	for (string curr=tstArr0.begin(); curr != tstArr0.end();
		curr = tstArr0.next())
		cout << "Key: " << left << setw(8) << curr <<
			"    Value: " << tstArr0[curr] << endl;

	cout << "Test Array Zero Stats" << endl;
	tstArr0.showStats();
	cout << endl;
    }

// -----------------------------------------------------------------
//  Slightly larger test set.

    {
	assocArray<short>	tstArr1;
	short			sum = 0;

	string	words1[50] = {"aah", "aahed", "aahing", "aahs", "aal",
			"aalii", "aaliis", "aals", "aardvark",
			"aardwolf", "aargh", "aarrgh", "aarrghh", "aas",
			"aasvogel", "ab", "aba", "abaca", "abacas",
			"abaci", "aback", "abacus", "abacuses", "abaft",
			"abaka", "abakas", "abalone", "abalones", "abamp",
			"abampere", "abamps", "abandon", "abandons",
			"abapical", "abas", "abase", "abased", "abasedly",
			"abaser", "abasers", "abases", "abash", "abashed",
			"abashes", "abashing", "abasia", "abasias",
			"abasing", "abatable", "abate" };
	int	len1 = 50;

	cout << stars << endl;

	for (int i=0; i<len1; i++)
		tstArr1[words1[i]] = static_cast<short>(i);

	for (int i=0; i<len1; i++) {
		if (!tstArr1.exists(words1[i])) {
			cout << "Error, array lost word " <<
				words1[i] << "." << endl;
		}
	}

	for (int i=0; i<len1; i++)
		sum += tstArr1[words1[i]];

	cout << endl << "Array Dump (for testing)" << endl;
	cout << bars << endl;

	for (string curr=tstArr1.begin(); curr != tstArr1.end();
		curr = tstArr1.next())
		cout << "Key: " << left << setw(8) << curr <<
			"    Value: " << tstArr1[curr] << endl;
	cout << endl << "Values Sum: " << sum << endl;
	cout << endl << endl;

	for (int i=0; i<len1; i++) {
		if (!tstArr1.erase(words1[i])) {
			cout << "Error, erase fail " <<
				words1[i] << "." << endl;
		}
	}

	// nothing should be displayed since array empty
	for (string curr=tstArr1.begin(); curr != tstArr1.end();
		curr = tstArr1.next())
		cout << "Key: " << left << setw(8) << curr <<
			"    Value: " << tstArr1[curr] << endl;

	cout << "Test Array One Stats" << endl;
	tstArr1.showStats();
	cout << endl;
    }

// -----------------------------------------------------------------
//  Much larger, more significant test.
// 	This test inserts, searches, and removes 26^4 (456,976)
//	'IDs' which are just unique letter strings for testing.

	assocArray<int>	tstArr2;
	char		ltr1, ltr2, ltr3, ltr4;
	string		str = "";

	cout << stars << endl;

	ltr1 = 'a';
	for (int i=0; i < 26; i++) {
		ltr2 = 'a';
		for (int j=0; j < 26; j++) {
			ltr3 = 'a';
			for (int k=0; k < 26; k++) {
				ltr4 = 'a';
				for (int l=0; l < 26; l++) {
					str = "";
					str.append(1, ltr1);
					str.append(1, ltr2);
					str.append(1, ltr3);
					str.append(1, ltr4);
					tstArr2[str] = i;
					ltr4++;
				}
				ltr3++;
			}
			ltr2++;
		}
		ltr1++;
	}

	ltr1 = 'a';
	for (int i=0; i < 26; i++) {
		ltr2 = 'a';
		for (int j=0; j < 26; j++) {
			ltr3 = 'a';
			for (int k=0; k < 26; k++) {
				ltr4 = 'a';
				for (int l=0; l < 26; l++) {
					str = "";
					str.append(1, ltr1);
					str.append(1, ltr2);
					str.append(1, ltr3);
					str.append(1, ltr4);
					if(!tstArr2.exists(str))
						cout << "Error, array lost word - "
							<< str << "." << endl;
					ltr4++;
				}
				ltr3++;
			}
			ltr2++;
		}
		ltr1++;
	}

	ltr1 = 'a';
	for (int i=0; i < 26; i++) {
		ltr2 = 'a';
		for (int j=0; j < 26; j++) {
			ltr3 = 'a';
			for (int k=0; k < 26; k++) {
				ltr4 = 'a';
				for (int l=0; l < 26; l++) {
					str = "";
					str.append(1, ltr1);
					str.append(1, ltr2);
					str.append(1, ltr3);
					str.append(1, ltr4);
					if(!tstArr2.erase(str))
						cout << "Error, array delete failed - "
							<< str << "." << endl;
					ltr4++;
				}
				ltr3++;
			}
			ltr2++;
		}
		ltr1++;
	}

	cout << "Test Array Two Stats" << endl;
	tstArr2.showStats();
	cout << endl;

// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}

