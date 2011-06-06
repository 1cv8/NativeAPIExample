cmake_minimum_required (VERSION 2.6)

set (PROJECT NativeXMLReader)

set (SOURCE_PATH 
	../sources)

set (HEADERS
	${SOURCE_PATH}/AddInNative.h
	${SOURCE_PATH}/dllmain.h
	${SOURCE_PATH}/QMyXmlReader.h
	${SOURCE_PATH}/stdafx.h
	${SOURCE_PATH}/LogTools.h
	../includes/ComponentBase.h
	../includes/types.h)

set (SOURCES
	${SOURCE_PATH}/AddInNative.cpp
	${SOURCE_PATH}/dllmain.cpp
	${SOURCE_PATH}/QMyXmlReader.cpp
	${SOURCE_PATH}/stdafx.cpp
	${SOURCE_PATH}/LogTools.cpp)

project (${PROJECT})

include_directories (../)
include_directories (../includes/)

set (UsingQTPrj TRUE)
set (UsingBOOSTPrj TRUE)

if (UsingQTPrj)

	find_package (Qt4 REQUIRED)

	set (QT_DONT_USE_QTGUI TRUE)

	include (${QT_USE_FILE})

	qt4_wrap_cpp (MOC_SOURCES ${HEADERS})

endif ()

if (UsingBOOSTPrj)

	set (Boost_USE_STATIC_LIBS ON)
	set (Boost_USE_MULTITHREADED ON)
	
#	set (BOOST_COMPONENTS 
#		bind)	

#	find_package (Boost 1.45.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
	find_package (Boost 1.45.0 REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	
endif ()

	
if (MSVC)
	add_definitions (/W3)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions (-Wall -pedantic)
else ()
	message ("Unknown compiler")
endif ()

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

if (UsingQTPrj)
	source_group ("Generated Files" FILES ${MOC_SOURCES})
	#source_group ("Resource Files" FILES ${QRC_SOURCES})
endif ()

if (UsingQTPrj)	
	add_library(${PROJECT} SHARED ${HEADERS} ${SOURCES} ${MOC_SOURCES})
else ()
	add_library(${PROJECT} SHARED ${HEADERS} ${SOURCES} )
endif ()

if (UsingQTPrj)
	target_link_libraries (${PROJECT} ${LIBRARIES} ${QT_LIBRARIES})
endif ()

if (UsingBOOSTPrj)
	target_link_libraries (${PROJECT} ${Boost_LIBRARIES})
endif ()
