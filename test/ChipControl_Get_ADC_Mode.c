#include "ChipControl.h"
#include "fake_LTC2943.h"
#include <stdio.h>

enum ctest_return_status { SUCCESS = 0, FAILURE = 1 } ctest_return_status;

uint8_t Get_ADC_Mode_AUTO();
uint8_t Get_ADC_Mode_AUTO() {

	// Set the Control Register before using
	register_map_values.control_register =
	    AUTO << CONTROL_REGISTER_ADC_MODE_BIT;

	GetADCModeResponse get_adc_response;

	// Unit Under Test
	uint8_t api_return = ChipControl_Get_ADC_Mode(&get_adc_response);

	if (get_adc_response.mode == AUTO && api_return == CC_STATUS_OK) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

uint8_t Get_ADC_Mode_SCAN();
uint8_t Get_ADC_Mode_SCAN() {

	// Set the Control Register before using
	register_map_values.control_register =
	    SCAN << CONTROL_REGISTER_ADC_MODE_BIT;

	GetADCModeResponse get_adc_response;

	// Unit Under Test
	uint8_t api_return = ChipControl_Get_ADC_Mode(&get_adc_response);

	if (get_adc_response.mode == SCAN && api_return == CC_STATUS_OK) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

uint8_t Get_ADC_Mode_MANUAL();
uint8_t Get_ADC_Mode_MANUAL() {

	// Set the Control Register before using
	register_map_values.control_register =
	    MANUAL << CONTROL_REGISTER_ADC_MODE_BIT;

	GetADCModeResponse get_adc_response;

	// Unit Under Test
	uint8_t api_return = ChipControl_Get_ADC_Mode(&get_adc_response);

	if (get_adc_response.mode == MANUAL &&
	    api_return == CC_STATUS_OK) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

uint8_t Get_ADC_Mode_SLEEP();
uint8_t Get_ADC_Mode_SLEEP() {

	// Set the Control Register before using
	register_map_values.control_register =
	    MANUAL << CONTROL_REGISTER_ADC_MODE_BIT;

	GetADCModeResponse get_adc_response;

	// Unit Under Test
	uint8_t api_return = ChipControl_Get_ADC_Mode(&get_adc_response);

	if (get_adc_response.mode == MANUAL &&
	    api_return == CC_STATUS_OK) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

int main() {

	// Get ADC Mode when the current Mode is set to Auto
	uint8_t status_auto = Get_ADC_Mode_AUTO();

	// Get ADC Mode when the current mode is set to Scan
	uint8_t status_scan = Get_ADC_Mode_SCAN();

	// Get ADC Mode when the current mode is set to Manual
	uint8_t status_manual = Get_ADC_Mode_MANUAL();

	// Get ADC Mode when the current mode is set to Sleep
	uint8_t status_sleep = Get_ADC_Mode_MANUAL();

	uint8_t status =
	    status_auto | status_scan | status_manual | status_sleep;

	return status;
}
