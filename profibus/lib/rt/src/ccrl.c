/******************************************************************************
*                                                                             *
*                      SOFTING Industrial Automation GmbH                     *
*                          Richard-Reitzner-Allee 6                           *
*                                D-85540 Haar                                 *
*                        Phone: (++49)-(0)89-45656-0                          *
*                        Fax:   (++49)-(0)89-45656-399                        *
*                                                                             *
*            Copyright (C) SOFTING Industrial Automation GmbH 1995-2012       *
*                              All Rights Reserved                            *
*                                                                             *
*******************************************************************************

FILE_NAME               CCRL.C

PROJECT_NAME            PROFIBUS

MODULE                  CCRL

COMPONENT_LIBRARY       PBT LIBs and DLL    (16-Bit)
                        PBTOOLS.DLL         (32-Bit)

AUTHOR                  SOFTING

VERSION                 5.21.0.00.release

DATE                    February-1998

STATUS                  finished

FUNCTIONAL_MODULE_DESCRIPTION

If you, as a PROFIBUS-API programmer, configurate your PROFIBUS board,
you must know - among other things - how many resources are allocated by your
CRL. The functions 'ccrl_resrces_init' and 'ccrl_resrces_add_entry' will
help you to get this information.

The CRL-resources are of different types. There are FAL-SDBs, FDL-SDBs,
Data-Buffers, API-Buffers, Poll-List-Entries and Subscriber-List-Entries.

If you use the 'ccrl_resrces_...' functions, you must know neither the
meaning of the resource types nor the algorithm for calculating the number
of resources!

You get the number of resources as follows:

At first, call 'ccrl_resrces_init' with a pointer to the CRL-Header as input
parameter.

Then, for every CRL-Entry, call 'ccrl_resrces_add_entry'. This function has
three parameter:

first:    input     / communication reference
second:   transient / pointer to CRL entry
third:    output    / pointer to a buffer with a minimum length of
                      sizeof(T_FMB_CONFIG_CRL) bytes

'ccrl_resrces_add_entry' does two action. First, it checks the CRL entry.
If the entry incorrect it tries to make it correct, otherwise it returns
with a negative result. If the entry is OK, 'ccrl_resrces_add_entry'
calculates resources. After function return, the output buffer holds the
sum of resources that are needed by all CRL entries that where put into
'ccrl_resrces_add_entry' since last call of 'ccrl_resrces_init'.

So, if you have put all entries of your CRL into 'ccrl_resrces_add_entry'
the output buffer of the last function call contains the number of resources
that are needed for your whole CRL. You can use this result as input for the
PROFIBUS configuration service (see typedef T_FMB_SET_CONFIGURATION_REQ).

A detailed description of the algorithm within 'ccrl_resrces_add_entry' is
given in the user manual.



RELATED_DOCUMENTS
=============================================================================*/
#include "keywords.h"

INCLUDES

#include <stdio.h>
#include <stdlib.h>

#if defined(WIN16) || defined(WIN32)
#include <windows.h>
#endif

#include <pb_type.h>
#include <pb_if.h>
#include <pb_fmb.h>
#include <pb_fm7.h>
#include <pb_err.h>
#include <pb_tools.h>

LOCAL_DEFINES

#define M_MM 0x00 /* Master in Master/Master connection */
#define M_MS 0x02 /* Master in Master/Slave connection */
#define S_MS 0x03 /* Slave in a Master/Slave connection */
#define S_CL 0x08 /* Broadcast/Multicast Sender */
#define R_CL 0x09 /* Broadcast/Multicast Receiver */

#define LLI_EVT_BIT LLI_E /* LLI events are enabled/disabled */

#define _CCRL_MAP_SAP_NR(sap) (USIGN8)((sap == 128) ? 64 : sap)
#define _IS_I_CONN(x) ((x & 0x03) == I_CONN)
#define _IS_CYCLIC(type) (type & 0x02)
#define _WITHOUT_SLAVE_INITIATIVE(type) (!(type & 0x04))
#define _IS_CONN_LESS(x) ((x & 0x09) == BRCT)
#define _IS_CONN_ORIENTED(x) (!_IS_CONN_LESS(x))

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

LOCAL_TYPEDEFS

typedef struct _T_CCRL_CONN_RESRCES
{
  USIGN8 no_of_fal_sdbs;
  USIGN8 no_of_fdl_sdbs;
  USIGN8 no_of_data_buffer;
  USIGN8 no_of_api_buffer;
} T_CCRL_CONN_RESRCES;

