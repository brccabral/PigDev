#ifndef _CPIGMODOANIMACAO_
#define _CPIGMODOANIMACAO_

#include <vector>

using namespace std;

// struct com as informações de cada estágio (frame) do modo
typedef struct
{
    int frame; // número do frame
    double tempo; // tempo de exibição do frame
    int audio; // audio a ser tocado quando o frame for exibido
    int altura, largura;
} PIGEstagioAnimacao;

class CPIGModoAnimacao
{

private:

    size_t frameAtual{}; // número do frame atual
    bool loop{}; // se o modo tem loop ou não
    bool encerrou; // indica se o modo terminou de eibir todos os frames
    vector<PIGEstagioAnimacao> estagios; // informações dos estágios (frames) que compõem o modo

public:

    // construtor do modo
    explicit CPIGModoAnimacao(bool emLoop = true);
    explicit CPIGModoAnimacao(const CPIGModoAnimacao *modoBase);
    // destrutor
    ~CPIGModoAnimacao();
    // cria um novo estágio (frame)
    int InsereEstagio(int idFrame, double tempo, int idAudio, int altura, int largura);
    // define o tempo de um estágio (frame) já criado
    void SetTempo(int idEstagio, double novoTempo);
    // define o audio de um estágio (frame) já criado
    void SetAudio(int idEstagio, int idAudio);
    // define se o modo estraáem loop ou não
    void SetLoop(bool emLoop);
    // retorna se o modo está em loop ou não
    [[nodiscard]] bool GetLoop() const;
    // muda arbitrariamente o índice (posição da sequência de frames) do frame a ser exibido
    void SetIndiceFrameAtual(size_t indice);
    // retorna o índice (posiçãod o vetor) do frame atual
    [[nodiscard]] int GetIndiceFrameAtual() const;
    // retorna o número do frame atual
    int GetFrameAtual();
    // retorna o audio do frame atual
    int GetAudioAtual();
    // retorna o tempo de exibição do frame atual
    double GetTempoAtual();
    // retorna o audio de um frame já criado (pelo seu índice no vetor)
    int GetAudioFrame(int indiceFrame);
    // retorna o tempo de um frame já criado (pelo seu índice no vetor)
    double GetTempoFrame(int indiceFrame);
    void GetDimensoesAtual(int &altura, int &largura);
    // teste se já passou o tempo necessário para mudar de frame
    int TestaTempo(double tempoDecorrido);
    // retorna se o modo já exibiu todos os frames (apenas se não estiver em loop)
    [[nodiscard]] bool GetEncerrou() const;
};

typedef CPIGModoAnimacao *PIGModoAnimacao;
#endif // _CPIGMODOANIMACAO_
