#include "ChipControl.h"

int main()
{
    ChipControl_Initialize();

    GetADCModeResponse response;
    ChipControl_Get_ADC_Mode(&response);
    return 0;
}