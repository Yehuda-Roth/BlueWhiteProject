# CMakeList.txt : CMake project for BlueWhiteProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BlueWhiteProject")

include_directories("include/ImplementModule" "include/Implement" "include/Communication")

# Add source to this project's executable.
add_executable (BlueWhiteProject "main.cpp"  "src/ImplementModule/ImplementModule.cpp" "include/ImplementModule/ImplementModule.h" "include/Communication/CommunicationIF.h" "include/Implement/ImplementBase.h" "include/Implement/ImplementIF.h" "include/ImplementModule/ImplementModuleIF.h" "include/Implement/ImplementMsg.h" "include/Implement/ImplementTypes.h" "include/Communication/UdpCommunication.h" "src/Communication/UdpCommunication.cpp" "include/Implement/ImplementMsg.h" "src/Implement/UdpImplement.cpp" "src/Implement/ImplementBase.cpp" "include/Communication/DummyCommunication.h")

# TODO: Add tests and install targets if needed.
