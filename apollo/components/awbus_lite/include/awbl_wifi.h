/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief WI-FI
 *
 * \internal
 * \par modification history
 * - 1.00 15-07-28  axn, first implementation
 * \endinternal
 */
#ifndef __AWBL_WIFI_H
#define __AWBL_WIFI_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "apollo.h"
#include "aw_types.h"
#include "awbus_lite.h"
#include "awbl_nic_manage.h"

/********************************************************************************************************
 * defines
 ********************************************************************************************************/
#define AWBL_WIFI_MAX_SSID_LEN                32
#define AWBL_WIFI_MAX_PASSPHRASE_LEN          64

#define AWBL_WIFI_WEP_ENABLED                 0x00000001
#define AWBL_WIFI_TKIP_ENABLED                0x00000002
#define AWBL_WIFI_AES_ENABLED                 0x00000004
#define AWBL_WIFI_WSEC_SWFLAG                 0x00000008
#define AWBL_WIFI_SHARED_ENABLED              0x00008000
#define AWBL_WIFI_WPS_ENABLED                 0x10000000
#define AWBL_WIFI_WPA_SECURITY                0x00200000
#define AWBL_WIFI_WPA2_SECURITY               0x00400000


/**
 * \brief Enumeration of network types
 */
typedef enum awbl_wifi_bss_type{

    AWBL_BSS_TYPE_INFRASTRUCTURE = 0,      /**< Denotes infrastructure network                  */
    AWBL_BSS_TYPE_ADHOC          = 1,      /**< Denotes an 802.11 ad-hoc IBSS network           */
    AWBL_BSS_TYPE_ANY            = 2,      /**< Denotes either infrastructure or ad-hoc network */
    AWBL_BSS_TYPE_UNKNOWN        = -1      /**< May be returned by scan function if BSS type is unknown.
                                                Do not pass this to the Join function            */
} awbl_wifi_bss_type_t;

/**
 * \brief Enumeration of 802.11 radio bands
 */
typedef enum awbl_802_11_band {

    AWBL_802_11_BAND_5GHZ   = 0,           /**< Denotes 5GHz radio band   */
    AWBL_802_11_BAND_2_4GHZ = 1            /**< Denotes 2.4GHz radio band */

} awbl_802_11_band_t;


/**
 * \brief Structure for storing a Service Set Identifier (i.e. Name of Access Point)
 */
typedef struct awbl_wifi_ssid {

    uint8_t length;                         /**< SSID length */
    uint8_t value[AWBL_WIFI_MAX_SSID_LEN];  /**< SSID name (AP name)  */

} awbl_wifi_ssid_t;

/**
 * \brief Structure for storing a MAC address (Wi-Fi Media Access Control address).
 */
typedef struct awbl_wifi_mac {

    uint8_t octet[6]; /**< Unique 6-byte MAC address */

} awbl_wifi_mac_t;

typedef awbl_wifi_mac_t awbl_mac_t;

typedef enum awbl_wifi_interface {

    AWBL_WIFI_STA_INTERFACE = 0,  /**< STA or Client Interface  */
    AWBL_WIFI_AP_INTERFACE  = 1,  /**< AP  Interface            */
    AWBL_WIFI_P2P_INTERFACE = 2,  /**< P2P Interface            */

} awbl_wifi_interface_t;

/**
 * \brief Enumeration of Wi-Fi security modes
 */
