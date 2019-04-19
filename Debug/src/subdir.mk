################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ita2_converter.cpp \
../src/lab_2.cpp \
../src/lorenz_machine.cpp \
../src/wheel_system.cpp 

OBJS += \
./src/ita2_converter.o \
./src/lab_2.o \
./src/lorenz_machine.o \
./src/wheel_system.o 

CPP_DEPS += \
./src/ita2_converter.d \
./src/lab_2.d \
./src/lorenz_machine.d \
./src/wheel_system.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


