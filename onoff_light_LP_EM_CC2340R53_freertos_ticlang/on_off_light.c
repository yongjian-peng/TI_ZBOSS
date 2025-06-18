/******************************************************************************
 Group: CMCU LPRF
 Target Device: cc23xx

 ******************************************************************************
 
 Copyright (c) 2024-2025, Texas Instruments Incorporated
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 *  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

 *  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 *  Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
 
 
 *****************************************************************************/

/***** Trace related defines *****/
#define ZB_TRACE_FILE_ID 40123

/****** Application defines ******/
#define ZB_OUTPUT_ENDPOINT          5
#define ZB_OUTPUT_MAX_CMD_PAYLOAD_SIZE 2
#define ENDPOINT_C 5

#include <ti/log/Log.h>

#include "ti_zigbee_config.h"
#include "zboss_api.h"
#include "zb_led_button.h"
#include "zboss_api_error.h"

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_fcfg.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)

/* for button handling */
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"

#ifdef ZB_CONFIGURABLE_MEM
#include "zb_mem_config_lprf3.h"
#endif

/****** Application variables declarations ******/
zb_uint16_t g_dst_addr;
zb_uint8_t g_addr_mode;
zb_uint8_t g_endpoint;
zb_bool_t perform_factory_reset = ZB_FALSE;

// 使用自定义开关 开始

// 使用自定义开关 结束

// 使用自定义门锁 开始

/* Identify cluster attributes data */
/* Basic cluster attributes data */
zb_uint8_t g_attr_basic_zcl_version = ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE;
zb_uint8_t g_attr_basic_application_version = ZB_ZCL_BASIC_APPLICATION_VERSION_DEFAULT_VALUE;
zb_uint8_t g_attr_basic_stack_version = ZB_ZCL_BASIC_STACK_VERSION_DEFAULT_VALUE;
zb_uint8_t g_attr_basic_hw_version = ZB_ZCL_BASIC_HW_VERSION_DEFAULT_VALUE;
zb_char_t g_attr_basic_manufacturer_name[] = ZB_ZCL_BASIC_MANUFACTURER_NAME_DEFAULT_VALUE;
zb_char_t g_attr_basic_model_identifier[] = ZB_ZCL_BASIC_MODEL_IDENTIFIER_DEFAULT_VALUE;
zb_char_t g_attr_basic_date_code[] = ZB_ZCL_BASIC_DATE_CODE_DEFAULT_VALUE;
zb_uint8_t g_attr_basic_power_source = ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE;
zb_char_t g_attr_basic_location_description[] = ZB_ZCL_BASIC_LOCATION_DESCRIPTION_DEFAULT_VALUE;
zb_uint8_t g_attr_basic_physical_environment = ZB_ZCL_BASIC_PHYSICAL_ENVIRONMENT_DEFAULT_VALUE;
zb_char_t g_attr_sw_build_id[] = ZB_ZCL_BASIC_SW_BUILD_ID_DEFAULT_VALUE;

ZB_ZCL_DECLARE_BASIC_ATTRIB_LIST_EXT(basic_attr_list, &g_attr_basic_zcl_version, &g_attr_basic_application_version, &g_attr_basic_stack_version, &g_attr_basic_hw_version, &g_attr_basic_manufacturer_name, &g_attr_basic_model_identifier, &g_attr_basic_date_code, &g_attr_basic_power_source, &g_attr_basic_location_description, &g_attr_basic_physical_environment, &g_attr_sw_build_id);


/********************* Declare device **************************/


// 使用自定义门锁 结束

/****** Application function declarations ******/
/* Handler for specific ZCL commands */
zb_uint8_t zcl_specific_cluster_cmd_handler(zb_uint8_t param);
void test_device_interface_cb(zb_uint8_t param);
void button_press_handler(zb_uint8_t param);



/****** Cluster declarations ******/
/* On/Off cluster attributes */
zb_uint8_t g_attr_on_off = ZB_ZCL_ON_OFF_ON_OFF_DEFAULT_VALUE;
#ifdef ZB_ENABLE_ZLL
/* On/Off cluster attributes additions */
zb_bool_t g_attr_global_scene_ctrl  = ZB_TRUE;
zb_uint16_t g_attr_on_time  = 0;
zb_uint16_t g_attr_off_wait_time  = 0;

