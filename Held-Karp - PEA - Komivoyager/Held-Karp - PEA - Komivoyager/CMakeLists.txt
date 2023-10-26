# CMakeList.txt: projekt CMake dla elementu Held-Karp - PEA - Komivoyager, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (CMakeTarget "Held-Karp - PEA - Komivoyager.cpp" "Held-Karp - PEA - Komivoyager.h" "KomivoyagerLocation.cpp" "KomivoyagerLocation.h" "Mensuration.cpp" "Mensuration.h" "HeldKarpAlg.cpp" "HeldKarpAlg.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
