#include "ChipControl.h"
#include "fake_LTC2943.h"
#include <stdio.h>

enum ctest_return_status { SUCCESS = 0, FAILURE = 1 } ctest_return_status;

uint8_t Set_ADC_Mode_AUTO();
uint8_t Set_ADC_Mode_AUTO() {

	SetADCModeInput input;
	input.mode = AUTO;

	// Set the rest of the Control Register with valid settings
	register_map_values.control_register =
	    CONTROL_REGISTER_NOT_ADC_MODE_MASK;

	// Unit Under Test
	ChipControl_Set_ADC_Mode(&input);

	// Retrieve Control Register, Mask out non ADC Bits, move to the
	// LSb, and check if equal to the desired mode
	if ((register_map_values.control_register &
	     CONTROL_REGISTER_ADC_MODE_MASK) >>
		CONTROL_REGISTER_ADC_MODE_BIT !=
	    AUTO) {
		return FAILURE;
	}

	return SUCCESS;
}

uint8_t Set_ADC_Mode_SCAN();
uint8_t Set_ADC_Mode_SCAN() {

	SetADCModeInput input;
	input.mode = SCAN;

	// Set the rest of the Control Register with valid settings
	register_map_values.control_register =
	    CONTROL_REGISTER_NOT_ADC_MODE_MASK;

	// Unit Under Test
	ChipControl_Set_ADC_Mode(&input);

	// Retrieve Control Register, Mask out non ADC Bits, move to the
	// LSb, and check if equal to the desired mode
	if ((register_map_values.control_register &
	     CONTROL_REGISTER_ADC_MODE_MASK) >>
		CONTROL_REGISTER_ADC_MODE_BIT !=
	    SCAN) {
		return FAILURE;
	}

	return SUCCESS;
}

uint8_t Set_ADC_Mode_MANUAL();
uint8_t Set_ADC_Mode_MANUAL() {

	SetADCModeInput input;
	input.mode = MANUAL;

	// Set the rest of the Control Register with valid settings
	register_map_values.control_register =
	    CONTROL_REGISTER_NOT_ADC_MODE_MASK;

	// Unit Under Test
	ChipControl_Set_ADC_Mode(&input);

	// Retrieve Control Register, Mask out non ADC Bits, move to the
	// LSb, and check if equal to the desired mode
	if ((register_map_values.control_register &
	     CONTROL_REGISTER_ADC_MODE_MASK) >>
		CONTROL_REGISTER_ADC_MODE_BIT !=
	    MANUAL) {
		return FAILURE;
	}

	return SUCCESS;
}

uint8_t Set_ADC_Mode_SLEEP();
uint8_t Set_ADC_Mode_SLEEP() {

	SetADCModeInput input;
	input.mode = SLEEP;

	// Set the rest of the Control Register with valid settings
	register_map_values.control_register =
	    CONTROL_REGISTER_NOT_ADC_MODE_MASK;

	// Unit Under Test
	ChipControl_Set_ADC_Mode(&input);

	// Retrieve Control Register, Mask out non ADC Bits, move to the
	// LSb, and check if equal to the desired mode
	if ((register_map_values.control_register &
	     CONTROL_REGISTER_ADC_MODE_MASK) >>
		CONTROL_REGISTER_ADC_MODE_BIT !=
	    SLEEP) {
		return FAILURE;
	}

	return SUCCESS;
}

int main() {

	// Get ADC Mode to Auto and confirm it was set
	uint8_t status_auto = Set_ADC_Mode_AUTO();

	// Get ADC Mode to Scan and confirm it was set
	uint8_t status_scan = Set_ADC_Mode_SCAN();

	// Get ADC Mode to Manual and confirm it was set
	uint8_t status_manual = Set_ADC_Mode_MANUAL();

	// Get ADC Mode to Sleep and confirm it was set
	uint8_t status_sleep = Set_ADC_Mode_SLEEP();

	uint8_t status =
	    status_auto | status_scan | status_manual | status_sleep;

	return status;
}
