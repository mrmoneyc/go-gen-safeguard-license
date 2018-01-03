/* psprolib function prototypes */

#ifndef __PSPROLIB_H_
#define __PSPROLIB_H_

#include "psprolib_enum.h"

#if defined(__cplusplus)
extern "C" {
#endif
/* Function prototypes */

int sgSetVendor             (int (*routine)(char *id));

int sgGenerateDate           (int days, char *sgdate);

int sgExtractComponent       (const char  *target,
                              char  *component,
                              char  *version,
                              char  *id,
                              char  *idtype,
                              char  *expires,
                              char  *certificate);

int sgEnableComponent        (const char  *target,
                              const char  *component,
                              const char  *version,
                              const char  *id,
                              const char  *idtype,
                              const char  *expires,
                              const char  *certificate);

int sgDisableComponent       (const char  *target,
                              const char  *component,
                              const char  *version,
                              const char  *id,
                              const char  *idtype);

int sgEnableAllComponents    (const char  *target,
                              const char  *file);

int sgValidateComponent      (const char  *component,
                              const char  *version,
                              const char  *id,
                              const char  *idtype,
                              const char  *expires,
                              const char  *certificate);

int sgAuthorized             (const char  *target,
                              const char  *component,
                              const char  *version);
   
int sgExpireDays             (const char  *target,
                              const char  *component,
                              const char  *version,
                              int   *days);

int sgConnect                (void);

int sgTest                   (const char *component, const char *version);

int sgCheckout               (const char *component, const char *version);

int sgCheckin                (const char *component, const char *version);

int sgTimer                  (void);

int sgDisconnect             (void);

int sgPing                   (void);

int sgShutdown               (void);

int sgRestart                (void);

int sgShowClient               (char *serverhost,
                                char *clienthost,
                                char *user,
                                char *component,
                                char *version,
                                int  *count);

int sgShowServer               (char *component,
                                char *version,
                                char *id,
                                char *idtype,
                                int  *count,
                                int  *current,
                                char *expires,
                                char *certificate);

int sgShowServerDetail         (int  *thread_id,
                                int  *sockfd,
                                char *ip,
                                int  *pid,
                                char *process,
                                char *user,
                                char *host,
                                char *component,
                                char *version,
                                int  *count);

int sgGetLastErrorString       (char  *string);


int sgSetAttrStr               (SG_ATTRTYPE attr, const char *val);

int sgSetAttrInt               (SG_ATTRTYPE attr, int val);

int sgSetAttrFnC               (SG_ATTRTYPE attr, void *val);

int sgGetAttrStr               (SG_ATTRTYPE attr, char *val);

int sgGetAttrInt               (SG_ATTRTYPE attr, int *val);


int sgArc4                     (int direction,
                                const char *key,
                                const char *instring,
                                char *out_arc4);

int sgDash                     (int direction,
                                const char *inkey,
                                char *out_dash);

int sgEnableComponentLine    (const char  *target,
                              const char  *componentline);

int sgPaActivate             (const char *web, int port, SG_ACTIVATETYPE activatetype, const char *cust, 
                              const char *component, const char *version, const char *email, 
                              char *outsrv, char *outlic);

int sgPaGetInstallationCode  (SG_IDTYPE idtype, char *ic);

int sgPaGetDemoActivationKeys       (const char *web, int port, const char *component, 
                                     const char *version, const char *email, char *ic, 
                                     char *lk, char *ak);

int sgPaGetPaidActivationKeys       (const char *web, int port, const char *cust, 
                                     const char *component, const char *version, 
                                     const char *email, char *ic, char *lk, 
                                     char *ak);

int sgPaAssembleKeys                (const char *ic, const char *lk, const char *ak,char *componentline);

int sgPaDecodeKey                   (const char *lk, char *lcomp, char *lversion, char *lidtype, char *ltimeout);

int sgPaShutdown                    (const char *web, int port, const char *password);

int sgPaRestart                     (const char *web, int port, const char *password);

int sgPaShowlog                     (const char *web, int port, const char *password, char *logfile);

#if defined(__cplusplus)
}
#endif

#endif
