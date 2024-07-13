# Detecção de Bordas em Imagens Digitais com Processos POSIX

## Contextualização

A área de processamento e análise de imagens digitais teve um grande avanço no século XXI, impulsionada por aplicações em medicina, biologia, automação industrial e sensoriamento remoto. O processamento digital de imagens utiliza técnicas computacionais para capturar, representar e transformar imagens, permitindo a extração de informações e melhorando a interpretação visual humana e automática.

## Detecção de Bordas

A detecção de bordas é uma etapa crucial no processamento de imagens, definindo limites entre diferentes regiões de intensidade. Um método comum é o uso de operadores de convolução, como os operadores de `Prewitt`. Estes operadores, representados por máscaras, são aplicados em direções `x` e `y` para identificar mudanças bruscas de intensidade.

Exemplo de máscaras de Prewitt:
```plaintext
Gx[3][3] = { {-1, 0, 1},
             {-1, 0, 1},
             {-1, 0, 1} };

Gy[3][3] = { {-1, -1, -1},
             { 0,  0,  0},
             { 1,  1,  1} };
```

## Algoritmo (Pseudocódigo)

Dada uma imagem `I` em nível de cinza de dimensões `M × N`:

Criar `Rx[M][N]`, `Ry[M][N]`, `R[M][N]` (matrizes para bordas)

```cpp
// Calculando as informações de bordas
Para i variando de 1 até M-2
    Para j variando de 1 até N-2
        // Cálculo de Rx...
        Rx[i][j] = ( I[i+1][j-1] + I[i+1][j] + I[i+1][j+1] ) - (
                   I[i-1][j-1] + I[i-1][j] + I[i-1][j+1] );
        
        // Deixando as intensidades no domínio [0, 255]...
        Se ( Rx[i][j] < 0 )
            Rx[i][j] = - Rx[i][j];
        Se ( Rx[i][j] > 255 )
            Rx[i][j] = 255;
        
        // Cálculo de Ry...
        Ry[i][j] = ( I[i-1][j+1] + I[i][j+1] + I[i+1][j+1] ) - (
                   I[i-1][j-1] + I[i][j-1] + I[i+1][j-1] );
        
        // Deixando as intensidades no domínio [0, 255]...
        Se ( Ry[i][j] < 0 )
            Ry[i][j] = - Ry[i][j];
        Se ( Ry[i][j] > 255 )
            Ry[i][j] = 255;
    fim-para
fim-para

// Gerando imagem de saída...
Para i variando de 0 até M-1
    Para j variando de 0 até N-1
        R[i][j] = Rx[i][j] + Ry[i][j];
        Se ( R[i][j] > 255 )
            R[i][j] = 255;
    fim-para
fim-
```

----

# Problema

Elaborar um programa em `C/C++` para um sistema `POSIX` (Linux), utilizando `GCC/G++`:

**1.** Criar um processo pai que abre uma imagem em nível de cinza e cria uma matriz representando essa imagem.
**2.** Utilizar `fork()` para criar um processo filho que calcula as bordas na direção `x` da imagem, salvando o resultado na matriz `Rx`.
**3.** Utilizar `fork()` novamente para criar outro filho que calcula as bordas na direção `y`, salvando o resultado na matriz `Ry`.
**4.** O processo pai deve esperar pela conclusão dos filhos e combinar `Rx` e `Ry` para formar a matriz `R`.
**5.** Salvar a matriz `R` como uma nova imagem de saída.

# Sobre o Programa

Este repositório contém um programa em C++ que utiliza o OpenCV para processamento de imagens e threads POSIX (pthreads) para operações paralelas. O programa é configurado e compilado usando CMake, facilitando a construção e execução do código.

## Estrutura do Programa

```css
processos/
├── .vscode/
│    └── (arquivos de configurações do vscode)
├── imgs/
│    └── (imagens geradas na execução do código)
├── assets/
│    └── coins.png
├── build/
│    └── (arquivos de construção)
├── bin/
│    └── (arquivo de execução)
├── src/
│    └── main.cpp
│    └── operations.cpp
├── include/
│    └── operations.h
├── CMakeLists.txt
├── dependencies.sh
├── Makefile
└── README.md
```

## Arquivos Principais

### `CMakeLists.txt`

Este arquivo é usado pelo CMake para gerenciar o processo de compilação do projeto. Ele configura a localização dos arquivos de cabeçalho do OpenCV, define os arquivos de origem, compila o projeto e liga com as bibliotecas necessárias.

### `dependencies.sh`

Script Bash utilizado para verificar as dependências necessárias para o projeto. Ele verifica a presença das bibliotecas OpenCV e pthreads no sistema e informa se alguma delas está ausente.

### `Makefile`

O Makefile define regras para automatizar a compilação, execução e limpeza do projeto. Ele utiliza o CMake para configurar e compilar o projeto (`build`), verifica as dependências (`check_dependencies`), executa o projeto compilado (`run`) e limpa os arquivos gerados (`clean`).

----

## Instalação das Dependências

Para executar o código corretamente, instale as seguintes bibliotecas no Ubuntu:

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libopencv-dev #instala: opencv
sudo apt-get install build-essential #instala: gcc/g++, cmake, pthreads...
```
ou
```bash
sudo apt-get install libpthread-stubs0-dev #instala: pthreads
```

**Obs:** Certifique que as instalações estejam nos caminhos: `/usr/lib/x86_64-linux-gnu/libopencv_core.so`  e `/usr/lib/x86_64-linux-gnu/libpthread.so.0`

## Compilação e Execução

Dentro da pasta do projeto, chamada `/processos`, utilize o comando `make` na bash para compilar e executar o programa.
```bash
make
```

### Usando o Comando `make` na Bash

Ao executar `make`, usamos a funcionalidade `all` que segue as funções do Makefile: `check_dependencies`, `clean`, `build` e `run`, respectivamente. Com isso, o fluxo de execução é:

* **Verificação de Dependências (`check_dependencies`)**: O Makefile primeiro verifica se todas as dependências estão instaladas utilizando o `check_dependencies`. Se alguma dependência estiver ausente, o processo é interrompido. Usa-se o script `dependencies.sh` para vasculhar a existência das dependências nos arquivos do sistema Linux.

* **Limpeza (`clean`)**: Em seguida o Makefile remove todos os arquivos gerados durante o processo de compilação passadas, mantendo apenas os arquivos fonte e necessários.

* **Compilação com CMake (`build`)**: O programa depois é configurado e compilado utilizando CMake. Os arquivos de origem são compilados e o executável `main` é gerado no diretório `bin`.

* **Execução do Projeto (`run`)**: Após a compilação, o Makefile executa o programa compilado a partir do diretório `bin`.

---

## Referências

1. [Operating System Concepts, 9th edition](https://www.wiley.com/en-us/Operating+System+Concepts%2C+9th+Edition-p-9781118129388)
2. [Modern Operating Systems, 4th edition](https://www.pearson.com/store/p/modern-operating-systems/P100000076678)
3. [Processos no Unix](https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node28.html)
4. [Imagens PGM](https://netpbm.sourceforge.net/doc/pgm.html#plainpgm)

**Obs:** Este arquivo contém todas as seções necessárias para entender, implementar e executar seu projeto de detecção de bordas em imagens digitais usando processos POSIX no ambiente Linux.
