
add_executable(recovery.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/recovery.cpp)
target_include_directories(recovery.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(recovery.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/recovery")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/abi/recovery.abi" "${CMAKE_CURRENT_SOURCE_DIR}/bin/recovery/recovery.abi" COPYONLY)

include_directories(${EOSIO_ROOT}/include)
