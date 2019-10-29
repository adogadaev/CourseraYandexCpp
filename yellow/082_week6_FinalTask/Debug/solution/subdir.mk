################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../solution/condition_parser.cpp \
../solution/condition_parser_test.cpp \
../solution/database.cpp \
../solution/database_test.cpp \
../solution/date.cpp \
../solution/date_test.cpp \
../solution/event_set.cpp \
../solution/main.cpp \
../solution/node.cpp \
../solution/node_test.cpp \
../solution/token.cpp 

OBJS += \
./solution/condition_parser.o \
./solution/condition_parser_test.o \
./solution/database.o \
./solution/database_test.o \
./solution/date.o \
./solution/date_test.o \
./solution/event_set.o \
./solution/main.o \
./solution/node.o \
./solution/node_test.o \
./solution/token.o 

CPP_DEPS += \
./solution/condition_parser.d \
./solution/condition_parser_test.d \
./solution/database.d \
./solution/database_test.d \
./solution/date.d \
./solution/date_test.d \
./solution/event_set.d \
./solution/main.d \
./solution/node.d \
./solution/node_test.d \
./solution/token.d 


# Each subdirectory must supply rules for building sources it contributes
solution/%.o: ../solution/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


