project("cooperative_multitask")
file(GLOB SOURCES
    **/*.cpp
    main.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
