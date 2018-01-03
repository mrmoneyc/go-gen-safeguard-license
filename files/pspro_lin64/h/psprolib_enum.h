/* psprolib function prototypes */

/* SafeGuard Definitions */

#ifndef __PSPROLIB_ENUM_H_
#define __PSPROLIB_ENUM_H_

typedef enum {
  SG_IDTYPE_DEFAULT,
  SG_IDTYPE_IPHONE,
  SG_IDTYPE_ANDROID,
  SG_IDTYPE_BLACKBERRY,
  SG_IDTYPE_ETHERNET,
  SG_IDTYPE_HOSTNAME,
  SG_IDTYPE_IPADDRESS,
  SG_IDTYPE_USERNAME,
  SG_IDTYPE_COUNTRY,
  SG_IDTYPE_INET6,
  SG_IDTYPE_VSN,
  SG_IDTYPE_VENDOR,
  SG_IDTYPE_ANY,
  SG_IDTYPE_HOSTID,
  SG_IDTYPE_MACINTOSH,
  SG_IDTYPE_METERED,
  SG_IDTYPE_OS,
  SG_IDTYPE_COMPOSITE
} SG_IDTYPE;

#define SG_IDTYPE_LEN 18


typedef enum {
  SG_LICENSETYPE_DEFAULT,
  SG_LICENSETYPE_EXTERNAL,
  SG_LICENSETYPE_INTERNAL,
  SG_LICENSETYPE_FLOATING,
} SG_LICENSETYPE;

#define SG_LICENSETYPE_LEN 4

typedef enum {
  SG_LANGUAGE_DEFAULT,
  SG_LANGUAGE_GER,
  SG_LANGUAGE_ENG,
  SG_LANGUAGE_SPA,
  SG_LANGUAGE_FRA,
  SG_LANGUAGE_ITA,
  SG_LANGUAGE_TUR,
  SG_LANGUAGE_KOR,
  SG_LANGUAGE_POR,
  SG_LANGUAGE_DEU,
  SG_LANGUAGE_DUT,
  SG_LANGUAGE_RUM,
  SG_LANGUAGE_UKR,
  SG_LANGUAGE_SRP,
  SG_LANGUAGE_SWE,
  SG_LANGUAGE_DAN,
  SG_LANGUAGE_SLO,
  SG_LANGUAGE_SLV,
  SG_LANGUAGE_JPN,
} SG_LANGTYPE;

#define SG_LANGTYPE_LEN 19

typedef enum {
  SG_ACTIVATE_DEMO_NODE,
  SG_ACTIVATE_PAID_NODE,
  SG_ACTIVATE_DEMO_FLOAT,
  SG_ACTIVATE_PAID_FLOAT,
} SG_ACTIVATETYPE;

typedef enum {
  SG_DATECHECK_STANDARD,
  SG_DATECHECK_EXTENDED,
} SG_DATECHECK;

typedef enum {
  SG_ATTR_DEFAULT_ID,
  SG_ATTR_IPHONE_ID,
  SG_ATTR_ANDROID_ID,
  SG_ATTR_BLACKBERRY_ID,
  SG_ATTR_ETHERNET_ID,
  SG_ATTR_HOSTNAME_ID,
  SG_ATTR_IPADDRESS_ID,
  SG_ATTR_USERNAME_ID,
  SG_ATTR_COUNTRY_ID,
  SG_ATTR_INET6_ID,
  SG_ATTR_VSN_ID,
  SG_ATTR_VENDOR_ID,
  SG_ATTR_ANY_ID,
  SG_ATTR_HOSTID_ID,
  SG_ATTR_MACINTOSH_ID,
  SG_ATTR_METERED_ID,
  SG_ATTR_OS_ID,
  SG_ATTR_COMPOSITE_ID,
  SG_ATTR_LOGFILE_PATH,
  SG_ATTR_DISALLOW_IDTYPE,
  SG_ATTR_DISALLOW_ALL_IDTYPE,
  SG_ATTR_ALLOW_IDTYPE,
  SG_ATTR_ALLOW_ALL_IDTYPE,
  SG_ATTR_LICENSETYPE,
  SG_ATTR_VENDOR_ROUTINE,
  SG_ATTR_VENDOR_LIBRARY,
  SG_ATTR_RELEASE,
  SG_ATTR_ARCHITECTURE,
  SG_ATTR_LANGUAGE,
  SG_ATTR_EXE_PATH,
  SG_ATTR_NULL,
  SG_ATTR_TCP_TIMEOUT,
  SG_ATTR_RETRY_INTERVAL,
  SG_ATTR_RETRY_COUNT,
  SG_ATTR_DISABLE_ALARM,
  SG_ATTR_LICENSE_FILE,
  SG_ATTR_MAXIMUM_TIMEDIFF,
  SG_ATTR_DISABLE_ENV,
  SG_ATTR_VENDOR_RECONNECT_EXIT,
  SG_ATTR_VENDOR_RECONNECT,
  SG_ATTR_VENDOR_RECONNECT_COMPLETE,
  SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL,
  SG_ATTR_DATECHECK,
  SG_ATTR_DISABLE_LANG,
} SG_ATTRTYPE;

