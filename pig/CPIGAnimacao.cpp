#include <pig/CPIGAnimacao.h>
#include <pig/CPIGGerenciadorAudios.h>

// muda o frame a ser exibido do modo atual
void CPIGAnimacao::AtualizaFrameAtual(const PIGModoAnimacao modo)
{
    frameAtual = modo->GetFrameAtual();
    CPIGSprite::MudaFrameAtual(frameAtual);

    int a, l;
    modo->GetDimensoesAtual(a, l);
    SetDimensoes(a, l);

#ifdef PIGCOMAUDIO
    int audio = modo->GetAudioAtual();
    if (audio >= 0)
    {
        CPIGGerenciadorAudios::Play(audio);
    }
#endif

    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(false);
}


// cria uma animação a partir de um arquivo de spritesheet
CPIGAnimacao::CPIGAnimacao(
        const int idAnimacao, const string &nomeArq, const int retiraFundo, const PIGCor *corFundo,
        const int idJanela)
    : CPIGObjeto(idAnimacao, nomeArq, retiraFundo, corFundo, idJanela)
{
    modoAtual = 0;

    for (auto &modo: modos)
    {
        modo = NULL;
    }

    idTimer = CPIGGerenciadorTimers::CriaTimer();
}

// cria uma animação a partir deoutra animação já existente
CPIGAnimacao::CPIGAnimacao(
        const int idAnimacao, CPIGAnimacao *base, const int retiraFundo, const PIGCor *corFundo,
        const int idJanela)
    : CPIGObjeto(idAnimacao, (PIGObjeto) base, retiraFundo, corFundo, idJanela)
{
    for (int i = 0; i < PIG_MAX_MODOS; i++)
    {
        if (base->modos[i])
        {
            modos[i] = new CPIGModoAnimacao(base->modos[i]);
        }
        else
        {
            modos[i] = NULL;
        }
    }

    offset = base->offset;
    modoAtual = base->modoAtual;

    idTimer = CPIGGerenciadorTimers::CriaTimer();
}

// cria uma animação a partir de um objeto
CPIGAnimacao::CPIGAnimacao(
        const int idAnimacao, const PIGObjeto base, const int retiraFundo, const PIGCor *corFundo,
        const int idJanela)
    : CPIGObjeto(idAnimacao, base, retiraFundo, corFundo, idJanela)
{
    modoAtual = 0;

    for (auto &modo: modos)
    {
        modo = NULL;
    }

    idTimer = CPIGGerenciadorTimers::CriaTimer();
}

// destroi uma animação
CPIGAnimacao::~CPIGAnimacao()
{
    for (const auto &modo: modos)
    {
        delete modo;
    }

    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

// cria um modo vazio, sem frames associados
void CPIGAnimacao::CriaModo(const int idModo, const int loop)
{
    if (modos[idModo])
    {
        delete modos[idModo];
    }
    modos[idModo] = new CPIGModoAnimacao(loop);
}

// insere um frame em um dos modos
void CPIGAnimacao::InsereFrame(
        const int idModo, const int idFrame, const float delayFrame, const int audio,
        int alturaFrame, int larguraFrame) const
{
    if (alturaFrame == -1)
    {
        alturaFrame = alt;
    }
    if (larguraFrame == -1)
    {
        larguraFrame = larg;
    }
    modos[idModo]->InsereEstagio(idFrame, delayFrame, audio, alturaFrame, larguraFrame);
}

// muda o modo atual
void CPIGAnimacao::MudaModo(const int idModo, const int indiceFrame, const int forcado)
{
    if (forcado || (modos[modoAtual] && modos[modoAtual]->GetEncerrou()))
    {
        modoAtual = idModo;

        modos[modoAtual]->SetIndiceFrameAtual(indiceFrame);

        AtualizaFrameAtual(modos[modoAtual]);
    }
}

// retorna o númerodo modo atual
int CPIGAnimacao::GetModoAtual() const
{
    return modoAtual;
}

// desenha a animação
int CPIGAnimacao::Desenha()
{
    int resp = 0; // 0 indica que que o modo de animação atual não encerrou

    if (modos[modoAtual] != NULL)
    {
        float tempoDecorrido = CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();

        if (modos[modoAtual]->TestaTempo(tempoDecorrido))
        {
            AtualizaFrameAtual(modos[modoAtual]);
        }
        else
        {
            resp = modos[modoAtual]->GetEncerrou(); // pode ter encerrado de desenhar todos os
        }
        // estágios do modo
    }

    int px = pos.x + offset.x;
    int py = pos.y + offset.y;

    CPIGObjeto::Move(px, py);
    CPIGObjeto::Desenha();

    px -= offset.x;
    py -= offset.y;

    CPIGObjeto::Move(px, py);

    return resp;
}

// pausa a animação
void CPIGAnimacao::Pausa() const
{
    CPIGGerenciadorTimers::GetTimer(idTimer)->Pausa();
}

// despausa a animação
void CPIGAnimacao::Despausa() const
{
    CPIGGerenciadorTimers::GetTimer(idTimer)->Despausa();
}

// define o tempo de um frame já criado
void CPIGAnimacao::SetTempoFrame(const int modo, const int indiceFrame, const double tempo) const
{
    modos[modo]->SetTempo(indiceFrame, tempo);
}

// define se um modo já criado terá ou não loop
void CPIGAnimacao::SetLoopModo(const int modo, const int loop) const
{
    modos[modo]->SetLoop(loop);
}

// define o audio de um frame já criado
void CPIGAnimacao::SetAudioFrame(const int modo, const int indiceFrame, const int idAudio) const
{
    modos[modo]->SetAudio(indiceFrame, idAudio);
}

// retorna o tempo de duração de um frame já criado
double CPIGAnimacao::GetTempoFrame(const int modo, const int indiceFrame) const
{
    return modos[modo]->GetTempoFrame(indiceFrame);
}

// retorna se um modo tem ou não loop
bool CPIGAnimacao::GetLoopModo(const int modo) const
{
    return modos[modo]->GetLoop();
}

// retorna o audio de um frame já criado
int CPIGAnimacao::GetAudioFrame(const int modo, const int indiceFrame) const
{
    return modos[modo]->GetAudioFrame(indiceFrame);
}
