set(CMAKE_CXX_STANDARD 17)
project(Lab2)
add_executable(Lab2
        main.cpp
        schedulingalgorithms/CPUScheduler.cpp
        schedulingalgorithms/FirstComeFirstServedScheduler.cpp
        schedulingalgorithms/RoundRobinScheduler.cpp
        )