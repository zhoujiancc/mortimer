/*
 * dvb_frontend.h
 *
 * Copyright (C) 2001 convergence integrated media GmbH
 * Copyright (C) 2004 convergence GmbH
 *
 * Written by Ralph Metzler
 * Overhauled by Holger Waechtler
 * Kernel I2C stuff by Michael Hunold <hunold@convergence.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _DVB_FRONTEND_H_
#define _DVB_FRONTEND_H_

#include <linux/types.h>
#include <linux/sched.h>
#include <linux/ioctl.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/slab.h>

#include <linux/dvb/frontend.h>

#include "dvbdev.h"

/*
 * Maximum number of Delivery systems per frontend. It
 * should be smaller or equal to 32
 */
#define MAX_DELSYS	8

struct dvb_frontend_tune_settings {
	int min_delay_ms;
	int step_size;
	int max_drift;
};

struct dvb_frontend;

struct dvb_tuner_info {
	char name[128];

	u32 frequency_min;
	u32 frequency_max;
	u32 frequency_step;

	u32 bandwidth_min;
	u32 bandwidth_max;
	u32 bandwidth_step;
};

struct analog_parameters {
	unsigned int frequency;
	unsigned int mode;
	unsigned int audmode;
	u64 std;
};

enum dvbfe_modcod {
	DVBFE_MODCOD_DUMMY_PLFRAME	= 0,
	DVBFE_MODCOD_QPSK_1_4,
	DVBFE_MODCOD_QPSK_1_3,
	DVBFE_MODCOD_QPSK_2_5,
	DVBFE_MODCOD_QPSK_1_2,
	DVBFE_MODCOD_QPSK_3_5,
	DVBFE_MODCOD_QPSK_2_3,
	DVBFE_MODCOD_QPSK_3_4,
	DVBFE_MODCOD_QPSK_4_5,
	DVBFE_MODCOD_QPSK_5_6,
	DVBFE_MODCOD_QPSK_8_9,
	DVBFE_MODCOD_QPSK_9_10,
	DVBFE_MODCOD_8PSK_3_5,
	DVBFE_MODCOD_8PSK_2_3,
	DVBFE_MODCOD_8PSK_3_4,
	DVBFE_MODCOD_8PSK_5_6,
	DVBFE_MODCOD_8PSK_8_9,
	DVBFE_MODCOD_8PSK_9_10,
	DVBFE_MODCOD_16APSK_2_3,
	DVBFE_MODCOD_16APSK_3_4,
	DVBFE_MODCOD_16APSK_4_5,
	DVBFE_MODCOD_16APSK_5_6,
	DVBFE_MODCOD_16APSK_8_9,
	DVBFE_MODCOD_16APSK_9_10,
	DVBFE_MODCOD_32APSK_3_4,
	DVBFE_MODCOD_32APSK_4_5,
	DVBFE_MODCOD_32APSK_5_6,
	DVBFE_MODCOD_32APSK_8_9,
	DVBFE_MODCOD_32APSK_9_10,
	DVBFE_MODCOD_RESERVED_1,
	DVBFE_MODCOD_BPSK_1_3,
	DVBFE_MODCOD_BPSK_1_4,
	DVBFE_MODCOD_RESERVED_2
};

enum tuner_param {
	DVBFE_TUNER_FREQUENCY		= (1 <<  0),
	DVBFE_TUNER_TUNERSTEP		= (1 <<  1),
	DVBFE_TUNER_IFFREQ		= (1 <<  2),
	DVBFE_TUNER_BANDWIDTH		= (1 <<  3),
	DVBFE_TUNER_REFCLOCK		= (1 <<  4),
	DVBFE_TUNER_IQSENSE		= (1 <<  5),
	DVBFE_TUNER_DUMMY		= (1 << 31)
};

