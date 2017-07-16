# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.8)

# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(swarm-http-server VERSION 0.1.0)

# Include config
include(Config/config.cmake)

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

# Target includes
target_include_directories(
    swarm-http-server
        
    PRIVATE
        ${cxx-log_INCLUDE_DIR}
        ${swarm-commons_INCLUDE_DIR}
        ${swarm-mapping_INCLUDE_DIR}
        ${swarm-http-api_INCLUDE_DIR}
)

# Target link
target_link_libraries(
    swarm-http-server
    
    swarm-commons
    swarm-mapping
    swarm-http-api
    ${CURL_LIBRARIES}
)

# Include build
include(Config/build.cmake)

# Include test
add_subdirectory(Tests)

