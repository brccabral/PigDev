#ifndef _CPIGANIMACAO_
#define _CPIGANIMACAO_
//
#include <cstddef>
#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGObjeto.h>
#include <pig/CPIGModoAnimacao.h>
#include <pig/CPIGGerenciadorTimers.h>

class CPIGAnimacao : public CPIGObjeto
{

private:

    PIGModoAnimacao modos[PIG_MAX_MODOS] = {}; // modos da animação
    int idTimer; // timer da animação (se estiver sendo utilizado o gerenciador de timers)
    SDL_Point offset =
            {}; // offset (x,y) a ser utilizado junto com a posição (x,y) para desenhar oa animação
    int modoAtual; // número que indica o modo atual

    // muda o frame a ser exibido do modo atual
    void AtualizaFrameAtual(PIGModoAnimacao modo);

public:

    // cria uma animação a partir de um arquivo de spritesheet
    CPIGAnimacao(
            int idAnimacao, const string &nomeArq, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int idJanela = 0);
    // cria uma animação a partir deoutra animação já existente
    CPIGAnimacao(
            int idAnimacao, CPIGAnimacao *base, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    // cria uma animação a partir de um objeto
    CPIGAnimacao(
            int idAnimacao, PIGObjeto base, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    // destroi uma animação
    ~CPIGAnimacao() override;
    // cria um modo vazio, sem frames associados
    void CriaModo(int idModo, int loop);
    // insere um frame em um dos modos
    void InsereFrame(
            int idModo, int idFrame, float delayFrame, int audio, int alturaFrame = -1,
            int larguraFrame = -1) const;
    // muda o modo atual
    void MudaModo(int idModo, int indiceFrame = 0, int forcado = 1);
    // retorna o númerodo modo atual
    int GetModoAtual() const;
    // desenha a animação
    int Desenha() override;
    // pausa a animação
    void Pausa() const;
    // despausa a animação
    void Despausa() const;
    // define o tempo de um frame já criado
    void SetTempoFrame(int modo, int indiceFrame, double tempo) const;
    // define se um modo já criado terá ou não loop
    void SetLoopModo(int modo, int loop) const;
    // define o audio de um frame já criado
    void SetAudioFrame(int modo, int indiceFrame, int idAudio) const;
    // retorna o tempo de duração de um frame já criado
    double GetTempoFrame(int modo, int indiceFrame) const;
    // retorna se um modo tem ou não loop
    bool GetLoopModo(int modo) const;
    // retorna o audio de um frame já criado
    int GetAudioFrame(int modo, int indiceFrame) const;
};

typedef CPIGAnimacao *PIGAnimacao;
#endif // _CPIGANIMACAO_
