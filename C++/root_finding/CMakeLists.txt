#Name: Alex Choi
#last edited: Nov 2024
#cmake config for newton_root_templatized.cpp

cmake_minimum_required( VERSION 3.20 )
project( newton_root_templatized VERSION 1.0 )

message( "Using sources: complex_newton.cpp" )
add_executable( newton_root_templatized )
target_sources( newton_root_templatized PRIVATE newton_root_templatized.cpp )

target_compile_features( newton_root_templatized PRIVATE cxx_std_17 )
install( TARGETS newton_root_templatized DESTINATION . )