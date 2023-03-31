import DataStructures
import ctypes
class FunctionWraper:
    #@classmethod
    def testWrapper(self, peParserBase, _instanceDLL):
        _instanceDLL.test.argtypes = [ctypes.POINTER(DataStructures.PEParserBase)]
        _instanceDLL.test.restype = ctypes.POINTER(DataStructures.PEParserBase)
        return _instanceDLL.test(ctypes.byref(peParserBase))
    #@classmethod
    def test2Wrapper(self, peHEADER, _instanceDLL):
        _instanceDLL.test2.argtypes = [ctypes.POINTER(DataStructures.PEHEADER)]
        _instanceDLL.test2.restype = ctypes.POINTER(DataStructures.PEHEADER)
        return _instanceDLL.test2(ctypes.byref(peHEADER))