ZB_ZCL_DECLARE_ON_OFF_ATTRIB_LIST_EXT(on_off_attr_list, &g_attr_on_off,
    &g_attr_global_scene_ctrl, &g_attr_on_time, &g_attr_off_wait_time);
#else
//ZB_ZCL_DECLARE_ON_OFF_ATTRIB_LIST(on_off_attr_list, &g_attr_on_off);
#endif

/* Basic cluster attributes */
zb_uint8_t g_attr_zcl_version  = ZB_ZCL_BASIC_ZCL_VERSION_DEFAULT_VALUE;
zb_uint8_t g_attr_power_source = ZB_ZCL_BASIC_POWER_SOURCE_DEFAULT_VALUE;

//ZB_ZCL_DECLARE_BASIC_ATTRIB_LIST(basic_attr_list, &g_attr_zcl_version, &g_attr_power_source);

/* Identify cluster attributes data */
zb_uint16_t g_attr_identify_identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE;
ZB_ZCL_DECLARE_IDENTIFY_ATTRIB_LIST(identify_attr_list, &g_attr_identify_identify_time);
/********************* Declare device **************************/
ZB_HA_DECLARE_DOOR_LOCK_CONTROLLER_CLUSTER_LIST(door_lock_controller_clusters, basic_attr_list, identify_attr_list);
ZB_HA_DECLARE_DOOR_LOCK_CONTROLLER_EP(door_lock_controller_ep, ENDPOINT_C, door_lock_controller_clusters);
ZB_HA_DECLARE_DOOR_LOCK_CONTROLLER_CTX(device_ctx, door_lock_controller_ep);

/* Identify cluster attributes */
//zb_uint16_t g_attr_identify_time = ZB_ZCL_IDENTIFY_IDENTIFY_TIME_DEFAULT_VALUE;

//ZB_ZCL_DECLARE_IDENTIFY_ATTRIB_LIST(identify_attr_list, &g_attr_identify_time);

/* Groups cluster attributes */
//zb_uint8_t g_attr_name_support = 0;

//ZB_ZCL_DECLARE_GROUPS_ATTRIB_LIST(groups_attr_list, &g_attr_name_support);

#ifdef ZB_ZCL_SUPPORT_CLUSTER_SCENES
/* Scenes cluster attributes */
// zb_uint8_t g_attr_scenes_scene_count = ZB_ZCL_SCENES_SCENE_COUNT_DEFAULT_VALUE;
// zb_uint8_t g_attr_scenes_current_scene = ZB_ZCL_SCENES_CURRENT_SCENE_DEFAULT_VALUE;
// zb_uint16_t g_attr_scenes_current_group = ZB_ZCL_SCENES_CURRENT_GROUP_DEFAULT_VALUE;
// zb_uint8_t g_attr_scenes_scene_valid = ZB_ZCL_SCENES_SCENE_VALID_DEFAULT_VALUE;
// zb_uint16_t g_attr_scenes_name_support = ZB_ZCL_SCENES_NAME_SUPPORT_DEFAULT_VALUE;

// ZB_ZCL_DECLARE_SCENES_ATTRIB_LIST(scenes_attr_list, &g_attr_scenes_scene_count,
    // &g_attr_scenes_current_scene, &g_attr_scenes_current_group,
    // &g_attr_scenes_scene_valid, &g_attr_scenes_name_support);
#else
zb_zcl_attr_t scenes_attr_list[] = { ZB_ZCL_NULL_ID, 0, 0, NULL };
#endif

extern void *logThread(void *arg0);

/* Declare cluster list for the device */
// ZB_HA_DECLARE_ON_OFF_OUTPUT_CLUSTER_LIST(on_off_output_clusters,
//                                          on_off_attr_list,
//                                          basic_attr_list,
//                                          identify_attr_list,
//                                          groups_attr_list,
//                                          scenes_attr_list);

/* Declare endpoint */
//ZB_HA_DECLARE_ON_OFF_OUTPUT_EP(on_off_output_ep, ZB_OUTPUT_ENDPOINT, on_off_output_clusters);

