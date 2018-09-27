set (PROJECTS
    starfield
    menger_sponge_fractal
    snake
    purple_rain
    space_invader
    mitosis
    solar
    maze_generator
    noise_terrain
    lorenz_system
    )

foreach(PROJECT ${PROJECTS})
    message("add challenge ${PROJECT}")

    add_executable(${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT}/${PROJECT}.cpp)
    set_target_properties(${PROJECT} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
    target_link_libraries(${PROJECT}
        m
        common
        ${Boost_LIBRARIES}
        )
endforeach()

file(COPY lorenz_system/lorenz_system.txt DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})