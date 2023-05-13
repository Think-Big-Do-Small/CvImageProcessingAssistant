cmake_minimum_required(VERSION 3.0.0)

# Packages
#FIND_PACKAGE( Qt5Widgets REQUIRED )

# For OpenCV
find_package( OPENCV REQUIRED )


# For Qt
#find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

project(CvImageProcessingAssistant VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME}  QtImageFormatOpStack ImageFilterWorker ImageDenoiseWorker ImageEnhanceWorker About.cpp QtDragWidgetOpStack.cpp mainwindow.cpp main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



