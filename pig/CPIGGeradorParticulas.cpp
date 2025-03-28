#include <pig/CPIGGeradorParticulas.h>
#include <pig/CPIGGerenciadorSprites.h>
#ifdef PIGCOMAUDIO
#include <pig/CPIGGerenciadorAudios.h>
#endif

void CPIGGeradorParticulas::IniciaBase(
        int maximoParticulas, int audioCriacao, int audioEncerramento, const PIGCor *corFundo,
        bool retiraFundo)
{
    maxParticulas = maximoParticulas;
    audioInicio = audioCriacao;
    audioFim = audioEncerramento;
    corFundoImagem = corFundo;
    retiraFundoImagem = retiraFundo;
    maxTempo = 9999999;
    maxEspaco = {INT_MIN, INT_MIN, INT_MAX, INT_MAX};
    hpParticulas = 1;
    automacaoGDP = NULL;
}

void CPIGGeradorParticulas::AtualizaParticulas()
{
    unsigned int i = 0;
    while (i < parts.size())
    {
        // printf("viva %d %d %d\n",i,parts[i]->ChecaViva(),parts[i]->GetId());
        if (!parts[i]->ChecaViva())
        {
            ;
            // printf("antes del %d (%f)\n",parts[i]->GetID(),maxTempo);
            CPIGGerenciadorSprites::DestroiAnimacao(parts[i]->GetId());

#ifdef PIGCOMAUDIO
            if (audioFim >= 0)
            {
                CPIGGerenciadorAudios::Play(audioFim);
            }
#endif

            parts.erase(parts.begin() + i);
            // printf("deletou %d %d size %d\n",id,i,parts.size());
        }
        else
        {
            parts[i]->TrataAutomacao();
            // printf("atualizei part %d\n",i);
            i++;
        }
    }
}

CPIGGeradorParticulas::CPIGGeradorParticulas(
        int idGerador, int maximoParticulas, PIGObjeto objBase, int audioCriacao,
        int audioEncerramento, bool retiraFundo, const PIGCor *corFundo, int idJanela)
    : CPIGAnimacao(idGerador, objBase, retiraFundo, corFundo, idJanela)
{
    IniciaBase(maximoParticulas, audioCriacao, audioEncerramento, corFundo, retiraFundo);
}

CPIGGeradorParticulas::CPIGGeradorParticulas(
        int idGerador, int maximoParticulas, PIGAnimacao animaBase, int audioCriacao,
        int audioEncerramento, bool retiraFundo, const PIGCor *corFundo, int idJanela)
    : CPIGAnimacao(idGerador, animaBase, retiraFundo, corFundo, idJanela)
{
    IniciaBase(maximoParticulas, audioCriacao, audioEncerramento, corFundo, retiraFundo);
}

CPIGGeradorParticulas::CPIGGeradorParticulas(
        int idGerador, int maximoParticulas, const string &nomeArqImagem, int audioCriacao,
        int audioEncerramento, bool retiraFundo, const PIGCor *corFundo, int idJanela)
    : CPIGAnimacao(idGerador, nomeArqImagem, retiraFundo, corFundo, idJanela)
{
    IniciaBase(maximoParticulas, audioCriacao, audioEncerramento, corFundo, retiraFundo);
}

void CPIGGeradorParticulas::DefineLimites(SDL_Rect espacoMax, double tempoMax)
{
    maxEspaco = espacoMax;
    maxTempo = tempoMax;
}

int CPIGGeradorParticulas::CriaParticula()
{
    if (parts.size() >= maxParticulas)
    {
        return -1;
    }

    int idPart = CPIGGerenciadorSprites::GetProxIndiceAnimacao();
    PIGParticula part = new CPIGParticula(
            idPart, this, hpParticulas, retiraFundoImagem, corFundoImagem, idJanela);
    CPIGGerenciadorSprites::InsereAnimacao(part);

    part->DefineLimites(maxEspaco, maxTempo);
    // printf("com tempo %f\n",maxTempo);
    part->IniciaAutomacao();
    parts.push_back(part);

#ifdef PIGCOMAUDIO
    if (audioInicio >= 0)
    {
        CPIGGerenciadorAudios::Play(audioInicio);
    }
#endif

    return parts.size();
}

void CPIGGeradorParticulas::MudaHP(int novoValor)
{
    hpParticulas = novoValor;
}

int CPIGGeradorParticulas::Desenha()
{
    AtualizaParticulas();
    // CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(pos.x,pos.y,10,10,ROXO);
    for (PIGParticula part: parts)
    {
        part->Desenha();
    }

    return 1;
}

bool CPIGGeradorParticulas::Colisao(PIGObjeto outro)
{
    bool resp = false;
    for (PIGParticula part: parts)
    {
        resp |= part->Colisao(outro);
    }
    return resp;
}

bool CPIGGeradorParticulas::Colisao()
{
    bool resp = false;
    unsigned int i = 0;
    while (i < parts.size() - 1)
    {
        unsigned int j = i + 1;
        while (j < parts.size())
        {
            resp |= parts[i]->Colisao(parts[j]);
            j++;
        }
        i++;
    }
    return resp;
}

int CPIGGeradorParticulas::GetQtdAtivas()
{
    return parts.size();
}

void CPIGGeradorParticulas::InsereTransicaoGDP(PIGTransicao t)
{
    InsereTransicao(t, automacaoGDP);
}

void CPIGGeradorParticulas::InsereTransicaoGDP(double tempo, const PIGEstadoTransicao &estado)
{
    InsereTransicao(tempo, estado, automacaoGDP);
}

void CPIGGeradorParticulas::LeTransicoesGDP(const string &nomeArq)
{
    LeTransicoes(nomeArq, automacaoGDP);
}

void CPIGGeradorParticulas::IniciaAutomacaoGDP()
{
    IniciaAutomacao(automacaoGDP);
}

void CPIGGeradorParticulas::LimpaTransicoesGDP()
{
    LimpaTransicoes(automacaoGDP);
}

bool CPIGGeradorParticulas::ExecutandoTransicaoGDP()
{
    return ExecutandoTransicao(automacaoGDP);
}

void CPIGGeradorParticulas::TrataAutomacaoGDP()
{
    TrataAutomacao(automacaoGDP);
}

void CPIGGeradorParticulas::InsereAcaoGDP(
        double tempo, double repeticao, PIGFuncaoSimples acao, void *param)
{
    InsereAcao(tempo, repeticao, acao, param, automacaoGDP);
}

void CPIGGeradorParticulas::DefineTipoTransicaoGDP(PIGTipoTransicao tipo)
{
    DefineTipoTransicao(tipo, automacaoGDP);
}
