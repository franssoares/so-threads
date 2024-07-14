// Diretiva para criar o módulo .h
#ifndef OPERATIONS_H
#define OPERATIONS_H

// Biblioteca
#include <opencv2/opencv.hpp> //uso em imagens

/* NOTE:
    Este arquivo contém as declarações das funções utilizadas para processamento de imagens
    e as variáveis globais que representam a imagem e as matrizes Rx, Ry, R.

    Funções declaradas:
    - carregarImagem: Carrega a imagem em escala de cinza e inicializa as matrizes globais.
    - calcularRxThread: Função executada pela thread filha para calcular as bordas Rx.
    - calcularRyThread: Função executada pela thread filha para calcular as bordas Ry.
    - combinarRxRy: Combina as imagens Rx e Ry para formar a imagem de bordas R.
    - combinarRxRy: Função para combinar Rx e Ry em R
*/

// Declaração das variáveis globais como extern
extern cv::Mat image;  // Imagem em escala de cinza
extern cv::Mat Rx;     // Matriz para armazenar Rx
extern cv::Mat Ry;     // Matriz para armazenar Ry
extern cv::Mat R;      // Matriz para armazenar R (resultado)

// Função para carregar a imagem (Thread Mãe)
void* carregarImagem(void* arg);

// Função para calcular Rx (Thread Filha)
void* calcularRxThread(void* arg);

// Função para calcular Ry (Thread Filha)
void* calcularRyThread(void* arg);

// Função para combinar Rx e Ry em R
void combinarRxRy(const cv::Mat& Rx, const cv::Mat& Ry, cv::Mat& R);

// Função para calcular Rx
void calcularRx(const cv::Mat& I, cv::Mat& Rx);

// Função para calcular Ry
void calcularRy(const cv::Mat& I, cv::Mat& Ry);

// Função para combinar Rx e Ry em R
void combinarRxRy(const cv::Mat& Rx, const cv::Mat& Ry, cv::Mat& R);

#endif // OPERATIONS_H