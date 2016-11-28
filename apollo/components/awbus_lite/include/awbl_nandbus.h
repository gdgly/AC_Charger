/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief NandBus head file
 *
 * define NandBus data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 14-12-16  deo, first implementation
 * \endinternal
 */
#ifndef __AWBL_NANDBUS_H
#define __AWBL_NANDBUS_H



#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_list.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "awbus_lite.h"
#include "string.h"


#define AWBL_NAND_CHIP_DECL(p_dev, p_awdev) \
			struct awbl_nand_chip *p_dev = \
				(struct awbl_nand_chip *)AW_CONTAINER_OF(	\
									p_awdev, \
									struct awbl_nand_chip, \
									super)

#define AWBL_NAND_CONTROLLER_DECL(p_dev, p_awdev) \
			struct awbl_nand_controller *p_dev = \
				(struct awbl_nand_controller *)AW_CONTAINER_OF( \
					AW_CONTAINER_OF(p_awdev, struct awbl_busctlr, super), \
					struct awbl_nand_controller, \
					awbus)

#define AWBL_NAND_CHIP_INFO_DECL(p_info, p_awdev) \
			struct awbl_nand_chip_info *p_info = \
				(struct awbl_nand_chip_info *)AWBL_DEVINFO_GET(p_awdev)

#define AWBL_NAND_CONTROLLER_INFO_DECL(p_info, p_awdev) \
			struct awbl_nand_controller_info *p_info = \
				(struct awbl_nand_controller_info *)AWBL_DEVINFO_GET(p_awdev)

#define AWBL_NAND_CONTROLLER_DRV_DECL(p_drv, p_awdrv) \
			struct awbl_nand_controller_drvinfo *p_drv = \
				(struct awbl_nand_controller_drvinfo *)AW_CONTAINER_OF( \
						p_awdrv, \
						struct awbl_nand_controller_drvinfo, \
						awdrv)

struct awbl_nand_ecc_req {
	/* request. */
	uint8_t	req;
#define AWBL_NAND_ECC_CALCULATE	1
#define AWBL_NAND_ECC_CORRECT	2

	/* ECC strength. */
	uint8_t	strength;

	/* memory for store ECC data,
	 * when read data, this buffer
	 * will be store by up layer
	 * for controller to correct,
	 * and when write data, it will
	 * be store by controller. */
	void	*buf;

	/* return the correct result.  */
	int		result;
#define AWBL_NAND_ECC_NO_ERR			0x00
#define AWBL_NAND_ECC_ERR_CORRECTED		0x01
#define AWBL_NAND_ECC_ERR_UNCORRECTED	0x02

};

/* operation to the controller. */
struct awbl_nand_opt {
	uint8_t						type;
#define NAND_CMD 		0x01
#define NAND_ADDR 		0x02
#define NAND_RD_DATA  	0x03
#define NAND_WR_DATA  	0x04
	uint8_t						lock_ce;
	const void					*ptr;
	uint32_t					len;
	struct awbl_nand_ecc_req	*ecc_req;
};

/* timing of the flash chip to the controller. */
struct awbl_nand_timing {
	/* ns for all */
	uint8_t		tcs;		/* CE setup */
	uint8_t		tch;		/* CE hold */
	uint8_t		tcls;		/* CLE setup */
	uint8_t		tclh;		/* CLE hold */
	uint8_t		tals;		/* ALE setup */
	uint8_t		talh;		/* ALE hold */
	uint8_t		tds;		/* data setup */
	uint8_t		tdh;		/* data hold */
	uint8_t		trp;		/* RE pulse width */
	uint8_t		trea;		/* RE access time */
	uint8_t		tcea;		/* CE access time */
	uint8_t		tchz;		/* CE high to output Hi-Z */
	uint8_t		trc;		/* read cycle time */
	uint8_t		trhz;		/* RE high to output Hi-Z */
	uint8_t		tclr;		/* CLE to RE delay */
	uint8_t		twp;		/* WE pulse width */
	uint8_t		twc;		/* WE high hold time */
};

/* flash chip. */
struct awbl_nand_chip {
	struct awbl_dev				awdev;
	bool_t						hw_ecc;
};

/* controller. */
struct awbl_nand_controller {
	struct awbl_busctlr		awbus;
	aw_spinlock_isr_t 		dev_lock;
	AW_MUTEX_DECL(dev_mux);
	bool_t					lock;
	uint8_t					ecc_support;
#define AWBL_NAND_ECC_NONE		0x00
#define AWBL_NAND_ECC_1BITS		0x01
#define AWBL_NAND_ECC_4BITS		0x08
#define AWBL_NAND_ECC_8BITS		0x80
};

/* flash chip driver information. */
struct awbl_nand_chip_drvinfo {
	struct awbl_drvinfo awdrv;
};

/* controller driver information. */
struct awbl_nand_controller_drvinfo {
	struct awbl_drvinfo awdrv;

	/* select the flash chip. */
    void (*select) (struct awbl_nand_controller	*p_controller,
    				struct awbl_nand_chip		*p_chip);

    /* operation. */
    aw_err_t (*opt) (	struct awbl_nand_controller	*p_controller,
    					struct awbl_nand_opt		*p_opt);

    /* check the flash chip ready status. */
    bool_t (*ready) (	struct awbl_nand_controller	*p_controller,
    					struct awbl_nand_chip		*p_chip);

    /* reset the controller. */
    void (*reset) (struct awbl_nand_controller *p_controller);

    int	(*get_ecc_len) (struct awbl_nand_controller	*p_controller,
    					int							data_size,
    					uint8_t						ecc_support);
};

/* flash chip configuration information. */
struct awbl_nand_chip_info {
	/* ID for the controller to select flash chip. */
	void					*id;
	/* timing information of the flash for the controller. */
	struct awbl_nand_timing	tim;
	/** \brief maximum ECC check bits the chip can support */
    uint8_t					ecc_strength;
};

/* controller configuration information. */
struct awbl_nand_controller_info {
	/* bus ID. */
	uint8_t     		bus_index;
};

/**
 * \brief NandBus initialize.
 */
void awbl_nandbus_init (void);

/**
 * \brief create a controller.
 */
aw_err_t awbl_nand_controller_create (
		struct awbl_nand_controller *p_controller,
		uint8_t						ecc_support);

/**
 * \brief lock controller.
 */
aw_err_t awbl_nand_controller_lock (struct awbl_nand_controller *p_controller);

/**
 * \brief unlock controller.
 */
aw_err_t awbl_nand_controller_unlock (struct awbl_nand_controller *p_controller);

/**
 * \brief reset controller.
 */
aw_err_t awbl_nand_controller_reset (struct awbl_nand_controller *p_controller);

/**
 * \brief select flash chip.
 */
aw_err_t awbl_nand_select (struct awbl_nand_chip *p_chip);

/**
 * \brief do a operation.
 */
aw_err_t awbl_nand_opt (struct awbl_nand_chip	*p_chip,
						struct awbl_nand_opt	*p_opt);

/**
 * \brief check the flash ready status.
 */
bool_t awbl_nand_is_ready (struct awbl_nand_chip *p_chip);

int awbl_nand_get_max_ecc_len (	struct awbl_nand_chip	*p_chip,
								int						data_len);

int awbl_nandbus_ecc_make (	const void	*data,
							int			data_len,
							void		*ecc);

int awbl_nandbus_ecc_correct (	void		*data,
								int			data_len,
								void		*read_ecc,
								const void	*test_ecc);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_NANDBUS_H */
