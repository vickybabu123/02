# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

if (DEFINED ENV{SdkRootDirPath})
	SET(SdkRootDirPath "$ENV{SdkRootDirPath}")
endif()

if (NOT DEFINED SdkRootDirPath)
	MESSAGE(FATAL_ERROR "SDK path could not be determined. Please update SdkRootDirPath value from your CMake presets file(s).")
endif()

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

# RESET FLAG VALUES
SET(CMAKE_ASM_FLAGS_DEBUG "")
SET(CMAKE_ASM_FLAGS_RELEASE "")
SET(CMAKE_C_FLAGS_DEBUG "")
SET(CMAKE_C_FLAGS_RELEASE "")
SET(CMAKE_CXX_FLAGS_DEBUG "")
SET(CMAKE_CXX_FLAGS_RELEASE "")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "")

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})

set(CMAKE_USER_MAKE_RULES_OVERRIDE "user_override.cmake")

project(LPC55S16_Project)
set(MCUX_SDK_PROJECT_NAME LPC55S16_Project.elf)

include(${ProjDirPath}/flags.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} "${ProjDirPath}/ADC/Driver_ADC.h"
"${ProjDirPath}/ADC/Driver_ADC.c"
"${ProjDirPath}/Alarm/Alarm.h"
"${ProjDirPath}/Alarm/Alarm.c"
"${ProjDirPath}/Battery/battery_frames.c"
"${ProjDirPath}/Battery/Battery.h"
"${ProjDirPath}/Battery/Battery.c"
"${ProjDirPath}/Bolus_Concept/Bolus_Screen.c"
"${ProjDirPath}/Bolus_Concept/bolus_menu_scrn.c"
"${ProjDirPath}/Bolus_Concept/bolus_limit.c"
"${ProjDirPath}/Bolus_Concept/Bolus_Header.h"
"${ProjDirPath}/Bolus_Concept/Bolus_Calculate..c"
"${ProjDirPath}/Boot_up/Boot_up.h"
"${ProjDirPath}/Boot_up/Boot_up.c"
"${ProjDirPath}/Brand/Frame_Brand_List.c"
"${ProjDirPath}/Brand/Brand.h"
"${ProjDirPath}/Brand/Brand.c"
"${ProjDirPath}/CMSIS/tz_context.h"
"${ProjDirPath}/CMSIS/mpu_armv8.h"
"${ProjDirPath}/CMSIS/core_cm33.h"
"${ProjDirPath}/CMSIS/cmsis_version.h"
"${ProjDirPath}/CMSIS/cmsis_gcc.h"
"${ProjDirPath}/CMSIS/cmsis_compiler.h"
"${ProjDirPath}/Calibration_Screen/Calibration_Screen.h"
"${ProjDirPath}/Calibration_Screen/Calibration_Screen.c"
"${ProjDirPath}/DAC_DRIVER/DAC_driver.h"
"${ProjDirPath}/DAC_DRIVER/DAC_driver.c"
"${ProjDirPath}/Dose_rate/Dose_frame.c"
"${ProjDirPath}/Dose_rate/Dosage_mode.h"
"${ProjDirPath}/Dose_rate/Dosage_mode.c"
"${ProjDirPath}/Driver_SPI/Driver_SPI.h"
"${ProjDirPath}/Driver_SPI/Driver_SPI.c"
"${ProjDirPath}/Driver_ST7789V/TFT_Commands.h"
"${ProjDirPath}/Driver_ST7789V/TFT_Commands.c"
"${ProjDirPath}/Drug_List/Rec_frame.c"
"${ProjDirPath}/Drug_List/Rec_drug_list.c"
"${ProjDirPath}/Drug_List/fav_frame.c"
"${ProjDirPath}/Drug_List/Fav_drug_list.c"
"${ProjDirPath}/Drug_List/Drug_name_search.c"
"${ProjDirPath}/Drug_List/Drug_List.h"
"${ProjDirPath}/Drug_List/Drug_List.c"
"${ProjDirPath}/Drug_List/Drug_frame.c"
"${ProjDirPath}/Drug_List/Drug_category.c"
"${ProjDirPath}/Drug_List/Dose_mode_fun.c"
"${ProjDirPath}/Drug_List/custom_drug_list.c"
"${ProjDirPath}/Drug_List/Add_Drug.c"
"${ProjDirPath}/Dynamic_Pressure/Dynamic_Pressure.h"
"${ProjDirPath}/Dynamic_Pressure/Dynamic_pressure.c"
"${ProjDirPath}/Event_log/Event_log.c"
"${ProjDirPath}/Event_log/Events_log_frames.c"
"${ProjDirPath}/Event_log/Events_log.h"
"${ProjDirPath}/FR_Calculate/FR_CALC.h"
"${ProjDirPath}/FR_Calculate/FR_CALC.c"
"${ProjDirPath}/Factory_Setting/manu_dt_yr.c"
"${ProjDirPath}/Factory_Setting/factory_menu.c"
"${ProjDirPath}/Factory_Setting/factory.h"
"${ProjDirPath}/Flowrate_screen/Flowrate_Screen.h"
"${ProjDirPath}/Flowrate_screen/Flowrate_Screen.c"
"${ProjDirPath}/Font_style/Font.h"
"${ProjDirPath}/Font_style/AKAS_LOGO.c"
"${ProjDirPath}/Font_style/9_Arial.c"
"${ProjDirPath}/Font_style/48_Calibri.c"
"${ProjDirPath}/Font_style/43_Calibri.c"
"${ProjDirPath}/Font_style/36_Arial.c"
"${ProjDirPath}/Font_style/35_Arial.c"
"${ProjDirPath}/Font_style/20_Arial.c"
"${ProjDirPath}/Font_style/14_Arial.c"
"${ProjDirPath}/Font_style/12_Arial.c"
"${ProjDirPath}/GPIO/GPIO.h"
"${ProjDirPath}/GPIO/GPIO.c"
"${ProjDirPath}/I2C/I2C.c"
"${ProjDirPath}/I2C/Driver_I2C.h"
"${ProjDirPath}/I2C/Driver_I2C.c"
"${ProjDirPath}/Infused_Calculate/infused_calculate.h"
"${ProjDirPath}/Infused_Calculate/Infused_Calculate.c"
"${ProjDirPath}/Keypad/Keypad.h"
"${ProjDirPath}/Keypad/Keypad.c"
"${ProjDirPath}/Last_Infusion_clear/Last_infusion.c"
"${ProjDirPath}/Linear_Pot_Calibration/Linear_pot.h"
"${ProjDirPath}/Linear_Pot_Calibration/Linear_pot.c"
"${ProjDirPath}/Main_screen/Main_screen_functionality.c"
"${ProjDirPath}/Main_screen/Main_screen.h"
"${ProjDirPath}/Main_screen/Main_frame.c"
"${ProjDirPath}/Menu_Setting/sys_sett_menu.c"
"${ProjDirPath}/Menu_Setting/occl_menu.c"
"${ProjDirPath}/Menu_Setting/Main_Menu.h"
"${ProjDirPath}/Menu_Setting/Main_menu.c"
"${ProjDirPath}/Menu_Setting/kvo_menu.c"
"${ProjDirPath}/Menu_Setting/Device_main_scrn.c"
"${ProjDirPath}/Mode_function/mode_screen.c"
"${ProjDirPath}/Mode_function/modes.h"
"${ProjDirPath}/Motor/Motor.h"
"${ProjDirPath}/Motor/Motor.c"
"${ProjDirPath}/Occlusion/Occlusion.h"
"${ProjDirPath}/Occlusion/Occlusion.c"
"${ProjDirPath}/Occlusion/Driver_HX711.h"
"${ProjDirPath}/Occlusion/Driver_HX711.c"
"${ProjDirPath}/PINT/Driver_PINT.h"
"${ProjDirPath}/PINT/Driver_PINT.c"
"${ProjDirPath}/PLUNGER_ALARM/plunger_alarm.h"
"${ProjDirPath}/PLUNGER_ALARM/plunger_alarm.c"
"${ProjDirPath}/PLUNGER_ALARM/Data_Sample.c"
"${ProjDirPath}/PWM/PWM.h"
"${ProjDirPath}/PWM/Driver_PWM.c"
"${ProjDirPath}/Password/Password_screens.c"
"${ProjDirPath}/Password/Password.h"
"${ProjDirPath}/Password/Password.c"
"${ProjDirPath}/Power_off/Power_off.h"
"${ProjDirPath}/Power_off/Power_off.c"
"${ProjDirPath}/Pressure_Calibration/Pressure_calib.c"
"${ProjDirPath}/RTC/year.c"
"${ProjDirPath}/RTC/RTC.h"
"${ProjDirPath}/RTC/RTC.c"
"${ProjDirPath}/RTC_DRIVER/RTC_driver.h"
"${ProjDirPath}/RTC_DRIVER/rtc_driver.c"
"${ProjDirPath}/SD_Calibration/SD_Calib_frames.c"
"${ProjDirPath}/SD_Calibration/SD_Calib.h"
"${ProjDirPath}/SD_Calibration/SD_Calib.c"
"${ProjDirPath}/Serial_no_setting/serialno_set.c"
"${ProjDirPath}/Shapes/Symbol.h"
"${ProjDirPath}/Shapes/Symbol.c"
"${ProjDirPath}/Shapes/Shapes.h"
"${ProjDirPath}/Shapes/Shapes.c"
"${ProjDirPath}/Shapes/Color.h"
"${ProjDirPath}/Sound/sound.h"
"${ProjDirPath}/Sound/sound.c"
"${ProjDirPath}/Stepper_Motor/STEPPER.h"
"${ProjDirPath}/Stepper_Motor/STEPPER.c"
"${ProjDirPath}/Syringe_Length_Calibration/SYR_length_frame.c"
"${ProjDirPath}/Syringe_Length_Calibration/SYR_length_calib.c"
"${ProjDirPath}/Syringe_Length_Calibration/Syringe_calib_header.h"
"${ProjDirPath}/TFT_String/TFT_String.h"
"${ProjDirPath}/TFT_String/TFT_String.c"
"${ProjDirPath}/Timer/Driver_Timer.h"
"${ProjDirPath}/Timer/Driver_Timer.c"
"${ProjDirPath}/Used_hrs/Used_hrs.c"
"${ProjDirPath}/Used_hrs/Consumed_hrs.h"
"${ProjDirPath}/VTBI/Target_fun.h"
"${ProjDirPath}/VTBI/Target_fun.c"
"${ProjDirPath}/board/pin_mux.h"
"${ProjDirPath}/board/pin_mux.c"
"${ProjDirPath}/board/peripherals.h"
"${ProjDirPath}/board/peripherals.c"
"${ProjDirPath}/board/clock_config.h"
"${ProjDirPath}/board/clock_config.c"
"${ProjDirPath}/board/board.h"
"${ProjDirPath}/board/board.c"
"${ProjDirPath}/device/system_LPC55S16.h"
"${ProjDirPath}/device/system_LPC55S16.c"
"${ProjDirPath}/device/LPC55S16_features.h"
"${ProjDirPath}/device/LPC55S16.h"
"${ProjDirPath}/device/fsl_device_registers.h"
"${ProjDirPath}/drivers/fsl_rtc.h"
"${ProjDirPath}/drivers/fsl_reset.h"
"${ProjDirPath}/drivers/fsl_reset.c"
"${ProjDirPath}/drivers/fsl_power.h"
"${ProjDirPath}/drivers/fsl_power.c"
"${ProjDirPath}/drivers/fsl_inputmux_connections.h"
"${ProjDirPath}/drivers/fsl_inputmux.h"
"${ProjDirPath}/drivers/fsl_inputmux.c"
"${ProjDirPath}/drivers/fsl_common_arm.h"
"${ProjDirPath}/drivers/fsl_common_arm.c"
"${ProjDirPath}/drivers/fsl_common.h"
"${ProjDirPath}/drivers/fsl_common.c"
"${ProjDirPath}/drivers/fsl_clock.h"
"${ProjDirPath}/drivers/fsl_clock.c"
"${ProjDirPath}/source/main.c"
"${ProjDirPath}/source/Linear_Header.h"
"${ProjDirPath}/source/HEADER.h"
"${ProjDirPath}/startup/startup_lpc55s16.c"
)




