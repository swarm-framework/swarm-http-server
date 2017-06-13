
# Find Curl
find_package(CURL REQUIRED)

# Include sub projects
find_dependencies(cxx-log)
find_dependencies(swarm-commons)
find_dependencies(swarm-mapping)
find_dependencies(swarm-http-api)

# Create targets
add_library(swarm-http-server
	
	Sources/swarm/http/process/HTTPProcess.hxx 
	Sources/swarm/http/process/HTTPContext.cxx Sources/swarm/http/process/HTTPContext.hxx 
	
    Sources/swarm/http/router/HTTPRouter.cxx Sources/swarm/http/router/HTTPRouter.hxx
    Sources/swarm/http/router/HTTPRouterBuilder.cxx Sources/swarm/http/router/HTTPRouterBuilder.hxx
	Sources/swarm/http/router/HTTPRouterChoice.cxx Sources/swarm/http/router/HTTPRouterChoice.hxx
	Sources/swarm/http/router/HTTPRouterEntry.cxx Sources/swarm/http/router/HTTPRouterEntry.hxx

    Sources/swarm/http/service/HTTPService.cxx Sources/swarm/http/service/HTTPService.hxx
    Sources/swarm/http/service/HTTPServiceBuilder.cxx Sources/swarm/http/service/HTTPServiceBuilder.hxx Sources/swarm/http/service/HTTPServiceBuilder.txx
    Sources/swarm/http/service/HTTPServiceHandlerBuilder.cxx Sources/swarm/http/service/HTTPServiceHandlerBuilder.hxx Sources/swarm/http/service/HTTPServiceHandlerBuilder.txx
    Sources/swarm/http/service/HTTPServiceProcessWrapper.cxx Sources/swarm/http/service/HTTPServiceProcessWrapper.hxx Sources/swarm/http/service/HTTPServiceProcessWrapper.txx

	Sources/swarm/http/server/HTTPServer.cxx Sources/swarm/http/server/HTTPServer.hxx 
	Sources/swarm/http/server/HTTPSession.hxx
	Sources/swarm/http/server/HTTPServerDelegate.hxx
	
	Sources/swarm/http/server/StandardErrorBuilder.cxx Sources/swarm/http/server/StandardErrorBuilder.hxx
)

# Properties of targets

# Add definitions for targets
# Values:
#   * Debug: -DSWARM_HTTP_SERVER_DEBUG=1
#   * Release: -DSWARM_HTTP_SERVER_DEBUG=0
#   * other: -DSWARM_HTTP_SERVER_DEBUG=0
target_compile_definitions(swarm-http-server  PUBLIC "SWARM_HTTP_SERVER_DEBUG=$<CONFIG:Debug>")

# Generate headers:
include(GenerateExportHeader)
generate_export_header(swarm-http-server)

# Global includes. Used by all targets
target_include_directories(
    swarm-http-server
    
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Sources>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        
    PRIVATE
        ${cxx-log_INCLUDE_DIR}
        ${swarm-commons_INCLUDE_DIR}
        ${swarm-mapping_INCLUDE_DIR}
        ${swarm-http-api_INCLUDE_DIR}
)

target_link_libraries(
    swarm-http-server
    swarm-commons
    swarm-mapping
    swarm-http-api
    ${CURL_LIBRARIES}
)

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/${target}.a
#   * header location after install: <prefix>/include/*.hxx
#   * headers can be included by C++ code `#include <project/*.hxx>`
install(
    TARGETS swarm-http-server
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Headers:
#   * Sources/${target}/*.hxx -> <prefix>/include/${target}/*.hxx
install(
    DIRECTORY "Sources/swarm"
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.[h;t]xx"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/${target}_export.h -> <prefix>/include/${target}_export.h
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/swarm-http-server_export.h"
    DESTINATION "${include_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/${project}/${Target}Config.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/${project}/${Target}Targets.cmake
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
