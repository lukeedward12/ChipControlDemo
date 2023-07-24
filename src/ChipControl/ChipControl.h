#ifndef CHIPCONTROL_H
#define CHIPCONTROL_H

#include <stdint.h>

enum ChipControlStatusCodes
{
    CC_STATUS_OK,
    CC_STATUS_ERROR,
    CC_STATUS_ERROR_PARAMS
};

typedef struct LTC2943RegisterMap
{
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

static LTC2943RegisterMap register_map = {0x00, 0x01, 0x02, 0x03, 0x04,
                                          0x05, 0x06, 0x07, 0x08, 0x09,
                                          0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
                                          0x0F, 0x010, 0x11, 0x12, 0x13,
                                          0x14, 0x15, 0x16, 0x17};

// ADC Mode Mask -> Bits [7:8]: 1100 0000
#define CONTROL_REGISTER_ADC_MODE_MASK 0xC0

// NOT ADC Mode Mask -> Bits [7:8]: 0011 0000
#define CONTROL_REGISTER_NOT_ADC_MODE_MASK 0x3F

enum ADCMode
{
    SLEEP = 0,
    MANUAL = 1,
    SCAN = 2,
    AUTO = 3
};

/**
 * @brief Initializes the ChipControl Module and by ownership the LTC2943 Device Driver
 *
 * @return uint8_t
 */
uint8_t ChipControl_Initialize(void);

typedef struct GetADCModeResponse
{
    uint8_t mode;
} GetADCModeResponse;

/**
 * @brief Probes the LTC2943's Control Register for the ADC Mode (Sleep, Manual, Scan, or Auto)
 * and populates a provided response struct
 *
 * @param response
 * @return uint8_t
 */
uint8_t ChipControl_Get_ADC_Mode(GetADCModeResponse *response);

typedef struct SetADCModeInput
{
    uint8_t mode;
} SetADCModeInput;

/**
 * @brief Sets the LTC2943's Control Register with a desired ADC Mode (Sleep, Manual, Scan, or Auto)
 *
 * @param input
 * @return uint8_t
 */
uint8_t ChipControl_Set_ADC_Mode(SetADCModeInput *input);

uint8_t ChipControl_Get_Temp_Status();
uint8_t ChipControl_Set_Charge_Thresholds();
uint8_t ChipControl_Get_Charge_Status();

#endif // CHIPCONTROL_H