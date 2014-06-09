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
	private:
		int pidLocation, pv1Location, obxLocation;
		string fullHL7msg;
		void parseSegments();
		void parseMSH();
		void parsePID();
		void parsePV1();
		void parseOBX();
};

