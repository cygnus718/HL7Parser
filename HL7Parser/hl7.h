#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class HL7
{
	public:
		HL7(string a);
		string MSH, PID, PV1, OBX;
		void reportSegments();
		void getSegmentFields(string segmentString);
		void detectPrivateInfo(string segmentArray[]);
		string MSHfields[20][2];
		void defineFields();
	private:
		int pidLocation, pv1Location, obxLocation;
		string fullHL7msg;
		void parseSegments();
		void parseMSH();
		void parsePID();
		void parsePV1();
		void parseOBX();
		//string MSHfields[20][2];
		string PIDfields[31][2];
		string PV1fields[25][2];
		string OBXfields[19][2];
};

