#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class HL7
{
	public:
		HL7(string a);
		string MSH, PID, PV1, OBX, NAT;
		void reportSegments();
		void getSegmentFields(string segmentString);
		void detectPrivateInfo(string segmentArray[]);
		string MSHfields[20][2];
		string PIDfields[31][2];
		string PV1fields[25][2];
		string OBXfields[19][2];
		string NATfields[6][2];
		void rebuildMessage();
		string messageControlID;
	private:
		int pidLocation, pv1Location, obxLocation;
		string fullHL7msg;
		void parseSegments();
		void parseMSH();
		void parsePID();
		void parsePV1();
		void parseOBX();
		void defineFields();
		void storeMessage();
		void buildPatient();
		bool checkDupeMessage();
};

class Patient
{
	//friend class HL7;
	public:
		Patient(string name, string mrn, string dob, string address, string phone);
		string patientName;
		string patientMRN;
		string patientDOB;
		string patientPhone;
		string patientAddress;
		void displayPatientValues();
	private:
		void savePatient();
};