if(${LIBRARY_TYPE} STREQUAL "REDLIB")
    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE $ENV{ARMGCC_DIR}/redlib/include)
endif()

set(c_include_directories "${ProjDirPath}/Infused_Calculate"
"${ProjDirPath}/board"
"${ProjDirPath}/ADC"
"${ProjDirPath}/Alarm"
"${ProjDirPath}/Battery"
"${ProjDirPath}/Bolus_Concept"
"${ProjDirPath}/Boot_up"
"${ProjDirPath}/Brand"
"${ProjDirPath}/Calibration_Screen"
"${ProjDirPath}/DAC_DRIVER"
"${ProjDirPath}/Dose_rate"
"${ProjDirPath}/Driver_SPI"
"${ProjDirPath}/Driver_ST7789V"
"${ProjDirPath}/Drug_List"
"${ProjDirPath}/Dynamic_Pressure"
"${ProjDirPath}/Event_log"
"${ProjDirPath}/Factory_Setting"
"${ProjDirPath}/Flowrate_screen"
"${ProjDirPath}/Font_style"
"${ProjDirPath}/FR_Calculate"
"${ProjDirPath}/GPIO"
"${ProjDirPath}/I2C"
"${ProjDirPath}/Infused_Calculate"
"${ProjDirPath}/Keypad"
"${ProjDirPath}/Last_Infusion_clear"
"${ProjDirPath}/Linear_Pot_Calibration"
"${ProjDirPath}/Main_screen"
"${ProjDirPath}/Menu_Setting"
"${ProjDirPath}/Mode_Function"
"${ProjDirPath}/Motor"
"${ProjDirPath}/Occlusion"
"${ProjDirPath}/Password"
"${ProjDirPath}/PINT"
"${ProjDirPath}/PLUNGER_ALARM"
"${ProjDirPath}/Power_off"
"${ProjDirPath}/Pressure_Calibration"
"${ProjDirPath}/PWM"
"${ProjDirPath}/RTC"
"${ProjDirPath}/RTC_DRIVER"
"${ProjDirPath}/SD_Calibration"
"${ProjDirPath}/Serial_no_setting"
"${ProjDirPath}/Shapes"
"${ProjDirPath}/Sound"
"${ProjDirPath}/Stepper_Motor"
"${ProjDirPath}/Syringe_Length_Calibration"
"${ProjDirPath}/TFT_String"
"${ProjDirPath}/Timer"
"${ProjDirPath}/Used_hrs"
"${ProjDirPath}/VTBI"
"${ProjDirPath}/source"
"${ProjDirPath}/freertos/freertos-kernel/include"
"${ProjDirPath}/drivers"
"${ProjDirPath}/device"
"${ProjDirPath}/CMSIS"
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:C>:${c_include_directories}>)

set(cpp_include_directories "")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${cpp_include_directories}>)

set(include_files "")


target_precompile_headers(${MCUX_SDK_PROJECT_NAME} PRIVATE ${include_files})

set(link_directories "")


set(link_libraries "")


target_link_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE ${link_directories})
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES} ${link_libraries})
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)





