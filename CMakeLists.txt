cmake_minimum_required(VERSION 2.6)

project(bluld CXX)

find_package(PkgConfig REQUIRED)
pkg_search_module(HIDAPI REQUIRED hidapi-libusb)

add_definitions(-Wall -Werror -Wextra)

include_directories(
  ${HIDAPI_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/blinkstick-userspace-led-daemon/include
)

add_executable(bluld
  blinkstick-userspace-led-daemon/src/BlinkStick.cpp
  blinkstick-userspace-led-daemon/src/LEDBinding.cpp
  blinkstick-userspace-led-daemon/src/LEDBindingRegistrationException.cpp
  blinkstick-userspace-led-daemon/src/RGBColor.cpp
  blinkstick-userspace-led-daemon/src/main.cpp
)
target_link_libraries(bluld ${HIDAPI_LIBRARIES})

install(TARGETS bluld DESTINATION sbin/)
