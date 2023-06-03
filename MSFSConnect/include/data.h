// data.h : Include file for standard system include files,
// or project specific include files.

#pragma once


struct {

} data_name;

struct {

} data_type;


static enum DATA_DEFINE_ID {
	DEFINITION_1,
};

static enum DATA_REQUEST_ID {
	REQUEST_1,
	REQUEST_2,
};

// Read data
struct SimResponse {
	// 
	double altitude;
	int32_t heading;
	int32_t speed;
	int32_t vertical_speed;
};

// Send data
