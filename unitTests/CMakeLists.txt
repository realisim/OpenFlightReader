project(UnitTests)

#------------------------------------------------------------------------------
# set output apps directory to bin/"BuildConfiguration"/${PROJECT_NAME}
#------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/UnitTests)


INCLUDE_DIRECTORIES( ${OpenFlightReader_SOURCE_DIR}/.)
INCLUDE_DIRECTORIES( ${OpenFlightReader_SOURCE_DIR}/openFlight/)

#local files
FILE (GLOB SOURCES *.h *.cpp)
FILE (GLOB OPENFLIGHT ../openFlight/*.h ../openFlight/*.cpp)
FILE (GLOB PRIMARYRECORDS ../openFlight/PrimaryRecords/*.h ../openFlight/PrimaryRecords/*.cpp)
FILE (GLOB ANCILLARYRECORDS ../openFlight/AncillaryRecords/*.h ../openFlight/AncillaryRecords/*.cpp)

#make executable
SOURCE_GROUP("application" FILES ${SOURCES})
SOURCE_GROUP("OpenFlight" FILES ${OPENFLIGHT})
SOURCE_GROUP("OpenFlight\\PrimaryRecords" FILES ${PRIMARYRECORDS})
SOURCE_GROUP("OpenFlight\\AncillaryRecords" FILES ${ANCILLARYRECORDS})

ADD_EXECUTABLE( ${PROJECT_NAME} ${SOURCES} ${OPENFLIGHT} ${PRIMARYRECORDS} ${ANCILLARYRECORDS})
