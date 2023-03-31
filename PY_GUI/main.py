import ctypes
import DataStructures
import FunctionWrapper

pEParserBase = DataStructures.PEParserBase()
pEHEADER = DataStructures.PEHEADER()
functionWrapper = FunctionWrapper.FunctionWraper()

_test = ctypes.CDLL('./PeParserPythonWrapper.dll')

pPEParserBase = functionWrapper.testWrapper(pEParserBase, _test)
pPEHEADER = functionWrapper.test2Wrapper(pEHEADER, _test)

print(functionWrapper.testWrapper(pEParserBase, _test).contents.bytes)
print(hex(ctypes.addressof(pEParserBase)), pEParserBase.bytes)
print(hex(ctypes.addressof(pPEParserBase.contents)), pEParserBase.bytes)