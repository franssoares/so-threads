// Diretiva para criar o módulo .h
#ifndef OPERATIONS_H
#define OPERATIONS_H

// Biblioteca
#include <opencv2/opencv.hpp> //uso em imagens

/* NOTE:
Funções implementadas em operations.cpp:
- calcularRx: Descrição sucinta da função que realiza Rx-operação.
- calcularRy: Descrição da função que realiza Ry-operação.
- combinarRxRy: Descrição da função que realiza R-operação.
*/

// Função para calcular Rx
void calcularRx(const cv::Mat& I, cv::Mat& Rx);

// Função para calcular Ry
void calcularRy(const cv::Mat& I, cv::Mat& Ry);

// Função para combinar Rx e Ry
void combinarRxRy(const cv::Mat& Rx, const cv::Mat& Ry, cv::Mat& R);

// Fim do OPERATIONS_H
#endif 