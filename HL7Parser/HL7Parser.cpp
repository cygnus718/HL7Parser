// HL7Parser.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "hl7.h"

int _tmain(int argc, _TCHAR* argv[])
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

	testMessage->reportSegments();
	
	cout << endl;

	//cout << testMessage->MSH << endl << endl << testMessage->PID << endl << endl << testMessage->PV1 << endl << endl << testMessage->OBX << endl;
;
	testMessage->detectPrivateInfo(*testMessage->MSHfields);
	testMessage->rebuildMessage();
	delete testMessage; //delete HL7 object

	cin.get();
	return 0;
}

