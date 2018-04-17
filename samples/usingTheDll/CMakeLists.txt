
PROJECT( "usingTheDll" )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OpenFlightReader_SOURCE_DIR}/bin/samples/usingThedll )

INCLUDE_DIRECTORIES( ${usingTheDll_SOURCE_DIR}/.)

# local files
FILE (GLOB SOURCES *.h *.cpp)
SOURCE_GROUP("application" FILES ${SOURCES})

# file for OFR
SET( OFR_DLL_DIR  ${usingTheDll_SOURCE_DIR}/dll )
SET( OFR_DLL_INCLUDE  ${usingTheDll_SOURCE_DIR}/include )
include_directories( "${OFR_DLL_INCLUDE}/" )

FILE (GLOB OPENFLIGHT "${OFR_DLL_INCLUDE}/*.h" )
FILE (GLOB PRIMARYRECORDS ${OFR_DLL_INCLUDE}/PrimaryRecords/*.h )
FILE (GLOB ANCILLARYRECORDS ${OFR_DLL_INCLUDE}/AncillaryRecords/*.h )
SOURCE_GROUP("OpenFlightReader" FILES ${OPENFLIGHT} )
SOURCE_GROUP("OpenFlightReader\\PrimaryRecords" FILES ${PRIMARYRECORDS} )
SOURCE_GROUP("OpenFlightReader\\AncillaryRecords" FILES ${ANCILLARYRECORDS} )

#make executable
ADD_EXECUTABLE( ${PROJECT_NAME} ${SOURCES} ${OPENFLIGHT} ${PRIMARYRECORDS} ${ANCILLARYRECORDS})

#------------------------------------------------------------------------------
# define OFR library and includes
#------------------------------------------------------------------------------

# in order to have the _decspec sets to import, add definition OPENFLIGHTREADER_USE_DLL
ADD_DEFINITIONS(-DOPENFLIGHTREADER_USE_DLL)

set(OFR_LIBRAIRIES 
	optimized "${OFR_DLL_DIR}/OpenFlightReader.lib" 
	debug "${OFR_DLL_DIR}/OpenFlightReader_d.lib")

target_link_libraries( ${PROJECT_NAME} 
	${OFR_LIBRAIRIES}
    )

#------------------------------------------------------------------------------
#install to bin folder with dlls
#------------------------------------------------------------------------------
SET( DLL_DEBUG  ${OFR_DLL_DIR}/OpenFlightReader_d.dll )
SET( DLL_RELEASE  ${OFR_DLL_DIR}/OpenFlightReader.dll )

INSTALL(FILES ${DLL_DEBUG} CONFIGURATIONS debug DESTINATION ${OpenFlightReader_SOURCE_DIR}/bin/samples/usingThedll/Debug/ )
INSTALL(FILES ${DLL_RELEASE}  CONFIGURATIONS Release  DESTINATION ${OpenFlightReader_SOURCE_DIR}/bin/samples/usingThedll/Release/ )
INSTALL(FILES ${DLL_RELEASE}  CONFIGURATIONS RelWithDebInfo  DESTINATION ${OpenFlightReader_SOURCE_DIR}/bin/samples/usingThedll/RelWithDebInfo/ )