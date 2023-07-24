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

    // If Read fails, return an Error Code and exit
    if (read_status != LTC_STATUS_OK)
    {
        return CC_STATUS_ERROR;
    }

    // Figure out which ADC Mode we got
    response->mode = probed_control_register & CONTROL_REGISTER_ADC_MODE_MASK;

    return CC_STATUS_OK;
}

uint8_t ChipControl_Set_ADC_Mode()
{
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