/*
 * ALGO_HW: (Hardware Algorithm)
 * ----------------------------------------------------------------
 * Devices that support this algorithm do everything in hardware
 * and no software support is needed to handle them.
 * Requesting these devices to LOCK is the only thing required,
 * device is supposed to do everything in the hardware.
 *
 * ALGO_SW: (Software Algorithm)
 * ----------------------------------------------------------------
 * These are dumb devices, that require software to do everything
 *
 * ALGO_CUSTOM: (Customizable Agorithm)
 * ----------------------------------------------------------------
 * Devices having this algorithm can be customized to have specific
 * algorithms in the frontend driver, rather than simply doing a
 * software zig-zag. In this case the zigzag maybe hardware assisted
 * or it maybe completely done in hardware. In all cases, usage of
 * this algorithm, in conjunction with the search and track
 * callbacks, utilizes the driver specific algorithm.
 *
 * ALGO_RECOVERY: (Recovery Algorithm)
 * ----------------------------------------------------------------
 * These devices have AUTO recovery capabilities from LOCK failure
 */
enum dvbfe_algo {
	DVBFE_ALGO_HW			= (1 <<  0),
	DVBFE_ALGO_SW			= (1 <<  1),
	DVBFE_ALGO_CUSTOM		= (1 <<  2),
	DVBFE_ALGO_RECOVERY		= (1 << 31)
};

struct tuner_state {
	u32 frequency;
	u32 tunerstep;
	u32 ifreq;
	u32 bandwidth;
	u32 iqsense;
	u32 refclock;
};

/*
 * search callback possible return status
 *
 * DVBFE_ALGO_SEARCH_SUCCESS
 * The frontend search algorithm completed and returned successfully
 *
 * DVBFE_ALGO_SEARCH_ASLEEP
 * The frontend search algorithm is sleeping
 *
 * DVBFE_ALGO_SEARCH_FAILED
 * The frontend search for a signal failed
 *
 * DVBFE_ALGO_SEARCH_INVALID
 * The frontend search algorith was probably supplied with invalid
 * parameters and the search is an invalid one
 *
 * DVBFE_ALGO_SEARCH_ERROR
 * The frontend search algorithm failed due to some error
 *
 * DVBFE_ALGO_SEARCH_AGAIN
 * The frontend search algorithm was requested to search again
 */
enum dvbfe_search {
	DVBFE_ALGO_SEARCH_SUCCESS	= (1 <<  0),
	DVBFE_ALGO_SEARCH_ASLEEP	= (1 <<  1),
	DVBFE_ALGO_SEARCH_FAILED	= (1 <<  2),
	DVBFE_ALGO_SEARCH_INVALID	= (1 <<  3),
	DVBFE_ALGO_SEARCH_AGAIN		= (1 <<  4),
	DVBFE_ALGO_SEARCH_ERROR		= (1 << 31),
};


/* values for TV_FE_MODE */
enum fe_tv_mode{
    FE_TV_MODE_DTV = 0,
    FE_TV_MODE_ATV = 1,
};

/* Just same as v4l2_tuner_type */
enum fe_tuner_type {
	FE_TUNER_RADIO	     = 1,
	FE_TUNER_ANALOG_TV	     = 2,
	FE_TUNER_DIGITAL_TV	     = 3,
};

struct dvb_tuner_ops {

	struct dvb_tuner_info info;

	int (*release)(struct dvb_frontend *fe);
	int (*init)(struct dvb_frontend *fe);
	int (*sleep)(struct dvb_frontend *fe);

	/** This is for simple PLLs - set all parameters in one go. */
	int (*set_params)(struct dvb_frontend *fe);
	int (*set_analog_params)(struct dvb_frontend *fe, struct analog_parameters *p);

	/** This is support for demods like the mt352 - fills out the supplied buffer with what to write. */
	int (*calc_regs)(struct dvb_frontend *fe, u8 *buf, int buf_len);

	/** This is to allow setting tuner-specific configs */
	int (*set_config)(struct dvb_frontend *fe, void *priv_cfg);

	int (*get_frequency)(struct dvb_frontend *fe, u32 *frequency);
	int (*get_bandwidth)(struct dvb_frontend *fe, u32 *bandwidth);
	int (*get_if_frequency)(struct dvb_frontend *fe, u32 *frequency);

#define TUNER_STATUS_LOCKED 1
#define TUNER_STATUS_STEREO 2
	int (*get_status)(struct dvb_frontend *fe, u32 *status);
	int (*get_rf_strength)(struct dvb_frontend *fe, u16 *strength);
	int (*get_afc)(struct dvb_frontend *fe, s32 *afc);