/* Declare application's device context for single-endpoint device */
//ZB_HA_DECLARE_ON_OFF_OUTPUT_CTX(on_off_output_ctx, on_off_output_ep);

// ZB_HA_DECLARE_DOOR_LOCK_CLUSTER_LIST(door_lock_clusters, door_lock_attr_list, basic_attr_list, identify_attr_list, groups_attr_list, scenes_attr_list);
// ZB_HA_DECLARE_DOOR_LOCK_EP(door_lock_ep, ENDPOINT_C, door_lock_clusters);
// ZB_HA_DECLARE_DOOR_LOCK_CTX(device_ctx, door_lock_ep);

/* Register device list */



static zb_bool_t error_ind_handler(zb_uint8_t severity,
                                   zb_ret_t error_code,
                                   void *additional_info);

void off_network_attention(zb_uint8_t param)
{
  ZVUNUSED(param);
  user_print( "off_network_attention");
  zb_osif_led_toggle(1);

  ZB_SCHEDULE_APP_ALARM(off_network_attention, 0, 1 * ZB_TIME_ONE_SECOND);
}

MAIN()
{
  ARGV_UNUSED;

  /* Global ZBOSS initialization */
  ZB_INIT("door_lock");

  logThread(NULL); // 日志初始化

  #ifdef ZB_LONG_ADDR
  // use the address that the customer set in the pre-defined symbols tab
  zb_ieee_addr_t g_long_addr = ZB_LONG_ADDR;
  zb_set_long_address(g_long_addr);
  #else
  /* Set the device's long address to the IEEE address pulling from the FCFG of the device */
  zb_ieee_addr_t ieee_mac_addr;
  ZB_MEMCPY(ieee_mac_addr, fcfg->deviceInfo.macAddr, 8);
  zb_set_long_address(ieee_mac_addr);
  #endif // ZB_LONG_ADDR

#ifdef ZB_COORDINATOR_ROLE
  /* Set up defaults for the commissioning */
  zb_set_network_coordinator_role(DEFAULT_CHANLIST);

  /* Set keepalive mode to mac data poll so sleepy zeds consume less power */
  zb_set_keepalive_mode(MAC_DATA_POLL_KEEPALIVE); 
#ifdef DEFAULT_NWK_KEY
  zb_uint8_t nwk_key[16] = DEFAULT_NWK_KEY;
  zb_secur_setup_nwk_key(nwk_key, 0);
#endif //DEFAULT_NWK_KEY
  zb_nwk_set_max_ed_capacity(MAX_ED_CAPACITY);

#elif defined ZB_ROUTER_ROLE && !defined ZB_COORDINATOR_ROLE
  zb_set_network_router_role(DEFAULT_CHANLIST);
  zb_nwk_set_max_ed_capacity(MAX_ED_CAPACITY);

  /* Set keepalive mode to mac data poll so sleepy zeds consume less power */
  zb_set_keepalive_mode(MAC_DATA_POLL_KEEPALIVE); 

#elif defined ZB_ED_ROLE
  zb_set_network_ed_role(DEFAULT_CHANLIST);

  /* Set end-device configuration parameters */
  zb_set_ed_timeout(ED_TIMEOUT_VALUE);
  zb_set_rx_on_when_idle(ED_RX_ALWAYS_ON);
#if ( ED_RX_ALWAYS_ON == ZB_FALSE )
  zb_set_keepalive_timeout(ZB_MILLISECONDS_TO_BEACON_INTERVAL(ED_POLL_RATE));
#ifdef DISABLE_TURBO_POLL
  // Disable turbo poll feature
  zb_zdo_pim_permit_turbo_poll(ZB_FALSE);
  zb_zdo_pim_set_long_poll_interval(ED_POLL_RATE);
#endif // DISABLE_TURBO_POLL
#endif //ED_RX_ALWAYS_ON
#endif //ZB_ED_ROLE

  zb_set_nvram_erase_at_start(ZB_TRUE);

#ifdef ZB_ENABLE_PTA
  zb_enable_pta(0);
#endif

 /* Register device ZCL context */
  ZB_AF_REGISTER_DEVICE_CTX(&device_ctx); // device_ctx on_off_output_ctx

  /* Register cluster commands handler for a specific endpoint */
  ZB_AF_SET_ENDPOINT_HANDLER(ZB_OUTPUT_ENDPOINT, zcl_specific_cluster_cmd_handler);

  /* Set Device user application callback */
  ZB_ZCL_REGISTER_DEVICE_CB(test_device_interface_cb);

  zb_error_register_app_handler(error_ind_handler);

  

  /* Initiate the stack start without starting the commissioning */
  if (zboss_start_no_autostart() != RET_OK)
  {
    user_print( "zboss_start failed");
  }
  else
  {
    GPIO_setConfig(CONFIG_GPIO_BTN1, GPIO_CFG_IN_PU);
    GPIO_setConfig(CONFIG_GPIO_BTN2, GPIO_CFG_IN_PU);
    // if either button 1 or button 2 gets pressed
    zb_bool_t sideButtonPressed = ((GPIO_read((zb_uint8_t)CONFIG_GPIO_BTN1) == 0U) || (GPIO_read((zb_uint8_t)CONFIG_GPIO_BTN2) == 0U));
    // then perform a factory reset
    if (sideButtonPressed)
    {
      perform_factory_reset = ZB_TRUE;
      user_print( "performing factory reset");
    }

    zb_osif_led_button_init();
    ZB_SCHEDULE_APP_ALARM(off_network_attention, 0, 1 * ZB_TIME_ONE_SECOND);

    /* Call the main loop */
    zboss_main_loop();
  }

  MAIN_RETURN(0);
}


