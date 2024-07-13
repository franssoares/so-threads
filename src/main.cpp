/* NOTE:

    IMPORTANTE: Ler o arquivo README.md para o entendimento do código.

    Autor: Franklin Luiz Soares do Nascimento Filho
    E-mail: franklin.soares.701@ufrn.edu.br
    Data: 4 de jul 15:23

    Instituição: Universidade Federal do Rio Grande do Norte (UFRN)
    Disciplina: DCA0108 – Sistemas Operacionais
    Turma: 01, 2024.1
    Horário: 24M12
    Docente: Diogo Pinheiro Fernandes Pedrosa (diogo.pedrosa@ufrn.br)

*/

// Bibliotecas
#include <iostream> //I/O
#include <opencv2/opencv.hpp> //uso em imagens
#include "../include/operations.h" //uso para processamento das imagens
#include <vector> //contêiner do STL
#include <sys/wait.h> //uso da interface dedicada do ubuntu
#include <unistd.h> //uso da interface POSIX

// Diretiva de Namespace
using namespace std;
using namespace cv;

/* NOTE:

    Nesse arquivo usa-se a biblioteca opencv para criar instancias para image, Rx, Ry e R. Seguindo o fluxo dos processos para cada
    procedimento de calcular as bordas e, por fim, a união das imagens.
    
*/

// Função principal
int main() {

    // Ler uma imagem do arquivo
    Mat image = imread("../assets/coins.png", IMREAD_GRAYSCALE);

    // Verificar se a leitura foi bem-sucedida
    if (image.empty()) {
        cerr << "Erro ao ler a imagem!" << endl;
        return -1;
    }

    // Dimensões da imagem
    int rows = image.rows;
    int cols = image.cols;

    // Matrizes para Rx, Ry e R
    Mat Rx(rows, cols, CV_8UC1);
    Mat Ry(rows, cols, CV_8UC1);
    Mat R(rows, cols, CV_8UC1);

    // Processo filho para calcular Rx
    pid_t pidRx = fork();
    if (pidRx == 0) {
        // Processo filho para Rx
        calcularRx(image, Rx);

        // Salvar Rx em um arquivo 
        imwrite("../imgs/Rx.png", Rx);

        exit(0);
    } else if (pidRx < 0) {
        cerr << "Erro ao criar processo filho para calcular Rx!" << endl;
        return -1;
    }

    // Processo pai aguarda processo filho Rx
    waitpid(pidRx, NULL, 0);

    // Processo filho para calcular Ry
    pid_t pidRy = fork();
    if (pidRy == 0) {
        // Processo filho para Ry
        calcularRy(image, Ry);

        // Salvar Ry em um arquivo
        imwrite("../imgs/Ry.png", Ry);

        exit(0);
    } else if (pidRy < 0) {
        cerr << "Erro ao criar processo filho para calcular Ry!" << endl;
        return -1;
    }

    // Processo pai aguarda processo filho Ry
    waitpid(pidRy, NULL, 0);

    // Os dados estaticos de Rx e Ry sao perdidos dentro de processos, mas dentro dos processos sao criadas as imagens de Rx e Ry
    Rx = imread("../imgs/Rx.png", IMREAD_GRAYSCALE);
    Ry = imread("../imgs/Ry.png", IMREAD_GRAYSCALE);

    // Combinar Rx e Ry para obter R
    combinarRxRy(Rx, Ry, R);

    // Salvar R em um arquivo (exemplo simples, pode ser ajustado conforme necessidade)
    imwrite("../imgs/R.png", R);

    // Criar e ajustar o tamanho das janelas
    namedWindow("Imagem Escolhida", WINDOW_NORMAL);
    resizeWindow("Imagem Escolhida", 640, 480);

    namedWindow("Imagem Rx", WINDOW_NORMAL);
    resizeWindow("Imagem Rx", 640, 480);

    namedWindow("Imagem Ry", WINDOW_NORMAL);
    resizeWindow("Imagem Ry", 640, 480);

    namedWindow("Imagem R", WINDOW_NORMAL);
    resizeWindow("Imagem R", 640, 480);

    // Exibir as imagens nas respectivas janelas
    imshow("Imagem Escolhida", image);
    imshow("Imagem Rx", Rx);
    imshow("Imagem Ry", Ry);
    imshow("Imagem R", R);

    // Aguardar até que uma tecla seja pressionada
    waitKey(0);

    // Fechar todas as janelas
    destroyAllWindows();

    // Finaliza a main
    return 0;
}