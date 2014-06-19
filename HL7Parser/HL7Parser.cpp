// HL7Parser.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "hl7.h"
#include "patient.h"
#include <fstream>

void mainMenu(); //main menu function
int menuSelection;
void selectMessage();

void runTestMessage(); //test function for demonstrative purposes

void createMessageArray(); //generates dynamically allocated array to store messages

string displayExistingPatients();
void displayExistingMessages();

int getNumberOfMessages();

int numberOfMessages = getNumberOfMessages(); //determine number of messages in messageDB file
string* hl7MessageArray = new string[numberOfMessages]; //create array with

Patient generatePatientFromHL7(string hl7message);

HL7* selectedMessage;
Patient* selectedPatient;


int _tmain(int argc, _TCHAR* argv[])
{
	mainMenu();


	cin.get();
	cin.get();
	delete hl7MessageArray;
	return 0;
}

int getNumberOfMessages()
{
	int numberOfMessages = 0;

	ifstream messageDB;
	messageDB.open("messageDB.txt"); //open file


	for (string line; getline(messageDB, line);) //for each line in message file
	{
		numberOfMessages++;
	}

	return numberOfMessages;
}

void mainMenu()
{
	cout << "Select an option: " << endl << endl << "1. Submit New Message \n2. View Existing Messages \n3. View Existing Patients \n4. Run Test Messages\n5. Exit" << endl;
	cin >> menuSelection;

	switch(menuSelection)
	{
		case 1: 
			cout << "Submit new message selected" << endl;
			break;
		case 2: 
			cout << "View existing messages selected" << endl;
			createMessageArray();
			displayExistingMessages();
			break;
		case 3: 
			cout << "View existing patients selected" << endl;
			break;
		case 4: 
			cout << "Running test message..." << endl;
			runTestMessage();
			break;
		case 5: 
			cout << "Quitting..." << endl;
			break;
		default: 
			cerr << "Error - invalid input - please select a valid input" << endl;
			mainMenu();
	}
	
}

void runTestMessage()
{
	HL7* testMessage; //initialize pointer

	testMessage = new HL7("MSH|^~\&|EPICADT|EPIC|SMSADT|SMS|201401271408|XMP|ADT^A04|1817457|D|2.5|PID || 0493575 ^ ^^2 ^ ID 1 | 454721 || DOE^JOHN^^^^ | DOE^JOHN^^^^ | 19480203 | M || B | 254 MYSTREET AVE^^MYTOWN^OH ^ 44123 ^ USA || (216)123 - 4567 || | M | NON | 400003403~1129086 |PV1 || O | 168 ~219~C~PMA^^^^^^^^^ || || 277 ^ ALLEN MYLASTNAME^BONNIE^^^^ || || || || || || 2688684 || || || || || || || || || || || || | 199912271408 || || || 002376853OBX|2|CE|001719^HIV-1 ABS, SEMI-QN^L||HTN|||||N|F|19910123|| 19980729155700|BN|");
	cout << endl << endl;
	/*
	testMessage->getSegmentFields(testMessage->MSH);
	testMessage->getSegmentFields(testMessage->PID);
	testMessage->getSegmentFields(testMessage->PV1);
	testMessage->getSegmentFields(testMessage->OBX);
	*/

	//testMessage->reportSegments();


	cout << endl;

	if (testMessage->detectPrivateInfo(*testMessage->MSHfields))
	{
		cout << "Private information detected, building NAT segment..." << endl;
	}
	testMessage->rebuildMessage();

	cout << testMessage->printFullMessage();

	Patient* testPatient;
	testPatient = new Patient(testMessage->PIDfields[4][1], testMessage->PIDfields[2][1], testMessage->PIDfields[6][1], testMessage->PIDfields[10][1], testMessage->PIDfields[12][1]);

	testPatient->displayPatientValues();
	delete testPatient;
	delete testMessage; //delete HL7 object
	
}

void createMessageArray()
{
	ifstream messageDB;
	messageDB.open("messageDB.txt"); //open file
	int i = 0;

	for (string line; getline(messageDB, line);) //for each line in message file
	{
		hl7MessageArray[i] = line;
		i++;
	}

	messageDB.close(); //close patientDB file
}

void displayExistingMessages()
{ 
	for (int i = 0; i < sizeof(hl7MessageArray) - 1; i++)
	{
		cout << i << ": " << hl7MessageArray[i] << endl;
	}

	selectMessage();
} 

void selectMessage()
{
	int messageSelection;

	cout << endl << "Please select a message" << endl;
	cin >> messageSelection;

	if (messageSelection > sizeof(hl7MessageArray - 1))
	{
		cout << "Error - invalid message index" << endl;
	}
	else
	{
		selectedMessage = new HL7(hl7MessageArray[messageSelection]);
		selectedPatient = new Patient(selectedMessage->PIDfields[4][1], selectedMessage->PIDfields[2][1], selectedMessage->PIDfields[6][1], selectedMessage->PIDfields[10][1], selectedMessage->PIDfields[12][1]);
		delete selectedMessage;
		selectedPatient->displayPatientValues();
		delete selectedPatient;
	}
}