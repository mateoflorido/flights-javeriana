cmake_minimum_required(VERSION 3.12)
project(flights_javeriana)

set(CMAKE_CXX_STANDARD 17)

add_executable(flights_javeriana main.cpp Ruta.cxx Ruta.h Venta.cxx Venta.h Agencia.cxx Agencia.h Aeronautica.cxx Aeronautica.h Comando.cxx Comando.h Consola.cxx Consola.h)