typedef struct _T_CCRL
{
  T_FMB_CONFIG_CRL ccrl;
  USIGN8 poll_sap;
  PB_BOOL mms_exist;
  USIGN8 rcv_resrces;
  T_CCRL_CONN_RESRCES isap_resrces[65];
} T_CCRL;

FUNCTION_DECLARATIONS

EXPORT_DATA

IMPORT_DATA

LOCAL_DATA

static T_CCRL ccrl_obj;

#if defined(WIN32) || defined(_WIN32) || defined(WIN16) || defined(_WIN16)
#pragma check_stack(off)
#endif

FUNCTION LOCAL USIGN16 ccrl_determine_role(IN T_CRL_STATIC FAR* crl_ptr,
                                           IN USIGN8* role_ptr)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

This function determines the role in which the station acts in a connection.

The possible roles are:

M_MM      -> Master in a Master/Master connection
M_MS      -> Master in a Master/Slave connection
S_MS      -> Slave in a Master/Slave connection
S_CL      -> Sender of multicast/broadcast messages
R_CL      -> Receiver of multicast/broadcast messages

----------------------------------------------------------------------------*/
{
  LOCAL_VARIABLES

  FUNCTION_BODY

  switch ((USIGN8)(crl_ptr->conn_type & 0x0F))
  {
  case MMAC:
    *role_ptr = M_MM;
    return (E_OK);

  case MSAC:
  case MSAC_SI:
  case MSCY:
  case MSCY_SI:
    if (crl_ptr->loc_lsap == ccrl_obj.poll_sap)
      *role_ptr = M_MS;
    else
      *role_ptr = S_MS;
    return (E_OK);

  case MULT:
  case BRCT:
    if (crl_ptr->rem_add == 127)
      *role_ptr = S_CL;
    else
      *role_ptr = R_CL;
    return (E_OK);

  default:
    return (E_FM7_CRL_INVALID_ENTRY);
  }
}

FUNCTION LOCAL VOID ccrl_correct_crl_entry(IN USIGN16 cr, IN USIGN8 role,
                                           INOUT T_CRL_STATIC FAR* crl_ptr)

/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

------------------------------------------------------------------------------*/
{
  LOCAL_VARIABLES

  FUNCTION_BODY

  if (crl_ptr->lli_sap == 1)
  {
    if (cr > 1)
    {
      /* There is a management client -----------------------------------------
       */
      crl_ptr->max_scc = 1;
      crl_ptr->max_sac = 0;
      crl_ptr->max_rcc = 0;
      crl_ptr->max_rac = 0;
    }
    else /* (cr == 1) */
    {
      /* There is a management server -----------------------------------------
       */
      crl_ptr->max_scc = 0;
      crl_ptr->max_sac = 0;
      crl_ptr->max_rcc = 1;
      crl_ptr->max_rac = 0;
    }
  }

  if (role == M_MS)
  {
    crl_ptr->max_rcc = 0;

    if (_IS_CYCLIC(crl_ptr->conn_type))
      crl_ptr->max_scc = 0;
    if (_WITHOUT_SLAVE_INITIATIVE(crl_ptr->conn_type))
      crl_ptr->max_rac = 0;
  }
  else if (role == S_MS)
  {
    crl_ptr->max_scc = 0;

    if (_IS_CYCLIC(crl_ptr->conn_type))
      crl_ptr->max_rcc = 0;
    if (_WITHOUT_SLAVE_INITIATIVE(crl_ptr->conn_type))
      crl_ptr->max_sac = 0;
  }

  return;
}

FUNCTION LOCAL VOID ccrl_update_resrc_ctr(INOUT USIGN8* stored_number_ptr,
                                          INOUT USIGN8* current_number_ptr)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

----------------------------------------------------------------------------*/
{
  LOCAL_VARIABLES

  USIGN8 diff;

  FUNCTION_BODY

  if (*stored_number_ptr < *current_number_ptr)
  {
    diff = (USIGN8)(*current_number_ptr - *stored_number_ptr);
    *stored_number_ptr = *current_number_ptr;
    *current_number_ptr = diff;
  }
  else
  {
    *current_number_ptr = 0;
  }

  return;
}

FUNCTION LOCAL VOID
ccrl_adapt_resrces(IN T_CCRL_CONN_RESRCES* in_resrces_ptr,
                   INOUT T_CCRL_CONN_RESRCES* out_resrces_ptr)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

