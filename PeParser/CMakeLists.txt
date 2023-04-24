# CMakeList.txt: CMake-Projekt für "PeParser". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)
#set(CMAKE_CXX_FLAG "-O1")
# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (PeParser "PeParser.cpp" "ExplicitTemplateInstances.h")

add_library(PeParserPythonWrapper SHARED "Python_wrapper/Python_wrapper.cpp" "ExplicitTemplateInstances.h")

add_library(PEParserCPPDLL SHARED "PEParserDLL/PEParserCPPDLL.cpp")

add_library(PEParserCDLL SHARED "PEParserDLL/PEParserCDLL.cpp")
target_link_libraries(PEParserCDLL "${CMAKE_BINARY_DIR}/PeParser/PEParserCPPDLL.lib")
add_dependencies(PEParserCDLL PEParserCPPDLL)

add_executable (TestCPP
				"PEParserDLL/Test.cpp"  
				"ExplicitTemplateInstances.h")
target_link_libraries(TestCPP "${CMAKE_BINARY_DIR}/PeParser/PEParserCPPDLL.lib" "${CMAKE_BINARY_DIR}/PeParser/PEParserCDLL.lib")
add_dependencies(TestCPP PEParserCPPDLL)

set_property(TARGET PeParserPythonWrapper PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_custom_command(TARGET PeParserPythonWrapper POST_BUILD COMMAND powershell -Command copy "${CMAKE_BINARY_DIR}/PeParser/PeParserPythonWrapper.dll" "${CMAKE_SOURCE_DIR}/PY_GUI")
add_custom_command(TARGET PeParserPythonWrapper PRE_BUILD COMMAND powershell -Command ls)
set_target_properties(PeParserPythonWrapper PROPERTIES LINKER_LANGUAGE CXX)
# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
