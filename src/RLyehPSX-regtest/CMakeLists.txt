add_executable(RLyehPSX-regtest
  regtest_host.cpp
)

target_link_libraries(RLyehPSX-regtest PRIVATE core common scmversion)

add_core_resources(RLyehPSX-regtest)