################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../bus_manager.cpp \
../main.cpp \
../query.cpp \
../responses.cpp 

OBJS += \
./bus_manager.o \
./main.o \
./query.o \
./responses.o 

CPP_DEPS += \
./bus_manager.d \
./main.d \
./query.d \
./responses.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


