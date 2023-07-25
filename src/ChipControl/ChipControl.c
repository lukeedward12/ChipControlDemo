#include "ChipControl.h"
#include "LTC2943.h"

LTC2943RegisterMap register_map = {0x00, 0x01, 0x02, 0x03, 0x04,  0x05,
				   0x06, 0x07, 0x08, 0x09, 0x0A,  0x0B,
				   0x0C, 0x0D, 0x0E, 0x0F, 0x010, 0x11,
				   0x12, 0x13, 0x14, 0x15, 0x16,  0x17};

uint8_t ChipControl_Initialize(void) {
	// Initialize the Device Driver
	bool init_status = LTC2943_Initialise();

	if (init_status == LTC_STATUS_OK) {
		return CC_STATUS_OK;
	} else {
		return CC_STATUS_ERROR;
	}
}

uint8_t ChipControl_Get_ADC_Mode(GetADCModeResponse *response) {
	uint8_t probed_control_register = 0;
	uint8_t dataSize = 1;
	bool read_status = 0;

	// Probe the LTC2943's Control Register
	read_status = LTC2943_Read(register_map.Control,
				   &probed_control_register, dataSize);

	if (read_status != LTC_STATUS_OK) {
		return CC_STATUS_ERROR;
	}

	// Figure out which ADC Mode we got
	response->mode =
	    (probed_control_register & CONTROL_REGISTER_ADC_MODE_MASK) >>
	    CONTROL_REGISTER_ADC_MODE_BIT;

	return CC_STATUS_OK;
}

uint8_t ChipControl_Set_ADC_Mode(SetADCModeInput *input) {
	uint8_t probed_control_register = 0;
	uint8_t dataSize = 1;
	bool write_status = 0;
	bool read_status = 0;

	// Check if input->mode contains a valid input ADC Mode
	if (!(input->mode == (uint8_t)SLEEP ||
	      input->mode == (uint8_t)MANUAL ||
	      input->mode == (uint8_t)SCAN ||
	      input->mode == (uint8_t)AUTO)) {
		return CC_STATUS_ERROR_PARAMS;
	}

	// Before writing to the Control Register, we should figure out the
	// current state of bits 0-5 and embed in desired control register

	// Probe the LTC2943's Control Register
	read_status = LTC2943_Read(register_map.Control,
				   &probed_control_register, dataSize);

	// Disregard the current ADC mode and strip from found control
	// register
	probed_control_register =
	    probed_control_register & CONTROL_REGISTER_NOT_ADC_MODE_MASK;

	if (read_status != LTC_STATUS_OK) {
		return CC_STATUS_ERROR;
	}

	// Combine current Control Register (Bits [0:5]) with Desired ADC
	// Mode (Bits [6:7])
	uint8_t desired_control_register =
	    (input->mode << CONTROL_REGISTER_ADC_MODE_BIT) |
	    probed_control_register;
	write_status = LTC2943_Write(register_map.Control,
				     &desired_control_register, dataSize);

	if (write_status != LTC_STATUS_OK) {
		return CC_STATUS_ERROR;
	}

	return CC_STATUS_OK;
}

uint8_t ChipControl_Get_Temp_Status(GetTempStatusResponse *response) {
	uint8_t probed_status_register = 0;
	uint8_t dataSize = 1;
	bool read_status = 0;

	// Probe the LTC2943's Control Register
	read_status = LTC2943_Read(register_map.Status,
				   &probed_status_register, dataSize);

	if (read_status != LTC_STATUS_OK) {
		return CC_STATUS_ERROR;
	}

	// To get the temp alert mask, AND the probed Status Register with
	// the Mask, and then move the bit to the MSb
	uint8_t temp_alert_status =
	    (probed_status_register & STATUS_REGISTER_TEMP_ALERT_MASK) >>
	    STATUS_REGISTER_TEMP_ALERT_BIT;

	response->status = temp_alert_status;

	return CC_STATUS_OK;
}

