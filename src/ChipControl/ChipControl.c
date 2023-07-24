#include "ChipControl.h"
#include "LCT2943.h"

uint8_t ChipControl_Initialize(void)
{
    // Initialize the Device Driver
    bool init_status = LTC2943_Initialise();

    if (init_status == LTC_STATUS_OK)
    {
        return CC_STATUS_OK;
    }
    else
    {
        return CC_STATUS_ERROR;
    }
}

uint8_t ChipControl_Get_ADC_Mode(GetADCModeResponse *response)
{
    uint8_t probed_control_register = 0;
    uint8_t dataSize = 1;
    bool read_status = 0;

    // Probe the LTC2943's Control Register
    read_status = LTC2943_Read(register_map.Control, &probed_control_register, dataSize);

    if (read_status != LTC_STATUS_OK)
    {
        return CC_STATUS_ERROR;
    }

    // Figure out which ADC Mode we got
    response->mode = probed_control_register & CONTROL_REGISTER_ADC_MODE_MASK;

    return CC_STATUS_OK;
}

uint8_t ChipControl_Set_ADC_Mode(SetADCModeInput *input)
{
    uint8_t probed_control_register = 0;
    uint8_t dataSize = 1;
    bool write_status = 0;
    bool read_status = 0;

    // Check if input->mode contains a valid input ADC Mode
    if (input->mode != SLEEP || input->mode != MANUAL || input->mode != SCAN || input->mode != AUTO)
    {
        return CC_STATUS_ERROR_PARAMS;
    }

    // Before writing to the Control Register, we should figure out the current state of bits 0-5 and embed in
    // desired control register

    // Probe the LTC2943's Control Register
    read_status = LTC2943_Read(register_map.Control, &probed_control_register, dataSize);

    // Disregard the current ADC mode and strip from found control register
    probed_control_register = probed_control_register & CONTROL_REGISTER_NOT_ADC_MODE_MASK;

    if (read_status != LTC_STATUS_OK)
    {
        return CC_STATUS_ERROR;
    }

    // Combine current Control Register (Bits [0:5]) with Desired ADC Mode (Bits [6:7])
    uint8_t desired_control_register = input->mode | probed_control_register;
    write_status = LTC2943_Write(register_map.Control, &desired_control_register, dataSize);

    if (write_status != LTC_STATUS_OK)
    {
        return CC_STATUS_ERROR;
    }

    return CC_STATUS_OK;
}

uint8_t ChipControl_Get_Temp_Status()
{
    return CC_STATUS_OK;
}

uint8_t ChipControl_Set_Charge_Thresholds()
{
    return CC_STATUS_OK;
}

uint8_t ChipControl_Get_Charge_Status()
{

    return CC_STATUS_OK;
}