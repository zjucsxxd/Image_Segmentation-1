################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main_Pkg/test.cpp 

OBJS += \
./main_Pkg/test.o 

CPP_DEPS += \
./main_Pkg/test.d 


# Each subdirectory must supply rules for building sources it contributes
main_Pkg/%.o: ../main_Pkg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


