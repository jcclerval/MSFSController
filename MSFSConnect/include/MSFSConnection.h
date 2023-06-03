// MSFSConnect.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "windows.h"
#include <string>
#include "SimConnect.h"
#include "common.h"

class MSFSConnection
{
public:
	MSFSConnection();

	void init_connection(void);
	void tick(void);
	void stop(void);
	health get_state(void);

	void pass_action(void);
	void pass_data(void);
	
	HANDLE m_sim;

private:
	void init_data(void);
	void read_data(void);
	void send_data(void);

	health m_state;

};

// TODO: Reference additional headers your program requires here.