################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ReceptiveFields.cpp 

H_SRCS += \
../src/ReceptiveFields.h 

CU_SRCS += \
../src/Parallelize.cu \
../src/main.cu 

CU_DEPS += \
./src/cu_Parallelize.d \
./src/cu_main.d 

MOC_OUTPUT_OUTPUTS += \
./src/moc_ReceptiveFields.cpp 

OBJS += \
./src/cu_Parallelize.o \
./src/ReceptiveFields.o \
./src/moc_ReceptiveFields.o \
./src/cu_main.o 

CPP_DEPS += \
./src/ReceptiveFields.d \
./src/moc_ReceptiveFields.d 


# Each subdirectory must supply rules for building sources it contributes
src/cu_%.o: ../src/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: CUDA NVCC Compiler'
	nvcc -c  -o "$@" "$<" && \
	echo -n '$(@:%.o=%.d)' $(dir $@) > '$(@:%.o=%.d)' && \
	nvcc -M   "$<" >> '$(@:%.o=%.d)'
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/moc_%.cpp: ../src/%.h
	@echo 'Building file: $<'
	@echo 'Invoking: QT Meta-Object Compiler'
	moc  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


