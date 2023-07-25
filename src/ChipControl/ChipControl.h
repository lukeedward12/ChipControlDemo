#ifndef CHIPCONTROL_H
#define CHIPCONTROL_H

#include <stdint.h>

// clang-format off
/***********************************************************************
 * FILENAME :        ChipControl.h
 *
 * DESCRIPTION :
 *       The ChipControl C Submodule provides APIs for Getting & Setting
 *	 	 registers within the LTC2943 through a LTC2943 I2C
 *		 Driver.
 *
 * PUBLIC FUNCTIONS :
 *       uint8_t ChipControl_Initialize(void)
 *       uint8_t ChipControl_Get_ADC_Mode(GetADCModeResponse *response)
 *       uint8_t ChipControl_Set_ADC_Mode(SetADCModeInput *input)
 *		 uint8_t ChipControl_Get_Temp_Status(GetTempStatusResponse *response)
 *		 uint8_t ChipControl_Set_Charge_Thresholds(SetChargeThresholdInput *input)
 * 		 uint8_t ChipControl_Get_Charge_Status(GetChargeStatusResponse *response)
 * 
 * NOTES :
 *       The ChipControl C Submodule is intended to be statically linked against a 
 *  	 single-threaded C/C++ Application, and currently does use any resource
 * 		 safety mechanisms to allow for API calls from multiple threads in a 
 * 		 multi-threaded application.
 * 		 
 * AUTHOR :    Luke Edward       START DATE :    21 July 2023
 *
 *
 **/
// clang-format on

enum ChipControlStatusCodes {
	CC_STATUS_OK,
	CC_STATUS_ERROR,
	CC_STATUS_ERROR_PARAMS
};

typedef struct LTC2943RegisterMap {
	uint8_t Status;
	uint8_t Control;
	uint8_t Accumlated_Charge_MSB;
	uint8_t Accumlated_Charge_LSB;
	uint8_t Charge_Threshold_High_MSB;
	uint8_t Charge_Threshold_High_LSB;
	uint8_t Charge_Threshold_Low_MSB;
	uint8_t Charge_Threshold_Low_LSB;
	uint8_t Voltage_MSB;
	uint8_t Voltage_LSB;
	uint8_t Voltage_Threshold_High_MSB;
	uint8_t Voltage_Threshold_High_LSB;
	uint8_t Voltage_Threshold_Low_MSB;
	uint8_t Voltage_Threshold_Low_LSB;
	uint8_t Current_MSB;
	uint8_t Current_LSB;
	uint8_t Current_Threshold_High_MSB;
	uint8_t Current_Threshold_High_LSB;
	uint8_t Current_Threshold_Low_MSB;
	uint8_t Current_Threshold_Low_LSB;
	uint8_t Temperature_MSB;
	uint8_t Temperature_LBS;
	uint8_t Temperature_Threshold_High;
	uint8_t Temperature_Threshold_Low;
} LTC2943RegisterMap;

extern LTC2943RegisterMap register_map;

// Control Register ADC Mode Mask -> Bits [6:7]: 1100 0000
#define CONTROL_REGISTER_ADC_MODE_MASK 0xC0
#define CONTROL_REGISTER_ADC_MODE_BIT 6

// Control Register (NOT) ADC Mode Mask -> Bits [6:7]: 0011 0000
#define CONTROL_REGISTER_NOT_ADC_MODE_MASK 0x3F

// Status Register Temperature Alert Mask -> Bits [4]: 0001 0000
#define STATUS_REGISTER_TEMP_ALERT_MASK 0x10
#define STATUS_REGISTER_TEMP_ALERT_BIT 4

// Status Register Charge Alert Mask -> Bits [3:2]: 0000 1100
#define STATUS_REGISTER_CHARGE_HIGH_ALERT_MASK 0x8
#define STATUS_REGISTER_CHARGE_HIGH_ALERT_BIT 3
#define STATUS_REGISTER_CHARGE_LOW_ALERT_MASK 0x4
#define STATUS_REGISTER_CHARGE_LOW_ALERT_BIT 2

