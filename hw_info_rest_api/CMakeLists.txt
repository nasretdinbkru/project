cmake_minimum_required(VERSION 3.20)

set(project_name hw_info_rest_api)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_library(${project_name}-lib
        src/AppComponent.h
        src/controller/AppController.h
        src/controller/NetIfInfoCollector.h
        src/controller/NetIfInfoCollector.cpp
        src/controller/MemInfoCollector.h
        src/controller/MemInfoCollector.cpp
        src/dto/DTOs.h
        src/controller/HddInfoCollector.h
        src/controller/HddInfoCollector.cpp
        src/controller/CpuInfoCollector.cpp
        src/controller/CpuInfoCollector.h
        src/controller/AppController.cpp
)

## link libs

find_package(oatpp 1.4.0 REQUIRED)
find_library(UDEV_LIB udev REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
)

target_include_directories(${project_name}-lib PUBLIC src)


add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib ${UDEV_LIB})
add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

