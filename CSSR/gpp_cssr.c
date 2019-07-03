#include "gpp_cssr.h"
#include "bit2buff.h"

/*******************************************************************************************************************************************************************************
													FUNCTIONS TO ALLOCATE MEMORY TO MESSAGE SUBTYPES
*******************************************************************************************************************************************************************************/

GPPLONG gpp_cssr_mask_add_header(pGPP_CSSR_MASK mask)
{
	if (!mask) return GPP_CSSR_ERR_INVALID_MASK;

	if (!mask->mask_header)
	{
		mask->mask_header = (GPP_CSSR_MASK_HEADER*)calloc(1, sizeof(GPP_CSSR_MASK_HEADER));
		if (!mask->mask_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;	//ok
}


GPPLONG gpp_cssr_mask_add_mask_message(pGPP_CSSR_MASK mask)
{
	if (!mask) return GPP_CSSR_ERR_INVALID_MASK;

	if (!mask->mask_message)
	{
		mask->mask_message = (pGPP_CSSR_MASK_MESSAGE*)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_MASK_MESSAGE));

		if (!mask->mask_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
		GPPUINT1 sys;
		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!mask->mask_message[sys])
			{
				mask->mask_message[sys] = (pGPP_CSSR_MASK_MESSAGE)calloc(1, sizeof(GPP_CSSR_MASK_MESSAGE));
				if (!mask->mask_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
			}
		}
	}

	return 0;	//ok
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


GPPLONG gpp_cssr_orb_add_header(pGPP_CSSR_ORB_CORRECTION orb)
{
	if (!orb) return GPP_CSSR_ERR_INVALID_ORB;

	if (!orb->orb_header)
	{
		orb->orb_header = (pGPP_CSSR_ORB_HEADER)calloc(1, sizeof(GPP_CSSR_ORB_HEADER));
		if (!orb->orb_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;	//ok
}


GPPLONG gpp_cssr_orb_add_mask_message(pGPP_CSSR_ORB_CORRECTION orb)
{
	if (!orb) return GPP_CSSR_ERR_INVALID_ORB;

	if (!orb->orb_message)
	{
		orb->orb_message = (pGPP_CSSR_ORB_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_ORB_MESSAGE*));
		if (!orb->orb_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
		
		GPPUINT1 sys,sat;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!orb->orb_message[sys])
			{
				orb->orb_message[sys] = (pGPP_CSSR_ORB_MESSAGE*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_ORB_MESSAGE));
				if (!orb->orb_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!orb->orb_message[sys][sat])
					{
						orb->orb_message[sys][sat]= (pGPP_CSSR_ORB_MESSAGE)calloc(1, sizeof(pGPP_CSSR_ORB_MESSAGE));
						if (!orb->orb_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
					}
				}
			}
		}
	}

	return 0;	//ok
}

//-------------------------------------------------------------------------------------------------------------------------------------


GPPLONG gpp_cssr_clk_add_header(pGPP_CSSR_CLK_CORRECTION clk)
{
	if (!clk) return GPP_CSSR_ERR_INVALID_ORB;

	if (!clk->clk_header)
	{
		clk->clk_header = (pGPP_CSSR_CLK_HEADER)calloc(1, sizeof(GPP_CSSR_CLK_HEADER));
		if (!clk->clk_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;	//ok
}


GPPLONG gpp_cssr_clk_add_mask_message(pGPP_CSSR_CLK_CORRECTION clk)
{
	if (!clk) return GPP_CSSR_ERR_INVALID_ORB;

	if (!clk->clk_message)
	{
		clk->clk_message = (pGPP_CSSR_CLK_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_CLK_MESSAGE*));
		if (!clk->clk_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!clk->clk_message[sys])
			{
				clk->clk_message[sys] = (pGPP_CSSR_CLK_MESSAGE*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_CLK_MESSAGE));
				if (!clk->clk_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!clk->clk_message[sys][sat])
					{
						clk->clk_message[sys][sat] = (pGPP_CSSR_CLK_MESSAGE)calloc(1, sizeof(GPP_CSSR_CLK_MESSAGE));
						if (!clk->clk_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
					}
				}
			}
		}
	}

	return 0;	//ok
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


