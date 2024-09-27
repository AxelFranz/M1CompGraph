# Install script for directory: /home/axel/3D/easycppogl/easycppogl_src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/axel/3D/easycppogl/build/easycppogl_src/libeasycppogl_d.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/easycppogl" TYPE FILE FILES
    "/home/axel/3D/easycppogl/easycppogl_src/imconfig.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imgui.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imgui_impl_glfw.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imgui_impl_opengl3.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imgui_impl_opengl3_loader.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imgui_internal.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imstb_rectpack.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imstb_textedit.h"
    "/home/axel/3D/easycppogl/easycppogl_src/imstb_truetype.h"
    "/home/axel/3D/easycppogl/easycppogl_src/portable_file_dialogs.h"
    "/home/axel/3D/easycppogl/easycppogl_src/gl_eigen.h"
    "/home/axel/3D/easycppogl/easycppogl_src/ebo.h"
    "/home/axel/3D/easycppogl/easycppogl_src/vbo.h"
    "/home/axel/3D/easycppogl/easycppogl_src/vao.h"
    "/home/axel/3D/easycppogl/easycppogl_src/shader_program.h"
    "/home/axel/3D/easycppogl/easycppogl_src/transform_feedback.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texture.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texture1d.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texture2d.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texture3d.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texturecubemap.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texture1darray.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texture2darray.h"
    "/home/axel/3D/easycppogl/easycppogl_src/texturebuffer.h"
    "/home/axel/3D/easycppogl/easycppogl_src/fbo.h"
    "/home/axel/3D/easycppogl/easycppogl_src/camera.h"
    "/home/axel/3D/easycppogl/easycppogl_src/gl_viewer.h"
    "/home/axel/3D/easycppogl/easycppogl_src/mframe.h"
    "/home/axel/3D/easycppogl/easycppogl_src/boundingbox.h"
    "/home/axel/3D/easycppogl/easycppogl_src/material.h"
    "/home/axel/3D/easycppogl/easycppogl_src/scenegraph.h"
    "/home/axel/3D/easycppogl/easycppogl_src/mesh.h"
    "/home/axel/3D/easycppogl/easycppogl_src/mesh_assimp_importer.h"
    "/home/axel/3D/easycppogl/easycppogl_src/ubo.h"
    "/home/axel/3D/easycppogl/easycppogl_src/ssbo.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/easycppogl" TYPE DIRECTORY FILES "/home/axel/3D/easycppogl/GL" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/easycppogl" TYPE DIRECTORY FILES "/home/axel/3D/easycppogl/KHR" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl/easycppoglTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl/easycppoglTargets.cmake"
         "/home/axel/3D/easycppogl/build/easycppogl_src/CMakeFiles/Export/642b13b4a7ac1fb8a12fda35d4012234/easycppoglTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl/easycppoglTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl/easycppoglTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl" TYPE FILE FILES "/home/axel/3D/easycppogl/build/easycppogl_src/CMakeFiles/Export/642b13b4a7ac1fb8a12fda35d4012234/easycppoglTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl" TYPE FILE FILES "/home/axel/3D/easycppogl/build/easycppogl_src/CMakeFiles/Export/642b13b4a7ac1fb8a12fda35d4012234/easycppoglTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/easycppogl" TYPE FILE FILES
    "/home/axel/3D/easycppogl/build/easycppogl_src/easycppogl/easycppoglConfig.cmake"
    "/home/axel/3D/easycppogl/build/easycppogl_src/easycppogl/easycppoglConfigVersion.cmake"
    )
endif()

