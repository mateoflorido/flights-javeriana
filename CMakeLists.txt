cmake_minimum_required (VERSION 3.12)
project (flights_javeriana)
#Version Number
set (flights_javeriana_VERSION_MAJOR 0)
set (flights_javeriana_VERSION_MINOR 1)
set (CMAKE_CXX_STANDARD 17)

add_executable(flights_javeriana main.cpp Ruta.cxx Ruta.h Venta.cxx Venta.h Agencia.cxx Agencia.h Aeronautica.cxx Aeronautica.h Consola.cxx Consola.h Archivo.cxx Archivo.h)
