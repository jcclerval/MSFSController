//
#include <iostream>
#include "Controller.h"


Controller::Controller()
{
	MSFSConnection sim_connect = MSFSConnection();
	PicoConnection pic_connect = PicoConnection();

	m_stop = false;
}


void Controller::init()
{
	// cout << "Hello CMake." << endl;
	printf("Initializing Connection...\n");

	sim_connect.init_connection();
	pic_connect.init_connection();

}

void Controller::run()
{
	while (m_stop != true )
	{
		sim_connect.process(PicoConnection::sim_in);
		sim_connect.tick();
		pic_connect.process(MSFSConnection::sim_out);
		pic_connect.tick();
		Sleep(1);

		check_health();
	}

	stop_sim();
}

void Controller::check_health()
{
	if (sim_connect.get_state() == ON && pic_connect.get_state() == ON)
	{
		// all good
		return void();
	}
	else
	{
		// Stop simulation
		m_stop = true;
		return void();
	}
}

void Controller::stop_sim()
{
	sim_connect.stop();
	pic_connect.stop();
}
