#include "bit2buff.h"
#include "gpp_cssr.h"

#define GPP_CSSR_ORB_DELTA_RADIAL_MIN -26.2128
#define GPP_CSSR_ORB_DELTA_RADIAL_MAX 26.2128
#define GPP_CSSR_ORB_DELTA_ALONG_TRACK_MIN -26.208
#define GPP_CSSR_ORB_DELTA_ALONG_TRACK_MAX 26.208
#define GPP_CSSR_ORB_DELTA_CROSS_TRACK_MIN -26.208
#define GPP_CSSR_ORB_DELTA_CROSS_TRACK_MAX 26.208

#define GPP_CSSR_ORB_DELTA_RADIAL_RES 0.0016
#define GPP_CSSR_ORB_DELTA_ALONG_TRACK_RES 0.0064
#define GPP_CSSR_ORB_DELTA_CROSS_TRACK_RES 0.0064
#define GPP_CSSR_ORB_DELTA_INVALID -26.2144

GPPLONG gpp_cssr_cssr2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPULONG rc;
	GPPLONG byte_pos0, bit_pos0;
	GPPLONG mybyte = 0, mybit = 0;

	// handling if byte_pos or bit_pos are null pointers
	if (!byte_pos) 	byte_pos = &mybyte;
	if (!bit_pos) 	bit_pos = &mybit;

	// get start position of byte_pos and bit_pos to get needed bits
	byte_pos0 = *byte_pos;
	bit_pos0 = *bit_pos;
	if (rc = gpp_cssr_header2buffer(cssr, buffer, byte_pos, bit_pos))
		return 0;

	if (rc = gpp_cssr_data2buffer(cssr, buffer, byte_pos, bit_pos))
		return 0;
	return  gpp_sapa_get_bit_diff(*byte_pos, *bit_pos, byte_pos0, bit_pos0);
}
GPPULONG gpp_cssr_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPULONG rc;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos,32 , cssr->header->preamble);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 8, cssr->header->prn);
	if (rc = gpp_cssr_l6_msg_type_id2buffer(cssr, buffer, byte_pos, bit_pos))
		return 0;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, cssr->header->alert_flag);
	return 0;
}

GPPULONG gpp_cssr_l6_msg_type_id2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 3, cssr->header->msg_type_id->vendor_id);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, cssr->header->msg_type_id->msg_gen_facility_id);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 2, cssr->header->msg_type_id->reserved);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, cssr->header->msg_type_id->sub_frame_indicator);
}

GPPULONG gpp_cssr_data2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPULONG rc;
	if(rc=gpp_cssr_mask2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_orb2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_clk2buffer(cssr,buffer, byte_pos, bit_pos)) return 0;
	/*if(rc=gpp_cssr_cb2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_pb2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_bias2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_ura2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_stec_correction2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_gridded_correction2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_service_info2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;
	if(rc=gpp_cssr_gnss_combine_correction2buffer(cssr, buffer, byte_pos, bit_pos)) return 0;*/
	return 0;
}

GPPULONG gpp_cssr_mask2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPULONG rc;
	GPPUINT1 sys;
	if (rc = gpp_cssr_mask_header2buffer(cssr, buffer, byte_pos, bit_pos))
		return 0;
	if (rc = gpp_cssr_mask_message2buffer(cssr,sys, buffer, byte_pos, bit_pos))
		return 0;
	return 0;
}

GPPULONG gpp_cssr_mask_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_CSSR_MASK_HEADER *mask_header = NULL;
	mask_header = cssr->data_part->mask->mask_header;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, mask_header->msg_number);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, mask_header->msg_sub_type_id);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 20, mask_header->gps_hourly_epoch_time);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, mask_header->update_interval);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, mask_header->multiple_msg_indicator);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, mask_header->iod_ssr);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, mask_header->no_of_gnss);

	return 0;
}

