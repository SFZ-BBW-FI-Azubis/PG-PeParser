import ctypes
#	class PEParserBase;
#	class PEHEADER;
#	class PEParser;
class PEParserBase(ctypes.Structure):
    _fields_ = [("hFile", ctypes.c_void_p),
        ("dwFileSize", ctypes.c_ulong),
        ("bytes", ctypes.c_ulong),
        ("fileBuffer",ctypes.c_void_p)]
class PEHEADER(ctypes.Structure):
    _fields_ = [("test", PEParserBase)]