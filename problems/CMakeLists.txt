
# source files
set(week1_src problem1.cpp)
set(week2_src problem2.cpp)
set(week3_src problem3.cpp)
set(week4_src problem4.cpp)

# add the executable
add_executable(week1 ${week1_src})
target_link_libraries( week1
	string_int 
	file_ops )

add_executable(week2 ${week2_src})
target_link_libraries( week2
	file_ops )

add_executable(week3 ${week3_src})
target_link_libraries( week3
	file_ops )

add_executable(week4 ${week4_src})
target_link_libraries( week4
	file_ops 
	graph )

