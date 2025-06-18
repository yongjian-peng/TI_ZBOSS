################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
osif/%.o: ../osif/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/SoftWare/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -Oz -flto -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang" -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/Debug" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/zigbee/osif/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/zigbee/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/common/cc26xx/flash_interface/" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/uECC" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/emill" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/zigbee/zboss_r23/thirdparty/nacl" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/kernel/freertos" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/ti/posix/ticlang" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/freertos/include" -I"C:/ti/simplelink_lowpower_f3_sdk_9_10_00_83/source/third_party/freertos/portable/GCC/ARM_CM0" -DSYNC_WRITE -DZB_TI_F3_ZBOSS -gdwarf-3 -Wno-gnu-folding-constant -Wno-unaligned-access -MMD -MP -MF"osif/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/xwb/workspace_ccstheia/onoff_switch_LP_EM_CC2340R53_freertos_ticlang/Debug/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


