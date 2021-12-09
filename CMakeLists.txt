cmake_minimum_required(VERSION 3.10)
project(emu C)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_C_STANDARD 90)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-int -Ofast" CACHE STRING "Set C Compiler Flags" FORCE)

set(
  SRC
  "entry.c"
  "bogus.c"
  "memop.c"
  "tab.c"
)

add_executable(emu ${SRC})