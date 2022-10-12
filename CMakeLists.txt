# CMakeList.txt : CMake project for BlueWhiteProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BlueWhiteProject")

include_directories("include/ImplementModule" "include/Implement" "include/Communication")

# Add source to this project's executable.
add_executable (BlueWhiteProject "main.cpp"  "src/ImplementModule/ImplementModule.cpp" "include/ImplementModule/ImplementModule.h" "include/Communication/CommunicationIF.h" "include/Implement/Implement.h" "include/Implement/ImplementIF.h" "include/ImplementModule/ImplementModuleIF.h" "include/ImplementModule/ImplementModuleMsg.h" "include/Implement/ImplementTypes.h" "include/Communication/UdpCommunication.h" "src/Communication/UdpCommunication.cpp")

# TODO: Add tests and install targets if needed.
