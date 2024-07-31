set(GOPATH "${CMAKE_CURRENT_BINARY_DIR}/go")
file(MAKE_DIRECTORY ${GOPATH})

function(ExternalGoProject_Add TARG)
  add_custom_target(${TARG} env GOPATH=${GOPATH} ${CMAKE_Go_COMPILER} get ${ARGN})
endfunction(ExternalGoProject_Add)

function(add_go_executable NAME)
  get_filename_component(CMAKE_C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME)
  get_filename_component(CMAKE_CXX_COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
  file(GLOB GO_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.go")
  if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT_DIR}/.timestamp
      COMMAND set "GOPATH=\"${GOPATH}\""
      COMMAND set "CGO_ENABLED=${CGO_ENABLED}"
      COMMAND ${CMAKE_Go_COMPILER} env -w CC=${CMAKE_C_COMPILER_NAME}
      COMMAND ${CMAKE_Go_COMPILER} env -w CXX=${CMAKE_CXX_COMPILER_NAME}
      COMMAND ${CMAKE_Go_COMPILER} build ${BUILD_MODE}
      -o "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}"
      ${CMAKE_GO_FLAGS} ${GO_SOURCE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
  else ()
    add_custom_command(OUTPUT ${OUTPUT_DIR}/.timestamp
      COMMAND env GOPATH=${GOPATH} ${CMAKE_Go_COMPILER} build
      -o "${CMAKE_CURRENT_BINARY_DIR}/${NAME}"
      ${CMAKE_GO_FLAGS} ${GO_SOURCE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
  endif ()
  add_custom_target(${NAME} ALL DEPENDS ${OUTPUT_DIR}/.timestamp ${ARGN})
  install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${NAME} DESTINATION bin)
endfunction(add_go_executable)

function(ADD_GO_LIBRARY NAME BUILD_TYPE)
  if (BUILD_TYPE STREQUAL "STATIC")
    set(BUILD_MODE -buildmode=c-archive)
    set(LIB_NAME "lib${NAME}.a")
  else ()
    set(BUILD_MODE -buildmode=c-shared)
    if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
      set(LIB_NAME "lib${NAME}.dylib")
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
      set(LIB_NAME "lib${NAME}.dll")
    else ()
      set(LIB_NAME "lib${NAME}.so")
    endif ()
  endif ()

  get_filename_component(CMAKE_C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME)
  get_filename_component(CMAKE_CXX_COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
  file(GLOB GO_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.go")
  if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT_DIR}/.timestamp
      COMMAND set "GOPATH=\"${GOPATH}\""
      COMMAND set "CGO_ENABLED=${CGO_ENABLED}"
      COMMAND ${CMAKE_Go_COMPILER} env -w CC=${CMAKE_C_COMPILER_NAME}
      COMMAND ${CMAKE_Go_COMPILER} env -w CXX=${CMAKE_CXX_COMPILER_NAME}
      COMMAND ${CMAKE_Go_COMPILER} build ${BUILD_MODE}
      -o "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}"
      ${CMAKE_GO_FLAGS} ${GO_SOURCE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
  else ()
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT_DIR}/.timestamp
      COMMAND env GOPATH=${GOPATH} ${CMAKE_Go_COMPILER} build ${BUILD_MODE}
      -o "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}"
      ${CMAKE_GO_FLAGS} ${GO_SOURCE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
  endif ()

  ADD_CUSTOM_TARGET(${NAME} ALL DEPENDS ${OUTPUT_DIR}/.timestamp ${ARGN})
  set_property(TARGET ${NAME} PROPERTY "type" ${BUILD_TYPE})

  if (NOT BUILD_TYPE STREQUAL "STATIC")
    install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME} DESTINATION bin)
  endif ()
endfunction(ADD_GO_LIBRARY)
