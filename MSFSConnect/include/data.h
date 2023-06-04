// data.h : Include file for standard system include files,
// or project specific include files.

#ifndef DATA_H
#define DATA_H


// Data to Read

enum DATA_DEFINE_ID {
	DEFINITION_1,
};

enum DATA_REQUEST_ID {
	REQUEST_1,
	REQUEST_2,
};

// Read data
struct SimResponse {
	double altitude;
	int32_t heading;
	int32_t speed;
	int32_t vertical_speed;
};

// Send data


// Actions to send

// Macro to send events
#define TxAction(action) SimConnect_TransmitClientEvent(m_sim, 0, action, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY)

typedef enum {
	FLAPS_DECR,			// Decrements flap handle position
	FLAPS_INCR,			// Increments flap handle position
	SPOILERS_TOGGLE,	// Toggles spoiler handle.
	// 
	// https://docs.flightsimulator.com/html/Programming_Tools/Event_IDs/Aircraft_Autopilot_Flight_Assist_Events.htm
	AP_MASTER,			// Toggles AP on / off
	AUTOPILOT_OFF,		// Turns AP off
	AUTOPILOT_ON,		// Turns AP on
	AP_AIRSPEED_HOLD,	// Toggles airspeed hold mode
} sim_actions;


#endif /* !DATA_H */

