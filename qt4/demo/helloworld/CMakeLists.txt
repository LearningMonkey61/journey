set(SOURCES
   helloworld.cpp
   )

set(MOC_HEADERS
   )


set(RESOURCES
   )

QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES})
QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS})

add_executable(helloworld ${SOURCES} ${MOC_SRCS} ${RES_SOURCES})
set_target_properties(helloworld PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(helloworld Qt4::QtGui Qt4::QtXml)
