# CMakeList.txt: projekt CMake dla elementu PEA - Komivoyager, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (CMakeTarget "PEA - Komivoyager.cpp" "PEA - Komivoyager.h" "Bruteforce.cpp" "Bruteforce.h" "KomivoyagerLocation.h" "KomivoyagerLocation.cpp" "Mensuration.h" "Mensuration.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