typedef enum awbl_wifi_security {

    AWBL_WIFI_SECURITY_OPEN           = 0,                                                /**< Open security                           */
    AWBL_WIFI_SECURITY_WEP_PSK        = AWBL_WIFI_WEP_ENABLED,                            /**< WEP Security with open authentication   */
    AWBL_WIFI_SECURITY_WEP_SHARED     = ( AWBL_WIFI_WEP_ENABLED   | AWBL_WIFI_SHARED_ENABLED ),  /**< WEP Security with shared authentication */
    AWBL_WIFI_SECURITY_WPA_TKIP_PSK   = ( AWBL_WIFI_WPA_SECURITY  | AWBL_WIFI_TKIP_ENABLED ),    /**< WPA Security with TKIP                  */
    AWBL_WIFI_SECURITY_WPA_AES_PSK    = ( AWBL_WIFI_WPA_SECURITY  | AWBL_WIFI_AES_ENABLED ),     /**< WPA Security with AES                   */
    AWBL_WIFI_SECURITY_WPA2_AES_PSK   = ( AWBL_WIFI_WPA2_SECURITY | AWBL_WIFI_AES_ENABLED ),     /**< WPA2 Security with AES                  */
    AWBL_WIFI_SECURITY_WPA2_TKIP_PSK  = ( AWBL_WIFI_WPA2_SECURITY | AWBL_WIFI_TKIP_ENABLED ),    /**< WPA2 Security with TKIP                 */
    AWBL_WIFI_SECURITY_WPA2_MIXED_PSK = ( AWBL_WIFI_WPA2_SECURITY | AWBL_WIFI_AES_ENABLED | AWBL_WIFI_TKIP_ENABLED ),   /**< WPA2 Security with AES & TKIP */

    AWBL_WIFI_SECURITY_WPS_OPEN       = ( AWBL_WIFI_WPS_ENABLED ),                        /**< WPS with open security                  */
    AWBL_WIFI_SECURITY_WPS_SECURE     = ( AWBL_WIFI_WPS_ENABLED | AWBL_WIFI_AES_ENABLED), /**< WPS with AES security                   */

    AWBL_WIFI_SECURITY_UNKNOWN        = -1,                                               /**< May be returned by scan function if security is unknown.
                                                                                               Do not pass this to the join function! */
    AWBL_WIFI_SECURITY_FORCE_32_BIT   = 0x7fffffff                                        /**< Exists only to force wiced_security_t type to 32 bits */

} awbl_wifi_security_t;

/**
 * \brief Structure for storing AP information
 */
typedef struct awbl_wifi_ap_info {

	awbl_wifi_ssid_t        ssid;             /**< Service Set Identification (i.e. Name of Access Point)                    */
	awbl_wifi_mac_t         bssid;            /**< Basic Service Set Identification (i.e. MAC address of Access Point)       */
	int16_t                 signal_strength;  /**< Receive Signal Strength Indication in dBm. <-90=Very poor, >-30=Excellent */
    uint32_t                max_data_rate;    /**< Maximum data rate in kilobits/s                                           */
    awbl_wifi_bss_type_t    bss_type;         /**< Network type                                                              */
    awbl_wifi_security_t    security;         /**< Security type                                                             */
    uint8_t                 channel;          /**< Radio channel that the AP beacon was received on                          */
    awbl_802_11_band_t      band;             /**< Radio band                                                                */

} awbl_wifi_ap_info_t;

/**
 * \brief Structure for storing STA information
 */
typedef struct awbl_wifi_sta_info {

	awbl_wifi_mac_t         bssid;            /**< Basic Service Set Identification     */
	int                     rssi;             /**< dbm */
	char                    host_name[32];
	uint32_t                ipaddr;

} awbl_wifi_sta_info_t;

/**
 * \brief Structure for storing scan results
 */
typedef struct awbl_wifi_scan_result {

	awbl_wifi_ssid_t        ssid;             /**< Service Set Identification (i.e. Name of Access Point)                    */
	awbl_wifi_mac_t         bssid;            /**< Basic Service Set Identification (i.e. MAC address of Access Point)       */
    int16_t                 signal_strength;  /**< Receive Signal Strength Indication in dBm. <-90=Very poor, >-30=Excellent */
    uint32_t                max_data_rate;    /**< Maximum data rate in kilobits/s                                           */
    awbl_wifi_bss_type_t    bss_type;         /**< Network type                                                              */
    awbl_wifi_security_t    security;         /**< Security type                                                             */
    uint8_t                 channel;          /**< Radio channel that the AP beacon was received on                          */
    awbl_802_11_band_t      band;             /**< Radio band                                                                */
    bool_t                  on_channel;       /**< True if scan result was recorded on the channel advertised in the packet  */
    struct awbl_wifi_scan_result *p_next;     /**< Pointer to the next scan result                                           */

} awbl_wifi_scan_result_t;

