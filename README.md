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
└── README.md

## Requirements
* Docker
* apt package manager

## Build & Test
All building and unit testing is handled with CMake and CTest in a Docker container to prevent conflicts with dev environment packages. \
To build and test: \
    `. ./build_test.sh`

## AstroScale Interview Question:
Question: without implementation, how would you handle this IO interface in a RTOS environment?

To handle this within an RTOS environment, I would go with one of the following choices:
1. Transition the ChipControl to an RTOS Task and move APIs from public functions to queues.
2. Allow the ChipControl to be statically linked to any RTOS Task, but introduce resource protection mechanisms
on shared resources (LTC2943 Driver & Static/Global Objects)

The better choice is probably (1), as interactions with shared resources become more deterministic (Task A submits a request to the API queue first, so its
request gets fulfilled before another request is handler), better concurrency control eliminates having to use synchronization mechanisms (mutex, semaphore) within itself to avoid race
conditions, and a more human-intuitive design (ChipControl access is encapsulated to its own task).

Continuing with option (1), I would design the **ChipControl Task** to block (Up to several seconds to allow for occasional LTC2943 Housekeeping, Health checks, and 
Watchdog Petting/Reporting) on a API Queue, where other Tasks populate the API queue with requests for certain behavior (Get ADC Mode, Get Temp, Set Thresholds, etc).
When the ChipControl Task receives a new message on the API queue, it would parse the request, enter the appropriate LTC2943 Handler, package the response from the LTC2943, 
and respond to the Task over a separate response queue. 
