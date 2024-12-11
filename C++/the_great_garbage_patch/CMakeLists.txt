#Last updated: Dec 6, 24

cmake_minimum_required( VERSION 3.20 )
project( ocean VERSION 1.0 )

message( "Using sources: ocean.cpp" )
add_executable( ocean )
target_sources( ocean PRIVATE ocean.cpp )

target_compile_features( ocean PRIVATE cxx_std_23 )
install( TARGETS ocean DESTINATION . )

