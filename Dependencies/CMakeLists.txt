if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/CMakeLists.txt)

    # Include cxx-log
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/Sources)

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/CMakeLists.txt)

    # Include swarm-commons
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/Sources)

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api/CMakeLists.txt)

    # Include swarm-http-api
    add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api)

    # Include sources
    include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-http-api/Sources)

endif()

# --- Find Curl package ---

# Find Curl
find_package(CURL REQUIRED)