GPPLONG cssr_cb_add_header(pGPP_CSSR_CB cb)
{
	if (!cb) return GPP_CSSR_ERR_INVALID_SAT_CODE_BIAS;

	if (!cb->cb_header)
	{
		cb->cb_header = (GPP_CSSR_CB_HEADER*)calloc(1, sizeof(GPP_CSSR_CB_HEADER));
		if (!cb->cb_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;
}


GPPLONG gpp_cssr_cb_add_mask_message(pGPP_CSSR_CB cb)
{
	if (!cb) return GPP_CSSR_ERR_INVALID_ORB;

	if (!cb->cb_message)
	{
		cb->cb_message = (pGPP_CSSR_CB_MESSAGE***)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_CB_MESSAGE**));
		if (!cb->cb_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat,code;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!cb->cb_message[sys])
			{
				cb->cb_message[sys] = (pGPP_CSSR_CB_MESSAGE**)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_CB_MESSAGE*));
				if (!cb->cb_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!cb->cb_message[sys][sat])
					{
						cb->cb_message[sys][sat] = (pGPP_CSSR_CB_MESSAGE*)calloc(GPP_CSSR_MAX_CODE, sizeof(pGPP_CSSR_CB_MESSAGE));
						if (!cb->cb_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
						for (code = 0; code < GPP_CSSR_MAX_CODE; code++)
						{
							if (!cb->cb_message[sys][sat][code])
							{
								cb->cb_message[sys][sat][code] = (pGPP_CSSR_CB_MESSAGE)calloc(1, sizeof(GPP_CSSR_CB_MESSAGE));
								if (!cb->cb_message[sys][sat][code])
									return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
							}
						}
					}
				}
			}
		}
	}

	return 0;	//ok
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


