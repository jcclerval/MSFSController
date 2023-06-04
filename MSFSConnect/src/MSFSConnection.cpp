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
			MSFSConnection::sim_out = *pS;

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

// Init sim_data
SimResponse MSFSConnection::sim_out = {
	0.,
	0,
	0,
	0
	};

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

	//
	m_state = INIT;

}

void MSFSConnection::tick()
{
	m_state = ON;

	// Read data from the simulation
	SimConnect_CallDispatch(m_sim, MyDispatchProc1, NULL);

	if (false)
	{
		m_state = FAIL;
	}

	// Update struct sim_out

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
	hr = SimConnect_MapClientEventToSimEvent(m_sim, FLAPS_DECR, "FLAPS_DECR");
	hr = SimConnect_MapClientEventToSimEvent(m_sim, FLAPS_INCR, "FLAPS_INCR");
	hr = SimConnect_MapClientEventToSimEvent(m_sim, SPOILERS_TOGGLE, "SPOILERS_TOGGLE");

	hr = SimConnect_MapClientEventToSimEvent(m_sim, AP_MASTER, "AP_MASTER");
	hr = SimConnect_MapClientEventToSimEvent(m_sim, AUTOPILOT_OFF, "AUTOPILOT_OFF");
	hr = SimConnect_MapClientEventToSimEvent(m_sim, AUTOPILOT_ON, "AUTOPILOT_ON");
	hr = SimConnect_MapClientEventToSimEvent(m_sim, AP_AIRSPEED_HOLD, "AP_AIRSPEED_HOLD");

}

health MSFSConnection::get_state()
{
	return m_state;
}


void MSFSConnection::process(SimCommand input_action)
{
	// Pass actions to the simulation

	// Decrease FLAPS
	if (input_action.dec_flaps)
	{
		printf("FLAPS DECREASE\n");
		TxAction(FLAPS_DECR);
	}
	// Increase FLAPS
	if (input_action.inc_flaps)
	{
		printf("FLAPS INCREASE\n");
		TxAction(FLAPS_INCR);
	}
	// Toggle spoilers
	if (input_action.toggle_spoilers)
	{
		TxAction(SPOILERS_TOGGLE);
	}
	// Toggle AP
	if (input_action.toggle_ap)
	{
		TxAction(AP_MASTER);
	}

}

