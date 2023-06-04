// MSFSConnection.h : Include file for standard system include files,
// or project specific include files.

#ifndef MSFS_CONNECT_H
#define MSFS_CONNECT_H

#include "windows.h"
#include <string>
#include "SimConnect.h"
#include "data.h"
#include "common.h"

class MSFSConnection
{
public:
	MSFSConnection();

	void init_connection(void);
	void tick(void);
	void stop(void);
	health get_state(void);

	void process(SimCommand);
	
	HANDLE m_sim;
	static SimResponse sim_out;

private:
	void init_data(void);

	health m_state;

};

// TODO: Reference additional headers your program requires here.

#endif /* ! MSFS_CONNECT_H */
