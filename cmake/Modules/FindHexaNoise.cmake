IF(HEXANOISE_LIBRARY AND HEXANOISE_INCLUDE_DIR)
  # in cache already
  SET(HEXANOISE_FIND_QUIETLY TRUE)
ENDIF(HEXANOISE_LIBRARY AND HEXANOISE_INCLUDE_DIR)

IF(NOT HEXANOISE_INCLUDE_DIR)
    find_path(HEXANOISE_INCLUDE_DIR
      hexanoise/generator_i.hpp
      "${CMAKE_SOURCE_DIR}/../hexanoise/")
ENDIF()

IF(NOT HEXANOISE_LIBRARY)
    find_library(HEXANOISE_LIBRARY hexanoise-s
      "${CMAKE_SOURCE_DIR}/../hexanoise/build/hexanoise"
      "${CMAKE_SOURCE_DIR}/../hexanoise-build/hexanoise"
      hexanoise)
ENDIF()


IF(HEXANOISE_LIBRARY AND HEXANOISE_INCLUDE_DIR)
  SET(HEXANOISE_FOUND "YES")
  IF(NOT HEXANOISE_FIND_QUIETLY)
    MESSAGE(STATUS "Found HexaNoise library: ${HEXANOISE_LIBRARY}")
  ENDIF(NOT HEXANOISE_FIND_QUIETLY)
ELSE(HEXANOISE_LIBRARY AND HEXANOISE_INCLUDE_DIR)
  IF(NOT HEXANOISE_FIND_QUIETLY)
    MESSAGE(STATUS "Warning: Unable to find HexaNoise! Get it from http://github.com/Nocte-/hexanoise")
  ENDIF(NOT HEXANOISE_FIND_QUIETLY)
ENDIF(HEXANOISE_LIBRARY AND HEXANOISE_INCLUDE_DIR)

