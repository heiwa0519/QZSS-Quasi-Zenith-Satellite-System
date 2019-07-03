#ifndef GPP_CSSR_H_
#define GPP_CSSR_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32   // fuer Linux NICHT packen !!!, wie vorgehen bei WIN64 ???  NM 2016-02-23
#pragma pack(push,1)
#endif

#include "compiler.h" //GPP types
#include<stdio.h>

#define GPP_CSSR_MAX_SYS 16
#define	GPP_CSSR_MAX_COEFF 4

#define GPP_CSSR_MAX_SAT 0
#define GPP_CSSR_MAX_CODE 0
#define GPP_CSSR_MAX_PHASE 0
#define GPP_CSSR_MAX_GRID 0


/******************************************
		CSSR ERROR Codes
******************************************/
#define GPP_CSSR_ERROR_BASE 						-54000
#define GPP_CSSR_ERR_NOT_YET_IMPLEMENTED			(GPP_CSSR_ERROR_BASE-1)		/* -54001 */
#define GPP_CSSR_ERR_NOT_ENOUGH_MEMORY				(GPP_CSSR_ERROR_BASE-2)		/* -54002 */
#define GPP_CSSR_ERR_INVALID_MASK					(GPP_CSSR_ERROR_BASE-3)		/* -54003 */
#define GPP_CSSR_ERR_INVALID_ORB					(GPP_CSSR_ERROR_BASE-4)		/* -54004 */
#define GPP_CSSR_ERR_INVALID_CLK					(GPP_CSSR_ERROR_BASE-5)		/* -54005 */
#define GPP_CSSR_ERR_INVALID_SAT_CODE_BIAS			(GPP_CSSR_ERROR_BASE-6)		/* -54006 */
#define GPP_CSSR_ERR_INVALID_SAT_PHASE_BIAS		   	(GPP_CSSR_ERROR_BASE-7)		/* -54007 */
#define GPP_CSSR_ERR_INVALID_SAT_BIAS				(GPP_CSSR_ERROR_BASE-8)		/* -54008 */
#define GPP_CSSR_ERR_INVALID_URA					(GPP_CSSR_ERROR_BASE-9)		/* -54009 */
#define GPP_CSSR_ERR_INVALID_STEC					(GPP_CSSR_ERROR_BASE-10)	/* -54010 */
#define GPP_CSSR_ERR_INVALID_GRID					(GPP_CSSR_ERROR_BASE-11)	/* -54011 */
#define GPP_CSSR_ERR_INVALID_SERVICE_INFO			(GPP_CSSR_ERROR_BASE-12)	/* -54012 */
#define GPP_CSSR_ERR_INVALID_COMBINED				(GPP_CSSR_ERROR_BASE-13)	/* -54012 */

typedef struct	GPP_CSSR_L6_MESSAGE_TYPE_ID
{
	GPPUINT1 vendor_id;
	GPPUINT1 msg_gen_facility_id;
	GPPUINT1 reserved;
	GPPUINT1 sub_frame_indicator;
}GPP_CSSR_L6_MESSAGE_TYPE_ID, *pGPP_CSSR_L6_MESSAGE_TYPE_ID;

typedef struct	GPP_CSSR_HEADER
{
	GPPUINT4 preamble;
	GPPUINT1 prn;
	pGPP_CSSR_L6_MESSAGE_TYPE_ID msg_type_id;
	GPPUINT1 alert_flag;
}GPP_CSSR_HEADER, *pGPP_CSSR_HEADER;

typedef struct GPP_CSSR_MASK_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gps_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		no_of_gnss;
}GPP_CSSR_MASK_HEADER, *pGPP_CSSR_MASK_HEADER;

typedef struct GPP_CSSR_MASK_MESSAGE
{
	GPPUINT1		gnss_id;
	GPPUINT8		sat_mask;
	GPPUINT2	    sig_mask;
	GPPUINT1		cell_mask_flag;
	//GPPUINT		cell_mask;
}GPP_CSSR_MASK_MESSAGE, *pGPP_CSSR_MASK_MESSAGE;

typedef struct GPP_CSSR_MASK
{
	pGPP_CSSR_MASK_HEADER		mask_header;
	pGPP_CSSR_MASK_MESSAGE		*mask_message; //[sys]
}GPP_CSSR_MASK, *pGPP_CSSR_MASK;

typedef struct GPP_CSSR_ORB_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT2		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}GPP_CSSR_ORB_HEADER, *pGPP_CSSR_ORB_HEADER;

typedef struct GPP_CSSR_ORB_MESSAGE
{
	GPPUINT2	gnss_iode;
	GPPDOUBLE	delta_radian;
	GPPDOUBLE	delta_along_track;
	GPPDOUBLE	delta_cross_track;
}GPP_CSSR_ORB_MESSAGE, *pGPP_CSSR_ORB_MESSAGE;

