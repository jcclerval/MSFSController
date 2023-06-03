// Controller.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "MSFSConnection.h"
#include "PicoConnection.h"


class Controller
{

public:
	Controller(void);
	~Controller(void) {};

	void init(void);
	void run(void);

private:

	MSFSConnection sim_connect;
	PicoConnection pic_connect;

	void check_health(void);
	void stop_sim(void);

	bool m_stop;

};

//