static zb_bool_t error_ind_handler(zb_uint8_t severity,
                                    zb_ret_t error_code,
                                    void *additional_info)
{
  zb_bool_t ret = ZB_FALSE;
  ZVUNUSED(additional_info);
  /* Unused without trace. */
  ZVUNUSED(severity);

  user_print( "error_ind_handler severity %d error_code %d", severity, error_code);

  if (error_code == ERROR_CODE(ERROR_CATEGORY_MACSPLIT, ZB_ERROR_MACSPLIT_RADIO_HANG))
  {
    user_print( "Fatal macsplit error");

    ret = ZB_TRUE;
    /* return TRUE to prevent default error handling by the stack */
  }
  if (error_code == ERROR_CODE(ERROR_CATEGORY_MACSPLIT, ZB_ERROR_MACSPLIT_RADIO_REBOOT))
  {
    user_print( "macsplit radio reboot");

    ret = ZB_TRUE;
  }
  user_print( "error_ind_handler ret %d", ret);
  return ret;
}


void test_device_interface_cb(zb_uint8_t param)
{
  zb_zcl_device_callback_param_t *device_cb_param =
    ZB_BUF_GET_PARAM(param, zb_zcl_device_callback_param_t);

  user_print( "> test_device_interface_cb param %d id 0x%x",
             param, device_cb_param->device_cb_id);

  device_cb_param->status = RET_OK;

  switch (device_cb_param->device_cb_id)
  {
    case ZB_ZCL_SET_ATTR_VALUE_CB_ID:
      if (device_cb_param->cb_param.set_attr_value_param.cluster_id == ZB_ZCL_CLUSTER_ID_ON_OFF &&
          device_cb_param->cb_param.set_attr_value_param.attr_id == ZB_ZCL_ATTR_ON_OFF_ON_OFF_ID)
      {
        if (device_cb_param->cb_param.set_attr_value_param.values.data8)
        {
          user_print( "set ON");
#ifdef ZB_USE_BUTTONS
          zb_osif_led_on(0);
#endif
        }
        else
        {
          user_print( "set OFF");
#ifdef ZB_USE_BUTTONS
          zb_osif_led_off(0);
#endif
        }
      }
      else if (device_cb_param->cb_param.set_attr_value_param.cluster_id == ZB_ZCL_CLUSTER_ID_IDENTIFY &&
               device_cb_param->cb_param.set_attr_value_param.attr_id == ZB_ZCL_ATTR_IDENTIFY_IDENTIFY_TIME_ID)
      {
        user_print( "identify time changed to %d (0x%x)",
                   device_cb_param->cb_param.set_attr_value_param.values.data16, device_cb_param->cb_param.set_attr_value_param.values.data16);
      }
      else
      {
        /* MISRA rule 15.7 requires empty 'else' branch. */
      }
      break;
    case ZB_ZCL_DOOR_LOCK_LOCK_DOOR_CB_ID:
    {
      zb_uint8_t lock_state = ZB_ZCL_ATTR_DOOR_LOCK_LOCK_STATE_LOCKED;
      uart2_printf("Lock the door");
      ZVUNUSED(zb_zcl_set_attr_val(ENDPOINT_C,
                                   ZB_ZCL_CLUSTER_ID_DOOR_LOCK,
                                   ZB_ZCL_CLUSTER_SERVER_ROLE,
                                   ZB_ZCL_ATTR_DOOR_LOCK_LOCK_STATE_ID,
                                   &lock_state,
                                   ZB_FALSE));
    }
    break;
    case ZB_ZCL_DOOR_LOCK_UNLOCK_DOOR_CB_ID:
    {
      zb_uint8_t lock_state = ZB_ZCL_ATTR_DOOR_LOCK_LOCK_STATE_UNLOCKED;
      uart2_printf("Unlock the door");
      ZVUNUSED(zb_zcl_set_attr_val(ENDPOINT_C,
                                   ZB_ZCL_CLUSTER_ID_DOOR_LOCK,
                                   ZB_ZCL_CLUSTER_SERVER_ROLE,
                                   ZB_ZCL_ATTR_DOOR_LOCK_LOCK_STATE_ID,
                                   &lock_state,
                                   ZB_FALSE));
    }
    break;

    default:
      device_cb_param->status = RET_ERROR;
      break;
  }

  user_print( "< test_device_interface_cb %d", device_cb_param->status);
}

