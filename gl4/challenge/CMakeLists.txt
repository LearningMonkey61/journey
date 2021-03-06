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
    reaction_diffusion
    fractal_tree
    lsystem_tree
    space_colonization_tree
    space_colonization_tree_3d
    superellipse
    supershape
    flow_field
    supershape3d
    firework
    poisson_disk_sample
    diffusion_limited
    lexicograph
    diastic_machine
    pixel_sort
    photo_mosaic
    circle_pack
    astar
    levy_flight
    islamic_pattern
    rose
    attraction_repulsion
    butterfly
    fractal_spirograph
    forward_kinematics
    inverse_kinematics
    shakespeare_monkey
    smart_rocket
    bloop
    clock
    movie_recommender
    recursion
    cube_wave
    knot
    snow
    floyd_steinberg_dithering
    double_pendulum
    octree_point
    octree_region
    ripple
    fire
    sandpiles
    barnsley_fern
    recaman_sequence
    spritesheet
    hypercube
    lissajous
    seven_segment
    mandelbrot_set
    evolutionary_steer
    lightning
    chaos
    secret_garden
    )

set(CMAKE_INCLUDE_CURRENT_DIR ON) # include qt generated files
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /opt/Qt5.7.0/5.7/gcc_64)

find_package(Qt5Widgets CONFIG REQUIRED)

foreach(PROJECT ${PROJECTS})
    message("add challenge ${PROJECT}")
    #DO
    IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT}/CMakeLists.txt)
        add_subdirectory(${PROJECT})
    ELSE()
        add_executable(${PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT}/${PROJECT}.cpp)
        set_target_properties(${PROJECT} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
        target_link_libraries(${PROJECT}
            common
            m
            ${Boost_LIBRARIES}
            )
    ENDIF()

endforeach()

file(COPY lorenz_system/lorenz_system.txt DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY supershape3d/supershape3d.txt DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
