/*  Filename: /data0/pwrp/pwrdemo41/common/inc/ra_plc_user.h    */

#include "pwr_profibusclasses.h"
#include "pwr_basecomponentclasses.h"
#include "pwr_abbclasses.h"
#include "pwr_othermanufacturerclasses.h"
#include "pwr_inorclasses.h"
#include "pwr_siemensclasses.h"
#include "pwr_simulclasses.h"
#include "pwr_miscellaneousclasses.h"
#include "simul.h"
#include "misc.h" 

#include "pwr_cvolpwrtest01classes.h"

void Pwrt01_NotEqual_exec(plc_sThread *tp, pwr_sClass_Pwrt01_NotEqual *o);
void pwrt01_random_string(char *str, int size);
void pwrt01_random_buf(void *buf, int size);
void pwrt01_random_uint32(pwr_tUInt32 *value);
void pwrt01_random_float(float *value, float min, float max);
void pwrt01_random_boolean(pwr_tBoolean *value);

