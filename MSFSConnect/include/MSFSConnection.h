// MSFSConnect.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "windows.h"
#include <string>
#include "SimConnect.h"

class MSFSConnection
{
public:
	MSFSConnection();

	void init_connection(void);
	void run(void);

private:
	double request_double(std::string requested_data);
	int request_int(std::string requested_data);
	bool request_bool(std::string requested_data);

	static HANDLE m_sim;

};

// TODO: Reference additional headers your program requires here.