	/** These are provided separately from set_params in order to facilitate silicon
	 * tuners which require sophisticated tuning loops, controlling each parameter separately. */
	int (*set_frequency)(struct dvb_frontend *fe, u32 frequency);
	int (*set_bandwidth)(struct dvb_frontend *fe, u32 bandwidth);

	/*
	 * These are provided separately from set_params in order to facilitate silicon
	 * tuners which require sophisticated tuning loops, controlling each parameter separately.
	 */
	int (*set_state)(struct dvb_frontend *fe, enum tuner_param param, struct tuner_state *state);
	int (*get_state)(struct dvb_frontend *fe, enum tuner_param param, struct tuner_state *state);

	int (*get_afd)(struct dvb_frontend *fe, s32 *afd); /* auto fine tune offset for ATV */
	int (*set_mft)(struct dvb_frontend *fe, s32 offset); /* Set manual fine tune, offset of 62.5kHz */
	int (*get_tune_type)(struct dvb_frontend *fe, u16 *tune_type); /* Set manual fine tune, offset of 62.5kHz */
};

struct analog_demod_info {
	char *name;
};

struct analog_demod_ops {

	struct analog_demod_info info;

	void (*set_params)(struct dvb_frontend *fe,
			   struct analog_parameters *params);
	int  (*has_signal)(struct dvb_frontend *fe, u16 *signal);
	int  (*get_afc)(struct dvb_frontend *fe, s32 *afc);
	void (*tuner_status)(struct dvb_frontend *fe);
	void (*standby)(struct dvb_frontend *fe);
	void (*release)(struct dvb_frontend *fe);
	int  (*i2c_gate_ctrl)(struct dvb_frontend *fe, int enable);

	/** This is to allow setting tuner-specific configuration */
	int (*set_config)(struct dvb_frontend *fe, void *priv_cfg);
};

struct dtv_frontend_properties;

struct dvb_frontend_ops {

	struct dvb_frontend_info info;

	u8 delsys[MAX_DELSYS];

	void (*release)(struct dvb_frontend* fe);
	void (*release_sec)(struct dvb_frontend* fe);

	int (*init)(struct dvb_frontend* fe);
	int (*sleep)(struct dvb_frontend* fe);

	int (*write)(struct dvb_frontend* fe, const u8 buf[], int len);

	/* if this is set, it overrides the default swzigzag */
	int (*tune)(struct dvb_frontend* fe,
		    bool re_tune,
		    unsigned int mode_flags,
		    unsigned int *delay,
		    fe_status_t *status);
	/* get frontend tuning algorithm from the module */
	enum dvbfe_algo (*get_frontend_algo)(struct dvb_frontend *fe);

	/* these two are only used for the swzigzag code */
	int (*set_frontend)(struct dvb_frontend *fe);
	int (*get_tune_settings)(struct dvb_frontend* fe, struct dvb_frontend_tune_settings* settings);

	int (*get_frontend)(struct dvb_frontend *fe);

	int (*read_status)(struct dvb_frontend* fe, fe_status_t* status);
	int (*read_ber)(struct dvb_frontend* fe, u32* ber);
	int (*read_signal_strength)(struct dvb_frontend* fe, u16* strength);
	int (*read_snr)(struct dvb_frontend* fe, u16* snr);
	int (*read_ucblocks)(struct dvb_frontend* fe, u32* ucblocks);

	int (*diseqc_reset_overload)(struct dvb_frontend* fe);
	int (*diseqc_send_master_cmd)(struct dvb_frontend* fe, struct dvb_diseqc_master_cmd* cmd);
	int (*diseqc_recv_slave_reply)(struct dvb_frontend* fe, struct dvb_diseqc_slave_reply* reply);
	int (*diseqc_send_burst)(struct dvb_frontend* fe, fe_sec_mini_cmd_t minicmd);
	int (*set_tone)(struct dvb_frontend* fe, fe_sec_tone_mode_t tone);
	int (*set_voltage)(struct dvb_frontend* fe, fe_sec_voltage_t voltage);
	int (*enable_high_lnb_voltage)(struct dvb_frontend* fe, long arg);
	int (*dishnetwork_send_legacy_command)(struct dvb_frontend* fe, unsigned long cmd);
	int (*i2c_gate_ctrl)(struct dvb_frontend* fe, int enable);
	int (*ts_bus_ctrl)(struct dvb_frontend* fe, int acquire);
	int (*set_lna)(struct dvb_frontend *);

