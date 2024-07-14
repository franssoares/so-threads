/* NOTE:

    IMPORTANTE: Ler o arquivo README.md para o entendimento do código.

    Autor: Franklin Luiz Soares do Nascimento Filho
    E-mail: franklin.soares.701@ufrn.edu.br
    Data: 5 de jul 2:23

    Instituição: Universidade Federal do Rio Grande do Norte (UFRN)
    Disciplina: DCA0108 – Sistemas Operacionais
    Turma: 01, 2024.1
    Horário: 24M12
    Docente: Diogo Pinheiro Fernandes Pedrosa (diogo.pedrosa@ufrn.br)

*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include "../include/operations.h" // Incluímos as declarações das funções e variáveis globais

using namespace std;
using namespace cv;


/* NOTE:
    Este arquivo contém a função principal que utiliza pthreads para realizar o processamento de imagens:
    - Uma thread mãe carrega uma imagem em escala de cinza e inicializa as matrizes Rx, Ry e R.
    - Duas threads filhas calculam as bordas Rx e Ry da imagem.
    - Após o cálculo das bordas, as imagens Rx, Ry são combinadas para formar R, que é então salva em um arquivo.
    - As imagens processadas são exibidas em janelas separadas para visualização.
*/

int main() {
    pthread_t threadmae;

    // Criar a thread mãe para carregar a imagem
    if (pthread_create(&threadmae, NULL, carregarImagem, NULL) != 0) {
        cerr << "Erro ao criar a thread mãe para carregar a imagem!" << endl;
        return -1;
    }
    
    // Esperar a thread mãe terminar
    pthread_join(threadmae, NULL);

    // Verificar se as imagens Rx e Ry foram carregadas corretamente
    if (Rx.empty() || Ry.empty()) {
        cerr << "Erro ao carregar as imagens Rx e Ry!" << endl;
        return -1;
    }

    // Combinar Rx e Ry para obter R
    combinarRxRy(Rx, Ry, R);

    // Salvar R em um arquivo
    imwrite("../imgs/R.png", R);

    // Criar e ajustar o tamanho das janelas para visualização
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

    // Aguardar até que uma tecla seja pressionada para fechar as janelas
    waitKey(0);

    // Fechar todas as janelas
    destroyAllWindows();

    return 0;
}
