
# Add sources files
set (${PROJECT_NAME}_SOURCES
	lib.cxx
)

# Set includes
include_directories(
    .                           # Current project
    ${cxx-logs-INCLUDE}         # Include cxx-log 
    ${swarm-commons_INCLUDE}   # Include Swarm commons
) 

# Create library
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

# Install exec in bin directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
