cmake_minimum_required(VERSION 3.15)
project(libcds VERSION 1.0 LANGUAGES CXX)

# Define el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")



# Location of internal cmake modules
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/cmake)

# Guard against in-source builds and bad build-type strings
include(ConfigSafeGuards)

# find_package(benchmark 1.6)

# if (NOT benchmark_FOUND)
#     include(ConfigGBench)
# endif ()

# list(APPEND LIBS benchmark::benchmark benchmark::benchmark_main)

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
    src/slp/Samplings/*.cpp
    src/slp/Utils/*.cpp
)


include(InternalUtils)

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
target_include_directories(cds PUBLIC include/slp/BinRel)
target_include_directories(cds PUBLIC include/slp/RePair)
target_include_directories(cds PUBLIC include/slp/Samplings)
target_include_directories(cds PUBLIC include/slp/Utils)


# Build benchmarks
#TODO Verify these compilation flags\
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -fstrict-aliasing -DNDEBUG -march=native -fopenmp")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -ggdb -Ofast -fstrict-aliasing -march=native")

# Always link with libstdc++fs.a (std::filesystem) when using GCC 8.
# Note: This command makes sure that this option comes pretty late on the cmdline.
link_libraries("$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:-lstdc++fs>")
add_link_options(LINKER:--as-needed)


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


# Define un ejecutable para el benchmark de construcción del índice
# add_executable(build_indice benchmarks/build_indice.cpp)

# Vincula el ejecutable con las bibliotecas necesarias
# target_link_libraries(build_indice PRIVATE cds ${LIBS})

# Configura directorios de encabezados para el ejecutable
# target_include_directories(build_indice PRIVATE include)
