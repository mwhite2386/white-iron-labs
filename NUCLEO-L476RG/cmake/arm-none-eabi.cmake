set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)


find_program(CMAKE_C_COMPILER arm-none-eabi-gcc)

if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "arm-none-eabi-gcc compiler not found")
endif()

find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++)

if(NOT CMAKE_CXX_COMPILER)
    message(FATAL_ERROR "arm-none-eabi-g++ compiler not found")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)