GPPLONG cssr_pb_add_header(pGPP_CSSR_PB pb)
{
	if (!pb) return GPP_CSSR_ERR_INVALID_SAT_PHASE_BIAS;

	if (!pb->pb_header)
	{
		pb->pb_header = (GPP_CSSR_PB_HEADER*)calloc(1, sizeof(GPP_CSSR_PB_HEADER));
		if (!pb->pb_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;
}


GPPLONG gpp_cssr_pb_add_mask_message(pGPP_CSSR_PB pb)
{
	if (!pb) return GPP_CSSR_ERR_INVALID_ORB;

	if (!pb->pb_message)
	{
		pb->pb_message = (pGPP_CSSR_PB_MESSAGE***)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_PB_MESSAGE**));
		if (!pb->pb_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat, code;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!pb->pb_message[sys])
			{
				pb->pb_message[sys] = (pGPP_CSSR_PB_MESSAGE**)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_PB_MESSAGE*));
				if (!pb->pb_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!pb->pb_message[sys][sat])
					{
						pb->pb_message[sys][sat] = (pGPP_CSSR_PB_MESSAGE*)calloc(GPP_CSSR_MAX_CODE, sizeof(pGPP_CSSR_PB_MESSAGE));
						if (!pb->pb_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
						for (code = 0; code < GPP_CSSR_MAX_CODE; code++)
						{
							if (!pb->pb_message[sys][sat][code])
							{
								pb->pb_message[sys][sat][code] = (pGPP_CSSR_PB_MESSAGE)calloc(1, sizeof(GPP_CSSR_PB_MESSAGE));
								if (!pb->pb_message[sys][sat][code])
									return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
							}
						}
					}
				}
			}
		}
	}

	return 0;	//ok
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_cssr_bias_add_header(pGPP_CSSR_BIAS	bias)
{
	if (!bias)
		return GPP_CSSR_ERR_INVALID_SAT_BIAS;

	if (!bias->bias_header)
	{
		bias->bias_header = (pGPP_CSSR_BIAS_HEADER*)calloc(1, sizeof(GPP_CSSR_BIAS_HEADER));
		if (!bias->bias_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;	//ok
}

GPPLONG gpp_cssr_bias_add_mask_message(pGPP_CSSR_BIAS bias)
{
	if (!bias) return GPP_CSSR_ERR_INVALID_SAT_BIAS;

	if (!bias->bias_message)
	{
		bias->bias_message = (pGPP_CSSR_BIAS_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_BIAS_MESSAGE*));
		if (!bias->bias_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat,code,phase;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!bias->bias_message[sys])
			{
				bias->bias_message[sys] = (pGPP_CSSR_BIAS_MESSAGE*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_BIAS_MESSAGE));
				if (!bias->bias_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!bias->bias_message[sys][sat])
					{
						bias->bias_message[sys][sat] = (pGPP_CSSR_BIAS_MESSAGE)calloc(1, sizeof(pGPP_CSSR_BIAS_MESSAGE));
						if (!bias->bias_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
						if (!bias->bias_message[sys][sat]->code_bias)
						{
							bias->bias_message[sys][sat]->code_bias = (pGPP_CSSR_CB_MESSAGE*)calloc(GPP_CSSR_MAX_CODE, sizeof(pGPP_CSSR_CB_MESSAGE));
							if (!bias->bias_message[sys][sat]->code_bias)
								return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
							for (code = 0; code < GPP_CSSR_MAX_CODE; code++)
							{
								if (!bias->bias_message[sys][sat]->code_bias[code])
								{
									bias->bias_message[sys][sat]->code_bias[code]= (pGPP_CSSR_CB_MESSAGE)calloc(1, sizeof(GPP_CSSR_CB_MESSAGE));
									if (!bias->bias_message[sys][sat]->code_bias[code])
										return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
								}
							}
							
						}

						if (!bias->bias_message[sys][sat]->phase_bias)
						{
							bias->bias_message[sys][sat]->phase_bias = (pGPP_CSSR_PB_MESSAGE*)calloc(GPP_CSSR_MAX_CODE, sizeof(pGPP_CSSR_PB_MESSAGE));
							if (!bias->bias_message[sys][sat]->phase_bias)
								return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
							for (phase = 0; phase < GPP_CSSR_MAX_PHASE; phase++)
							{
								if (!bias->bias_message[sys][sat]->phase_bias[phase])
								{
									bias->bias_message[sys][sat]->phase_bias[phase] = (pGPP_CSSR_PB_MESSAGE)calloc(1, sizeof(GPP_CSSR_PB_MESSAGE));
									if (!bias->bias_message[sys][sat]->phase_bias[phase])
										return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
								}
							}

						}

					}
				}
			}
		}
	}
	return 0;	//ok
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_cssr_ura_add_header(pGPP_CSSR_URA ura)
{
	if (!ura) return GPP_CSSR_ERR_INVALID_URA;
	if (!ura->ura_header)
	{
		ura->ura_header = (pGPP_CSSR_URA_HEADER)calloc(1, sizeof(GPP_CSSR_URA_HEADER));
		if (!ura->ura_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;
}


GPPLONG gpp_cssr_ura_add_mask_message(pGPP_CSSR_URA ura)
{
	if (!ura) return GPP_CSSR_ERR_INVALID_URA;

	if (!ura) return GPP_CSSR_ERR_INVALID_URA;

	if (!ura->ura_message)
	{
		ura->ura_message = (pGPP_CSSR_URA_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_URA_MESSAGE*));
		if (!ura->ura_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!ura->ura_message[sys])
			{
				ura->ura_message[sys] = (GPP_CSSR_URA_MESSAGE*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_URA_MESSAGE));
				if (!ura->ura_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!ura->ura_message[sys][sat])
					{
						ura->ura_message[sys][sat] = (pGPP_CSSR_URA_MESSAGE)calloc(1, sizeof(GPP_CSSR_URA_MESSAGE));
						if (!ura->ura_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
					}
				}
			}
		}
	}

	return 0;	//ok
}


