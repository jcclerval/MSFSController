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

	void pass_action(void);
	void pass_data(void);
	
	HANDLE m_sim;
	SimResponse sim_data;

private:
	void init_data(void);
	void read_from_sim(void);
	void send_to_sim(void);

	health m_state;
	
	int temp_count;

};

// TODO: Reference additional headers your program requires here.

#endif /* ! MSFS_CONNECT_H */
