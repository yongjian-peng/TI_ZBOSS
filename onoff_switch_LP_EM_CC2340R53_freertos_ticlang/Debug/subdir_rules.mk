################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/SoftWare/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -Oz -flto -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang" -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/Debug" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/zigbee/osif/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/zigbee/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/common/cc26xx/flash_interface/" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/uECC" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/emill" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/nacl" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/kernel/freertos" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/posix/ticlang" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/freertos/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/freertos/portable/GCC/ARM_CM0" -DSYNC_WRITE -DZB_TI_F3_ZBOSS -gdwarf-3 -Wno-gnu-folding-constant -Wno-unaligned-access -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1900830575: ../on_off_switch.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.23.1/sysconfig_cli.bat" --script "C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/on_off_switch.syscfg" -o "syscfg" -s "C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_devices_config.c: build-1900830575 ../on_off_switch.syscfg
syscfg/ti_radio_config.c: build-1900830575
syscfg/ti_radio_config.h: build-1900830575
syscfg/ti_drivers_config.c: build-1900830575
syscfg/ti_drivers_config.h: build-1900830575
syscfg/ti_utils_build_linker.cmd.genlibs: build-1900830575
syscfg/ti_utils_build_linker.cmd.genmap: build-1900830575
syscfg/ti_utils_build_compiler.opt: build-1900830575
syscfg/syscfg_c.rov.xs: build-1900830575
syscfg/ti_zigbee_config.h: build-1900830575
syscfg/ti_zigbee_config.c: build-1900830575
syscfg/FreeRTOSConfig.h: build-1900830575
syscfg/ti_freertos_config.c: build-1900830575
syscfg/ti_freertos_portable_config.c: build-1900830575
syscfg: build-1900830575

syscfg/%.o: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/SoftWare/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -Oz -flto -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang" -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/Debug" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/zigbee/osif/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/zigbee/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/common/cc26xx/flash_interface/" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/uECC" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/emill" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/nacl" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/kernel/freertos" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/posix/ticlang" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/freertos/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/freertos/portable/GCC/ARM_CM0" -DSYNC_WRITE -DZB_TI_F3_ZBOSS -gdwarf-3 -Wno-gnu-folding-constant -Wno-unaligned-access -MMD -MP -MF"syscfg/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


