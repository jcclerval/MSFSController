//

#include "MSFSConnection.h"


void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
	bool quit = false;

	printf("Callback");
	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;

		switch (pObjData->dwRequestID)
		{
		case 0:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			double* pS = (double*)&pObjData->dwData;
			printf("\nObjectID=%d  Alt=%f", ObjectID, *pS);
			break;
		}

		default:
			break;
		}
		break;
	}


	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = true;
		printf("Exiting...\n");
		break;
	}

	default:
		printf("\nReceived:%d", pData->dwID);
		break;
	}
}

MSFSConnection::MSFSConnection()
{
	HANDLE m_sim = NULL;
}

void MSFSConnection::run()
{
	SimConnect_CallDispatch(m_sim, MyDispatchProcRD, NULL);
}

void MSFSConnection::init_connection()
{
	// init data
	HRESULT hr;

	hr = SimConnect_Open(&m_sim, "Your Application Name", NULL, 0, 0, SIMCONNECT_OPEN_CONFIGINDEX_LOCAL);

	if (hr == E_FAIL)
	{
		printf("Connection failed...\n");
		return void();
	}

	const char* szState = "Sim";
	// hr = SimConnect_RequestSystemState(m_sim, 0, szState);

	printf("Connection success\n");

	// Test
	hr = SimConnect_AddToDataDefinition(m_sim, 0, "Indicated Altitude", "feet");
}

double MSFSConnection::request_double(std::string requested_data)
{
	return 0.;
}

int MSFSConnection::request_int(std::string requested_data)
{
	return 0;
}
bool MSFSConnection::request_bool(std::string requested_data)
{
	return false;
}
