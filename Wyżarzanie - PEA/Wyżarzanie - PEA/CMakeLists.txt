# CMakeList.txt: projekt CMake dla elementu Wyżarzanie - PEA, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
<<<<<<< HEAD
add_executable (CMakeTarget "Wyżarzanie - PEA.cpp" "Wyżarzanie - PEA.h" "KomivoyagerLocation.cpp" "KomivoyagerLocation.h" "Mensuration.cpp" "Mensuration.h" "AS_Alg.cpp" "AS_Alg.h" )
=======
add_executable (CMakeTarget "Wyżarzanie - PEA.cpp" "Wyżarzanie - PEA.h" "KomivoyagerLocation.cpp" "KomivoyagerLocation.h" "Mensuration.cpp" "Mensuration.h" "AS_Alg.cpp" "AS_Alg.h")
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
