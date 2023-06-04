// MSFSConnect.cpp : Defines the entry point for the application.
//

#include "Controller.h"

using namespace std;

int main()
{
	Controller new_controller = Controller();

	new_controller.init();

	new_controller.run();

	return 0;
}
