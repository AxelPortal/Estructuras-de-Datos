cmake_minimum_required(VERSION 4.0)
project(Estructuras)

set(CMAKE_CXX_STANDARD 20)

add_executable(Estructuras main.cpp
        LinkedList.h
        DoublyLinkedList.h
        CircleLinkedList.h
        Vector.h
        Queue.h
        Stack.h
        Deque.h
        HashTable.h
        Heap.h)

file(GLOB HASH_PROBLEMS "Hash_Problems/*.cpp")
foreach(problem_file ${HASH_PROBLEMS})
    get_filename_component(problem_name ${problem_file} NAME_WE)
    add_executable(${problem_name} ${problem_file}
            AVL_Problems/EsUnAVL.cpp
            Recursion_Problems/TorresDeHanoi.cpp
            Recursion_Problems/PagoExacto.cpp
            Heap_Problems/SimuladorDeHeap.cpp
            Heap_Problems/ValidacionDeHeap.cpp
            Heap_Problems/ConstruirHeap.cpp
            Heap_Problems/KesimoMayorEnUnStream.cpp
            AVL_Problems/ConstruirUnAvl.cpp
            AVL_Problems/ContarRotaciones.cpp
            AVL_Problems/VecinoMasCercano.cpp
            AVL_Problems/ReservasDeSala.cpp
            AVL_Problems/LaModaEnVivo.cpp
            AVL_Problems/RankingDePuntajes.cpp
            AVL_Problems/KesimoMenor.cpp
            AVL_Problems/ContarEnRango.cpp
            Recursion_Problems/RepartoDeCaramelos.cpp
            AVL_Problems/BloquesDeEntradas.cpp
            AVL_Problems/AlturasEnUnAvl.cpp
            AVL_Problems/RotacionesAMano.cpp
            Recursion_Problems/Mudanza.cpp
            AVL_Problems/SumaEnRango.cpp
            Graph_Problems/PerimetroDelTerreno.cpp
            Graph_Problems/PuentesDeKoningsberg.cpp
            Graph_Problems/SeguidoresMutuos.cpp
            Graph_Problems/AgendaDeContactos.cpp
            Graph_Problems/CablesEntreServidores.cpp
            Graph_Problems/AmigosEnComun.cpp
            BFSProblems/Laberinto.cpp
            Graph_Problems/LasJarras.cpp
            Graph_Problems/TriosDeAmigos.cpp
            Graph_Problems/EscaleraDePalabras.cpp)
endforeach()
