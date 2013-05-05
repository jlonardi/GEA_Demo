cmake_minimum_required(VERSION 2.6)

project(GEA_Demo)

add_subdirectory(Demo)

IF ( MSVC )
	     MESSAGE ( STATUS "Setting MSVC MT switches")
	    SET (
        CMAKE_CXX_FLAGS_DEBUG
	          "/D_DEBUG /MTd /Zi  /Ob0 /Od /RTC1"
	          CACHE STRING "MSVC MT flags " FORCE
	      )
	          SET(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	 
	      SET (
	        CMAKE_CXX_FLAGS_RELEASE
	          "/MT /O2 /Ob2 /D NDEBUG"
	          CACHE STRING "MSVC MT flags " FORCE
	      )
	          SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
	 
	      SET (
	        CMAKE_CXX_FLAGS_MINSIZEREL
	          "/MT /O1 /Ob1 /D NDEBUG"
            CACHE STRING "MSVC MT flags " FORCE
	      )
	          SET(CMAKE_C_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL})
	 
	      SET (
	        CMAKE_CXX_FLAGS_RELWITHDEBINFO
	          "/MT /Zi /O2 /Ob1 /D NDEBUG"
	          CACHE STRING "MSVC MT flags " FORCE
	      )
	          SET(CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
	     
	      # Maybe future CMake versions will implement this
	      #SET (
	      #  CMAKE_CXX_FLAGS_RELEASE
	      #    "/RuntimeLibrary:MT ${CMAKE_CXX_FLAGS_RELEASE}"
	      #)
	    ENDIF ( MSVC )
	   
	    IF ( CMAKE_COMPILER_IS_GNUCXX )
	      MESSAGE ( STATUS "Setting GCC MT switches" )
	      SET (
	        CMAKE_CXX_FLAGS
	          "${CMAKE_CXX_FLAGS} -pthread"
	      )
	    ENDIF ( CMAKE_COMPILER_IS_GNUCXX )