typedef struct GPP_CSSR_ORB_CORRECTION
{
	pGPP_CSSR_ORB_HEADER		orb_header;
	pGPP_CSSR_ORB_MESSAGE		**orb_message; //[sys][sat]
}GPP_CSSR_ORB_CORRECTION, *pGPP_CSSR_ORB_CORRECTION;

typedef struct GPP_CSSR_CLK_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT2		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}GPP_CSSR_CLK_HEADER, *pGPP_CSSR_CLK_HEADER;

typedef struct GPP_CSSR_CLK_MESSAGE
{
	GPPDOUBLE		delta_clock_c0;
}GPP_CSSR_CLK_MESSAGE, *pGPP_CSSR_CLK_MESSAGE;

typedef struct GPP_CSSR_CLK_CORRECTION
{
	pGPP_CSSR_CLK_HEADER		clk_header;
	pGPP_CSSR_CLK_MESSAGE	    **clk_message; //[sys][sat]
}GPP_CSSR_CLK_CORRECTION, *pGPP_CSSR_CLK_CORRECTION;

typedef struct GPP_CSSR_CB_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}GPP_CSSR_CB_HEADER, *pGPP_CSSR_CB_HEADER;

typedef struct GPP_CSSR_CB_MESSAGE
{
	GPPDOUBLE		cb;
}GPP_CSSR_CB_MESSAGE, *pGPP_CSSR_CB_MESSAGE;

typedef struct GPP_CSSR_CB
{
	pGPP_CSSR_CB_HEADER		cb_header;
	pGPP_CSSR_CB_MESSAGE   ***cb_message; //[sys][sat][code]
}GPP_CSSR_CB, *pGPP_CSSR_CB;

typedef struct GPP_CSSR_PB_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}GPP_CSSR_PB_HEADER, *pGPP_CSSR_PB_HEADER;

typedef struct GPP_CSSR_PB_MESSAGE
{
	GPPDOUBLE		pb;
	GPPUINT1		phase_discontinuity_indicator;
}GPP_CSSR_PB_MESSAGE, *pGPP_CSSR_PB_MESSAGE;

typedef struct GPP_CSSR_PB
{
	pGPP_CSSR_PB_HEADER		pb_header;
	pGPP_CSSR_PB_MESSAGE   ***pb_message; //[sys][sat][phase]
}GPP_CSSR_PB, *pGPP_CSSR_PB;

typedef struct GPP_CSSR_BIAS_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1		cb_existing_flag;
	GPPUINT1		pb_existing_flag;
	GPPUINT1		network_bias_correction;
	GPPUINT1		compact_network_id;
	//GPPUINT			network_sv_mask;
}GPP_CSSR_BIAS_HEADER, *pGPP_CSSR_BIAS_HEADER;

typedef struct GPP_CSSR_BIAS_MESSAGE
{
	pGPP_CSSR_CB_MESSAGE	*code_bias;
	pGPP_CSSR_PB_MESSAGE    *phase_bias;
}GPP_CSSR_BIAS_MESSAGE, *pGPP_CSSR_BIAS_MESSAGE;

typedef struct GPP_CSSR_BIAS
{
	pGPP_CSSR_BIAS_HEADER		bias_header;
	pGPP_CSSR_BIAS_MESSAGE   **bias_message; //[sys][sat][code/phase]
}GPP_CSSR_BIAS, *pGPP_CSSR_BIAS;

typedef struct GPP_CSSR_URA_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
}GPP_CSSR_URA_HEADER, *pGPP_CSSR_URA_HEADER;

typedef struct GPP_CSSR_URA_MESSAGE
{
	GPPUINT1		ssr_ura;
}GPP_CSSR_URA_MESSAGE, *pGPP_CSSR_URA_MESSAGE;


typedef struct GPP_CSSR_URA
{
	pGPP_CSSR_URA_HEADER		ura_header;
	pGPP_CSSR_URA_MESSAGE   **ura_message; //[sys][sat]
}GPP_CSSR_URA, *pGPP_CSSR_URA;

typedef struct GPP_CSSR_STEC_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1        correction_type;
	GPPUINT1        network_id;
	//GPP             sv_mask;
}GPP_CSSR_STEC_HEADER, *pGPP_CSSR_STEC_HEADER;

typedef struct GPP_CSSR_STEC_MESSAGE
{
	GPPUINT1 quality_indicator;
	GPPDOUBLE poly_coeff[GPP_CSSR_MAX_COEFF];
}GPP_CSSR_STEC_MESSAGE, *pGPP_CSSR_STEC_MESSAGE;

typedef struct GPP_CSSR_STEC_CORRECTION
{
	pGPP_CSSR_STEC_HEADER		stec_header;
	pGPP_CSSR_STEC_MESSAGE    **stec_message; //[sys][sat]
}GPP_CSSR_STEC_CORRECTION, *pGPP_CSSR_STEC_CORRECTION;

