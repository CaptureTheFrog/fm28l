cmake_minimum_required(VERSION 3.25)
project(fm28l C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# Specify the cross compiler
#SET(CMAKE_C_COMPILER /usr/local/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc)
#SET(CMAKE_CXX_COMPILER /usr/local/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(LIBADWAITA REQUIRED libadwaita-1)

add_executable(fm28l main.c font.h font.c draw.c draw.h screen.h)
#add_executable(darwin darwin/main.c darwin/darwin_credentials.h darwin/ftp.c darwin/ftp.h darwin/xml.c darwin/xml.h min.h darwin/s3.c darwin/s3.h darwin/utils/type_conversions.h darwin/pushport/schema/common_types.h darwin/pushport/schema/xml_timetable.h darwin/pushport/schema/xml_ref_data.h darwin/pushport/schema/push_port.h darwin/pushport/schema/push_port_status.h darwin/pushport/schema/push_port_schedules.h darwin/pushport/schema/push_port_formations.h darwin/pushport/schema/push_port_forecasts.h darwin/pushport/schema/push_port_station_messages.h darwin/pushport/schema/push_port_train_alerts.h darwin/pushport/schema/push_port_train_order.h darwin/pushport/schema/push_port_td_data.h darwin/pushport/schema/push_port_alarms.h awsS3/awsS3.h awsS3/utils/string_operations.h awsS3/utils/string_operations.c awsS3/utils/aws_signature_v4.h)
add_executable(font_editor font_editor.c font.h font.c glyph_names.h)
#add_executable(gziptest darwin/gziptest.c)

target_include_directories(font_editor PRIVATE ${GTK4_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})
target_link_directories(font_editor PRIVATE ${GTK4_LIBRARY_DIRS} ${LIBADWAITA_LIBRARY_DIRS})
target_link_libraries(font_editor PRIVATE ${GTK4_LIBRARIES} ${LIBADWAITA_LIBRARIES})

#target_include_directories(darwin PRIVATE /usr/include/libxml2)

target_link_libraries(fm28l ncurses)
#target_include_directories(font_editor PRIVATE ${GTK4_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})
#target_link_libraries(darwin curl)
#target_link_libraries(darwin z)
#target_link_libraries(darwin xml2)
#target_link_libraries(darwin crypto)
#target_link_libraries(darwin ssl)
#
#
#target_link_libraries(gziptest z)