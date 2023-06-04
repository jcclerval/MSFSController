//

#include "PicoConnection.h"

SimCommand PicoConnection::sim_in = {
	false,
	false,
	false,

	false,
	false,
	false,
	false,
};

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
	reset_sim_in();

	m_count += 1;

	if (m_count == 200)
	{
		sim_in.inc_flaps = true;
	}
	else if (m_count == 400)
	{
		sim_in.inc_flaps = true;
	}
	else if (m_count == 600)
	{
		sim_in.inc_flaps = true;
	}
	else if (m_count == 800)
	{
		sim_in.dec_flaps = true;
	}
	else if (m_count == 1000)
	{
		sim_in.dec_flaps = true;
	}
	else if (m_count == 1200)
	{
		sim_in.dec_flaps = true;
		m_count = 0;
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

void PicoConnection::process(SimResponse out_data)
{
	// Get data from simulation, to send to Pico
}

void PicoConnection::reset_sim_in()
{
	sim_in = {
	false,
	false,
	false,

	false,
	false,
	false,
	false,
	};
}