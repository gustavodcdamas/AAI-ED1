################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AAI-ED1-Gabriel-GustavoD-GustavoS-Isabela.c \
../src/funcoes.c 

C_DEPS += \
./src/AAI-ED1-Gabriel-GustavoD-GustavoS-Isabela.d \
./src/funcoes.d 

OBJS += \
./src/AAI-ED1-Gabriel-GustavoD-GustavoS-Isabela.o \
./src/funcoes.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/AAI-ED1-Gabriel-GustavoD-GustavoS-Isabela.d ./src/AAI-ED1-Gabriel-GustavoD-GustavoS-Isabela.o ./src/funcoes.d ./src/funcoes.o

.PHONY: clean-src

