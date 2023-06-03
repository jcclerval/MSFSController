//

#include "PicoConnection.h"

PicoConnection::PicoConnection()
{
	m_state = OFF;

	// TEMP //
	m_count = 0;
}

void PicoConnection::init_connection()
{
	m_state = INIT;
}

void PicoConnection::tick()
{
	m_state = ON;

	if (m_count > 1000)
	{
		m_count = 0;
		// Do something
	}
}

void PicoConnection::stop()
{
	m_state = OFF;
}

health PicoConnection::get_state()
{
	// Retun PicoConnection state to Controller
	return m_state;
}

void PicoConnection::pass_data()
{
	// Get data from simulation, to send to Pico
}

void PicoConnection::pass_action()
{
	// Send actions from Pico for simulation
}
