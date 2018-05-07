PROJECT(OpenFlightReader)
cmake_minimum_required(VERSION 3.1)

#------------------------------------------------------------------------------
# Options and variables in CMake GUI
#------------------------------------------------------------------------------
option(BUILD_AS_SHARED_LIB "Builds the shared library (.dll)" OFF)
option(BUILD_CSHARP_GENERATOR "Build CSharp Generator" OFF)

#------------------------------------------------------------------------------
# Options and variables in CMake GUI
#------------------------------------------------------------------------------
option(BUILD_SAMPLES "Builds the samples" OFF)
option(BUILD_UNIT_TESTS "Builds the unit tests" OFF)

SET ( destinationBinPath ${OpenFlightReader_SOURCE_DIR}/bin/ )

if (BUILD_CSHARP_GENERATOR)
	ADD_SUBDIRECTORY(generators)
endif()

#------------------------------------------------------------------------------
# Create main lib project (shared and static)
#------------------------------------------------------------------------------
INCLUDE_DIRECTORIES( ${OpenFlightReader_SOURCE_DIR}/.)
INCLUDE_DIRECTORIES( ${OpenFlightReader_SOURCE_DIR}/openFlight/)

# local files
#local files
FILE (GLOB OPENFLIGHT openFlight/*.h openFlight/*.cpp)
FILE (GLOB PRIMARYRECORDS openFlight/PrimaryRecords/*.h openFlight/PrimaryRecords/*.cpp)
FILE (GLOB ANCILLARYRECORDS openFlight/AncillaryRecords/*.h openFlight/AncillaryRecords/*.cpp)

#make executable
SOURCE_GROUP("OpenFlight" FILES ${OPENFLIGHT})
SOURCE_GROUP("OpenFlight\\PrimaryRecords" FILES ${PRIMARYRECORDS})
SOURCE_GROUP("OpenFlight\\AncillaryRecords" FILES ${ANCILLARYRECORDS})

# make lib
IF(BUILD_AS_SHARED_LIB)
	ADD_DEFINITIONS(-DOPENFLIGHTREADER_USE_DLL -DOPENFLIGHTREADER_DLL_EXPORT)
	ADD_LIBRARY( ${PROJECT_NAME} SHARED ${OPENFLIGHT} ${PRIMARYRECORDS} ${ANCILLARYRECORDS})
ELSE(BUILD_AS_SHARED_LIB)
	ADD_LIBRARY( ${PROJECT_NAME} STATIC ${OPENFLIGHT} ${PRIMARYRECORDS} ${ANCILLARYRECORDS})
ENDIF(BUILD_AS_SHARED_LIB)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)

#------------------------------------------------------------------------------
# conditionnal projects: samples and unit tests.
#------------------------------------------------------------------------------
IF(BUILD_SAMPLES)
    ADD_SUBDIRECTORY(samples)
ENDIF()

IF(BUILD_UNIT_TESTS)
    ADD_SUBDIRECTORY(unitTests)
ENDIF()

#------------------------------------------------------------------------------
# INSTALL the libs, dll and include package
#------------------------------------------------------------------------------
# Install library
IF(BUILD_AS_SHARED_LIB)
	install(TARGETS ${PROJECT_NAME} DESTINATION ${destinationBinPath}/dll/)
ELSE(BUILD_AS_SHARED_LIB)
	install(TARGETS ${PROJECT_NAME} DESTINATION ${destinationBinPath}/lib/)
ENDIF(BUILD_AS_SHARED_LIB)

# Install library headers
FILE (GLOB HEADERS_OPENFLIGHT openFlight/*.h)
FILE (GLOB HEADERS_PRIMARY openFlight/PrimaryRecords/*.h)
FILE (GLOB HEADERS_ANCILLARY openFlight/AncillaryRecords/*.h)

install(FILES ${HEADERS_OPENFLIGHT} DESTINATION ${destinationBinPath}/include)
install(FILES ${HEADERS_PRIMARY} DESTINATION ${destinationBinPath}/include/PrimaryRecords)
install(FILES ${HEADERS_ANCILLARY} DESTINATION ${destinationBinPath}/include/AncillaryRecords)

#------------------------------------------------------------------------------
# install assets to bin folder
#------------------------------------------------------------------------------
INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${destinationBinPath}/assets )