// Battery Characteristics. As a battery for this example was not provided,
// the example application provided in the LTC2943 (Pg. 11) will be used
// such that M = 4096, I_MAX = 100 Milli-Amps, Q_BAT = 2228 mAh, R_SENSE =
// 500 Milli-Ohms, and Q_LSb = 0.034 Milli-Ah
#define CHARGE_PRESCALAR 4096
#define R_SENSE 500  // Milli-Ohm
#define I_MAX 100    // Milli-Amps
#define q_LSb 0.034f // Milli-Ah
#define BATTERY_CHARGE_MAX 2228
#define BATTERY_CHARGE_MIN 0

#define LSB_16BIT_MASK 0x00FF
#define MSB_16BIT_MASK 0xFF00
#define MSB_16BIT_POSITION 8

enum ADCMode { SLEEP = 0, MANUAL = 1, SCAN = 2, AUTO = 3 };

enum Alert { NoAlert = 0, Alert = 1 };

/**
 * @brief Initializes the ChipControl Module and by ownership the LTC2943
 * Device Driver
 *
 * @return uint8_t ChipControl Status Code
 */
uint8_t ChipControl_Initialize(void);

typedef struct GetADCModeResponse {
	uint8_t mode;
} GetADCModeResponse;

/**
 * @brief Probes the LTC2943's Control Register for the ADC Mode (Sleep,
 * Manual, Scan, or Auto) and populates a provided response struct
 *
 * @param response LTC2943 probed ADC Mode (SLEEP = 0, MANUAL = 1, SCAN =
 * 2, AUTO = 3 )
 * @return uint8_t ChipControl Status Code
 */
uint8_t ChipControl_Get_ADC_Mode(GetADCModeResponse *response);

typedef struct SetADCModeInput {
	uint8_t mode;
} SetADCModeInput;

/**
 * @brief Sets the LTC2943's Control Register with a desired ADC Mode
 * (Sleep, Manual, Scan, or Auto)
 *
 * @param input Desired LTC2943 ADC Mode (SLEEP = 0, MANUAL = 1, SCAN = 2,
 * AUTO = 3)
 * @return uint8_t ChipControl Status Code
 */
uint8_t ChipControl_Set_ADC_Mode(SetADCModeInput *input);

typedef struct GetTempStatusResponse {
	uint8_t status;
} GetTempStatusResponse;

/**
 * @brief Probes the LTC2943's Status Register for the Temperature Alert
 * (Bit [4]) and populates a provided response struct. This API ignores
 * whether the LTC2943's ADC is in sleep mode and the device's Alerts are
 * being used.
 *
 * @param response LTC2943 probed Temperature Alert Status (NoAlert = 0,
 * Alert = 1)
 * @return uint8_t ChipControl Status Code
 */
uint8_t ChipControl_Get_Temp_Status(GetTempStatusResponse *response);

typedef struct SetChargeThresholdInput {
	uint32_t max_threshold;
	uint32_t min_threshold;
} SetChargeThresholdInput;

/**
 * @brief Takes a desired max/min charge in mAh, converts from mAh
 * to 16 bit fixed width, and sets the LTC2943 Charge Threshold Registers
 *
 * @param input Desired max/min charge thresholds in mAh. Min: 0 Max: 2228
 * mAh
 * @return uint8_t ChipControl Status Code
 */
uint8_t ChipControl_Set_Charge_Thresholds(SetChargeThresholdInput *input);

typedef struct GetChargeStatusResponse {

	uint8_t high_charge_status;
	uint8_t low_charge_status;

} GetChargeStatusResponse;

/**
 * @brief Probes the LTC2943's Status Register for the Charge Alerts
 * (Bit [2:3]) and populates a provided response struct. This API ignores
 * whether the LTC2943's ADC is in sleep mode and the device's Alerts are
 * being used.
 *
 * @param response LTC2943 probed Charge Alert Status (NoAlert = 0,
 * Alert = 1)
 * @return uint8_t ChipControl Status Code
 */
uint8_t ChipControl_Get_Charge_Status(GetChargeStatusResponse *response);

#endif // CHIPCONTROL_H