uint8_t ChipControl_Set_Charge_Thresholds(SetChargeThresholdInput *input) {
	uint8_t dataSize = 1;
	bool write_status_max_lsb = 0;
	bool write_status_max_msb = 0;
	bool write_status_min_lsb = 0;
	bool write_status_min_msb = 0;

	// First, determine if Max or Min desired Charge Threshold is
	// within battery limits of 0 mAh <-> 2228 mAh

	if (input->max_threshold > BATTERY_CHARGE_MAX ||
	    input->min_threshold > BATTERY_CHARGE_MAX) {
		return CC_STATUS_ERROR_PARAMS;
	}

	// Convert input threshold (mAh) to 16 bit fixed width such that
	// 0.034 mAh = 1 Least Significant Bit Fixed Width = Desired Charge
	// [mAh] / 0.034 [mAh / LSb]
	uint16_t max_threshold_fixed = input->max_threshold / q_LSb;
	uint16_t min_threshold_fixed = input->min_threshold / q_LSb;

	// Split Fixed Width Threshold to LSB and MSB
	uint8_t max_threshold_fixed_LSB =
	    max_threshold_fixed & LSB_16BIT_MASK;
	uint8_t max_threshold_fixed_MSB =
	    (max_threshold_fixed & MSB_16BIT_MASK) >> MSB_16BIT_POSITION;
	uint8_t min_threshold_fixed_LSB =
	    min_threshold_fixed & LSB_16BIT_MASK;
	uint8_t min_threshold_fixed_MSB =
	    (min_threshold_fixed & MSB_16BIT_MASK) >> MSB_16BIT_POSITION;

	// Set the Charge Thresholds in the LTC2943
	write_status_max_lsb =
	    LTC2943_Write(register_map.Charge_Threshold_High_LSB,
			  &max_threshold_fixed_LSB, dataSize);

	write_status_max_msb =
	    LTC2943_Write(register_map.Charge_Threshold_High_MSB,
			  &max_threshold_fixed_MSB, dataSize);

	write_status_min_lsb =
	    LTC2943_Write(register_map.Charge_Threshold_Low_LSB,
			  &min_threshold_fixed_LSB, dataSize);

	write_status_min_msb =
	    LTC2943_Write(register_map.Charge_Threshold_Low_MSB,
			  &min_threshold_fixed_MSB, dataSize);

	if (write_status_max_lsb != LTC_STATUS_OK ||
	    write_status_max_msb != LTC_STATUS_OK ||
	    write_status_min_lsb != LTC_STATUS_OK ||
	    write_status_min_msb != LTC_STATUS_OK) {
		return CC_STATUS_ERROR;
	}

	return CC_STATUS_OK;
}

uint8_t ChipControl_Get_Charge_Status(GetChargeStatusResponse *response) {

	uint8_t probed_status_register = 0;
	uint8_t dataSize = 1;
	bool read_status = 0;

	// Probe the LTC2943's Control Register
	read_status = LTC2943_Read(register_map.Status,
				   &probed_status_register, dataSize);

	if (read_status != LTC_STATUS_OK) {
		return CC_STATUS_ERROR;
	}

	// To get the charge alert mask, AND the probed Status Register
	// with the Mask, and then move the bit to the MSb
	uint8_t charge_high_alert_status =
	    (probed_status_register &
	     STATUS_REGISTER_CHARGE_HIGH_ALERT_MASK) >>
	    STATUS_REGISTER_CHARGE_HIGH_ALERT_BIT;
	uint8_t charge_low_alert_status =
	    (probed_status_register &
	     STATUS_REGISTER_CHARGE_LOW_ALERT_MASK) >>
	    STATUS_REGISTER_CHARGE_LOW_ALERT_BIT;

	response->high_charge_status = charge_high_alert_status;
	response->low_charge_status = charge_low_alert_status;

	return CC_STATUS_OK;
}