PROJECT(OpenFlightReader)
cmake_minimum_required(VERSION 3.1)


ADD_SUBDIRECTORY(samples)

#install assets to bin folder
SET ( destinationBinPath ${OpenFlightReader_SOURCE_DIR}/bin/ )
INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${destinationBinPath}/assets )