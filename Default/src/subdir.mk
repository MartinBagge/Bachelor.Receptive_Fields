################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parallelize.cpp \
../src/ReceptiveFields.cpp \
../src/main.cpp 

H_SRCS += \
../src/Parallelize.h \
../src/ReceptiveFields.h 

MOC_OUTPUT_OUTPUTS += \
./src/moc_Parallelize.cpp \
./src/moc_ReceptiveFields.cpp 

OBJS += \
./src/Parallelize.o \
./src/moc_Parallelize.o \
./src/ReceptiveFields.o \
./src/moc_ReceptiveFields.o \
./src/main.o 

CPP_DEPS += \
./src/Parallelize.d \
./src/moc_Parallelize.d \
./src/ReceptiveFields.d \
./src/moc_ReceptiveFields.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: C++ Compiler'
	g++ -I/usr/local/cuda-7.5/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
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
	g++ -I/usr/local/cuda-7.5/include -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


