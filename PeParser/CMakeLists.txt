# CMakeList.txt: CMake-Projekt für "PeParser". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (PeParser "PeParser.cpp" "PeParser.h" "DataStructures.h" "Templates.h" "Concepts.h" "Include.h" "Offsets.h")
add_executable (PeParserPythonWrapper "Python_wrapper.h")
# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
