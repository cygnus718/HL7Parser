#include "hl7.h"

using namespace std;
C:\Users\jkinney\Documents\Visual Studio 2013\Projects\HL7Parser\hl7.cpp
C : \Users\jkinney\Documents\Visual Studio 2013\Projects\HL7Parser\HL7Parser\hl7.h
HL7::HL7(string HL7message)
{
	cout << "Building HL7 object..." << endl;
	fullHL7msg = HL7message;
}

void parseMSH()
{
	found = fullHL7msg.find("PID");
	cout << "PID segment found at: " << found << endl;
	MSH = fullHL7msg.substr(0, found);
}

void parsePID()
{
	found2 = fullHL7msg.find("PV1");
	cout << "PV1 segment found at: " << found2 << endl;

	PID = fullHL7msg.substr(found, found2 - found);
}

void parsePV1()
{
	PV1 = fullHL7msg.substr(found2);
}

void HL7::parseSegments()
{
	parseMSH();

	parsePID();

	parsePV1();
}

void HL7::getMSHFields()
{
	int i = 0;
	int leadBarPosition, trailBarPosition;
	bool leadBarSet = false;

	for (char& c : MSH)
	{
		if (c == '|') //iterate through string to find bars
		{
			if (!leadBarSet) //if bar is found, and no leadBar is defined
			{
				leadBarPosition = i; //set leadBar to current index
				leadBarSet = true; //flag leadbar as true
			}
			else if (leadBarSet) //if bar is found, and leadBar is defined
			{
				trailBarPosition = i; //set trailBar to current index
				cout << MSH.substr(leadBarPosition + 1, trailBarPosition - leadBarPosition - 1) << endl;
				leadBarSet = false;
			}
		}
		i++;
	}
}

void HL7::getPIDFields()
{
	int i = 0;
	int leadBarPosition, trailBarPosition;
	bool leadBarSet = false;

	for (char& c : PID)
	{
		if (c == '|') //iterate through string to find bars
		{
			if (!leadBarSet) //if bar is found, and no leadBar is defined
			{
				leadBarPosition = i; //set leadBar to current index
				leadBarSet = true; //flag leadbar as true
			}
			else if (leadBarSet) //if bar is found, and leadBar is defined
			{
				trailBarPosition = i; //set trailBar to current index
				cout << "SEGMENT: " << PID.substr(leadBarPosition + 1, trailBarPosition - leadBarPosition - 1) << endl;
				leadBarSet = false;
			}
		}
		i++;
	}
}
