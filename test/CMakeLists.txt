set(SOURCES
    ChipControl_Unit.c
    ChipControl/ChipControl.c
    fakes/fake_LTC2943.c
    # Add more source files here
)

add_executable(ChipControl_Tests ChipControl_Unit.c) # Create a new executable for your tests.
add_test(NAME MyTest COMMAND ChipControl_Tests) # Define a test. 
target_include_directories(ChipControl_Tests PRIVATE ${SOURCE_DIR}/ChipControl)
target_include_directories(ChipControl_Tests PRIVATE ${SOURCE_DIR}/Drivers)