----------------------------------------------------------------------------*/
{
  LOCAL_VARIABLES

  FUNCTION_BODY

  ccrl_update_resrc_ctr(&in_resrces_ptr->no_of_fal_sdbs,
                        &out_resrces_ptr->no_of_fal_sdbs);
  ccrl_update_resrc_ctr(&in_resrces_ptr->no_of_fdl_sdbs,
                        &out_resrces_ptr->no_of_fdl_sdbs);
  ccrl_update_resrc_ctr(&in_resrces_ptr->no_of_data_buffer,
                        &out_resrces_ptr->no_of_data_buffer);
  ccrl_update_resrc_ctr(&in_resrces_ptr->no_of_api_buffer,
                        &out_resrces_ptr->no_of_api_buffer);

  return;
}

/******************************************************************************/
/* EXPORTED FUNCTIONS                                                         */
/******************************************************************************/

FUNCTION GLOBAL VOID CALL_CONV ccrl_resrces_init(IN T_CRL_HDR FAR* crl_hdr_ptr)

/*----------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

At first this function has to be called to initialize the internal structures
for calculating the memory requirements.

possible return values:
- NONE

----------------------------------------------------------------------------*/
{
  LOCAL_VARIABLES

  USIGN8 i;

  FUNCTION_BODY

  ccrl_obj.ccrl.max_no_fal_sdbs = 0;
  ccrl_obj.ccrl.max_no_fdl_sdbs = 0;
  ccrl_obj.ccrl.max_no_data_buffer = 0;
  ccrl_obj.ccrl.max_no_api_buffer = 0;
  ccrl_obj.ccrl.max_no_poll_entries = 0;
  ccrl_obj.ccrl.max_no_subscr_entries = 0;

  ccrl_obj.poll_sap = crl_hdr_ptr->poll_sap;
  ccrl_obj.mms_exist = PB_FALSE;

  for (i = 0; i < 65; i++)
  {
    ccrl_obj.isap_resrces[i].no_of_fal_sdbs = 0;
    ccrl_obj.isap_resrces[i].no_of_fdl_sdbs = 0;
    ccrl_obj.isap_resrces[i].no_of_data_buffer = 0;
    ccrl_obj.isap_resrces[i].no_of_api_buffer = 0;
  }

  return;
}

FUNCTION GLOBAL USIGN16 CALL_CONV
ccrl_resrces_add_entry(IN USIGN16 cr, IN T_CRL_STATIC FAR* crl_ptr,
                       OUT T_FMB_CONFIG_CRL FAR* config_ptr)

