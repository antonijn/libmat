cmake_minimum_required (VERSION 2.8.11)
project (mat)

add_library (mat INTERFACE)
install (FILES include/mat/mat.h include/mat/vec.h include/mat/misc.h DESTINATION include/mat)
