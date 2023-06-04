# CMakeList.txt : CMake project for MSFSConnect, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MSFSConnect")

# Add source files and include dir
file( GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp )
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add MSFS SDK
include_directories( "C:/MSFS SDK/SimConnect SDK/include" )
link_directories( "C:/MSFS SDK/SimConnect SDK/lib" )

# Add source to this project's executable.
add_executable (MSFSConnect ${SRC_FILES})

# Link
target_link_libraries( MSFSConnect "SimConnect")

# Copy DLL
add_custom_command(TARGET MyTest MSFSConnect                # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different           # which executes "cmake - E copy_if_different..."
        "C:/MSFS SDK/SimConnect SDK/lib/SimConnect.dll"     # <--this is in-file
        $<TARGET_FILE_DIR:MSFSConnect>)                     # <--this is out-file path

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MSFSConnect PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