typedef aw_err_t (*awbl_wifi_scan_result_handler_t)(/* @out */awbl_wifi_scan_result_t *p_result, bool_t complete);

typedef aw_err_t (*awbl_wifi_scan_handler_t)(awbl_dev_t *p_nic_dev, awbl_wifi_scan_result_handler_t scan_result);

typedef aw_err_t (*awbl_wifi_join_handler_t)(awbl_dev_t          *p_nic_dev,
											 char                *ssid,
											 awbl_wifi_security_t auth_type,
											 char                *key,
											 char                *ip,
											 char                *netmask,
											 char                *gateway);

typedef aw_err_t (*awbl_wifi_leave_handler_t)(awbl_dev_t *p_nic_dev);
typedef aw_err_t (*awbl_wifi_get_ap_info_hander) (awbl_dev_t *p_nic_dev, /* @out */awbl_wifi_ap_info_t *info);


typedef aw_err_t (*awbl_wifi_start_ap_handler_t)(awbl_dev_t          *p_dev,
                                                 char                *ssid,
                                                 awbl_wifi_security_t auth_type,
                                                 char                *key,
                                                 uint8_t              channel,
                                                 char                *ip,
                                                 char                *netmask,
                                                 char                *gw);

typedef aw_err_t (*awbl_wifi_stop_ap_handler_t)(awbl_dev_t *p_nic_dev);


typedef aw_err_t (*awbl_wifi_get_sta_result_handler_t)(/* @out */awbl_wifi_sta_info_t *sta_info, bool_t complete);
typedef aw_err_t (*awbl_wifi_get_sta_handler_t)(awbl_dev_t *p_nic_dev, awbl_wifi_get_sta_result_handler_t result);
typedef aw_err_t (*awbl_wifi_status_hander_t)(awbl_dev_t *p_nic_dev, awbl_nic_type_t nic_type,/* @out */bool_t *up);

/*********************************************************************************************************
 * STA APIs
 *********************************************************************************************************/

/**
 * \brief Scan all enabled channels and get a list of APs found.
 */
aw_err_t awbl_wifi_scan (char                           *p_nic_name,
		                 awbl_wifi_scan_result_handler_t scan_result);

/**
 * \brief Join an AP. DHCP assumed if no IP address provided
 */
aw_err_t awbl_wifi_join (char                *p_nic_name,
		                 char                *ssid,
		                 awbl_wifi_security_t auth_type,
		                 char                *key,
		                 char                *ip,
		                 char                *netmask,
		                 char                *gw);

/**
 * \brief Leave an associated access point
 */
aw_err_t awbl_wifi_leave (char *p_nic_name);

/**
 * \brief Get AP information
 */
aw_err_t awbl_wifi_get_ap_info (char *p_nic_name, /* @out */awbl_wifi_ap_info_t *info);


/*********************************************************************************************************
 * AP APIs
 ********************************************************************************************************/
/**
 * \brief Starts a AP as specified by the provided arguments.
 *        Will use default settings if no IP address provided.
 *        default IP: 192.168.0.1, net mask: 255.255.255.0, gateway: 192.168.0.1
 */
aw_err_t awbl_wifi_start_ap (char                *p_nic_name,
                             char                *ssid,
                             awbl_wifi_security_t auth_type,
                             char                *key,
                             uint8_t              channel,
                             char                *ip,
                             char                *netmask,
                             char                *gw);

/**
 * \brief Stop a running AP
 */
aw_err_t awbl_wifi_stop_ap (char *p_nic_name);

/**
 * \brief Get list of associated clients
 */
aw_err_t awbl_wifi_get_associated_sta_list (char *p_nic_name, awbl_wifi_get_sta_result_handler_t result);

/**
 * \brief Gets the status of the Wi-Fi interface
 */
aw_err_t awbl_wifi_status (char *p_nic_name, /* @out */awbl_nic_type_t *type, /* @out */bool_t *up);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_WIFI_H */

/* @end of file */
