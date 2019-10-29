################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main.cpp \
../merge_sort_p1.cpp \
../merge_sort_p2.cpp 

OBJS += \
./main.o \
./merge_sort_p1.o \
./merge_sort_p2.o 

CPP_DEPS += \
./main.d \
./merge_sort_p1.d \
./merge_sort_p2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


