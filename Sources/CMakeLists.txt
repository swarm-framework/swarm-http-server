
# Add sources files
set (${PROJECT_NAME}_SOURCES
    
	swarm/http/process/HTTPProcess.hxx 
	swarm/http/process/HTTPContext.cxx swarm/http/process/HTTPContext.hxx 
	
    swarm/http/router/HTTPRouter.cxx swarm/http/router/HTTPRouter.hxx
    swarm/http/router/HTTPRouterBuilder.cxx swarm/http/router/HTTPRouterBuilder.hxx
    
    swarm/http/service/HTTPService.cxx swarm/http/service/HTTPService.hxx
    swarm/http/service/HTTPServiceBuilder.cxx swarm/http/service/HTTPServiceBuilder.hxx

	swarm/http/server/HTTPServer.cxx swarm/http/server/HTTPServer.hxx 
	swarm/http/server/HTTPSession.hxx
	swarm/http/server/HTTPServerDelegate.hxx
	
	swarm/http/server/StandardErrorBuilder.cxx swarm/http/server/StandardErrorBuilder.hxx
)

# Set includes
include_directories(
    .                           # Current project
) 

# Create library
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

# Link library
target_link_libraries(${PROJECT_NAME}
    swarm-http-api
)

# Install exec in bin directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
