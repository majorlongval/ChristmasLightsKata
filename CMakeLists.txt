cmake_minimum_required(VERSION 3.13.4)

project(CLK)


add_subdirectory(src)

add_subdirectory(googletest)

target_include_directories(${PROJECT_NAME}
        PUBLIC googletest/googletest/include/gtest
        PUBLIC googletest/googlemock/include/gtest
	)

target_link_directories(${PROJECT_NAME}
        PRIVATE googletest/googletest/src
	PRIVATE googletest/googlemock/src
        )

target_link_libraries(${PROJECT_NAME} gtest_main gtest
	)


	
