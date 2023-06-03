//

#include "MSFSConnection.h"
#include "data.h"
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

	// EVERY SECOND REQUEST DATA FOR DEFINITION 1 ON THE CURRENT USER AIRCRAFT (SIMCONNECT_OBJECT_ID_USER)
	hr = SimConnect_RequestDataOnSimObject(m_sim, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);

	//
	m_state = INIT;

}

void MSFSConnection::tick()
{
	int EVENT_THROTTLE_FULL = 0;
	int GROUP_A = 0;

	HRESULT hr;

	hr = SimConnect_MapClientEventToSimEvent(m_sim, EVENT_THROTTLE_FULL, "THROTTLE_FULL");
	hr = SimConnect_AddClientEventToNotificationGroup(m_sim, GROUP_A, EVENT_THROTTLE_FULL);
	hr = SimConnect_SetNotificationGroupPriority(m_sim, GROUP_A, SIMCONNECT_GROUP_PRIORITY_HIGHEST);
	
	SimConnect_TransmitClientEvent(m_sim, 0, EVENT_THROTTLE_FULL, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);

	// 
	// SimConnect_CallDispatch(m_sim, MyDispatchProc1, NULL);

	//
	// read_data();

	//
	// send_data();

}

void MSFSConnection::stop()
{
	m_state = OFF;
}


void MSFSConnection::init_data()
{
	// Fonction to initialize all data to be read
	HRESULT hr;

	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "Indicated Altitude", "feet");
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "HEADING INDICATOR", "degrees", SIMCONNECT_DATATYPE_INT32);
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "Airspeed Indicated", "knots", SIMCONNECT_DATATYPE_INT32);
	hr = SimConnect_AddToDataDefinition(m_sim, DEFINITION_1, "VERTICAL SPEED", "Feet per second", SIMCONNECT_DATATYPE_INT32);
}

health MSFSConnection::get_state()
{
	return m_state;
}

void MSFSConnection::read_data()
{
	m_state = ON;

	if (false)
	{
		m_state = FAIL;
	}
}

void MSFSConnection::send_data()
{
	// Send data to simulation
}

void MSFSConnection::pass_action()
{
	// Pass actions to the simulation
}

void MSFSConnection::pass_data()
{
	// Send data to the Pico
}