//----------------------------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_cssr_stec_correction_add_header(pGPP_CSSR_STEC_CORRECTION stec)
{
	if (!stec) return GPP_CSSR_ERR_INVALID_STEC;
	if (!stec->stec_header)
	{
		stec->stec_header = (pGPP_CSSR_STEC_HEADER)calloc(1, sizeof(GPP_CSSR_STEC_HEADER));
		if (!stec->stec_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;
}


GPPLONG gpp_cssr_stec_add_mask_message(pGPP_CSSR_STEC_CORRECTION stec)
{
	if (!stec) return GPP_CSSR_ERR_INVALID_STEC;

	if (!stec->stec_message)
	{
		stec->stec_message = (pGPP_CSSR_STEC_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_STEC_MESSAGE*));
		if (!stec->stec_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!stec->stec_message[sys])
			{
				stec->stec_message[sys] = (pGPP_CSSR_STEC_MESSAGE*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_STEC_MESSAGE));
				if (!stec->stec_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!stec->stec_message[sys][sat])
					{
						stec->stec_message[sys][sat] = (pGPP_CSSR_STEC_MESSAGE)calloc(1, sizeof(GPP_CSSR_STEC_MESSAGE));
						if (!stec->stec_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
					}
				}
			}
		}
	}

	return 0;	//ok
}

//---------------------------------------------------------------------------------------------------------------------------

