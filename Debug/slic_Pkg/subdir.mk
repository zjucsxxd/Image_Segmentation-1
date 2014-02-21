################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../slic_Pkg/Slic.cpp 

OBJS += \
./slic_Pkg/Slic.o 

CPP_DEPS += \
./slic_Pkg/Slic.d 


# Each subdirectory must supply rules for building sources it contributes
slic_Pkg/%.o: ../slic_Pkg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


