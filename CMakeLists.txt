cmake_minimum_required(VERSION 3.13)
project(PathFinder VERSION 0.1)

add_executable(PathFinder "")

add_subdirectory(src/)
add_subdirectory(inc/)

#TESTING should only be set to true if you are trying to perform unit tests
#  as it creates a unit test specific executable
#To create the actual executable, make sure TESTING is set to false
if(TESTING)
   add_subdirectory(test/)
   
   
   # -----------  GOOGLETEST  ---------------
   # Download and unpack googletest at configure time
   configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
   execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
     RESULT_VARIABLE result
     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
   if(result)
     message(FATAL_ERROR "CMake step for googletest failed: ${result}")
   endif(result)
   execute_process(COMMAND ${CMAKE_COMMAND} --build .
     RESULT_VARIABLE result
     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
   if(result)
     message(FATAL_ERROR "Build step for googletest failed: ${result}")
   endif(result)

   # Prevent overriding the parent project's compiler/linker
   # settings on Windows
   set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

   # Add googletest directly to our build. This defines
   # the gtest and gtest_main targets.
   add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                    EXCLUDE_FROM_ALL)

   # The gtest/gtest_main targets carry header search path
   # dependencies automatically when using CMake 2.8.11 or
   # later. Otherwise we have to add them here ourselves.
   if (CMAKE_VERSION VERSION_LESS 2.8.11)
     include_directories("${gtest_SOURCE_DIR}/include")
   endif()
   # ---------  GOOGLETEST END  -------------
   
   target_link_libraries(PathFinder gtest_main)
endif(TESTING)

include_directories(inc/)

