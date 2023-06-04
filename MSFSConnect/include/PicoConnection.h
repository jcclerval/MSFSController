// PicoConnection.h : Include file for standard system include files,
// or project specific include files.

#ifndef PICO_CONNECT_H
#define PICO_CONNECT_H

#include "common.h"

class PicoConnection
{
public:
	PicoConnection();

	void init_connection(void);
	void tick(void);
	void stop(void);

	void pass_data(void);
	void pass_action(void);

	health get_state(void);

private:
	health m_state;

	// TEMP //
	int m_count;
};

// TODO: Reference additional headers your program requires here.

#endif /* !PICO_CONNECT_H */
