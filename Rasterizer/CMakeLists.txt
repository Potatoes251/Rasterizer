#project


file(GLOB_RECURSE PROJECT_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_executable(${EXE_NAME})

target_sources(${EXE_NAME} PRIVATE ${PROJECT_FILES})

target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/raylib/include)

target_include_directories(${EXE_NAME} PRIVATE ${LIB_INCLUDE_DIR})

target_link_libraries(${EXE_NAME}
debug ${CMAKE_SOURCE_DIR}/raylib/Debug/raylib.lib

optimized ${CMAKE_SOURCE_DIR}/raylib/Release/raylib.lib)

target_link_libraries(${EXE_NAME} winmm)

target_link_libraries(${EXE_NAME} ${LIB_NAME})