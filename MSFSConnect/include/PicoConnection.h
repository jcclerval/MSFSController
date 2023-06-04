// PicoConnection.h : Include file for standard system include files,
// or project specific include files.

#ifndef PICO_CONNECT_H
#define PICO_CONNECT_H

#include "common.h"
#include "data.h"

class PicoConnection
{
public:
	PicoConnection();

	void init_connection(void);
	void tick(void);
	void stop(void);

	void process(SimResponse);

	health get_state(void);
	static SimCommand sim_in;

private:

	void reset_sim_in(void);

	health m_state;

	// TEMP //
	int m_count;
};

// TODO: Reference additional headers your program requires here.

#endif /* !PICO_CONNECT_H */
