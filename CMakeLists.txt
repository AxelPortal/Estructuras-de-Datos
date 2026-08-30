cmake_minimum_required(VERSION 4.0)
project(Estructuras)

set(CMAKE_CXX_STANDARD 20)

add_executable(Estructuras main.cpp
        LinkedList.h
        DoublyLinkedList.h
        CircleLinkedList.h
        Vector.h)
