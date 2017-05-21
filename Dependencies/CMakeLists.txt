
# Enable ExternalProject CMake module
include(ExternalProject)

# --- Logs ---

# cxxlog version
set(cxx-logs-VERSION master)

# Download and install swarm commons
ExternalProject_Add(
    cxx-logs
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/volatile
    GIT_REPOSITORY git@github.com:lib-cxx/cxx-log.git
    GIT_TAG "${swarm-commons-VERSION}"
    INSTALL_COMMAND ""
)

# Set cxxlog variable
set(cxx-logs-INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/volatile/src/cxx-logs/Sources PARENT_SCOPE)

# --- Swarm commons ---

# swarm commons version
set(swarm-commons-VERSION dev)

# Download and install swarm commons
ExternalProject_Add(
    swarm-commons
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/volatile
    GIT_REPOSITORY git@github.com:swarm-framework/swarm-commons.git
    GIT_TAG "${swarm-commons-VERSION}"
    INSTALL_COMMAND ""
)

# Set swarm commons variable
set(swarm-commons_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/volatile/src/swarm-commons/Sources PARENT_SCOPE)

# --- Swarm HTTP API ---

# swarm api version
set(swarm-http-api-VERSION dev)

# Download and install swarm api
ExternalProject_Add(
    swarm-http-api
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/volatile
    GIT_REPOSITORY git@github.com:swarm-framework/swarm-http-api.git
    GIT_TAG "${swarm-http-api-VERSION}"
    INSTALL_COMMAND ""
)

# Set swarm api variable
set(swarm-http-api_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/volatile/src/swarm-http-api/Sources PARENT_SCOPE)

# --- Curl ---

# Find Curl
find_package(CURL REQUIRED)

