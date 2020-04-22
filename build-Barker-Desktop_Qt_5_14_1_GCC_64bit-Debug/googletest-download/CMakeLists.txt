cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "/home/esther/Escritorio/Informática Industrial/PROYECTO/Proyecto1/build-Barker-Desktop_Qt_5_14_1_GCC_64bit-Debug/googletest-src"
  BINARY_DIR        "/home/esther/Escritorio/Informática Industrial/PROYECTO/Proyecto1/build-Barker-Desktop_Qt_5_14_1_GCC_64bit-Debug/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
