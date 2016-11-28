/**
 * @file
 * @brief Ethernet interface for idrv.
 *
 * @internal
 * @par History
 * - 15-01-08, axn, add dhcp_en in struct ethernet_if
 * - 13-03-25, orz, First implementation.
 * @endinternal
 */

#ifndef __IDRV_ETHERNET_IF_H /* { */
#define __IDRV_ETHERNET_IF_H

#include "aw_types.h"
#include "lwip/netif.h"
#include "lwip/opt.h"

#if BYTE_ORDER == BIG_ENDIAN
/** Convert to an IP address given by the four byte-parts */
#define TO_IP4_ADDR(a, b, c, d)     (((u32_t)((a) & 0xff) << 24) | \
                                     ((u32_t)((b) & 0xff) << 16) | \
                                     ((u32_t)((c) & 0xff) << 8)  | \
                                      (u32_t)((d) & 0xff))
#else
/**
 * Convert to an IP address given by the four byte-parts.
 * Little-endian version that prevents the use of htonl.
 */
#define TO_IP4_ADDR(a, b, c, d)     (((u32_t)((d) & 0xff) << 24) | \
                                     ((u32_t)((c) & 0xff) << 16) | \
                                     ((u32_t)((b) & 0xff) << 8)  | \
                                      (u32_t)((a) & 0xff))
#endif

/******************************************************************************/
/** \brief drop and relaim the padding word of pbuf */
#if ETH_PAD_SIZE
#define PBUF_HEADER_DROP_PAD(pbuf)      pbuf_header(pbuf, -ETH_PAD_SIZE)
#define PBUF_HEADER_RECLAIM_PAD(pbuf)   pbuf_header(pbuf, ETH_PAD_SIZE)
#else
#define PBUF_HEADER_DROP_PAD(pbuf)      do { } while (0)
#define PBUF_HEADER_RECLAIM_PAD(pbuf)   do { } while (0)
#endif

/******************************************************************************/
struct ethernet_if;

/** @brief Ethernet if ops */
struct ethernet_if_ops {
    /* ethernet link init */
    err_t (*link_init)  (struct ethernet_if *ethif);

    /* Get a link packet(frame) length */
    int   (*pkt_len)   (struct ethernet_if *ethif);

    /* Drop a link packet(frame) */
    void  (*pkt_drop)  (struct ethernet_if *ethif);

    /* Read a link packet to pbuf payload */
	err_t (*pkt_input) (struct ethernet_if *ethif, struct pbuf *p);

    /* Send a pbuf payload to link */
	err_t (*pkt_output)(struct ethernet_if *ethif, struct pbuf *p);
    /*
     * handler for receiving packets. If this handler is not NULL, then
     * the ethernet if core will call this handler instead of pkt_len(),
     * pkt_drop() and pkt_input().
     */
    void  (*pkt_rx_hdl)(struct ethernet_if *ethif);
};

/** @brief Ethernet if structure */
struct ethernet_if {
	struct netif                  netif;    /**< @brief net if instance */
    const struct ethernet_if_ops *ops;      /**< @brief Ethernet if ops */
    uint16_t                      mtu;      /**< @brief MTU of this device */
    uint16_t                      unit;     /**< @brief NVINFO unit */
    const char                   *p_name;   /**< @brief NVINFO name*/
    uint8_t                       dhcp_en;  /**< @brief DHCP enable */
};

/******************************************************************************/
int ethernet_if_init (struct ethernet_if           *ethif,
                      const struct ethernet_if_ops *ops,
                      unsigned int                  mtu,
                      int                           unit,
                      const char                   *p_name);

int ethernet_if_pkt_ready (struct ethernet_if *ethif);

void ethernet_if_set_link_up(struct ethernet_if *ethif);
void ethernet_if_set_link_down(struct ethernet_if *ethif);

/** @brief Ethernet interface */

#endif /* } __IDRV_ETHERNET_IF_H */

/* end of file */
