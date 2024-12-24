cmake_minimum_required(VERSION 3.15)
project(libcds VERSION 1.0 LANGUAGES CXX)

# Define el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Encuentra todos los archivos fuente en src
file(GLOB_RECURSE SOURCES
    src/static/*.cpp
    src/static/bitsequence/*.cpp
    src/static/coders/*.cpp
    src/static/mapper/*.cpp
    src/static/permutation/*.cpp
    src/static/sequence/*.cpp
    src/static/suffixtree/*.cpp
    src/utils/*.cpp
    src/slp/*.cpp
    src/slp/BinRel/*.cpp
    src/slp/RePair/*.cpp
    src/slp/Sampling/*.cpp
    src/slp/Utils/*.cpp
)

# Asegúrate de que se encuentren archivos fuente
if(!SOURCES)
    # message(STATUS "Archivos fuente encontrados: ${SOURCES}")
# else()
    message(FATAL_ERROR "No se encontraron archivos fuente en src/")
endif()

# Define la biblioteca estática "cds"
add_library(cds STATIC ${SOURCES})

# Configura directorios de encabezados para la biblioteca
target_include_directories(cds PUBLIC include/static/bitsequence)
target_include_directories(cds PUBLIC include/static/coders)
target_include_directories(cds PUBLIC include/static/mapper)
target_include_directories(cds PUBLIC include/static/permutation)
target_include_directories(cds PUBLIC include/static/sequence)
target_include_directories(cds PUBLIC include/static/suffixtree)
target_include_directories(cds PUBLIC include/utils)
target_include_directories(cds PUBLIC include/slp)

# Configuración de instalación
install(TARGETS cds ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Habilita pruebas si es necesario
option(ENABLE_TESTS "Build tests" ON)
if(ENABLE_TESTS)
    enable_testing()
    file(GLOB_RECURSE TEST_SOURCES test/*.cpp)

    # Crea ejecutables para cada prueba
    foreach(TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        target_link_libraries(${TEST_NAME} cds)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()
