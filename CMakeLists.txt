cmake_minimum_required(VERSION 3.20)
project(tarefas)

# Especifica a localização dos arquivos de cabeçalho do OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Define os arquivos de origem do seu projeto .cpp
set(SOURCES 
    src/main.cpp
    src/operations.cpp
)

# Define o diretório onde estão os arquivos de cabeçalho .h ou .hpp
include_directories(include)

# Cria o executável do seu projeto
add_executable(main ${SOURCES})

# Link com a biblioteca do OpenCV
target_link_libraries(main ${OpenCV_LIBS})

# Adiciona as flags de compilação necessárias
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Adiciona as bibliotecas necessárias para o uso de processos
target_link_libraries(main pthread)