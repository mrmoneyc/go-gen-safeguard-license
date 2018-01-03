# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.7
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.



from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_PSProlibProxy', [dirname(__file__)])
        except ImportError:
            import _PSProlibProxy
            return _PSProlibProxy
        if fp is not None:
            try:
                _mod = imp.load_module('_PSProlibProxy', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _PSProlibProxy = swig_import_helper()
    del swig_import_helper
else:
    import _PSProlibProxy
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


SG_IDTYPE_DEFAULT = _PSProlibProxy.SG_IDTYPE_DEFAULT
SG_IDTYPE_IPHONE = _PSProlibProxy.SG_IDTYPE_IPHONE
SG_IDTYPE_ANDROID = _PSProlibProxy.SG_IDTYPE_ANDROID
SG_IDTYPE_BLACKBERRY = _PSProlibProxy.SG_IDTYPE_BLACKBERRY
SG_IDTYPE_ETHERNET = _PSProlibProxy.SG_IDTYPE_ETHERNET
SG_IDTYPE_HOSTNAME = _PSProlibProxy.SG_IDTYPE_HOSTNAME
SG_IDTYPE_IPADDRESS = _PSProlibProxy.SG_IDTYPE_IPADDRESS
SG_IDTYPE_USERNAME = _PSProlibProxy.SG_IDTYPE_USERNAME
SG_IDTYPE_COUNTRY = _PSProlibProxy.SG_IDTYPE_COUNTRY
SG_IDTYPE_INET6 = _PSProlibProxy.SG_IDTYPE_INET6
SG_IDTYPE_VSN = _PSProlibProxy.SG_IDTYPE_VSN
SG_IDTYPE_VENDOR = _PSProlibProxy.SG_IDTYPE_VENDOR
SG_IDTYPE_ANY = _PSProlibProxy.SG_IDTYPE_ANY
SG_IDTYPE_HOSTID = _PSProlibProxy.SG_IDTYPE_HOSTID
SG_IDTYPE_MACINTOSH = _PSProlibProxy.SG_IDTYPE_MACINTOSH
SG_IDTYPE_METERED = _PSProlibProxy.SG_IDTYPE_METERED
SG_IDTYPE_OS = _PSProlibProxy.SG_IDTYPE_OS
SG_IDTYPE_COMPOSITE = _PSProlibProxy.SG_IDTYPE_COMPOSITE
SG_IDTYPE_LEN = _PSProlibProxy.SG_IDTYPE_LEN
SG_LICENSETYPE_DEFAULT = _PSProlibProxy.SG_LICENSETYPE_DEFAULT
SG_LICENSETYPE_EXTERNAL = _PSProlibProxy.SG_LICENSETYPE_EXTERNAL
SG_LICENSETYPE_INTERNAL = _PSProlibProxy.SG_LICENSETYPE_INTERNAL
SG_LICENSETYPE_FLOATING = _PSProlibProxy.SG_LICENSETYPE_FLOATING
SG_LICENSETYPE_LEN = _PSProlibProxy.SG_LICENSETYPE_LEN
SG_LANGUAGE_DEFAULT = _PSProlibProxy.SG_LANGUAGE_DEFAULT
SG_LANGUAGE_GER = _PSProlibProxy.SG_LANGUAGE_GER
SG_LANGUAGE_ENG = _PSProlibProxy.SG_LANGUAGE_ENG
SG_LANGUAGE_SPA = _PSProlibProxy.SG_LANGUAGE_SPA
SG_LANGUAGE_FRA = _PSProlibProxy.SG_LANGUAGE_FRA
SG_LANGUAGE_ITA = _PSProlibProxy.SG_LANGUAGE_ITA
SG_LANGUAGE_TUR = _PSProlibProxy.SG_LANGUAGE_TUR
SG_LANGUAGE_KOR = _PSProlibProxy.SG_LANGUAGE_KOR
SG_LANGUAGE_POR = _PSProlibProxy.SG_LANGUAGE_POR
SG_LANGUAGE_DEU = _PSProlibProxy.SG_LANGUAGE_DEU
SG_LANGUAGE_DUT = _PSProlibProxy.SG_LANGUAGE_DUT
SG_LANGUAGE_RUM = _PSProlibProxy.SG_LANGUAGE_RUM
SG_LANGUAGE_UKR = _PSProlibProxy.SG_LANGUAGE_UKR
SG_LANGUAGE_SRP = _PSProlibProxy.SG_LANGUAGE_SRP
SG_LANGUAGE_SWE = _PSProlibProxy.SG_LANGUAGE_SWE
SG_LANGUAGE_DAN = _PSProlibProxy.SG_LANGUAGE_DAN
SG_LANGUAGE_SLO = _PSProlibProxy.SG_LANGUAGE_SLO
SG_LANGUAGE_SLV = _PSProlibProxy.SG_LANGUAGE_SLV
SG_LANGUAGE_JPN = _PSProlibProxy.SG_LANGUAGE_JPN
SG_LANGTYPE_LEN = _PSProlibProxy.SG_LANGTYPE_LEN
SG_ACTIVATE_DEMO_NODE = _PSProlibProxy.SG_ACTIVATE_DEMO_NODE
SG_ACTIVATE_PAID_NODE = _PSProlibProxy.SG_ACTIVATE_PAID_NODE
SG_ACTIVATE_DEMO_FLOAT = _PSProlibProxy.SG_ACTIVATE_DEMO_FLOAT
SG_ACTIVATE_PAID_FLOAT = _PSProlibProxy.SG_ACTIVATE_PAID_FLOAT
SG_DATECHECK_STANDARD = _PSProlibProxy.SG_DATECHECK_STANDARD
SG_DATECHECK_EXTENDED = _PSProlibProxy.SG_DATECHECK_EXTENDED
SG_ATTR_DEFAULT_ID = _PSProlibProxy.SG_ATTR_DEFAULT_ID
SG_ATTR_IPHONE_ID = _PSProlibProxy.SG_ATTR_IPHONE_ID
SG_ATTR_ANDROID_ID = _PSProlibProxy.SG_ATTR_ANDROID_ID
SG_ATTR_BLACKBERRY_ID = _PSProlibProxy.SG_ATTR_BLACKBERRY_ID
SG_ATTR_ETHERNET_ID = _PSProlibProxy.SG_ATTR_ETHERNET_ID
SG_ATTR_HOSTNAME_ID = _PSProlibProxy.SG_ATTR_HOSTNAME_ID
SG_ATTR_IPADDRESS_ID = _PSProlibProxy.SG_ATTR_IPADDRESS_ID
SG_ATTR_USERNAME_ID = _PSProlibProxy.SG_ATTR_USERNAME_ID
SG_ATTR_COUNTRY_ID = _PSProlibProxy.SG_ATTR_COUNTRY_ID
SG_ATTR_INET6_ID = _PSProlibProxy.SG_ATTR_INET6_ID
SG_ATTR_VSN_ID = _PSProlibProxy.SG_ATTR_VSN_ID
SG_ATTR_VENDOR_ID = _PSProlibProxy.SG_ATTR_VENDOR_ID
SG_ATTR_ANY_ID = _PSProlibProxy.SG_ATTR_ANY_ID
SG_ATTR_HOSTID_ID = _PSProlibProxy.SG_ATTR_HOSTID_ID
SG_ATTR_MACINTOSH_ID = _PSProlibProxy.SG_ATTR_MACINTOSH_ID
SG_ATTR_METERED_ID = _PSProlibProxy.SG_ATTR_METERED_ID
SG_ATTR_OS_ID = _PSProlibProxy.SG_ATTR_OS_ID
SG_ATTR_COMPOSITE_ID = _PSProlibProxy.SG_ATTR_COMPOSITE_ID
SG_ATTR_LOGFILE_PATH = _PSProlibProxy.SG_ATTR_LOGFILE_PATH
SG_ATTR_DISALLOW_IDTYPE = _PSProlibProxy.SG_ATTR_DISALLOW_IDTYPE
SG_ATTR_DISALLOW_ALL_IDTYPE = _PSProlibProxy.SG_ATTR_DISALLOW_ALL_IDTYPE
SG_ATTR_ALLOW_IDTYPE = _PSProlibProxy.SG_ATTR_ALLOW_IDTYPE
SG_ATTR_ALLOW_ALL_IDTYPE = _PSProlibProxy.SG_ATTR_ALLOW_ALL_IDTYPE
SG_ATTR_LICENSETYPE = _PSProlibProxy.SG_ATTR_LICENSETYPE
SG_ATTR_VENDOR_ROUTINE = _PSProlibProxy.SG_ATTR_VENDOR_ROUTINE
SG_ATTR_VENDOR_LIBRARY = _PSProlibProxy.SG_ATTR_VENDOR_LIBRARY
SG_ATTR_RELEASE = _PSProlibProxy.SG_ATTR_RELEASE
SG_ATTR_ARCHITECTURE = _PSProlibProxy.SG_ATTR_ARCHITECTURE
SG_ATTR_LANGUAGE = _PSProlibProxy.SG_ATTR_LANGUAGE
SG_ATTR_EXE_PATH = _PSProlibProxy.SG_ATTR_EXE_PATH
SG_ATTR_NULL = _PSProlibProxy.SG_ATTR_NULL
SG_ATTR_TCP_TIMEOUT = _PSProlibProxy.SG_ATTR_TCP_TIMEOUT
SG_ATTR_RETRY_INTERVAL = _PSProlibProxy.SG_ATTR_RETRY_INTERVAL
SG_ATTR_RETRY_COUNT = _PSProlibProxy.SG_ATTR_RETRY_COUNT
SG_ATTR_DISABLE_ALARM = _PSProlibProxy.SG_ATTR_DISABLE_ALARM
SG_ATTR_LICENSE_FILE = _PSProlibProxy.SG_ATTR_LICENSE_FILE
SG_ATTR_MAXIMUM_TIMEDIFF = _PSProlibProxy.SG_ATTR_MAXIMUM_TIMEDIFF
SG_ATTR_DISABLE_ENV = _PSProlibProxy.SG_ATTR_DISABLE_ENV
SG_ATTR_VENDOR_RECONNECT_EXIT = _PSProlibProxy.SG_ATTR_VENDOR_RECONNECT_EXIT
SG_ATTR_VENDOR_RECONNECT = _PSProlibProxy.SG_ATTR_VENDOR_RECONNECT
SG_ATTR_VENDOR_RECONNECT_COMPLETE = _PSProlibProxy.SG_ATTR_VENDOR_RECONNECT_COMPLETE
SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL = _PSProlibProxy.SG_ATTR_VENDOR_RECONNECT_CHECKOUT_FAIL
SG_ATTR_DATECHECK = _PSProlibProxy.SG_ATTR_DATECHECK
SG_ATTR_DISABLE_LANG = _PSProlibProxy.SG_ATTR_DISABLE_LANG
SG_ATTRTYPE_LEN = _PSProlibProxy.SG_ATTRTYPE_LEN
SG_SUCCESS = _PSProlibProxy.SG_SUCCESS
SG_AUTHORIZED = _PSProlibProxy.SG_AUTHORIZED
SG_TARGET_FILE_NOT_FOUND = _PSProlibProxy.SG_TARGET_FILE_NOT_FOUND
SG_NOT_AUTHORIZED_FOR_COMPONENT = _PSProlibProxy.SG_NOT_AUTHORIZED_FOR_COMPONENT
SG_NOT_AUTHORIZED_FOR_VERSION = _PSProlibProxy.SG_NOT_AUTHORIZED_FOR_VERSION
SG_COMPONENT_EXPIRED = _PSProlibProxy.SG_COMPONENT_EXPIRED
SG_CANT_CREATE_TARGET_FILE = _PSProlibProxy.SG_CANT_CREATE_TARGET_FILE
SG_CANT_GET_ID = _PSProlibProxy.SG_CANT_GET_ID
SG_INVALID_CERTIFICATE = _PSProlibProxy.SG_INVALID_CERTIFICATE
SG_INVALID_TARGET_INFORMATION = _PSProlibProxy.SG_INVALID_TARGET_INFORMATION
SG_NO_MORE_COMPONENTS_IN_FILE = _PSProlibProxy.SG_NO_MORE_COMPONENTS_IN_FILE
SG_NO_COMPONENT_MATCHING_ID = _PSProlibProxy.SG_NO_COMPONENT_MATCHING_ID
SG_COMPONENT_NAME_TOO_LONG = _PSProlibProxy.SG_COMPONENT_NAME_TOO_LONG
SG_CANT_WRITE_TO_TARGET_FILE = _PSProlibProxy.SG_CANT_WRITE_TO_TARGET_FILE
SG_CANT_READ_TARGET_FILE = _PSProlibProxy.SG_CANT_READ_TARGET_FILE
SG_INVALID_ID_LENGTH = _PSProlibProxy.SG_INVALID_ID_LENGTH
SG_CANT_CREATE_TEMPORARY_FILE = _PSProlibProxy.SG_CANT_CREATE_TEMPORARY_FILE
SG_CANT_OPEN_TEMPORARY_FILE = _PSProlibProxy.SG_CANT_OPEN_TEMPORARY_FILE
SG_CANT_DELETE_TARGET_FILE = _PSProlibProxy.SG_CANT_DELETE_TARGET_FILE
SG_CANT_RENAME_TARGET_FILE = _PSProlibProxy.SG_CANT_RENAME_TARGET_FILE
SG_CANT_READ_TEXT_FILE = _PSProlibProxy.SG_CANT_READ_TEXT_FILE
SG_CANT_WRITE_TEXT_FILE = _PSProlibProxy.SG_CANT_WRITE_TEXT_FILE
SG_CANT_DELETE_TEXT_FILE = _PSProlibProxy.SG_CANT_DELETE_TEXT_FILE
SG_CANT_RENAME_TEXT_FILE = _PSProlibProxy.SG_CANT_RENAME_TEXT_FILE
SG_TEXT_FILE_NOT_FOUND = _PSProlibProxy.SG_TEXT_FILE_NOT_FOUND
SG_NO_COMPONENT_FOUND_IN_FILE = _PSProlibProxy.SG_NO_COMPONENT_FOUND_IN_FILE
SG_NO_FREE_SLOTS = _PSProlibProxy.SG_NO_FREE_SLOTS
SG_INVALID_TIMEOUT = _PSProlibProxy.SG_INVALID_TIMEOUT
SG_VERSION_LENGTH_TOO_LONG = _PSProlibProxy.SG_VERSION_LENGTH_TOO_LONG
SG_IDTYPE_NOT_SUPPORTED = _PSProlibProxy.SG_IDTYPE_NOT_SUPPORTED
SG_BAD_LICENSETYPE = _PSProlibProxy.SG_BAD_LICENSETYPE
SG_ATTRTYPE_NOT_SUPPORTED = _PSProlibProxy.SG_ATTRTYPE_NOT_SUPPORTED
SG_ATTRTYPE_INVALID = _PSProlibProxy.SG_ATTRTYPE_INVALID
SG_CANT_CREATE_LOGFILE = _PSProlibProxy.SG_CANT_CREATE_LOGFILE
SG_LOGFILE_NOT_SET = _PSProlibProxy.SG_LOGFILE_NOT_SET
SG_INVALID_OPTION_FOR_LICENSETYPE = _PSProlibProxy.SG_INVALID_OPTION_FOR_LICENSETYPE
SG_NO_MORE_CLIENT_COMPONENTS = _PSProlibProxy.SG_NO_MORE_CLIENT_COMPONENTS
SG_NO_MORE_SERVER_COMPONENTS = _PSProlibProxy.SG_NO_MORE_SERVER_COMPONENTS
SG_INVALID_LICENSE_KEY = _PSProlibProxy.SG_INVALID_LICENSE_KEY
SG_VERSION_NOT_NUMERIC = _PSProlibProxy.SG_VERSION_NOT_NUMERIC
SG_NOT_A_CALLABLE_OBJECT = _PSProlibProxy.SG_NOT_A_CALLABLE_OBJECT
SG_SYSTEM_CLOCK_SET_BACK = _PSProlibProxy.SG_SYSTEM_CLOCK_SET_BACK
SG_NO_MORE_SERVER_DETAIL = _PSProlibProxy.SG_NO_MORE_SERVER_DETAIL
SG_INVALID_LICENSE_COUNT = _PSProlibProxy.SG_INVALID_LICENSE_COUNT
SG_SERVERNORESPOND = _PSProlibProxy.SG_SERVERNORESPOND
SG_BADCOMMUNICATION = _PSProlibProxy.SG_BADCOMMUNICATION
SG_INVALIDHOST = _PSProlibProxy.SG_INVALIDHOST
SG_BADCONNECT = _PSProlibProxy.SG_BADCONNECT
SG_BADREAD = _PSProlibProxy.SG_BADREAD
SG_BADWRITE = _PSProlibProxy.SG_BADWRITE
SG_MAXSERVERCONNECTIONS = _PSProlibProxy.SG_MAXSERVERCONNECTIONS
SG_LOSTCONNECT = _PSProlibProxy.SG_LOSTCONNECT
SG_ALL_LICENSES_IN_USE = _PSProlibProxy.SG_ALL_LICENSES_IN_USE
SG_NO_SUCH_COMPONENT = _PSProlibProxy.SG_NO_SUCH_COMPONENT
SG_NOT_LICENSED_FOR_VERSION = _PSProlibProxy.SG_NOT_LICENSED_FOR_VERSION
SG_ALREADY_CHECKED_OUT = _PSProlibProxy.SG_ALREADY_CHECKED_OUT
SG_NOT_CHECKED_OUT = _PSProlibProxy.SG_NOT_CHECKED_OUT
SG_TIMEDIFF_TOO_LARGE = _PSProlibProxy.SG_TIMEDIFF_TOO_LARGE
SG_COMPONENT_NOT_AVAILABLE = _PSProlibProxy.SG_COMPONENT_NOT_AVAILABLE
SG_COMPONENT_ALREADY_ISSUED = _PSProlibProxy.SG_COMPONENT_ALREADY_ISSUED
SG_BAD_PASSWORD = _PSProlibProxy.SG_BAD_PASSWORD
SG_CANT_QUERY_SQLDB = _PSProlibProxy.SG_CANT_QUERY_SQLDB
SG_CANT_CONNECT_TO_SQLDB = _PSProlibProxy.SG_CANT_CONNECT_TO_SQLDB
SG_WRONG_SERVER = _PSProlibProxy.SG_WRONG_SERVER
SG_REJECTED = _PSProlibProxy.SG_REJECTED
SG_NOLOG = _PSProlibProxy.SG_NOLOG
SG_UNKNOWN_ERROR = _PSProlibProxy.SG_UNKNOWN_ERROR

def sgGenerateDate(*args):
  return _PSProlibProxy.sgGenerateDate(*args)
sgGenerateDate = _PSProlibProxy.sgGenerateDate

def sgExtractComponent(*args):
  return _PSProlibProxy.sgExtractComponent(*args)
sgExtractComponent = _PSProlibProxy.sgExtractComponent

def sgEnableComponent(*args):
  return _PSProlibProxy.sgEnableComponent(*args)
sgEnableComponent = _PSProlibProxy.sgEnableComponent

def sgDisableComponent(*args):
  return _PSProlibProxy.sgDisableComponent(*args)
sgDisableComponent = _PSProlibProxy.sgDisableComponent

def sgEnableAllComponents(*args):
  return _PSProlibProxy.sgEnableAllComponents(*args)
sgEnableAllComponents = _PSProlibProxy.sgEnableAllComponents

def sgValidateComponent(*args):
  return _PSProlibProxy.sgValidateComponent(*args)
sgValidateComponent = _PSProlibProxy.sgValidateComponent

def sgAuthorized(*args):
  return _PSProlibProxy.sgAuthorized(*args)
sgAuthorized = _PSProlibProxy.sgAuthorized

def sgExpireDays(*args):
  return _PSProlibProxy.sgExpireDays(*args)
sgExpireDays = _PSProlibProxy.sgExpireDays

def sgGetLastErrorString():
  return _PSProlibProxy.sgGetLastErrorString()
sgGetLastErrorString = _PSProlibProxy.sgGetLastErrorString

def sgConnect():
  return _PSProlibProxy.sgConnect()
sgConnect = _PSProlibProxy.sgConnect

def sgTest(*args):
  return _PSProlibProxy.sgTest(*args)
sgTest = _PSProlibProxy.sgTest

def sgCheckout(*args):
  return _PSProlibProxy.sgCheckout(*args)
sgCheckout = _PSProlibProxy.sgCheckout

def sgCheckin(*args):
  return _PSProlibProxy.sgCheckin(*args)
sgCheckin = _PSProlibProxy.sgCheckin

def sgTimer():
  return _PSProlibProxy.sgTimer()
sgTimer = _PSProlibProxy.sgTimer

def sgDisconnect():
  return _PSProlibProxy.sgDisconnect()
sgDisconnect = _PSProlibProxy.sgDisconnect

def sgPing():
  return _PSProlibProxy.sgPing()
sgPing = _PSProlibProxy.sgPing

def sgShutdown():
  return _PSProlibProxy.sgShutdown()
sgShutdown = _PSProlibProxy.sgShutdown

def sgRestart():
  return _PSProlibProxy.sgRestart()
sgRestart = _PSProlibProxy.sgRestart

def sgShowClient():
  return _PSProlibProxy.sgShowClient()
sgShowClient = _PSProlibProxy.sgShowClient

def sgShowServer():
  return _PSProlibProxy.sgShowServer()
sgShowServer = _PSProlibProxy.sgShowServer

def sgShowServerDetail():
  return _PSProlibProxy.sgShowServerDetail()
sgShowServerDetail = _PSProlibProxy.sgShowServerDetail

def sgSetAttrInt(*args):
  return _PSProlibProxy.sgSetAttrInt(*args)
sgSetAttrInt = _PSProlibProxy.sgSetAttrInt

def sgSetAttrStr(*args):
  return _PSProlibProxy.sgSetAttrStr(*args)
sgSetAttrStr = _PSProlibProxy.sgSetAttrStr

def sgSetAttrFnP(*args):
  return _PSProlibProxy.sgSetAttrFnP(*args)
sgSetAttrFnP = _PSProlibProxy.sgSetAttrFnP

def sgGetAttrStr(*args):
  return _PSProlibProxy.sgGetAttrStr(*args)
sgGetAttrStr = _PSProlibProxy.sgGetAttrStr

def sgGetAttrInt(*args):
  return _PSProlibProxy.sgGetAttrInt(*args)
sgGetAttrInt = _PSProlibProxy.sgGetAttrInt

def sgArc4(*args):
  return _PSProlibProxy.sgArc4(*args)
sgArc4 = _PSProlibProxy.sgArc4

def sgDash(*args):
  return _PSProlibProxy.sgDash(*args)
sgDash = _PSProlibProxy.sgDash

def sgEnableComponentLine(*args):
  return _PSProlibProxy.sgEnableComponentLine(*args)
sgEnableComponentLine = _PSProlibProxy.sgEnableComponentLine

def sgPaActivate(*args):
  return _PSProlibProxy.sgPaActivate(*args)
sgPaActivate = _PSProlibProxy.sgPaActivate

def sgPaGetInstallationCode(*args):
  return _PSProlibProxy.sgPaGetInstallationCode(*args)
sgPaGetInstallationCode = _PSProlibProxy.sgPaGetInstallationCode

def sgPaGetDemoActivationKeys(*args):
  return _PSProlibProxy.sgPaGetDemoActivationKeys(*args)
sgPaGetDemoActivationKeys = _PSProlibProxy.sgPaGetDemoActivationKeys

def sgPaGetPaidActivationKeys(*args):
  return _PSProlibProxy.sgPaGetPaidActivationKeys(*args)
sgPaGetPaidActivationKeys = _PSProlibProxy.sgPaGetPaidActivationKeys

def sgPaAssembleKeys(*args):
  return _PSProlibProxy.sgPaAssembleKeys(*args)
sgPaAssembleKeys = _PSProlibProxy.sgPaAssembleKeys

def sgPaDecodeKey(*args):
  return _PSProlibProxy.sgPaDecodeKey(*args)
sgPaDecodeKey = _PSProlibProxy.sgPaDecodeKey

def sgPaShutdown(*args):
  return _PSProlibProxy.sgPaShutdown(*args)
sgPaShutdown = _PSProlibProxy.sgPaShutdown

def sgPaRestart(*args):
  return _PSProlibProxy.sgPaRestart(*args)
sgPaRestart = _PSProlibProxy.sgPaRestart

def sgPaShowlog(*args):
  return _PSProlibProxy.sgPaShowlog(*args)
sgPaShowlog = _PSProlibProxy.sgPaShowlog
# This file is compatible with both classic and new-style classes.


