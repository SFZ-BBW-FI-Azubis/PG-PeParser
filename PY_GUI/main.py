#Paul stinkt
import ctypes
class PEParserBase(ctypes.Structure):
    _fields_ = [("hFile", ctypes.c_void_p),
        ("dwFileSize", ctypes.c_ulong),
        ("bytes", ctypes.c_ulong),
        ("fileBuffer",ctypes.c_void_p)]
class PEHEADER(ctypes.Structure):
    xc = 0
def testWrapper(peParserBase):
    print("Hallo welt")
pEParserBase = PEParserBase()
print("hallo welt")
_test = ctypes.CDLL('PeParserPythonWrapper.dll')
_test.test.argtypes = [ctypes.POINTER(PEParserBase)]
_test.test.restype = PEParserBase
result = _test.test(ctypes.byref(pEParserBase))
print(result.bytes)
x = ctypes.c_int.in_dll(_test, "x")
print(x);
testWrapper
#print(int(_test.test(None)))