typedef struct GPP_CSSR_GRID_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1        tropo_delay_correction_type;
	GPPUINT1        resisual_correction_range;
	GPPUINT1        network_id;
	//GPP             sv_mask;
	GPPUINT1        tropo_delay_quality_indicator;
	GPPUINT1        no_of_grids;
}GPP_CSSR_GRID_HEADER, *pGPP_CSSR_GRID_HEADER;

typedef struct GPP_CSSR_GRID_RESDIUAL_CORRECTION
{
	GPPDOUBLE residual_correction;
}GPP_CSSR_GRID_RESDIUAL_CORRECTION, *pGPP_CSSR_GRID_RESDIUAL_CORRECTION;

typedef struct GPP_CSSR_GRID_MESSAGE
{
	GPPDOUBLE tropo_hsvd;
	GPPDOUBLE tropo_wvd;
	pGPP_CSSR_GRID_RESDIUAL_CORRECTION  *residual;//[sat]
}GPP_CSSR_GRID_MESSAGE, *pGPP_CSSR_GRID_MESSAGE;

typedef struct GPP_CSSR_GRIDDED_CORRECTION
{
	pGPP_CSSR_GRID_HEADER		grid_header;
	pGPP_CSSR_GRID_MESSAGE    **grid_message; //[sys][grid]
}GPP_CSSR_GRIDDED_CORRECTION, *pGPP_CSSR_GRIDDED_CORRECTION;

typedef struct GPP_CSSR_CLAS_SERVICE_INFO
{
	//to be done
	int nothing;
}GPP_CSSR_CLAS_SERVICE_INFO, *pGPP_CSSR_CLAS_SERVICE_INFO;

typedef struct GPP_CSSR_COMBINE_CORRECTION_HEADER
{
	GPPUINT2		msg_number;
	GPPUINT1		msg_sub_type_id;
	GPPUINT4		gns_hourly_epoch_time;
	GPPUINT1		update_interval;
	GPPUINT1		multiple_msg_indicator;
	GPPUINT1		iod_ssr;
	GPPUINT1        orb_existing_flag;
	GPPUINT1        clk_existing_flag;
	GPPUINT1        network_correction;
	GPPUINT1        network_id;
	//GPP             sv_mask;
}GPP_CSSR_COMBINE_CORRECTION_HEADER, *pGPP_CSSR_COMBINE_CORRECTION_HEADER;

typedef struct GPP_CSSR_COMBINE_CORRECTION_MESSAGE
{
	GPPUINT2 gnss_iode;
	GPPDOUBLE delta_radial;
	GPPDOUBLE delta_along_track;
	GPPDOUBLE delta_cross_track;
	GPPDOUBLE delta_clock_C0;
}GPP_CSSR_COMBINE_CORRECTION_MESSAGE, *pGPP_CSSR_COMBINE_CORRECTION_MESSAGE;

typedef struct GPP_CSSR_GNSS_COMBINE_CORRECTION
{
	pGPP_CSSR_COMBINE_CORRECTION_HEADER		combine_header;
	pGPP_CSSR_COMBINE_CORRECTION_MESSAGE    **combine_message; //[sys][sat]
}GPP_CSSR_GNSS_COMBINE_CORRECTION, *pGPP_CSSR_GNSS_COMBINE_CORRECTION;

typedef struct	GPP_CSSR_DATA_PART
{
	pGPP_CSSR_MASK mask;
	pGPP_CSSR_ORB_CORRECTION orb;
	pGPP_CSSR_CLK_CORRECTION clk;
	pGPP_CSSR_CB    cb;
	pGPP_CSSR_PB    pb;
	pGPP_CSSR_BIAS	bias;
	pGPP_CSSR_URA   ura;
	pGPP_CSSR_STEC_CORRECTION stec;
	pGPP_CSSR_GRIDDED_CORRECTION grid;
	pGPP_CSSR_CLAS_SERVICE_INFO service_info;
	pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine;
}GPP_CSSR_DATA_PART, *pGPP_CSSR_DATA_PART;

typedef struct	GPP_CSSR
{
	pGPP_CSSR_HEADER header;
	pGPP_CSSR_DATA_PART data_part;
}GPP_CSSR, *pGPP_CSSR;


