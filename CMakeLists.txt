PROJECT(OpenFlightReader)
cmake_minimum_required(VERSION 3.1)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME} )

INCLUDE_DIRECTORIES( ${OpenFlightReader_SOURCE_DIR}/.)
INCLUDE_DIRECTORIES( ${OpenFlightReader_SOURCE_DIR}/openFlight/)

#local files
FILE (GLOB SOURCES *.h *.cpp)
FILE (GLOB OPENFLIGHT openFlight/*.h openFlight/*.cpp)
FILE (GLOB PRIMARYRECORDS openFlight/PrimaryRecords/*.h openFlight/PrimaryRecords/*.cpp)
FILE (GLOB ANCILLARYRECORDS openFlight/AncillaryRecords/*.h openFlight/AncillaryRecords/*.cpp)

#make executable
SOURCE_GROUP("application" FILES ${SOURCES})
SOURCE_GROUP("OpenFlight" FILES ${OPENFLIGHT})
SOURCE_GROUP("OpenFlight\\PrimaryRecords" FILES ${PRIMARYRECORDS})
SOURCE_GROUP("OpenFlight\\AncillaryRecords" FILES ${ANCILLARYRECORDS})

ADD_EXECUTABLE( ${PROJECT_NAME} ${SOURCES} ${OPENFLIGHT} ${PRIMARYRECORDS} ${ANCILLARYRECORDS})

#install to bin and move assets
SET ( destinationPath ${OpenFlightReader_SOURCE_DIR}/bin/${PROJECT_NAME} )
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${destinationPath} )
INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${destinationPath}/assets )