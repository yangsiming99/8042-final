# CMakeList.txt : CMake project for GIS, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GIS")

# Add source to this project's executable.
add_executable (GIS "GIS.cpp" "headers/GIS.h" "headers/GISRecord.h" "classes/GISRecord.cpp" "classes/NameIndex.cpp" "classes/CoordinateIndex.cpp" "classes/BufferPool.cpp" "classes/SystemManager.cpp" "classes/CommandProceessor.cpp" "headers/BufferPool.h" "headers/CommandProcessor.h" "headers/CoordinateIndex.h" "headers/NameIndex.h" "headers/Logger.h" "headers/SystemManager.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GIS PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
