
cmake_minimum_required(VERSION 3.12)
project(flights_javeriana)

set(CMAKE_CXX_STANDARD 14)

add_executable(flights_javeriana main.cpp Aeronautica.cxx Aeronautica.h Agencia.cxx Agencia.h Archivo.cxx Archivo.h Consola.cxx Consola.h Ruta.cxx Ruta.h Venta.cxx Venta.h Trie.cxx Trie.h)
