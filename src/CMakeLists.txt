set(SOURCES
    main.c
    ChipControl/ChipControl.c
    Drivers/LTC2943.c
    # Add more source files here
)


add_executable(target ${SOURCES}) # specify the executable to be built and its source files
target_include_directories(target PUBLIC Drivers)
target_include_directories(target PUBLIC ChipControl)