GPPULONG gpp_cssr_mask_message2buffer(const pGPP_CSSR cssr,GPPUINT1 sys, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_CSSR_MASK_MESSAGE *mask_message = NULL;
	mask_message = cssr->data_part->mask->mask_message;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, mask_message->gnss_id);
	//gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 40, mask_message->sat_mask);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 16, mask_message->sig_mask);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, mask_message->sig_mask);

	return 0;
}

GPPULONG gpp_cssr_orb2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPULONG rc;
	GPPUINT1 sys, sat;
	if (rc = gpp_cssr_orb_header2buffer(cssr, buffer, byte_pos, bit_pos))
		return 0;
	if (rc = gpp_cssr_orb_message2buffer(cssr,sys,sat,buffer, byte_pos, bit_pos))
		return 0;
	return 0;
}

GPPULONG gpp_cssr_orb_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_CSSR_ORB_HEADER *orb_header = NULL;
	orb_header = cssr->data_part->orb->orb_header;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, orb_header->msg_number);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, orb_header->msg_sub_type_id);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, orb_header->gns_hourly_epoch_time);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, orb_header->update_interval);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, orb_header->multiple_msg_indicator);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, orb_header->iod_ssr);

	return 0;
}

GPPULONG gpp_cssr_orb_message2buffer(const pGPP_CSSR cssr, GPPUINT1 sys,GPPUINT1 sat,GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_CSSR_ORB_MESSAGE *orb_message = NULL;
	orb_message = cssr->data_part->orb->orb_message[sys][sat];
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 8, orb_message->gnss_iode); //8 or 10 bits
	//gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_CSSR_ORB_DELTA_RADIAL_MIN, GPP_CSSR_ORB_DELTA_RADIAL_MAX, 15, GPP_CSSR_ORB_DELTA_RADIAL_RES, GPP_CSSR_ORB_DELTA_INVALID, orb_message->delta_radian);
	//gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_CSSR_ORB_DELTA_ALONG_TRACK_MIN, GPP_CSSR_ORB_DELTA_ALONG_TRACK_MAX, 13, GPP_CSSR_ORB_DELTA_ALONG_TRACK_RES, GPP_CSSR_ORB_DELTA_INVALID, orb_message->delta_along_track);
	//gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_CSSR_ORB_DELTA_CROSS_TRACK_MIN, GPP_CSSR_ORB_DELTA_CROSS_TRACK_MAX, 13, GPP_CSSR_ORB_DELTA_CROSS_TRACK_RES, GPP_CSSR_ORB_DELTA_INVALID, orb_message->delta_cross_track);
	return 0;
}

GPPULONG gpp_cssr_clk2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPPULONG rc;
	GPPUINT1 sys=0, sat=0;
	if (rc = gpp_cssr_clk_header2buffer(cssr, buffer, byte_pos, bit_pos))
		return 0;
	if (rc = gpp_cssr_clk_message2buffer(cssr, sys,sat,buffer, byte_pos, bit_pos))
		return 0;
	return 0;
}

GPPULONG gpp_cssr_clk_header2buffer(const pGPP_CSSR cssr, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_CSSR_CLK_HEADER *clk_header = NULL;
	clk_header = cssr->data_part->clk->clk_header;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, clk_header->msg_number);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, clk_header->msg_sub_type_id);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 12, clk_header->gns_hourly_epoch_time);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, clk_header->update_interval);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 1, clk_header->multiple_msg_indicator);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 4, clk_header->iod_ssr);

	return 0;
}

GPPULONG gpp_cssr_clk_message2buffer(const pGPP_CSSR cssr, GPPUINT1 sys, GPPUINT1 sat, GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos)
{
	GPP_CSSR_CLK_MESSAGE *clk_message = NULL;
	clk_message = cssr->data_part->clk->clk_message[sys][sat];
	//gpp_sapa_float2buffer(buffer, byte_pos, bit_pos, GPP_CSSR_ORB_DELTA_CROSS_TRACK_MIN, GPP_CSSR_ORB_DELTA_CROSS_TRACK_MAX, 13, GPP_CSSR_ORB_DELTA_CROSS_TRACK_RES, GPP_CSSR_ORB_DELTA_INVALID, clk_message->delta_clock_c0);
	return 0;
}