static void handle_diag_data_resp(zb_bufid_t buf)
{
  zb_zdo_get_diag_data_resp_params_t *resp_params;

  resp_params = ZB_BUF_GET_PARAM(buf, zb_zdo_get_diag_data_resp_params_t);

  ZVUNUSED(resp_params);

  user_print( "handle_diag_data_resp, status: %d, addr: 0x%x, lqi: %d, rssi: %d",
             resp_params->status, resp_params->short_address,
             resp_params->lqi, resp_params->rssi);

  zb_buf_free(buf);
}

static void send_diag_data_req(zb_uint16_t short_address)
{
  zb_zdo_get_diag_data_req_params_t *req;
  zb_bufid_t buf;

  buf = zb_buf_get_out();
  if (buf != ZB_BUF_INVALID)
  {
    req = ZB_BUF_GET_PARAM(buf, zb_zdo_get_diag_data_req_params_t);
    ZB_BZERO(req, sizeof(*req));

    req->short_address = short_address;
    zb_zdo_get_diag_data_async(buf, handle_diag_data_resp);
  }
  else
  {
    user_print( "Failed to get a buffer");
  }
}

zb_uint8_t zcl_specific_cluster_cmd_handler(zb_uint8_t param)
{
  zb_zcl_parsed_hdr_t cmd_info;

  user_print( "> zcl_specific_cluster_cmd_handler");

  ZB_ZCL_COPY_PARSED_HEADER(param, &cmd_info);

  g_dst_addr = ZB_ZCL_PARSED_HDR_SHORT_DATA(&cmd_info).source.u.short_addr;
  g_endpoint = ZB_ZCL_PARSED_HDR_SHORT_DATA(&cmd_info).src_endpoint;
  g_addr_mode = ZB_APS_ADDR_MODE_16_ENDP_PRESENT;

  ZB_ZCL_DEBUG_DUMP_HEADER(&cmd_info);
  user_print( "payload size: %i", zb_buf_len(param));

  send_diag_data_req(g_dst_addr);

  if (cmd_info.cmd_direction == ZB_ZCL_FRAME_DIRECTION_TO_CLI)
  {
    user_print( "Unsupported \"from server\" command direction");
  }

  user_print( "< zcl_specific_cluster_cmd_handler");
  return ZB_FALSE;
}

void restart_commissioning(zb_uint8_t param)
{
  ZVUNUSED(param);
  bdb_start_top_level_commissioning(ZB_BDB_NETWORK_STEERING);
}

