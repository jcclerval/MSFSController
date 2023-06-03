//
#include <iostream>
#include "Controller.h"

bool quit = false;

Controller::Controller()
{
	MSFSConnection sim_connect = MSFSConnection();
	PicoConnection pic_connect = PicoConnection();
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

	while ( quit != true )
	{
		sim_connect.run();
		pic_connect.run();
		Sleep(100);
	}
}

