#Name: Alex Choi
#Last Edited: October 20, 2024
# CMake config for ordered_linked_list.cpp

cmake_minimum_required( VERSION 3.20 )
project( ordered_linked_list VERSION 1.0 )

message( "Using sources: linkedptr.cpp" )
add_executable( ordered_linked_list )
target_sources( ordered_linked_list PRIVATE ordered_linked_list.cpp )

target_compile_features( ordered_linked_list PRIVATE cxx_std_17 )
install( TARGETS ordered_linked_list DESTINATION . )