void button_press_handler(zb_uint8_t param)
{
  ZVUNUSED(param);
  user_print( "button is pressed, do nothing");
}

// ------------------ 自定义开关开始 -----------------------------

// ------------------ 自定义开关结束 -----------------------------

/* Callback to handle the stack events */


/* Callback to handle the stack events */
void zboss_signal_handler(zb_uint8_t param)
{
  // zb_zdo_app_signal_type_t sig = zb_get_app_signal(param, NULL);

  zb_zdo_app_signal_hdr_t *sg_p = NULL;
  zb_zdo_app_signal_type_t sig = zb_get_app_signal(param, &sg_p);

  if (ZB_GET_APP_SIGNAL_STATUS(param) == 0)
  {
    user_print( "if sig: %d\r\n", sig);
    switch(sig)
    {
#ifndef ZB_MACSPLIT_HOST
      case ZB_ZDO_SIGNAL_SKIP_STARTUP:
#else
      case ZB_MACSPLIT_DEVICE_BOOT:
#endif /* ZB_MACSPLIT_HOST */

#ifdef TEST_USE_INSTALLCODE
        zb_secur_ic_str_add(g_ed_addr, g_installcode, NULL);
#endif
        zboss_start_continue();
        break;

      case ZB_BDB_SIGNAL_DEVICE_FIRST_START:
      case ZB_BDB_SIGNAL_DEVICE_REBOOT:
      {
        zb_nwk_device_type_t device_type = ZB_NWK_DEVICE_TYPE_NONE;
        device_type = zb_get_device_type();
        ZVUNUSED(device_type);
        user_print( "Device (%d) STARTED OK", device_type);
        if (perform_factory_reset)
        {
          user_print( "Performing a factory reset.");
          zb_bdb_reset_via_local_action(0);
          perform_factory_reset = ZB_FALSE;
        }
        bdb_start_top_level_commissioning(ZB_BDB_NETWORK_STEERING);

#ifdef ZB_USE_BUTTONS
        zb_button_register_handler(0, 0, button_press_handler);
#endif
        break;
      }
      case ZB_COMMON_SIGNAL_CAN_SLEEP:
      {
#ifdef ZB_USE_SLEEP
        //user_print( "Sleeping now");
        zb_sleep_now();
#endif
        break;
      }
      case ZB_BDB_SIGNAL_STEERING:
        user_print( "Successful steering, start f&b target");
        zb_bdb_finding_binding_target(ZB_OUTPUT_ENDPOINT);
        ZB_SCHEDULE_APP_ALARM_CANCEL(off_network_attention, ZB_ALARM_ANY_PARAM);
        zb_osif_led_off(1);
        break;

      default:
        Log_printf(LogModule_Zigbee_App, Log_WARNING, "Unknown signal %d", (zb_uint16_t)sig);
    }
  }
  else
  {
    user_print( "else sig: %d\r\n", sig);
    switch(sig)
    { 
      case ZB_BDB_SIGNAL_DEVICE_FIRST_START:
        Log_printf(LogModule_Zigbee_App, Log_WARNING, "Device can not find any network on start, so try to perform network steering");
        ZB_SCHEDULE_APP_ALARM(restart_commissioning, 0, 10 * ZB_TIME_ONE_SECOND);
        break; /* ZB_BDB_SIGNAL_DEVICE_FIRST_START */

      case ZB_ZDO_SIGNAL_PRODUCTION_CONFIG_READY:
        user_print( "Production config is not present or invalid");
        break;

      case ZB_BDB_SIGNAL_STEERING:
        Log_printf(LogModule_Zigbee_App, Log_WARNING, "Steering failed, retrying again in 10 seconds");
        ZB_SCHEDULE_APP_ALARM(restart_commissioning, 0, 10 * ZB_TIME_ONE_SECOND);
        break; /* ZB_BDB_SIGNAL_STEERING */
       

      default:
        user_print( "Device started FAILED status %d sig %d", ZB_GET_APP_SIGNAL_STATUS(param), sig);
    }
  }

  /* Free the buffer if it is not used */
  if (param)
  {
    zb_buf_free(param);
  }
}
