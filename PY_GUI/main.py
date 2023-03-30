#Paul stinkt
import ctypes
#DataStructures.py
class PEParserBase(ctypes.Structure):
    _fields_ = [("hFile", ctypes.c_void_p),
        ("dwFileSize", ctypes.c_ulong),
        ("bytes", ctypes.c_ulong),
        ("fileBuffer",ctypes.c_void_p)]
class PEHEADER(ctypes.Structure):
    xc = 0
#FunctionWrapper.py
def testWrapper(peParserBase, _instanceDLL):
    _instanceDLL.test.argtypes = [ctypes.POINTER(PEParserBase)]
    _instanceDLL.test.restype = PEParserBase
    return _instanceDLL.test(ctypes.byref(pEParserBase))

pEParserBase = PEParserBase()
print("hallo welt")
_test = ctypes.CDLL('PeParserPythonWrapper.dll')

#x = ctypes.c_int.in_dll(_test, "x")
#print(x);
#id should be the same, but it is not
print(id(testWrapper(pEParserBase, _test)))
print(id(pEParserBase))