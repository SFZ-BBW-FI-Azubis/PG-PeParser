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
        _instanceDLL[4].argtypes = [ctypes.POINTER(DataStructures.PEParserBase)]
        _instanceDLL[4].restype = ctypes.POINTER(DataStructures.PEParserBase)
        return _instanceDLL[4](ctypes.byref(peHEADER))