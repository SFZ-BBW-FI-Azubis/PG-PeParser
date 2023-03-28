#Paul stinkt
import ctypes
print("hallo welt")
_test = ctypes.CDLL('PeParserPythonWrapper.dll')
_test.test()
#print(int(_test.test(None)))