/*------------------------------------------------------------------------------
FUNCTIONAL_DESCRIPTION

For each CRL entry this function has to be called to evaluate the number of
resources.
Two actions are performed by this function. First, it checks the CRL entry.
If the entry is incorrect it tries to correct it. If the entry cannot be
corrected
it returns with a negative result. If the entry is OK, this function calculates
the
resources. After function return, the output buffer holds the sum of resources
that
are needed by all CRL entries that where put into ccrl_resrces_add_entry since
last
call of ccrl_resrces_init. The result after the last call of
ccrl_resrces_add_entry
this is the number of all needed resources for the whole CRL. This result can be
used
as input for the PROFIBUS configuration service.

IN:  cr                       -> communication reference
IN:  crl_ptr                  -> pointer to static part of the CRL entry
OUT: config_ptr               -> pointer to CRL configuraton structure

possible return values:
- E_OK                        -> function executed correctly
- E_FM7_CRL_INVALID_ENTRY     -> invalid entry found in CRL, resources are not
                                 calculated

----------------------------------------------------------------------------- */
{
  LOCAL_VARIABLES

  USIGN8 role;
  USIGN8 max_scc;
  USIGN8 max_sac;
  USIGN8 max_rcc;
  USIGN8 max_rac;
  USIGN32 ci;
  USIGN8 multiplier;
  USIGN8 snd_req;
  USIGN8 snd_req_csrd;
  USIGN8 snd_req_srd;
  USIGN8 rcv_res;
  USIGN8 rcv_ind;
  USIGN8 rcv_ind_csrd;
  USIGN8 snd_res_srd;
  USIGN8 lli_api_resrc;
  USIGN8 lli_api_snd_resrc;
  USIGN8 lli_sr_snd_resrc;
  USIGN8 lli_rcv_ind;
  USIGN8 lli_poll_elem;
  USIGN8 lli_idm;
  USIGN8 lli_evt_resrc;
  USIGN8 fdl_sap;
  USIGN8 fdl_rsap;
  USIGN16 no_of_fal_sdbs;
  USIGN16 no_of_fdl_sdbs;
  USIGN16 no_of_data_buffer;
  USIGN16 no_of_api_buffer;
  USIGN16 result;

  T_CCRL_CONN_RESRCES conn_resrc;

  FUNCTION_BODY

  if ((result = ccrl_determine_role(crl_ptr, &role)) != E_OK)
    return (result);

  ccrl_correct_crl_entry(cr, role, crl_ptr);

  max_scc = crl_ptr->max_scc;
  max_sac = crl_ptr->max_sac;
  max_rcc = crl_ptr->max_rcc;
  max_rac = crl_ptr->max_rac;
  ci = crl_ptr->ci;
  multiplier = crl_ptr->multiplier;

  snd_req = 0;      /* (FAL + DATA) + FDL */
  snd_req_csrd = 0; /* (FAL + DATA) */
  snd_req_srd = 0;  /* (FDL + DATA) */

  rcv_res = 0; /* (FDL + DATA) */

  rcv_ind = 0;      /* (FDL + DATA) + FAL */
  rcv_ind_csrd = 0; /* (FAL + DATA) */

  snd_res_srd = 0; /* (FDL + API) */

  lli_api_resrc = 0;     /* (FAL + API) */
  lli_api_snd_resrc = 0; /* (FAL + API) + FDL */
  lli_sr_snd_resrc = 0;  /* (FAL + DATA) + FDL */
  lli_rcv_ind = 0;       /* (FDL + DATA) */

  lli_poll_elem = 0; /* (POLL + API) + (FDL + DATA) */
  lli_idm = 0;       /* (DATA) */
  lli_evt_resrc = 0; /* (FAL + DATA) */
  fdl_sap = 0;       /* (FDL) */
  fdl_rsap = 0;      /* (DATA or FDL + DATA) */

  switch (role)
  {
  case M_MM:
    /* Master in Master/Master Connection ----------------------------- */

    snd_req = (USIGN8)(max(1,           /* snd ASS.req */
                           (max_scc     /* snd DTC.req */
                            + max_sac)) /* snd DTA.req */
                       + 1              /* snd ABT.req */
                       );

    lli_api_snd_resrc = (USIGN8)(min(ci, 1) /* snd IDLE.req */
                                 + 1        /* LLI abort resrc */
                                 );

    rcv_res = (USIGN8)(max(1,           /* rcv ASS_RES_PDU */
                           (max_scc     /* rcv DTC_RES_PDU */
                            + max_sac)) /* rcv DTA_ACK_PDU */
                       );

    rcv_ind = (USIGN8)(max(1,           /* rcv ASS_REQ_PDU */
                           (max_rcc     /* rcv DTC_REQ_PDU */
                            + max_rac)) /* rcv DTA_REQ_PDU */
                       + 1              /* rcv ABT_REQ_PDU */
                       );

    lli_rcv_ind = (USIGN8)min(ci, 1); /* rcv IDLE_REQ_PDU */
    fdl_sap = 1;                      /* act/deact LSAP */
    break;

  case M_MS:
    /* Master in a cyclic master/slave connection --------------------- */

    if (_IS_CYCLIC(crl_ptr->conn_type))
    {
      max_scc = 1;
      ci = 0;
      lli_idm = 1; /* image data memory */

      if (crl_ptr->conn_type & LLI_EVT_BIT)
        lli_evt_resrc = 1;
    }
    else /* _IS_ACYCLIC (crl_ptr->conn_type) */
    {
      multiplier = 1;
    }

    lli_poll_elem = (USIGN8)(max(multiplier, 1)); /* poll_list_element */

    lli_api_resrc = (USIGN8)(min(ci, 1) /* snd IDLE_REQ_PDU */
                             + 1        /* LLI abort resrc */
                             );

    snd_req_csrd = (USIGN8)(max(1,           /* snd ASS.req */
                                (max_scc     /* snd DTC.req */
                                 + max_sac)) /* snd DTA.req */
                            + 1              /* snd ABT.req */
                            );

    snd_req_srd = max_sac; /* snd DTA.req (high) */

    rcv_ind_csrd = (USIGN8)(max_rac /* rcv DTA_REQ_PDU */
                            + 1     /* rcv ABT_REQ_PDU */
                            );

    snd_res_srd = max_rac; /* snd DTA.ack (high)*/

    if (!ccrl_obj.mms_exist)
    {
      fdl_sap = 1;
      ccrl_obj.mms_exist = PB_TRUE;
    }
    break;

  case S_MS:
    /* Slave in a master/slave connection ----------------------------- */

    fdl_rsap = 1; /* reply update buffer */

    if (_IS_CYCLIC(crl_ptr->conn_type))
    {
      max_rcc = 1;
      ci = 0;
      lli_idm = 1; /* image data memory */
    }

    snd_req = (USIGN8)(max_sac /* snd DTA.req */
                       + 1     /* snd ABT.req */
                       );

    rcv_res = max_sac; /* rcv DTA_ACK_PDU */

    lli_sr_snd_resrc = (USIGN8)(min(ci, 1) /* snd IDLE.req */
                                + 1        /* LLI abort resrc */
                                );

    rcv_ind = (USIGN8)(max(1,           /* rcv ASS_REQ_PDU */
                           (max_rcc     /* rcv DTC_REQ_PDU */
                            + max_rac)) /* rcv DTA_REQ_PDU */
                       + 1              /* rcv ABT_REQ_PDU */
                       );

    lli_rcv_ind = (USIGN8)(min(ci, 1) /* rcv IDLE_REQ_PDU */
                           + 2        /* rcv poll telegrams */
                           );
    fdl_sap = 1; /* act/deact LSAP */

    break;

  case S_CL:
    /* Broadcast/Multicast Sender ------------------------------------- */
    snd_req = (USIGN8)max(1, max_sac); /* snd DTU.req */
    fdl_sap = 1;                       /* act/deact LSAP */
    break;

  case R_CL:
    /* Broadcast/Multicast Receiver ----------------------------------- */
    rcv_ind = (USIGN8)max(1, max_rac); /* rcv DTU_REQ_PDU */
    fdl_sap = 1;                       /* act/deact LSAP */
    break;

  default:
    return (E_FM7_CRL_INVALID_ENTRY);
  }

  no_of_fal_sdbs = (USIGN16)(snd_req + snd_req_csrd + rcv_ind + rcv_ind_csrd +
                             lli_api_resrc + lli_api_snd_resrc +
                             lli_sr_snd_resrc + lli_evt_resrc);

  no_of_fdl_sdbs =
      (USIGN16)(snd_req + snd_req_srd + rcv_res + rcv_ind + snd_res_srd +
                lli_api_snd_resrc + lli_sr_snd_resrc + lli_rcv_ind + fdl_sap +
                lli_poll_elem);

  no_of_fdl_sdbs = (USIGN16)(no_of_fdl_sdbs + fdl_rsap);

  no_of_data_buffer =
      (USIGN16)(snd_req + snd_req_csrd + snd_req_srd + rcv_res + rcv_ind +
                rcv_ind_csrd + lli_sr_snd_resrc + lli_poll_elem + lli_idm +
                lli_rcv_ind + fdl_rsap + lli_evt_resrc);

  no_of_api_buffer = (USIGN16)(snd_res_srd + lli_api_resrc + lli_api_snd_resrc +
                               lli_poll_elem);

  if ((no_of_fal_sdbs > 0xFF) || (no_of_fdl_sdbs > 0xFF) ||
      (no_of_data_buffer > 0xFF) || (no_of_api_buffer > 0xFF))
  {
    return (E_FM7_CRL_INVALID_ENTRY);
  }

  ccrl_obj.rcv_resrces = (USIGN8)(rcv_ind + lli_rcv_ind);

  conn_resrc.no_of_fal_sdbs = (USIGN8)no_of_fal_sdbs;
  conn_resrc.no_of_fdl_sdbs = (USIGN8)no_of_fdl_sdbs;
  conn_resrc.no_of_data_buffer = (USIGN8)no_of_data_buffer;
  conn_resrc.no_of_api_buffer = (USIGN8)no_of_api_buffer;

  if ((role == M_MM) && (_IS_I_CONN(crl_ptr->conn_attr)))
  {
    ccrl_adapt_resrces(
        &ccrl_obj.isap_resrces[_CCRL_MAP_SAP_NR(crl_ptr->loc_lsap)],
        &conn_resrc);
  }

  ccrl_obj.ccrl.max_no_fal_sdbs =
      (USIGN16)(ccrl_obj.ccrl.max_no_fal_sdbs + conn_resrc.no_of_fal_sdbs);

  ccrl_obj.ccrl.max_no_fdl_sdbs =
      (USIGN16)(ccrl_obj.ccrl.max_no_fdl_sdbs + conn_resrc.no_of_fdl_sdbs);

  ccrl_obj.ccrl.max_no_data_buffer = (USIGN16)(
      ccrl_obj.ccrl.max_no_data_buffer + conn_resrc.no_of_data_buffer);

  ccrl_obj.ccrl.max_no_api_buffer =
      (USIGN16)(ccrl_obj.ccrl.max_no_api_buffer + conn_resrc.no_of_api_buffer);

  ccrl_obj.ccrl.max_no_poll_entries =
      (USIGN16)(ccrl_obj.ccrl.max_no_poll_entries + lli_poll_elem);

  *config_ptr = ccrl_obj.ccrl;

  return (result);
}

#if defined(WIN32) || defined(_WIN32) || defined(WIN16) || defined(_WIN16)
#pragma check_stack
#endif
