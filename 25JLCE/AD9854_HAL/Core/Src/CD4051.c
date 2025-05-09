#include "CD4051.h"



void CD_4051_SetChannel(u8 channel)
{
   channel & 0x01 ? CD4051_CTRA_SET : CD4051_CTRA_CLR;
   (channel>>1) & 0x01 ? CD4051_CTRB_SET : CD4051_CTRB_CLR;
   (channel>>2) & 0x01 ? CD4051_CTRC_SET : CD4051_CTRC_CLR;
}