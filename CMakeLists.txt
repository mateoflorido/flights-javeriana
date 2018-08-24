cmake_minimum_required (VERSION 2.6)
project (flights_javeriana)

#Version Number
set (flights_javeriana_VERSION_MAJOR 0)
set (flights_javeriana_VERSION_MINOR 1)
set (CMAKE_CXX_STANDARD 17)

add_executable(flights_javeriana main.cpp Ruta.cxx Venta.cxx Agencia.cxx Aeronautica.cxx Consola.cxx Archivo.cxx)
