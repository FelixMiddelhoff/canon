add_executable(isobit_quickstart quickstart.cpp)
target_link_libraries(isobit_quickstart PRIVATE isobit::isobit)

add_executable(isobit_vecmat_example vecmat.cpp)
target_link_libraries(isobit_vecmat_example PRIVATE isobit::isobit)

add_executable(isobit_hash_determinism hash_determinism.cpp)
target_link_libraries(isobit_hash_determinism PRIVATE isobit::isobit)

# Plain C, to prove the C ABI (include/isobit/isobit.h) actually works
# without a C++ toolchain on the consumer side. The static lib itself is
# C++, so force the C++ linker even though this target's only source is C.
add_executable(isobit_c_abi_example c_abi.c)
target_link_libraries(isobit_c_abi_example PRIVATE isobit::isobit)
set_target_properties(isobit_c_abi_example PROPERTIES LINKER_LANGUAGE CXX)
