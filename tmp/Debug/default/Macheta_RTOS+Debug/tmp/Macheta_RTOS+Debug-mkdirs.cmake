# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug")
  file(MAKE_DIRECTORY "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug")
endif()
file(MAKE_DIRECTORY
  "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/1"
  "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug"
  "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug/tmp"
  "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug/src/Macheta_RTOS+Debug-stamp"
  "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug/src"
  "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug/src/Macheta_RTOS+Debug-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug/src/Macheta_RTOS+Debug-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/admin/Desktop/RTOS/tmp/Debug/default/Macheta_RTOS+Debug/src/Macheta_RTOS+Debug-stamp${cfgdir}") # cfgdir has leading slash
endif()
