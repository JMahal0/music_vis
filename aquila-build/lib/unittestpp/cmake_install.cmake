# Install script for directory: /home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ubuntu/Desktop/music_vis/aquila-build/lib/unittestpp/libUnitTest++.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/XmlTestReporter.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/UnitTestPP.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/UnitTest++.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TimeHelpers.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TimeConstraint.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestSuite.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestRunner.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestResults.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestReporterStdout.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestReporter.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestMacros.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestList.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/TestDetails.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/Test.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/ReportAssertImpl.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/ReportAssert.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/MemoryOutStream.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/HelperMacros.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/ExecuteTest.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/ExceptionMacros.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/DeferredTestResult.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/DeferredTestReporter.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/CurrentTest.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/Config.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/CompositeTestReporter.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/Checks.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/CheckMacros.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/AssertException.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Posix" TYPE FILE FILES
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/Posix/TimeHelpers.h"
    "/home/ubuntu/Desktop/music_vis/aquila-src/lib/unittestpp/UnitTest++/Posix/SignalTranslator.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

