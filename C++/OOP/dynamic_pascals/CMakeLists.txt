#Name: Alex Choi
#Last edited: October 2024
#Cmake config for dynamic_pascals_triangle.cpp

cmake_minimum_required( VERSION 3.20 )
project( dynamic_pascals_triangle VERSION 1.0 )

message( "Using sources: dynamic_pascals_triangle.cpp" )
add_executable( dynamic_pascals_triangle )
target_sources( dynamic_pascals_triangle PRIVATE dynamic_pascals_triangle.cpp )

target_compile_features( dynamic_pascals_triangle PRIVATE cxx_std_17 )
install( TARGETS dynamic_pascals_triangle DESTINATION . )