GPPLONG gpp_cssr_grid_correction_add_header(pGPP_CSSR_GRIDDED_CORRECTION grid)
{
	if (!grid) return GPP_CSSR_ERR_INVALID_GRID;
	if (!grid->grid_header)
	{
		grid->grid_header = (pGPP_CSSR_GRID_HEADER)calloc(1, sizeof(GPP_CSSR_GRID_HEADER));
		if (!grid->grid_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;
}


GPPLONG gpp_cssr_grid_add_mask_message(pGPP_CSSR_GRIDDED_CORRECTION grid)
{
	if (!grid) return GPP_CSSR_ERR_INVALID_GRID;

	if (!grid->grid_message)
	{
		grid->grid_message = (pGPP_CSSR_GRID_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_GRID_MESSAGE*));
		if (!grid->grid_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat,igrid;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!grid->grid_message[sys])
			{
				grid->grid_message[sys] = (pGPP_CSSR_GRID_MESSAGE*)calloc(GPP_CSSR_MAX_GRID, sizeof(pGPP_CSSR_GRID_MESSAGE));
				if (!grid->grid_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (igrid = 0; igrid < GPP_CSSR_MAX_GRID; igrid++)
				{
					if (!grid->grid_message[sys][igrid])
					{
						grid->grid_message[sys][igrid] = (pGPP_CSSR_GRID_MESSAGE)calloc(1, sizeof(pGPP_CSSR_GRID_MESSAGE));
						if (!grid->grid_message[sys][igrid])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

						if (!grid->grid_message[sys][igrid]->residual)
						{
							grid->grid_message[sys][igrid]->residual = (pGPP_CSSR_GRID_RESDIUAL_CORRECTION*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_GRID_RESDIUAL_CORRECTION));
							if (!grid->grid_message[sys][igrid]->residual)
								return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
							for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
							{
								if (!grid->grid_message[sys][igrid]->residual[sat])
								{
									grid->grid_message[sys][igrid]->residual[sat]= (pGPP_CSSR_GRID_RESDIUAL_CORRECTION)calloc(1, sizeof(GPP_CSSR_GRID_RESDIUAL_CORRECTION));
									if (!grid->grid_message[sys][igrid]->residual[sat])
										return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;	//ok
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------


GPPLONG gpp_cssr_gnss_combine_correction_add_header(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine)
{
	if (!gnss_combine) return GPP_CSSR_ERR_INVALID_GRID;
	if (!gnss_combine->combine_header)
	{
		gnss_combine->combine_header = (pGPP_CSSR_COMBINE_CORRECTION_HEADER)calloc(1, sizeof(GPP_CSSR_COMBINE_CORRECTION_HEADER));
		if (!gnss_combine->combine_header)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
	}
	return 0;
}

GPPLONG gpp_cssr_gnss_combine_correction_add_mask_message(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine)
{
	if (!gnss_combine) return GPP_CSSR_ERR_INVALID_COMBINED;

	if (!gnss_combine->combine_message)
	{
		gnss_combine->combine_message = (pGPP_CSSR_COMBINE_CORRECTION_MESSAGE**)calloc(GPP_CSSR_MAX_SYS, sizeof(pGPP_CSSR_COMBINE_CORRECTION_MESSAGE*));
		if (!gnss_combine->combine_message)
			return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;

		GPPUINT1 sys, sat;

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (!gnss_combine->combine_message[sys])
			{
				gnss_combine->combine_message[sys] = (pGPP_CSSR_COMBINE_CORRECTION_MESSAGE*)calloc(GPP_CSSR_MAX_SAT, sizeof(pGPP_CSSR_COMBINE_CORRECTION_MESSAGE));
				if (!gnss_combine->combine_message[sys])
					return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (!gnss_combine->combine_message[sys][sat])
					{
						gnss_combine->combine_message[sys][sat] = (pGPP_CSSR_COMBINE_CORRECTION_MESSAGE)calloc(1, sizeof(GPP_CSSR_COMBINE_CORRECTION_MESSAGE));
						if (!gnss_combine->combine_message[sys][sat])
							return GPP_CSSR_ERR_NOT_ENOUGH_MEMORY;
					}
				}
			}
		}
	}
	return 0;	//ok
}



//***************************************************************************************//
//                            FREE FUNCTIONS
//****************************************************************************************//


GPPLONG gpp_cssr_mask_free_header(pGPP_CSSR_MASK mask)
{
	if (mask)
	{
		if (mask->mask_header)
		{
			free(mask->mask_header);
			mask->mask_header = NULL;
		}
	}
	return 0;//ok
}

GPPLONG gpp_cssr_mask_free_spec_part(pGPP_CSSR_MASK mask)
{
	GPPUINT1 sys;
	if (mask)
	{
		if (mask->mask_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (mask->mask_message[sys])
				{
					free(mask->mask_message[sys]);
				}

			}
			free(mask->mask_message);
			mask->mask_message = NULL;
		}
	}
	return 0;//ok
}


GPPLONG gpp_cssr_orb_free_header(pGPP_CSSR_ORB_CORRECTION orb)
{
	if (orb)
	{
		if (orb->orb_header)
		{
			free(orb->orb_header);
			orb->orb_header = NULL;
		}
	}
	return 0;//ok

}

GPPLONG gpp_cssr_orb_free_mask_message(pGPP_CSSR_ORB_CORRECTION orb)
{
	GPPUINT1 sys, sat;
	if (orb)
	{
		if (orb->orb_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (orb->orb_message[sys])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (orb->orb_message[sys][sat])
							free(orb->orb_message[sys][sat]);
					}
					free(orb->orb_message[sys]);
				}

			}
			free(orb->orb_message);
			orb->orb_message = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_clk_free_header(pGPP_CSSR_CLK_CORRECTION clk)
{
	if (clk)
	{
		if (clk->clk_header)
		{
			free(clk->clk_header);
			clk->clk_header = NULL;
		}
	}
	return 0;//ok

}

GPPLONG gpp_cssr_clk_free_mask_message(pGPP_CSSR_CLK_CORRECTION clk)
{
	GPPUINT1 sys, sat;
	if (clk)
	{
		if (clk->clk_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (clk->clk_message[sys])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (clk->clk_message[sys][sat])
							free(clk->clk_message[sys][sat]);
					}
					free(clk->clk_message[sys]);
				}

			}
			free(clk->clk_message);
			clk->clk_message = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_cb_free_header(pGPP_CSSR_CB cb)
{
	if (cb)
	{
		if (cb->cb_header)
		{
			free(cb->cb_header);
			cb->cb_header = NULL;
		}
	}
	return 0; //ok
}
GPPLONG gpp_cssr_cb_free_mask_message(pGPP_CSSR_CB cb)
{
	GPPUINT1 sys, sat, code;
	if (cb)
	{
		if (cb->cb_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (cb->cb_message[sys])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (cb->cb_message[sys][sat])
						{
							for (code = 0; code < GPP_CSSR_MAX_CODE; code++)
							{
								free(cb->cb_message[sys][sat][code]);
							}
						}
						free(cb->cb_message[sys][sat]);
					}
					free(cb->cb_message[sys]);
				}
			}
			free(cb->cb_message);
			cb->cb_message = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_pb_free_header(pGPP_CSSR_PB pb)
{
	if (pb)
	{
		if (pb->pb_header)
		{
			free(pb->pb_header);
			pb->pb_header = NULL;
		}
	}

	return 0;//ok
}


GPPLONG gpp_cssr_pb_free_mask_message(pGPP_CSSR_PB pb)
{
	GPPUINT1 sys, sat, code;
	if (pb)
	{
		if (pb->pb_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (pb->pb_message[sys])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (pb->pb_message[sys][sat])
						{
							for (code = 0; code < GPP_CSSR_MAX_CODE; code++)
							{
								free(pb->pb_message[sys][sat][code]);
							}
						}
						free(pb->pb_message[sys][sat]);
					}
					free(pb->pb_message[sys]);
				}
			}
			free(pb->pb_message);
			pb->pb_message = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_bias_free_header(pGPP_CSSR_BIAS bias)
{
	if (bias)
	{
		if (bias->bias_header)
		{
			free(bias->bias_header);
			bias->bias_header = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_bias_free_message(pGPP_CSSR_BIAS bias)
{
	GPPUINT1 sys, sat, code, phase;
	if (bias->bias_message)
	{

		for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
		{
			if (bias->bias_message[sys])
			{
				for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
				{
					if (bias->bias_message[sys][sat])
					{
						if (bias->bias_message[sys][sat]->code_bias)
						{
							for (code = 0; code < GPP_CSSR_MAX_CODE; code++)
							{
								if (bias->bias_message[sys][sat]->code_bias[code])
									free(bias->bias_message[sys][sat]->code_bias[code]);
							}
							free(bias->bias_message[sys][sat]->code_bias);
						}

						if (bias->bias_message[sys][sat]->phase_bias)
						{
							for (phase = 0; phase < GPP_CSSR_MAX_PHASE; phase++)
							{
								if (bias->bias_message[sys][sat]->phase_bias[code])
									free(bias->bias_message[sys][sat]->phase_bias[code]);
							}
							free(bias->bias_message[sys][sat]->phase_bias);
						}
						free(bias->bias_message[sys][sat]);
					}

				}
				free(bias->bias_message[sys]);
			}
		}
		free(bias->bias_message);
		bias->bias_message = NULL;
	}
	return 0; //ok
}

GPPLONG gpp_cssr_ura_free_header(pGPP_CSSR_URA ura)
{
	if (ura)
	{
		if (ura->ura_header)
		{
			free(ura->ura_header);
			ura->ura_header = NULL;

		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_ura_free_mask_message(pGPP_CSSR_URA ura)
{
	GPPUINT1 sys, sat;
	if (ura)
	{
		if (ura->ura_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (ura->ura_message[sys][sat])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (ura->ura_message[sys][sat])
							free(ura->ura_message[sys][sat]);
					}
				}
			}
			free(ura->ura_message);
		}
	}
	return 0; //ok

}

GPPLONG gpp_cssr_stec_correction_free_header(pGPP_CSSR_STEC_CORRECTION stec)
{
	if (stec)
	{
		if (stec->stec_header)
		{
			free(stec->stec_header);
			stec->stec_header = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_stec_free_mask_message(pGPP_CSSR_STEC_CORRECTION stec)
{
	GPPUINT1 sys, sat;
	if (stec)
	{
		if (stec->stec_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (stec->stec_message[sys])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (stec->stec_message[sys][sat])
							free(stec->stec_message[sys][sat]);
					}
					free(stec->stec_message[sys]);
				}
			}
			free(stec->stec_message);
			stec->stec_message = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_grid_correction_free_header(pGPP_CSSR_GRIDDED_CORRECTION grid)
{
	if (grid)
	{
		if (grid->grid_header)
		{
			free(grid->grid_header);
			grid->grid_header = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_grid_correction_free_mask_message(pGPP_CSSR_GRIDDED_CORRECTION grid)
{
	GPPUINT1 sys, sat, igrid;
	if (grid)
	{
		if (grid->grid_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (grid->grid_message[sys])
				{
					for (igrid = 0; igrid < GPP_CSSR_MAX_GRID; grid++)
					{
						if (grid->grid_message[sys][igrid])
						{
							if (grid->grid_message[sys][igrid]->residual)
							{
								for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
								{
									if (grid->grid_message[sys][igrid]->residual[sat])
										free(grid->grid_message[sys][igrid]->residual[sat]);
								}
								free(grid->grid_message[sys][igrid]->residual);
							}
							free(grid->grid_message[sys][igrid]);
						}
					}
					free(grid->grid_message[sys]);
				}
			}
			free(grid->grid_message);
			grid->grid_message = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_gnss_combine_correction_free_header(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine)
{
	if (gnss_combine)
	{
		if (gnss_combine->combine_header)
		{
			free(gnss_combine->combine_header);
			gnss_combine->combine_header = NULL;
		}
	}
	return 0; //ok
}

GPPLONG gpp_cssr_gnss_combine_correction_free_mask_message(pGPP_CSSR_GNSS_COMBINE_CORRECTION gnss_combine)
{
	GPPUINT1 sys, sat;
	if (gnss_combine)
	{
		if (gnss_combine->combine_message)
		{
			for (sys = 0; sys < GPP_CSSR_MAX_SYS; sys++)
			{
				if (gnss_combine->combine_message[sys])
				{
					for (sat = 0; sat < GPP_CSSR_MAX_SAT; sat++)
					{
						if (gnss_combine->combine_message[sys][sat])
						{
							free(gnss_combine->combine_message[sys][sat]);
						}
					}
					free(gnss_combine->combine_message[sys]);
				}
			}
			free(gnss_combine->combine_message);
			gnss_combine->combine_message = NULL;
		}
	}
	return 0; //ok
}


extern void gpp_sapa_float2buffer(GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPDOUBLE max, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid, GPPDOUBLE value)
{
	GN_LONG lval = 0;

	if (value<min || value>max) {
		if (invalid) {
			gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, bits, *invalid);
			return;
		}
		else
		{
			gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, bits, lval);
			return;
		}
	}

	lval = (value - min) / res;
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, bits, lval);


} /* gpp_sapa_float2buffer() */

extern GPPFLOAT gpp_sapa_buffer2float(const GPPUCHAR *buffer, GPPLONG *byte_pos, GPPLONG *bit_pos, GPPDOUBLE min, GPPUINT1 bits, GPPDOUBLE res, GPPUINT2 *invalid)
{
	GPPLONG *inv_val = NULL;
	GN_LONG lval = gn_get_ulong_from_buffer(buffer, byte_pos, bit_pos, bits);
	if (invalid == inv_val)
	{
		if (lval == 0)
			return lval;
		else
			return ((lval*res) + min);
	}
	else
	{
		if (*invalid == lval)
			return lval;
		else
			return ((lval*res) + min);
	}

} /* gpp_sapa_buffer2float() */

GPPLONG gpp_sapa_get_bit_diff(GPPLONG byte_pos, GPPLONG bit_pos, GPPLONG byte_pos0, GPPLONG bit_pos0)
{
	return (byte_pos - byte_pos0) * 8 + (bit_pos - bit_pos0);
}

void gpp_sapa_set_area_bits(GPPUINT8*area_bits, int value)
{
	GPPINT8 temp = 1 << (value % 64);
	area_bits[(value / 64)] = temp | area_bits[value / 64];
}


