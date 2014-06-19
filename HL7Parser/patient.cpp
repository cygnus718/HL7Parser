#pragma once

#include "stdafx.h"
#include "hl7.h"
#include "patient.h"
#include <iostream>
#include <fstream>

Patient::Patient(string name, string mrn, string dob, string address, string phone) //patient class constructor
{
	patientName = name;
	patientMRN = mrn;
	patientDOB = dob;
	patientAddress = address;
	patientPhone = phone;

	cout << "Checking if patient exists..." << endl << endl;
	if (checkDupePatient()) //if check for existing message in patientDB returns true...
	{
		cout << "Patient already exists, not writing to file" << endl << endl; //do nothing
	}
	else //if current HL7 message string not found in db...
	{
		cout << "Storing Patient..." << endl << endl;
		savePatient(); //store contents of fullHL7message in the db
	}
}

void Patient::displayPatientValues()
{
	cout << "Patient Object Name: " << patientName << endl;
	cout << "Patient MRN: " << patientMRN << endl;
	cout << "Patient DOB: " << patientDOB << endl;
	cout << "Patient Address: " << patientAddress << endl;
	cout << "Patient Phone Number: " << patientPhone << endl;
}

void Patient::savePatient()
{
	ofstream patientDB;
	patientDB.open("patientDB.txt", ofstream::app); //open patientDB file, set write mode to append
	patientDB << this->patientName << "," << this->patientMRN << "," << this->patientDOB << "," << this->patientAddress << "," << this->patientPhone << endl; //write message to patientDB file
	patientDB.close(); //close file 
}

bool Patient::checkDupePatient() //check to see if message already exists in database
{
	ifstream patientDB;
	patientDB.open("patientDB.txt"); //open file

	for (string line; getline(patientDB, line);) //for each line in patientDB file
	{
		if (line.find(this->patientMRN) != string::npos ) //if no MRN match was found in the patientDB file
		{
			return true;
			break;
		}

	}

	patientDB.close(); //close patientDB file

	return false;
}