	int (*get_packet_err)(struct dvb_frontend *fe, int *status);

	/* These callbacks are for devices that implement their own
	 * tuning algorithms, rather than a simple swzigzag
	 */
	enum dvbfe_search (*search)(struct dvb_frontend *fe);

	struct dvb_tuner_ops tuner_ops;
	struct analog_demod_ops analog_ops;

	int (*set_property)(struct dvb_frontend* fe, struct dtv_property* tvp);
	int (*get_property)(struct dvb_frontend* fe, struct dtv_property* tvp);

	int (*send_dbg_cmd)(struct dvb_frontend* fe, struct fe_dbg_cmd* cmd);
	int (*get_lock_time)(struct dvb_frontend* fe, __u32 *ms);
	int (*get_sync_time)(struct dvb_frontend* fe, __u32 *ms);
	int (*get_stream_id_list)(struct dvb_frontend* fe, unsigned int *cnt, unsigned char *data);
	int (*send_positioner_cmd)(struct dvb_frontend* fe, unsigned char cmd, int param);
	int (*send_satcr_cmd)(struct dvb_frontend* fe, unsigned char cmd, bool  SatCR_Enable, unsigned char slotNumber, int slotFrequency);
	int (*set_lnb_power)(struct dvb_frontend* fe, bool bLNBPower);
	int (*get_lnb_power)(struct dvb_frontend* fe, bool *bLNBPower);
	int (*get_ber)(struct dvb_frontend* fe, int *data);
	int (*get_reference_ber)(struct dvb_frontend* fe, int *data);
	int (*get_bit_errorlevel)(struct dvb_frontend* fe, unsigned int *data);
	int (*get_signal_quality_margin)(struct dvb_frontend* fe, int *data);
	int (*get_signal_strength_margin)(struct dvb_frontend* fe, int *data);
	int (*get_cellid)(struct dvb_frontend* fe, int *data);
	int (*get_demod_hierarchy)(struct dvb_frontend* fe, int *data);
	int (*get_signal_quality)(struct dvb_frontend* fe, int *data);
	int (*get_signal_strength)(struct dvb_frontend* fe, int *data);
	int (*get_stream_id)(struct dvb_frontend* fe, int *data);
};

#ifdef __DVB_CORE__
#define MAX_EVENT 8

struct dvb_fe_events {
	struct dvb_frontend_event events[MAX_EVENT];
	int			  eventw;
	int			  eventr;
	int			  overflow;
	wait_queue_head_t	  wait_queue;
	struct mutex		  mtx;
};
#endif


typedef struct  {
	int posParameter;
	unsigned char posCommand;
	bool UsePositioner;
}fe_sat_positioner_t;

struct fe_sat_parameter_t {

//DTV_POSITIONER
	fe_sat_positioner_t position;


//no used::	unsigned int 		orbital_position;		//!< Orbital position [1/10 deg].

	// Satellite settings.
//no used::	bool 			east;				//!< East part of orbit if TRUE.

//DTV_LNB_HI_OSC
   unsigned int 		lnb_hi_osc;			//!< Lnb hi oscillator freq [kHz].

//DTV_LNB_LOW_OSC
	unsigned int 		lnb_lo_osc;			//!< Lnb low oscillator freq [kHz].

//DTV_DISEQC_MODE
	int 				diseqc_mode;		//!< DiseqC mode.

//DTV_TONE
	int 				tone_22_khz;		//!< Tone 22 kHz for LNB. //dtv_tone
//no used::		int 				roll_off;				//!< Roll-off factor used in DVB-S2.

//etc
	bool 				LineCompensation;//!< Compensate for the voltage loss in very long cables.
	unsigned int		bandSwitchFrequency;  //!< Frequency of switching satellite bands from low to high in [MHz].
};

