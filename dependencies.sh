#!/bin/bash

echo "Verificando dependências..."

# Verifica o OpenCV
if [ ! -f "/usr/lib/x86_64-linux-gnu/libopencv_core.so" ]; then
  echo 'Erro: OpenCV não encontrado. Instale OpenCV.' >&2
  exit 1
fi

# Verifica se o arquivo da biblioteca pthreads está presente
if [ ! -f "/usr/lib/x86_64-linux-gnu/libpthread.so.0" ]; then
    echo 'Erro: pthreads não encontrado. Instale pthreads.' >&2
    exit 1
fi

echo "Todas as dependências estão instaladas corretamente."