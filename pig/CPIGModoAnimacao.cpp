#include <pig/CPIGModoAnimacao.h>

// construtor do modo
CPIGModoAnimacao::CPIGModoAnimacao(bool emLoop)
{
    frameAtual = 0;
    loop = emLoop;
    encerrou = false;
}

CPIGModoAnimacao::CPIGModoAnimacao(const CPIGModoAnimacao *modoBase)
{
    encerrou = modoBase->encerrou;
    estagios = modoBase->estagios;
    SetLoop(modoBase->loop);
    SetIndiceFrameAtual(modoBase->frameAtual);
}

// destrutor
CPIGModoAnimacao::~CPIGModoAnimacao()
{
    estagios.clear();
}

// cria um novo estágio (frame)
int CPIGModoAnimacao::InsereEstagio(int idFrame, double tempo, int idAudio, int altura, int largura)
{
    PIGEstagioAnimacao estagio = {idFrame, tempo, idAudio, altura, largura};
    estagios.push_back(estagio);
    return estagios.size() - 1;
}

// define o tempo de um estágio (frame) já criado
void CPIGModoAnimacao::SetTempo(int idEstagio, double novoTempo)
{
    estagios[idEstagio].tempo = novoTempo;
}

// define o audio de um estágio (frame) já criado
void CPIGModoAnimacao::SetAudio(int idEstagio, int idAudio)
{
    estagios[idEstagio].audio = idAudio;
}

// define se o modo estraáem loop ou não
void CPIGModoAnimacao::SetLoop(bool emLoop)
{
    loop = emLoop;
}

// retorna se o modo está em loop ou não
[[nodiscard]] bool CPIGModoAnimacao::GetLoop() const
{
    return loop;
}

// muda arbitrariamente o índice (posição da sequência de frames) do frame a ser exibido
void CPIGModoAnimacao::SetIndiceFrameAtual(size_t indice)
{
    if (indice < frameAtual)
    {
        encerrou = false;
    }
    frameAtual = indice;
}

// retorna o índice (posiçãod o vetor) do frame atual
[[nodiscard]] int CPIGModoAnimacao::GetIndiceFrameAtual() const
{
    return frameAtual;
}

// retorna o número do frame atual
int CPIGModoAnimacao::GetFrameAtual()
{
    return estagios[frameAtual].frame;
}

// retorna o audio do frame atual
int CPIGModoAnimacao::GetAudioAtual()
{
    return estagios[frameAtual].audio;
}

// retorna o tempo de exibição do frame atual
double CPIGModoAnimacao::GetTempoAtual()
{
    return estagios[frameAtual].tempo;
}

// retorna o audio de um frame já criado (pelo seu índice no vetor)
int CPIGModoAnimacao::GetAudioFrame(int indiceFrame)
{
    return estagios[indiceFrame].audio;
}

// retorna o tempo de um frame já criado (pelo seu índice no vetor)
double CPIGModoAnimacao::GetTempoFrame(int indiceFrame)
{
    return estagios[indiceFrame].tempo;
}

void CPIGModoAnimacao::GetDimensoesAtual(int &altura, int &largura)
{
    // if (estagios[frameAtual].altura < 0) return false;
    altura = estagios[frameAtual].altura;
    largura = estagios[frameAtual].largura;
    // return true;
}

// teste se já passou o tempo necessário para mudar de frame
int CPIGModoAnimacao::TestaTempo(double tempoDecorrido)
{
    encerrou = false;
    if (estagios.empty())
    {
        return 0; // nao foi criado nenhum estagio nesse modo
    }
    size_t frameAntigo = frameAtual; // armazena o valor do frameAtual
    if (tempoDecorrido >= estagios[frameAtual].tempo)
    {
        if (frameAtual < estagios.size() - 1)
        { // se ainda nao chegou no último estágio
            frameAtual++;
        }
        else
        { // chegou no último estágio
            if (loop)
            {
                frameAtual = 0; // se está em loop, volta ao primeiro frame
            }
            else
            {
                encerrou = true;
            }
        }
    }
    return frameAtual != frameAntigo; // retorna se alterou o frameAtual
}

// retorna se o modo já exibiu todos os frames (apenas se não estiver em loop)
[[nodiscard]] bool CPIGModoAnimacao::GetEncerrou() const
{
    return encerrou;
}
