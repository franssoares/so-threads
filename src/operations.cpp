#include "../include/operations.h"
#include <iostream>      // I/O
#include <pthread.h>
#include <opencv2/opencv.hpp> //uso em imagens

// Diretiva de Namespace
using namespace std;
using namespace cv;

// Definição das variáveis globais
cv::Mat image;  // Imagem em escala de cinza
cv::Mat Rx;     // Matriz para armazenar Rx
cv::Mat Ry;     // Matriz para armazenar Ry
cv::Mat R;      // Matriz para armazenar R (resultado)

/* NOTE:
    Este arquivo implementa as funções declaradas em operations.h para processamento de imagens.

    Funções implementadas:
    - carregarImagem: Carrega a imagem em escala de cinza a partir do arquivo "coins.png" e inicializa as matrizes globais.
    - calcularRxThread: Calcula as bordas Rx da imagem usando um filtro de Prewitt.
    - calcularRyThread: Calcula as bordas Ry da imagem usando um filtro de Prewitt.
    - combinarRxRy: Combina as imagens Rx e Ry para formar a imagem de bordas R.
*/

// Função para carregar a imagem (Thread Mãe)
void* carregarImagem(void* arg) {

    pthread_t threadRx, threadRy;

    // Carrega a imagem a partir do arquivo "coins.png" em escala de cinza
    image = imread("../assets/coins.png", IMREAD_GRAYSCALE);

    // Verifica se a leitura da imagem foi bem-sucedida
    if (image.empty()) {
        cerr << "Erro ao ler a imagem!" << endl;
        pthread_exit(NULL);  // Encerra a thread mãe se houver um erro na leitura
    }

    // Obtém as dimensões da imagem para inicializar as matrizes Rx, Ry e R
    int rows = image.rows;
    int cols = image.cols;

    // Inicializa as matrizes Rx, Ry e R com as dimensões da imagem
    Rx = cv::Mat::zeros(rows, cols, CV_8UC1); // 8U -> uint de 8bits, C1 -> 1 canal (grayscale)
    Ry = cv::Mat::zeros(rows, cols, CV_8UC1);
    R = cv::Mat::zeros(rows, cols, CV_8UC1);

    // Criar as threads filhas para calcular Rx e Ry
    pthread_create(&threadRx, NULL, calcularRxThread, (void*)&image);
    pthread_create(&threadRy, NULL, calcularRyThread, (void*)&image);

    // Esperar as threads filhas terminarem
    pthread_join(threadRx, NULL);
    pthread_join(threadRy, NULL);

    pthread_exit(NULL);  // Encerra a thread mãe após carregar a imagem e inicializar as matrizes
}

// Função para calcular Rx (Thread Filha)
void* calcularRxThread(void* arg) {
    const Mat& I = *((Mat*)arg);  // Argumento recebido é a imagem carregada
    calcularRx(I, Rx);            // Chama a função para calcular Rx
    imwrite("../imgs/Rx.png", Rx); // Salva Rx em um arquivo
    pthread_exit(NULL);           // Encerra a thread filha
}

// Função para calcular Ry (Thread Filha)
void* calcularRyThread(void* arg) {
    const Mat& I = *((Mat*)arg);  // Argumento recebido é a imagem carregada
    calcularRy(I, Ry);            // Chama a função para calcular Ry
    imwrite("../imgs/Ry.png", Ry); // Salva Ry em um arquivo
    pthread_exit(NULL);           // Encerra a thread filha
}

// Função para calcular Rx
void calcularRx(const cv::Mat& I, cv::Mat& Rx) {
    int M = I.rows;
    int N = I.cols;
    int sum;

    for (int i = 1; i < M - 1; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            sum = (I.at<uchar>(i+1, j-1) + I.at<uchar>(i+1, j) + I.at<uchar>(i+1, j+1)) -
                    (I.at<uchar>(i-1, j-1) + I.at<uchar>(i-1, j) + I.at<uchar>(i-1, j+1));
            
            // Calcula o valor absoluto do gradiente
            sum = std::abs(sum);

            // Garante que o valor esteja no intervalo [0, 255]
            sum = std::min(sum, 255);

            Rx.at<uchar>(i, j) = static_cast<uchar>(sum);
        }
    }
}

// Função para calcular Ry
void calcularRy(const cv::Mat& I, cv::Mat& Ry) {
    int M = I.rows;
    int N = I.cols;
    int sum;

    for (int i = 1; i < M - 1; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            sum = (I.at<uchar>(i-1, j+1) + I.at<uchar>(i, j+1) + I.at<uchar>(i+1, j+1)) -
                (I.at<uchar>(i-1, j-1) + I.at<uchar>(i, j-1) + I.at<uchar>(i+1, j-1));
            
            // Calcula o valor absoluto do gradiente
            sum = std::abs(sum);

            // Garante que o valor esteja no intervalo [0, 255]
            sum = std::min(sum, 255);

            Ry.at<uchar>(i, j) = static_cast<uchar>(sum);
        }
    }
}

// Função para combinar Rx e Ry em R
void combinarRxRy(const cv::Mat& Rx, const cv::Mat& Ry, cv::Mat& R) {
    int M = R.rows;
    int N = R.cols;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int soma = static_cast<int>(Rx.at<uchar>(i, j)) + static_cast<int>(Ry.at<uchar>(i, j));
            R.at<uchar>(i, j) = static_cast<uchar>(std::min(soma, 255));
        }
    }
}
