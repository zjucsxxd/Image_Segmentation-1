################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SLIC/Slic.cpp 

OBJS += \
./SLIC/Slic.o 

CPP_DEPS += \
./SLIC/Slic.d 


# Each subdirectory must supply rules for building sources it contributes
SLIC/%.o: ../SLIC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


