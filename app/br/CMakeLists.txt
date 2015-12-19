if(UNIX)
  find_package(Threads REQUIRED)
endif()

add_executable(br br.cpp ${BR_RESOURCES})
add_executable(faceTest faceTest.cpp ${BR_RESOURCES})

target_link_libraries(br openbr ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(faceTest openbr ${CMAKE_THREAD_LIBS_INIT} ${BR_THIRDPARTY_LIBS})

qt5_use_modules(br ${QT_DEPENDENCIES})
qt5_use_modules(faceTest ${QT_DEPENDENCIES})

install(TARGETS br RUNTIME DESTINATION bin)
add_test(NAME br_initialize WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND br)