GPPLONG gpp_cssr_cssr2buffer(const pGPP_CSSR cssr,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPLONG gpp_cssr_buffer2csrr(pGPP_CSSR ocb, const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);


GPPULONG gpp_cssr_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_l6_msg_type_id2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_data2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_mask2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_mask_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_mask_message2buffer(const pGPP_CSSR cssr,GPPUINT1 sys, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_orb2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_orb_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_orb_message2buffer(const pGPP_CSSR cssr,GPPUINT1 sys,GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_clk2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_clk_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);
GPPULONG gpp_cssr_clk_message2buffer(const pGPP_CSSR cssr, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos);

/*************************************************************************************************************
					PROTOTYPES FOR MEMORY ALLOCATION AND FREE FUNCTIONS
*************************************************************************************************************/

GPPLONG gpp_cssr_mask_add_header(pGPP_CSSR_MASK mask);
GPPLONG gpp_cssr_mask_add_mask_message(pGPP_CSSR_MASK mask);

GPPLONG gpp_cssr_orb_add_header(pGPP_CSSR_ORB_CORRECTION orb);
GPPLONG gpp_cssr_orb_add_mask_message(pGPP_CSSR_ORB_CORRECTION orb);

GPPLONG gpp_cssr_clk_add_header(pGPP_CSSR_CLK_CORRECTION clk);
GPPLONG gpp_cssr_clk_add_mask_message(pGPP_CSSR_CLK_CORRECTION clk);

GPPLONG cssr_cb_add_header(pGPP_CSSR_CB cb);
GPPLONG gpp_cssr_cb_add_mask_message(pGPP_CSSR_CB cb);

GPPLONG cssr_pb_add_header(pGPP_CSSR_PB pb);
GPPLONG gpp_cssr_pb_add_mask_message(pGPP_CSSR_PB pb);

GPPLONG gpp_cssr_bias_add_header(pGPP_CSSR_BIAS	bias);
GPPLONG gpp_cssr_bias_add_mask_message(pGPP_CSSR_BIAS bias);

GPPLONG gpp_cssr_ura_add_header(pGPP_CSSR_URA ura);
GPPLONG gpp_cssr_ura_add_mask_message(pGPP_CSSR_URA ura);

GPPLONG gpp_cssr_stec_correction_add_header(pGPP_CSSR_STEC_CORRECTION stec);
GPPLONG gpp_cssr_stec_add_mask_message(pGPP_CSSR_STEC_CORRECTION stec);

GPPLONG gpp_cssr_grid_correction_add_header(pGPP_CSSR_GRIDDED_CORRECTION grid);
GPPLONG gpp_cssr_grid_add_mask_message(pGPP_CSSR_GRIDDED_CORRECTION grid);

GPPLONG gpp_cssr_gnss_combine_correction_add_header(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine);
GPPLONG gpp_cssr_gnss_combine_correction_add_mask_message(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine);


GPPLONG gpp_cssr_mask_free_header(pGPP_CSSR_MASK mask);
GPPLONG gpp_cssr_mask_free_spec_part(pGPP_CSSR_MASK mask);

GPPLONG gpp_cssr_orb_free_header(pGPP_CSSR_ORB_CORRECTION orb);
GPPLONG gpp_cssr_orb_free_mask_message(pGPP_CSSR_ORB_CORRECTION orb);

GPPLONG gpp_cssr_clk_free_header(pGPP_CSSR_CLK_CORRECTION clk);
GPPLONG gpp_cssr_clk_add_mask_message(pGPP_CSSR_CLK_CORRECTION clk);

GPPLONG gpp_cssr_cb_free_header(pGPP_CSSR_CB cb);
GPPLONG gpp_cssr_cb_free_mask_message(pGPP_CSSR_CB cb);

GPPLONG gpp_cssr_pb_free_header(pGPP_CSSR_PB pb);
GPPLONG gpp_cssr_pb_free_mask_message(pGPP_CSSR_PB pb);

GPPLONG gpp_cssr_bias_free_header(pGPP_CSSR_BIAS bias);
GPPLONG gpp_cssr_bias_free_message(pGPP_CSSR_BIAS bias);

GPPLONG gpp_cssr_ura_add_header(pGPP_CSSR_URA ura);
GPPLONG gpp_cssr_ura_free_mask_message(pGPP_CSSR_URA ura);

GPPLONG gpp_cssr_stec_correction_free_header(pGPP_CSSR_STEC_CORRECTION stec);
GPPLONG gpp_cssr_stec_free_mask_message(pGPP_CSSR_STEC_CORRECTION stec);

GPPLONG gpp_cssr_grid_correction_free_header(pGPP_CSSR_GRIDDED_CORRECTION grid);
GPPLONG gpp_cssr_grid_correction_free_mask_message(pGPP_CSSR_GRIDDED_CORRECTION grid);

GPPLONG gpp_cssr_gnss_combine_correction_free_header(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine);
GPPLONG gpp_cssr_gnss_combine_correction_free_mask_message(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine);

extern void gpp_sapa_float2buffer(GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPDOUBLE max, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid, GPPDOUBLE value);
extern GPPFLOAT gpp_sapa_buffer2float(const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid);
GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0);

#ifdef __cplusplus
}
#endif

#endif //GPP_CSSR_H_