/* JUR add */
typedef struct  {
	// SatCR parameters.
	int slotFrequency;				// [MHz]
	bool  SatCR_Enable;
	unsigned char slotNumber;		// 1 - 8 slot numbers are allowed
} fe_satcr_config_t;


struct dtv_frontend_properties {

	/* Cache State */
	u32			state;

	u32			frequency;
	fe_modulation_t		modulation;

	fe_sec_voltage_t	voltage;
	fe_sec_tone_mode_t	sectone;
	fe_spectral_inversion_t	inversion;
	fe_code_rate_t		fec_inner;
	fe_transmit_mode_t	transmission_mode;
	u32			bandwidth_hz;	/* 0 = AUTO */
	fe_guard_interval_t	guard_interval;
	fe_hierarchy_t		hierarchy;
	u32			symbol_rate;
	fe_code_rate_t		code_rate_HP;
	fe_code_rate_t		code_rate_LP;

	fe_pilot_t		pilot;
	fe_rolloff_t		rolloff;

	fe_delivery_system_t	delivery_system;

	enum fe_interleaving	interleaving;

	/* ISDB-T specifics */
	u8			isdbt_partial_reception;
	u8			isdbt_sb_mode;
	u8			isdbt_sb_subchannel;
	u32			isdbt_sb_segment_idx;
	u32			isdbt_sb_segment_count;
	u8			isdbt_layer_enabled;
	struct {
	    u8			segment_count;
	    fe_code_rate_t	fec;
	    fe_modulation_t	modulation;
	    u8			interleaving;
	} layer[3];

	/* Multistream specifics */
	u32			stream_id;

	/* ATSC-MH specifics */
	u8			atscmh_fic_ver;
	u8			atscmh_parade_id;
	u8			atscmh_nog;
	u8			atscmh_tnog;
	u8			atscmh_sgn;
	u8			atscmh_prc;

	u8			atscmh_rs_frame_mode;
	u8			atscmh_rs_frame_ensemble;
	u8			atscmh_rs_code_mode_pri;
	u8			atscmh_rs_code_mode_sec;
	u8			atscmh_sccc_block_mode;
	u8			atscmh_sccc_code_mode_a;
	u8			atscmh_sccc_code_mode_b;
	u8			atscmh_sccc_code_mode_c;
	u8			atscmh_sccc_code_mode_d;

	u32			lna;

	/* statistics data */
	struct dtv_fe_stats	strength;
	struct dtv_fe_stats	cnr;
	struct dtv_fe_stats	pre_bit_error;
	struct dtv_fe_stats	pre_bit_count;
	struct dtv_fe_stats	post_bit_error;
	struct dtv_fe_stats	post_bit_count;
	struct dtv_fe_stats	block_error;
	struct dtv_fe_stats	block_count;

	int tv_mode;
	struct analog_parameters fe_atv_prop;
	u8			scan_mode;
	struct fe_sat_parameter_t fe_sat_prop;
	fe_satcr_config_t fe_satcr_config;
};

struct dvb_frontend {
	struct dvb_frontend_ops ops;
	struct dvb_adapter *dvb;
	void *demodulator_priv;
	void *tuner_priv;
	void *frontend_priv;
	void *sec_priv;
	void *analog_demod_priv;

	void *config_data;
	int  freq_prev;
	int  dtv_lock_status_prev;
	int  mft_prev;
	struct dtv_frontend_properties dtv_property_cache;
#define DVB_FRONTEND_COMPONENT_TUNER 0
#define DVB_FRONTEND_COMPONENT_DEMOD 1
	int (*callback)(void *adapter_priv, int component, int cmd, int arg);
	int id;
};

extern int dvb_register_frontend(struct dvb_adapter *dvb,
				 struct dvb_frontend *fe);

extern int dvb_unregister_frontend(struct dvb_frontend *fe);

extern void dvb_frontend_detach(struct dvb_frontend *fe);

extern void dvb_frontend_reinitialise(struct dvb_frontend *fe);
extern int dvb_frontend_suspend(struct dvb_frontend *fe);
extern int dvb_frontend_resume(struct dvb_frontend *fe);

extern void dvb_frontend_sleep_until(struct timeval *waketime, u32 add_usec);
extern s32 timeval_usec_diff(struct timeval lasttime, struct timeval curtime);

#endif
