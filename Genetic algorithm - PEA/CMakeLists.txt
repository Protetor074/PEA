# CMakeList.txt: projekt CMake dla elementu Genetic algorithm - PEA, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Genetic algorithm - PEA")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (CMakeTarget "Genetic algorithm - PEA.cpp" "Genetic algorithm - PEA.h"  "GenAlg.h" "GenAlg.cpp" "KomivoyagerLocation.h" "KomivoyagerLocation.cpp" "Mensuration.h" "Mensuration.cpp" "SimpleIni.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
