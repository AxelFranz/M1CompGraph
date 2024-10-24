cmake_minimum_required(VERSION 3.0)

project(TP_Prog_Graphique_3D LANGUAGES CXX)

set (TP_SHADERS_PATH $ENV{HOME} CACHE PATH "Path where to put GLSL shaders ...")
set (SYS_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data)
set (TP_SHADERS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

add_definitions("-DDEF_SHADERS_PATH=${TP_SHADERS_PATH}")

macro(compile)
  add_executable(${ARGV0} ${ARGV0}.cpp)
  target_link_libraries(${ARGV0} easycppogl)
endmacro()

set( tp_list
    tuto_1
    tp1
    tuto2_1
    tuto2_2
    tp6
    tuto2_3
    tuto2_4
    tuto3
    tuto4
    tp3
    tp5
)

foreach( exec_tp ${tp_list})
	compile(${exec_tp})
endforeach()

# nice vs solution
set_target_properties(${tp_list} PROPERTIES FOLDER TP_Prog_Graphique_3D)
