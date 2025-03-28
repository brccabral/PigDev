#include <pig/PIG.h>

PIGEvento evento; // evento ser tratado a cada passada do loop principal
PIGTeclado meuTeclado; // variável como mapeamento do teclado

int main(int argc, char *args[])
{

    // criando o jogo (aplicação)
    CriaJogo("Meu Jogo");

    // associando o teclado (basta uma única vez) com a variável meuTeclado
    meuTeclado = GetTeclado();

    CriaFonteNormal("assets/fontes/MesloLGS NF Regular.ttf", PIG_FONTE_PADRAO_TAM, PIG_FONTE_PADRAO_COR, PIG_ESTILO_NORMAL);

    // loop principal do jogo
    while (JogoRodando())
    {

        // pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        // aqui o evento deve ser tratado e tudo deve ser atualizado

        // será feita a preparação do frame que será exibido na tela
        IniciaDesenho();

        // todas as chamadas de desenho devem ser feitas aqui na ordem desejada
        EscreverEsquerda("Hello, World", 20, 40, VERMELHO);

        // o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    // o jogo será encerrado
    FinalizaJogo();

    return 0;
}
