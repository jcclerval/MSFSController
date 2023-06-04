//

#include "MSFSConnection.h"
#include <iostream>


void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	switch (pData->dwID)
	{

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST_1:

			SimResponse* pS = (SimResponse*)&pObjData->dwData;

			std::cout

				<< "\rAltitude: " << pS->altitude
				<< " - Heading: " << pS->heading
				<< " - Speed (knots): " << pS->speed
				<< " - Vertical Speed: " << pS->vertical_speed

				<< std::flush;

			// Copy data in local var

			// MSFSConnection::sim_data.altitude = pS->altitude;

			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_QUIT:
	{
		// Problem
		break;
	}

	default:
		break;
	}
}


MSFSConnection::MSFSConnection()
{
	HANDLE m_sim = NULL;

	m_state = OFF;
	sim_data = {
		0.,
		0,
		0,
		0
	};

	temp_count = 0;
}

void MSFSConnection::init_connection()
{
	// init data
	HRESULT hr;

	hr = SimConnect_Open(&m_sim, "Your Application Name", NULL, 0, 0, SIMCONNECT_OPEN_CONFIGINDEX_LOCAL);

	if (hr == E_FAIL)
	{
		printf("Connection failed...\n");
		m_state = FAIL;
		return void();
	}

	const char* szState = "Sim";
	// hr = SimConnect_RequestSystemState(m_sim, 0, szState);

	printf("Connection success\n");

	// DATA
	init_data();

	//
	m_state = INIT;

}

void MSFSConnection::tick()
{
	//
	read_from_sim();

	//
	send_to_sim();

}

void MSFSConnection::stop()
{
	m_state = OFF;
}


void MSFSConnection::init_data()
{
	// Fonction to initialize all data to be readn and all actions to be transmitted to the sim
	HRESULT hr;

	// Data to read
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "Indicated Altitude", "feet");
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "HEADING INDICATOR", "degrees", SIMCONNECT_DATATYPE_INT32);
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "Airspeed Indicated", "knots", SIMCONNECT_DATATYPE_INT32);
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "VERTICAL SPEED", "Feet per second", SIMCONNECT_DATATYPE_INT32);


	// EVERY SECOND REQUEST DATA FOR DEFINITION 1 ON THE CURRENT USER AIRCRAFT (SIMCONNECT_OBJECT_ID_USER)
	hr = SimConnect_RequestDataOnSimObject(m_sim, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);

	// Actions to send
	hr = SimConnect_MapClientEventToSimEvent(m_sim, SPOILERS_TOGGLE, "SPOILERS_TOGGLE");

}

health MSFSConnection::get_state()
{
	return m_state;
}

void MSFSConnection::read_from_sim()
{
	// Read data from the simulation
	m_state = ON;

	// Read
	SimConnect_CallDispatch(m_sim, MyDispatchProc1, NULL);

	if (false)
	{
		m_state = FAIL;
	}
}

void MSFSConnection::send_to_sim()
{
	// Send data to simulation

	if (temp_count < 200)
	{
		temp_count += 1;
	}
	else
	{
		temp_count = 0;
		printf("Toggle SPOILER\n");
		TxAction(SPOILERS_TOGGLE);
		// SimConnect_TransmitClientEvent(m_sim, 0, SPOILERS_TOGGLE, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
	}
	
}

void MSFSConnection::pass_action()
{
	// Pass actions to the simulation
}

void MSFSConnection::pass_data()
{
	// Send data to the Pico
}
