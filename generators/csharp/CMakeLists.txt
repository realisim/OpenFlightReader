project("OpenFlightReader.CSharp" CSharp)

set(CPPSHARP_VERSION 0.8.19)
set(DOTNET_TARGET_FRAMEWORK 4.6)

find_program(NUGET nuget)
string(REPLACE "." "" NUGET_TARGET_FRAMEWORK ${DOTNET_TARGET_FRAMEWORK})

if (NOT NUGET)
	message(FATAL_ERROR "Unable to find the Nuget Command Line Interface !\nYou can download it at https://www.nuget.org/downloads")
else()
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/packages.config" "${CMAKE_CURRENT_BINARY_DIR}/packages.config" @ONLY)
	execute_process(COMMAND ${NUGET} restore "${PROJECT_NAME}.sln" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

set(SRC_FILES
	"Program.cs"
	"OpenFlightLibrary.cs"
	# "packages.config"
	"Properties/Resources.resx")

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties( ${PROJECT_NAME} PROPERTIES
  VS_GLOBAL_ROOTNAMESPACE "OpenFlight.CSharp"
  VS_DOTNET_TARGET_FRAMEWORK_VERSION "v${DOTNET_TARGET_FRAMEWORK}"
  VS_GLOBAL_StartupObject "OpenFlight.CSharp.Program"
  # VS_DOTNET_REFERENCE_Baseclass.Contrib.Nuget.Output.Build "${CMAKE_CURRENT_BINARY_DIR}/packages/Baseclass.Contrib.Nuget.Output.2.4.3/build/Baseclass.Contrib.Nuget.Output.Build.dll"
  VS_DOTNET_REFERENCE_CppSharp "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/lib/CppSharp.dll"
  VS_DOTNET_REFERENCE_CppSharp.AST "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/lib/CppSharp.AST.dll"
  # VS_DOTNET_REFERENCE_CppSharp.CppParser "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/output/CppSharp.CppParser.dll"
  VS_DOTNET_REFERENCE_CppSharp.Generator "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/lib/CppSharp.Generator.dll"
  VS_DOTNET_REFERENCE_CppSharp.Parser "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/lib/CppSharp.Parser.dll"
  VS_DOTNET_REFERENCE_CppSharp.Parser.CLI "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/lib/CppSharp.Parser.CLI.dll"
  VS_DOTNET_REFERENCE_CppSharp.Runtime "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/lib/CppSharp.Runtime.dll"
  VS_DOTNET_REFERENCE_CppSharp.Runtime "${CMAKE_CURRENT_BINARY_DIR}/packages/CommandLineParser.2.2.1/lib/net45/CommandLine.dll"
  VS_DOTNET_REFERENCES "System"
)

target_compile_options(${PROJECT_NAME} PUBLIC "/unsafe")

add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/output/CppSharp.CppParser.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  VERBATIM)
add_custom_command(TARGET ${PROJECT_NAME}
  POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_BINARY_DIR}/packages/CppSharp.${CPPSHARP_VERSION}/output/lib" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/lib"
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  VERBATIM)