################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include board/subdir.mk
-include VTBI/subdir.mk
-include Used_hrs/subdir.mk
-include Timer/subdir.mk
-include TFT_String/subdir.mk
-include Syringe_Length_Calibration/subdir.mk
-include Stepper_Motor/subdir.mk
-include Sound/subdir.mk
-include Shapes/subdir.mk
-include Serial_no_setting/subdir.mk
-include SD_Calibration/subdir.mk
-include RTC_DRIVER/subdir.mk
-include RTC/subdir.mk
-include Pressure_Calibration/subdir.mk
-include Power_off/subdir.mk
-include Password/subdir.mk
-include PWM/subdir.mk
-include PLUNGER_ALARM/subdir.mk
-include PINT/subdir.mk
-include Occlusion/subdir.mk
-include Motor/subdir.mk
-include Mode_function/subdir.mk
-include Menu_Setting/subdir.mk
-include Main_screen/subdir.mk
-include Linear_Pot_Calibration/subdir.mk
-include Last_Infusion_clear/subdir.mk
-include Keypad/subdir.mk
-include Infused_Calculate/subdir.mk
-include I2C/subdir.mk
-include GPIO/subdir.mk
-include Font_style/subdir.mk
-include Flowrate_screen/subdir.mk
-include Factory_Setting/subdir.mk
-include FR_Calculate/subdir.mk
-include External_RTC/subdir.mk
-include Event_log/subdir.mk
-include Dynamic_Pressure/subdir.mk
-include Drug_List/subdir.mk
-include Driver_ST7789V/subdir.mk
-include Driver_SPI/subdir.mk
-include Dose_rate/subdir.mk
-include DAC_DRIVER/subdir.mk
-include Calibration_Screen/subdir.mk
-include Brand/subdir.mk
-include Boot_up/subdir.mk
-include Bolus_Concept/subdir.mk
-include Battery/subdir.mk
-include Alarm/subdir.mk
-include ADC/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := LPC55S16_Project
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: LPC55S16_Project.axf

# Tool invocations
LPC55S16_Project.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="LPC55S16_Project.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T LPC55S16_Project_Debug.ld -o "LPC55S16_Project.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) LPC55S16_Project.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "LPC55S16_Project.axf"; # arm-none-eabi-objcopy -v -O binary "LPC55S16_Project.axf" "LPC55S16_Project.bin" ; # checksum -p LPC55S16 -d "LPC55S16_Project.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
