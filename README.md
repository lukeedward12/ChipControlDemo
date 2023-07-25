# ChipControlDemo
## Overview
This repository is a C project Demonstration for developing a ChipControl C Submodule. The C Submodule, constituted by ChipControl.c & ChipControl.h, interacts with a LTC2943 Multicell Battery Gas Gauge 
through a LTC2943-I2C Device Driver (https://www.analog.com/media/en/technical-documentation/data-sheets/2943fa.pdf). 

ChipControl APIs:
* uint8_t ChipControl_Initialize(void)
* uint8_t ChipControl_Get_ADC_Mode(GetADCModeResponse *response)
* uint8_t ChipControl_Set_ADC_Mode(SetADCModeInput *input)
* uint8_t ChipControl_Get_Temp_Status(GetTempStatusResponse *response)
* uint8_t ChipControl_Set_Charge_Thresholds(SetChargeThresholdInput *input)
* uint8_t ChipControl_Get_Charge_Status(GetChargeStatusResponse *response)

## Directory Overview
├── build                   # Compiled source and testing targets \
├── src                     # Source files \
├── test                    # Unit Testing \
├── build_test.sh \
├── ChipControl_Architecture.drawio \
├── CMakeLists.txt \
├── dockerfile \
└── README.md \

## Requirements
* Docker
* apt package manager

## Build & Test
All building and unit testing is handling with CMake and CTest in a docker container. 
To build and test:
    `. ./build_test.sh`

## AstroScale Interview Question:
Question: without implementation, how would you handle this IO interface in a RTOS environment?