#define SG_ATTRTYPE_LEN 44


/* Error codes */

#define SG_SUCCESS                          (0)
#define SG_AUTHORIZED                       (10)
#define SG_TARGET_FILE_NOT_FOUND            (-1)
#define SG_NOT_AUTHORIZED_FOR_COMPONENT     (-2)
#define SG_NOT_AUTHORIZED_FOR_VERSION       (-3)
#define SG_COMPONENT_EXPIRED                (-4)
#define SG_CANT_CREATE_TARGET_FILE          (-5)
#define SG_CANT_GET_ID                      (-6)
#define SG_INVALID_CERTIFICATE              (-7)
#define SG_INVALID_TARGET_INFORMATION       (-8)
#define SG_NO_MORE_COMPONENTS_IN_FILE       (-9)
#define SG_NO_COMPONENT_MATCHING_ID         (-10)
#define SG_COMPONENT_NAME_TOO_LONG          (-11)
#define SG_CANT_WRITE_TO_TARGET_FILE        (-12)
#define SG_CANT_READ_TARGET_FILE            (-13)
#define SG_INVALID_ID_LENGTH                (-14)
#define SG_CANT_CREATE_TEMPORARY_FILE       (-15)
#define SG_CANT_OPEN_TEMPORARY_FILE         (-16)
#define SG_CANT_DELETE_TARGET_FILE          (-17)
#define SG_CANT_RENAME_TARGET_FILE          (-18)
#define SG_CANT_READ_TEXT_FILE              (-19)
#define SG_CANT_WRITE_TEXT_FILE             (-20)
#define SG_CANT_DELETE_TEXT_FILE            (-21)
#define SG_CANT_RENAME_TEXT_FILE            (-22)
#define SG_TEXT_FILE_NOT_FOUND              (-23)
#define SG_NO_COMPONENT_FOUND_IN_FILE       (-24)
#define SG_NO_FREE_SLOTS                    (-25)
#define SG_INVALID_TIMEOUT                  (-26)
#define SG_VERSION_LENGTH_TOO_LONG          (-27)
#define SG_IDTYPE_NOT_SUPPORTED             (-28)
#define SG_BAD_LICENSETYPE                  (-29)
#define SG_ATTRTYPE_NOT_SUPPORTED           (-30)
#define SG_ATTRTYPE_INVALID                 (-31)
#define SG_CANT_CREATE_LOGFILE              (-32)
#define SG_LOGFILE_NOT_SET                  (-33)
#define SG_INVALID_OPTION_FOR_LICENSETYPE   (-34)
#define SG_NO_MORE_CLIENT_COMPONENTS        (-35)
#define SG_NO_MORE_SERVER_COMPONENTS        (-36)
#define SG_INVALID_LICENSE_KEY              (-37)
#define SG_VERSION_NOT_NUMERIC              (-38)
#define SG_NOT_A_CALLABLE_OBJECT            (-39)
#define SG_SYSTEM_CLOCK_SET_BACK            (-40)
#define SG_NO_MORE_SERVER_DETAIL            (-41)

/* client return codes for floating licenses */
#define SG_INVALID_LICENSE_COUNT            (-60)
#define SG_SERVERNORESPOND                  (-61)
#define SG_BADCOMMUNICATION                 (-62)
#define SG_INVALIDHOST                      (-63)
#define SG_BADCONNECT                       (-64)
#define SG_BADREAD                          (-65)
#define SG_BADWRITE                         (-66)
#define SG_MAXSERVERCONNECTIONS             (-67)
#define SG_LOSTCONNECT                      (-68)
/* WARNING: these have to be the same as in sgserver.h */
#define SG_ALL_LICENSES_IN_USE              (-80)
#define SG_NO_SUCH_COMPONENT                (-81)
#define SG_NOT_LICENSED_FOR_VERSION         (-82)
#define SG_ALREADY_CHECKED_OUT              (-83) /* currently not active */
#define SG_NOT_CHECKED_OUT                  (-84)
#define SG_TIMEDIFF_TOO_LARGE               (-85)
#define SG_COMPONENT_NOT_AVAILABLE          (-86)
#define SG_COMPONENT_ALREADY_ISSUED         (-87)
#define SG_BAD_PASSWORD                     (-88)
#define SG_CANT_QUERY_SQLDB                 (-89)
#define SG_CANT_CONNECT_TO_SQLDB            (-90)
#define SG_WRONG_SERVER                     (-91)
#define SG_REJECTED                         (-92)
#define SG_NOLOG                            (-93)
/* WARNING: these have to be the same as in sgserver.h */


#define SG_UNKNOWN_ERROR                    (-99)

#endif
