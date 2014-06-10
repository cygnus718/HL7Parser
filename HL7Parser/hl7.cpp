#pragma once

#include "stdafx.h"
#include "hl7.h"

string MSHfields[19] =
{
	"Field Separator",
	"Sending Application",
	"Sending Facility",
	"Receiving Application",
	"Receiving Facility",
	"Date/Time of Message",
	"Security",
	"Message Type",
	"Message Control Id",
	"Processing Id",
	"Version Id",
	"Sequence Number",
	"Continuation Pointer",
	"Accept Acknowledgement Type",
	"Application Acknowledgement Type",
	"Country Code",
	"Character Set",
	"Principal Language of Message"
};

string PIDfields[30] =
{
	"Set ID - Patient ID",
	"Patient ID (External ID)",
	"Patient ID (Internal ID)",
	"Alternate Patient ID - PID",
	"Patient Name",
	"Mother's Maiden Name",
	"Date/Time of Birth",
	"Sex",
	"Patient Alias",
	"Race",
	"Patient Address",
	"Country Code",
	"Phone Number - Home",
	"Phone Number - Business",
	"Primary Language",
	"Marital Status",
	"Religion",
	"Patient Account Number",
	"SSN Number - Patient",
	"Driver's License Number - Patient",
	"Mother's Identifier",
	"Ethnic Group",
	"Birth Place",
	"Multiple Birth Indicator",
	"Birth Order",
	"Citizenship",
	"Veterans Millitary Status",
	"Nationality",
	"Patient Death Date and Time",
	"Patient Death Indicator"
};

string PV1fields[24] =
{
	"Patient Class",
	"Assigned Patient Location",
	"Admission Type",
	"Preadmit Number",
	"Prior Patient Location",
	"Attending Doctor",
	"Referring Doctor",
	"Consulting Doctor",
	"Hospital Service",
	"Temporary Location",
	"Preadmit Test Indicator",
	"Readmission Indicator",
	"Admit Source",
	"Ambulatory Status",
	"VIP Indicator",
	"Admitting Doctor",
	"Patient Type",
	"Visit Number",
	"Financial Class",
	"Charge Price Indicator",
	"Courtesy Code",
	"Credit Rating",
	"Contract Code",
	"Contract Effective Date"
};

HL7::HL7(string HL7message)
{
	cout << "Building HL7 object..." << endl;
	
		cout << "Loading Message..." << endl;
		fullHL7msg = HL7message;

		cout << "Parsing Segments..." << endl;
		parseSegments(); //encapsulate each HL7 segment into a string
}

void HL7::parseMSH()
{
	pidLocation = fullHL7msg.find("PID");
	cout << "PID segment found at: " << pidLocation << endl;
	MSH = fullHL7msg.substr(0, pidLocation);
}

void HL7::parsePID()
{
	pv1Location = fullHL7msg.find("PV1");
	cout << "PV1 segment found at: " << pv1Location << endl;

	PID = fullHL7msg.substr(pidLocation, pv1Location - pidLocation);
}

void HL7::parsePV1()
{
	obxLocation = fullHL7msg.find("OBX");
	cout << "OBX segment found at: " << obxLocation << endl;
	PV1 = fullHL7msg.substr(pv1Location, obxLocation - pv1Location);
}

void HL7::parseOBX()
{
	OBX = fullHL7msg.substr(obxLocation);
}

void HL7::parseSegments()
{
	parseMSH();

	parsePID();

	parsePV1();

	parseOBX();
}


void HL7::getSegmentFields(string segmentString)
{
	int i = 0; //Index of current character
	int n = 0; //MSH field array index
	int p = 0; //
	int leadBarPosition, trailBarPosition;
	bool leadBarSet = false;

	for (char& c : segmentString) //iterate through the MSG segment string, storing each character in c
	{
		if (c == '|') //if the current character is a bar,
		{
			if (!leadBarSet) //if bar is pidLocation, and no leadBar is defined
			{
				leadBarPosition = i; //set leadBar to current index
				leadBarSet = true; //flag leadbar as true
			}
			else if (leadBarSet) //if bar is pidLocation, and leadBar is defined
			{
				trailBarPosition = i; //set trailBar to current index
				if (segmentString == this->MSH)
				{
					cout << MSHfields[n] << ": " << segmentString.substr(leadBarPosition + 1, trailBarPosition - leadBarPosition - 1) << endl;
				}
				else if (segmentString == this->PID)
				{
					cout << PIDfields[n] << ": " << segmentString.substr(leadBarPosition + 1, trailBarPosition - leadBarPosition - 1) << endl;
				}
				else 
				{
					cout << "SEGMENT " << n << ": " << segmentString.substr(leadBarPosition + 1, trailBarPosition - leadBarPosition - 1) << endl;
				}
				leadBarPosition = i;
				n++;
			}
		}
		i++; //iterate to next character
	}
}

void HL7::reportSegments()
{
	getSegmentFields(this->MSH);
	getSegmentFields(this->PID);
	getSegmentFields(this->PV1);
	getSegmentFields(this->OBX);
}