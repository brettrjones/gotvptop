# Install script for directory: F:/GoTvCode/DependLibs/libp8platform

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/p8-platform")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/GoTvCode/DependLibs/libp8platform/Debug/p8-platform.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/GoTvCode/DependLibs/libp8platform/Release/p8-platform.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/GoTvCode/DependLibs/libp8platform/MinSizeRel/p8-platform.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/GoTvCode/DependLibs/libp8platform/RelWithDebInfo/p8-platform.lib")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/p8-platform" TYPE FILE FILES "F:/GoTvCode/DependLibs/libp8platform/src/os.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/p8-platform/windows" TYPE FILE FILES
    "F:/GoTvCode/DependLibs/libp8platform/src/windows/dlfcn-win32.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/windows/os-socket.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/windows/os-threads.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/windows/os-types.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/p8-platform/sockets" TYPE FILE FILES
    "F:/GoTvCode/DependLibs/libp8platform/src/sockets/cdevsocket.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/sockets/socket.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/sockets/tcp.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/p8-platform/threads" TYPE FILE FILES
    "F:/GoTvCode/DependLibs/libp8platform/src/threads/atomics.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/threads/mutex.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/threads/threads.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/p8-platform/util" TYPE FILE FILES
    "F:/GoTvCode/DependLibs/libp8platform/src/util/atomic.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/util/buffer.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/util/StringUtils.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/util/StdString.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/util/timeutils.h"
    "F:/GoTvCode/DependLibs/libp8platform/src/util/util.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/p8-platform" TYPE FILE FILES "F:/GoTvCode/DependLibs/libp8platform/p8-platform-config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "F:/GoTvCode/DependLibs/libp8platform/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
