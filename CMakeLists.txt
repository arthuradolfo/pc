set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT(compilador)
FIND_PACKAGE(FLEX REQUIRED)
FIND_PACKAGE(BISON REQUIRED)
FLEX_TARGET(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)
BISON_TARGET(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c VERBOSE parser.output)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR}/src/)
ADD_EXECUTABLE(main
  ${FLEX_scanner_OUTPUTS}
  ${BISON_parser_OUTPUTS}
  src/main.c
  src/cc_misc.c
  src/cc_gv.c
  src/cc_dict.c
  src/cc_list.c
  src/cc_tree.c
  src/symbols_table.c
  src/syntax_tree.c
  src/semantics.c
  src/tac.c
  src/execution.c
  src/optimization.c
)
TARGET_LINK_LIBRARIES(main ${FLEX_LIBRARIES} m)

ADD_EXECUTABLE(cc_dict_main_example src/cc_dict.c src/cc_dict_main_example.c)

ENABLE_TESTING()
SET(i 0)
FILE(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(GLOB tests "tests/e*/*tesh")
LIST(SORT tests)
FOREACH(file ${tests})
  MATH(EXPR i ${i}+1)
  STRING(REGEX REPLACE "^.*/tests/" "" etapa ${file})
  STRING(REGEX REPLACE "/.*$" "" etapa ${etapa})
  STRING(REGEX REPLACE ".*/" "" testname ${file})
  STRING(REGEX REPLACE ".tesh$" "" testname ${testname})
  ADD_TEST(${etapa}_${testname} perl -I ./tests/scripts ./tests/scripts/tesh ${file})
ENDFOREACH()

OPTION(ETAPA_1 "The Etapa 1 compilation" OFF)
OPTION(ETAPA_2 "The Etapa 2 compilation" OFF)
OPTION(ETAPA_3 "The Etapa 3 compilation" OFF)
OPTION(ETAPA_4 "The Etapa 4 compilation" OFF)
OPTION(ETAPA_5 "The Etapa 5 compilation" OFF)
OPTION(ETAPA_6 "The Etapa 6 compilation" OFF)
OPTION(ETAPA_7 "The Etapa 7 compilation" ON)
OPTION(DEBUG "Enables debug-logging" OFF)
OPTION(RBSS_INIT "Custom init for rbss" OFF)

IF(ETAPA_1)
  add_definitions(-DAVALIACAO_ETAPA_1=1)
ELSEIF(ETAPA_2)
  add_definitions(-DAVALIACAO_ETAPA_2=1)
ELSEIF(ETAPA_3)
  add_definitions(-DAVALIACAO_ETAPA_3=1)
ELSEIF(ETAPA_4)
  add_definitions(-DAVALIACAO_ETAPA_4=1)
ELSEIF(ETAPA_5)
  add_definitions(-DAVALIACAO_ETAPA_5=1)
ELSEIF(ETAPA_6)
  add_definitions(-DAVALIACAO_ETAPA_6=1)
ELSEIF(ETAPA_7)
  add_definitions(-DAVALIACAO_ETAPA_7=1)
ENDIF(ETAPA_1)

IF(DEBUG)
 add_definitions(-DDEBUG=1)
ENDIF(DEBUG)

IF(RBSS_INIT)
  add_definitions(-DRBSS_INIT=1)
ENDIF(RBSS_INIT)

IF(O2)
    add_definitions(-DO2=1)
ELSEIF(O1)
    add_definitions(-DO1=1)
ELSE()
    add_definitions(-DO0=1)
ENDIF(O2)

IF(OPTM_TST)
    add_definitions(-DOPTM_TST=1)
ENDIF(OPTM_TST)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   message(STATUS "Setting build type to 'Debug' as none was specified.")
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()
