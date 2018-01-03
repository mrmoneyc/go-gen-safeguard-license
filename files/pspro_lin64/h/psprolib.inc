      ! This is the FORTRAN include file that you will need
      ! to include in your FORTRAN source code.  It will set
      ! up everything you need.


      ! these define the full set of SafeGuardLM integer
      ! functions so that their return values can be sent
      ! back to fortran.

      external sgAuthorized,sgGenerateDate,sgExtractComponent
      external sgEnableComponent,sgDisableComponent
      external sgEnableAllComponents,sgValidateComponent
      external sgExpireDays,sgConnect,sgTest,sgCheckout,sgCheckin
      external sgTimer,sgPing,sgDisconnect,sgShutdown,sgRestart
      external sgShowClient,sgShowServer,sgShowServerDetail
      external sgGetLastErrorString,sgPaGetInstallationCode
      external sgSetAttrStr,sgSetAttrInt,sgGetAttrStr,sgGetAttrInt
      external sgArc4,sgDash,sgEnableComponentLine,sgPaActivate
      external sgPaGetDemoActovationKeys,sgPaGetPaidActivationKeys
      external sgPaAssmbleKeys,sgPaDecodeKey,sgPaShutdown,sgPaRestart
      external sgPaShowlog,charlen

 

      integer sgAuthorized,sgGenerateDate,sgExtractComponent
      integer sgEnableComponent,sgDisableComponent
      integer sgEnableAllComponents,sgValidateComponent
      integer sgExpireDays,sgConnect,sgTest,sgCheckout,sgCheckin
      integer sgTimer,sgPing,sgDisconnect,sgShutdown,sgRestart
      integer sgShowClient,sgShowServer,sgShowServerDetail
      integer sgGetLastErrorString,sgPaGetInstallationCode
      integer sgSetAttrStr,sgSetAttrInt,sgGetAttrStr,sgGetAttrInt
      integer sgArc4,sgDash,sgEnableComponentLine,sgPaActivate
      integer sgPaGetDemoActovationKeys,sgPaGetPaidActivationKeys
      integer sgPaAssembleKeys,sgPaDecodeKey,sgPaShutdown,sgPaRestart
      integer sgPaShowlog,charlen

      ! these are the standard set of enum's found in psprolib_enum.h

      enum, bind ( C )
        enumerator :: SG_LICENSETYPE_DEFAULT = 0
        enumerator :: SG_LICENSETYPE_EXTERNAL = 1
        enumerator :: SG_LICENSETYPE_INTERNAL = 2
        enumerator :: SG_LICENSETYPE_FLOATING = 3
      end enum

      enum, bind ( C )
        enumerator :: SG_IDTYPE_DEFAULT = 0
        enumerator :: SG_IDTYPE_IPHONE = 1
        enumerator :: SG_IDTYPE_ANDROID = 2
        enumerator :: SG_IDTYPE_BLACKBERRY = 3
        enumerator :: SG_IDTYPE_ETHERNET = 6
        enumerator :: SG_IDTYPE_HOSTNAME = 7
        enumerator :: SG_IDTYPE_IPADDRESS = 8
        enumerator :: SG_IDTYPE_USERNAME = 9
        enumerator :: SG_IDTYPE_COUNTRY = 10
        enumerator :: SG_IDTYPE_INET6 = 11
        enumerator :: SG_IDTYPE_VSN = 12
        enumerator :: SG_IDTYPE_VENDOR = 13
        enumerator :: SG_IDTYPE_ANY = 14
        enumerator :: SG_IDTYPE_HOSTID = 15
        enumerator :: SG_IDTYPE_MACINTOSH = 16
        enumerator :: SG_IDTYPE_METERED = 17
        enumerator :: SG_IDTYPE_OS = 18
        enumerator :: SG_IDTYPE_COMPOSITE = 19
      end enum

      enum, bind ( C )
        enumerator :: SG_LANGUAGE_DEFAULT = 0
  	enumerator :: SG_LANGUAGE_GER = 1
  	enumerator :: SG_LANGUAGE_ENG = 2
  	enumerator :: SG_LANGUAGE_SPA = 3
  	enumerator :: SG_LANGUAGE_FRA = 4
  	enumerator :: SG_LANGUAGE_ITA = 5
  	enumerator :: SG_LANGUAGE_TUR = 6
  	enumerator :: SG_LANGUAGE_KOR = 7
  	enumerator :: SG_LANGUAGE_POR = 8
  	enumerator :: SG_LANGUAGE_DEU = 9
  	enumerator :: SG_LANGUAGE_DET = 10
  	enumerator :: SG_LANGUAGE_RUM = 11
  	enumerator :: SG_LANGUAGE_UKR = 12
  	enumerator :: SG_LANGUAGE_SRP = 13
  	enumerator :: SG_LANGUAGE_SWE = 14
  	enumerator :: SG_LANGUAGE_DAN = 15
  	enumerator :: SG_LANGUAGE_SLO = 16
  	enumerator :: SG_LANGUAGE_SLV = 17
  	enumerator :: SG_LANGUAGE_JPN = 18
      end enum

      enum, bind ( C )
        enumerator :: SG_ACTIVATE_DEMO_NODE = 0
        enumerator :: SG_ACTIVATE_PAID_NODE = 1
        enumerator :: SG_ACTIVATE_DEMO_FLOAT = 2
        enumerator :: SG_ACTIVATE_PAID_FLOAT = 3
      end enum

      enum, bind ( C )
        enumerator :: SG_DATECHECK_STANDARD = 0
        enumerator :: SG_DATECHECK_EXTENDED = 1
      end enum

      enum, bind ( C )
        enumerator :: SG_ATTR_DEFAULT_ID = 0
        enumerator :: SG_ATTR_IPHONE_ID = 1
        enumerator :: SG_ATTR_ANDROID_ID = 2
        enumerator :: SG_ATTR_BLACKBERRY_ID = 3
        enumerator :: SG_ATTR_ETHERNET_ID = 4
        enumerator :: SG_ATTR_HOSTNAME_ID = 5
        enumerator :: SG_ATTR_IPADDRESS_ID = 6
        enumerator :: SG_ATTR_USERNAME_ID = 7
        enumerator :: SG_ATTR_COUNTRY_ID = 8
        enumerator :: SG_ATTR_INET6_ID = 9
        enumerator :: SG_ATTR_VSN_ID = 10
        enumerator :: SG_ATTR_VENDOR_ID = 11
        enumerator :: SG_ATTR_ANY_ID = 12
        enumerator :: SG_ATTR_HOSTID_ID = 13
        enumerator :: SG_ATTR_MACINTOSH_ID = 14
        enumerator :: SG_ATTR_METERED_ID = 15
        enumerator :: SG_ATTR_COMPOSITE_ID = 16
        enumerator :: SG_ATTR_OS_ID = 17
        enumerator :: SG_ATTR_LOGFILE_PATH = 18
        enumerator :: SG_ATTR_DISALLOW_IDTYPE = 19
        enumerator :: SG_ATTR_DISALLOW_ALL_IDTYPE = 20
        enumerator :: SG_ATTR_ALLOW_IDTYPE = 21
        enumerator :: SG_ATTR_ALLOW_ALL_IDTYPE = 22
        enumerator :: SG_ATTR_LICENSETYPE = 23
        enumerator :: SG_ATTR_VENDOR_ROUTINE = 24
        enumerator :: SG_ATTR_VENDOR_LIBRARY = 25
        enumerator :: SG_ATTR_RELEASE = 26
        enumerator :: SG_ATTR_ARCHITECTURE = 27
        enumerator :: SG_ATTR_LANGUAGE = 28
        enumerator :: SG_ATTR_EXE_PATH = 29
        enumerator :: SG_ATTR_NULL = 30
        enumerator :: SG_ATTR_TCP_TIMEOUT = 31
        enumerator :: SG_ATTR_RETRY_INTERVAL = 32
        enumerator :: SG_ATTR_RETRY_COUNT = 33
        enumerator :: SG_ATTR_DISABLE_ALARM = 34
        enumerator :: SG_ATTR_LICENSE_FILE = 35
        enumerator :: SG_ATTR_MAXIMUM_TIMEDIFF = 36
        enumerator :: SG_ATTR_DISABLE_ENV = 37
        enumerator :: SG_ATTR_VENDOR_RECONNECT_EXIT = 38
        enumerator :: SG_ATTR_VENDOR_RECONNECT = 39
        enumerator :: SG_ATTR_VENDOR_RECONNECT_COMPLETE = 40
        enumerator :: SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL = 41
        enumerator :: SG_ATTR_DATECHECK = 42
        enumerator :: SG_ATTR_DISABLE_LANG = 43
      end enum

      enum, bind ( C )
        enumerator :: SG_SUCCESS = 0
        enumerator :: SG_AUTHORIZED = 10
        enumerator :: SG_TARGET_FILE_NOT_FOUND = -1
        enumerator :: SG_NOT_AUTHORIZED_FOR_COMPONENT = -2
        enumerator :: SG_NOT_AUTHORIZED_FOR_VERSION = -3
        enumerator :: SG_COMPONENT_EXPIRED = -4
        enumerator :: SG_CANT_CREATE_TARGET_FILE = -5
        enumerator :: SG_CANT_GET_ID = -6
        enumerator :: SG_INVALID_CERTIFICATE = -7
        enumerator :: SG_INVALID_TARGET_INFORMATION = -8
        enumerator :: SG_NO_MORE_COMPONENTS_IN_FILE = -9
        enumerator :: SG_NO_COMPONENT_MATCHING_ID = -10
        enumerator :: SG_COMPONENT_NAME_TOO_LONG = -11
        enumerator :: SG_CANT_WRITE_TO_TARGET_FILE = -12
        enumerator :: SG_CANT_READ_TARGET_FILE = -13
        enumerator :: SG_INVALID_ID_LENGTH = -14
        enumerator :: SG_CANT_CREATE_TEMPORARY_FILE = -15
        enumerator :: SG_CANT_OPEN_TEMPORARY_FILE = -16
        enumerator :: SG_CANT_DELETE_TARGET_FILE = -17
        enumerator :: SG_CANT_RENAME_TARGET_FILE = -18
        enumerator :: SG_CANT_READ_TEXT_FILE = -19
        enumerator :: SG_CANT_WRITE_TEXT_FILE = -20
        enumerator :: SG_CANT_DELETE_TEXT_FILE = -21
        enumerator :: SG_CANT_RENAME_TEXT_FILE = -22
        enumerator :: SG_TEXT_FILE_NOT_FOUND = -23
        enumerator :: SG_NO_COMPONENT_FOUND_IN_FILE = -24
        enumerator :: SG_NO_FREE_SLOTS = -25
        enumerator :: SG_INVALID_TIMEOUT = -26
        enumerator :: SG_VERSION_LENGTH_TOO_LONG = -27
        enumerator :: SG_IDTYPE_NOT_SUPPORTED = -28
        enumerator :: SG_BAD_LICENSETYPE = -29
        enumerator :: SG_ATTRTYPE_NOT_SUPPORTED = -30
        enumerator :: SG_ATTRTYPE_INVALID = -31
        enumerator :: SG_CANT_CREATE_LOGFILE = -32
        enumerator :: SG_LOGFILE_NOT_SET = -33
        enumerator :: SG_INVALID_OPTION_FOR_LICENSETYPE = -34
        enumerator :: SG_NO_MORE_CLIENT_COMPONENTS = -35
        enumerator :: SG_NO_MORE_SERVER_COMPONENTS = -36
        enumerator :: SG_INVALID_LICENSE_KEY = -37
        enumerator :: SG_VERSION_NOT_NUMERIC = -38
        enumerator :: SG_NOT_A_CALLABLE_OBJECT = -39
        enumerator :: SG_SYSTEM_CLOCK_SET_BACK = -40
        enumerator :: SG_NO_MORE_SERVER_DETAIL = -41
        enumerator :: SG_INVALID_LICENSE_COUNT = -60
        enumerator :: SG_SERVERNORESPOND = -61
        enumerator :: SG_BADCOMMUNICATION = -62
        enumerator :: SG_INVALIDHOST = -63
        enumerator :: SG_BADCONNECT = -64
        enumerator :: SG_BADREAD = -65
        enumerator :: SG_BADWRITE = -66
        enumerator :: SG_MAXSERVERCONNECTIONS = -67
        enumerator :: SG_LOSTCONNECT = -68
        enumerator :: SG_ALL_LICENSES_IN_USE = -80
        enumerator :: SG_NO_SUCH_COMPONENT = -81
        enumerator :: SG_NOT_LICENSED_FOR_VERSION = -82
        enumerator :: SG_ALREADY_CHECKED_OUT = -83
        enumerator :: SG_NOT_CHECKED_OUT = -84
        enumerator :: SG_TIMEDIFF_TOO_LARGE = -85
        enumerator :: SG_COMPONENT_NOT_AVAILABLE = -86
        enumerator :: SG_COMPONENT_ALREADY_ISSUED = -87
        enumerator :: SG_BAD_PASSWORD = -88
        enumerator :: SG_CANT_QUERY_SQLDB = -89
        enumerator :: SG_CANT_CONNECT_TO_SQLDB = -90
        enumerator :: SG_WRONG_SERVER = -91
        enumerator :: SG_REJECTED = -92
        enumerator :: SG_NOLOG = -93
        enumerator :: SG_UNKNOWN_ERROR = -99
      end enum
