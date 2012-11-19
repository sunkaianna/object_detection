CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
file(GLOB source
    "*.h"
    "*.cpp"
    )

#${M_LIBRARY}/data.cpp
ADD_EXECUTABLE(object_detection ${source})
INCLUDE_DIRECTORIES(/usr/include/opencv)
#INCLUDE_DIRECTORIES(/usr/include/qt4/QtCore)

TARGET_LINK_LIBRARIES(object_detection 
    /usr/lib/libxmlrpc_abyss.so
    /usr/lib/libxmlrpc_client++.so
    /usr/lib/libxmlrpc++.so
    /usr/lib/libxmlrpc.so.3
    /usr/lib/libboost_graph.so
    /usr/lib/libopencv_highgui.so
    /usr/lib/libxmlrpc_server_abyss++.so
    /usr/lib/libxmlrpc_server++.so
    /usr/lib/libboost_system.so
    /usr/lib/libopencv_core.so
    /usr/lib/libopencv_imgproc.so
    /usr/lib/libboost_regex.so)
#TARGET_LINK_LIBRARIES(object_detection /usr/lib/qt4/

#INSTALL (TARGETS object_detection
    #RUNTIME DESTINATION ..
    #)
#INSTALL_TARGETS(.. object_detection)