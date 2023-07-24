#include "ChipControl.h"
#include "fake_LTC2943.h"
#include <stdio.h>

enum ctest_return_status { SUCCESS = 0, FAILURE = 1 } ctest_return_status;

uint8_t Get_Charge_Status_ALERT();
uint8_t Get_Charge_Status_ALERT() {
	register_map_values.status_register = 0;

	register_map_values.status_register =
	    register_map_values.status_register |
	    STATUS_REGISTER_CHARGE_HIGH_ALERT_MASK |
	    STATUS_REGISTER_CHARGE_LOW_ALERT_MASK;

	GetChargeStatusResponse response = {.high_charge_status = 0,
					    .low_charge_status = 0};

	// Unit Under Test
	uint8_t api_return = ChipControl_Get_Charge_Status(&response);

	if (response.high_charge_status == Alert &&
	    response.low_charge_status == Alert &&
	    api_return == CC_STATUS_OK) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

uint8_t Get_Charge_Status_NOMINAL();
uint8_t Get_Charge_Status_NOMINAL() {
	register_map_values.status_register = 0;

	GetChargeStatusResponse response = {.high_charge_status = 0,
					    .low_charge_status = 0};

	// Unit Under Test
	uint8_t api_return = ChipControl_Get_Charge_Status(&response);

	if (response.high_charge_status == NoAlert &&
	    response.low_charge_status == NoAlert &&
	    api_return == CC_STATUS_OK) {
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

int main() {

	// Get the Temp Status when there is an alert
	uint8_t status_alert = Get_Charge_Status_ALERT();

	// Get the Temp Status when there is no alert
	uint8_t status_nominal = Get_Charge_Status_NOMINAL();

	uint8_t status = status_alert | status_nominal;
	return status;
}
