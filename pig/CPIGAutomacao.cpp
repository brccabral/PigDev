#include <pig/CPIGAutomacao.h>

CPIGAutomacao::CPIGAutomacao(const int idProprietario)
{
    idDono = idProprietario;
    tipo = PIG_TRANSICAO_NORMAL;
    transAtual = 0;
    somaTrans = +1;
    timerAcoes = new CPIGTimer(true);
    iniciado = false;
}

CPIGAutomacao::CPIGAutomacao(const int idProprietario, const CPIGAutomacao *outro)
{
    idDono = idProprietario;
    tipo = outro->tipo;
    transAtual = outro->transAtual;
    somaTrans = outro->somaTrans;
    timerAcoes = new CPIGTimer(true);
    timelineAcoes = outro->timelineAcoes;
    for (auto *transicoe: outro->transicoes)
    {
        PIGTransicao t = new CPIGTransicao(transicoe);
        transicoes.push_back(t);
    }
    iniciado = false;
}

CPIGAutomacao::~CPIGAutomacao()
{
    delete timerAcoes;
    LimpaTransicoes();
    timelineAcoes.clear();
}

bool CPIGAutomacao::TemTransicoes() const
{
    return !transicoes.empty();
}

void CPIGAutomacao::InsereTransicao(CPIGTransicao *t)
{
    transicoes.push_back(t);
}

void CPIGAutomacao::SetTipoTransicao(const PIGTipoTransicao valor)
{
    tipo = valor;
}

void CPIGAutomacao::IniciaAutomacao(const PIGEstadoTransicao &inicial)
{
    iniciado = true;
    timerAcoes->Despausa();
    if (transAtual < (int) transicoes.size())
    {
        transAtual = 0;
        transicoes[transAtual]->IniciaTransicao(inicial);
    }
}

void CPIGAutomacao::PausaAutomacao() const
{
    timerAcoes->Pausa();
    if (transAtual < (int) transicoes.size())
    {
        transicoes[transAtual]->Pausa();
    }
}

void CPIGAutomacao::DespausaAutomacao() const
{
    timerAcoes->Despausa();
    if (transAtual < (int) transicoes.size())
    {
        transicoes[transAtual]->Despausa();
    }
}

bool CPIGAutomacao::ExecutandoTransicao() const
{
    return iniciado && transAtual < (int) transicoes.size();
}

PIGTransicao CPIGAutomacao::GetTransicaoAtual()
{
    if ((int) transicoes.size() <= transAtual || !iniciado)
    {
        return NULL;
    }
    const double sobra = transicoes[transAtual]->CalculaTransicao();
    if (sobra >= 0)
    {
        const PIGEstadoTransicao atual = transicoes[transAtual]->GetFim();
        if (tipo == PIG_TRANSICAO_VAIVEM)
        {
            transAtual += somaTrans;
            if (transAtual == (int) transicoes.size() || transAtual == -1)
            {
                somaTrans = -somaTrans;
                transAtual += somaTrans;
                for (auto &transicoe: transicoes)
                {
                    transicoe->Inverte();
                }
            }
        }
        else
        {
            transAtual++;
            if (tipo == PIG_TRANSICAO_LOOP)
            {
                transAtual %= transicoes.size(); // volta à transicao com índice 0
            }
            else
            {
                if (transAtual == (int) transicoes.size())
                {
                    return transicoes[transAtual - 1]; // as transicoes acabaram
                }
            }
        }
        transicoes[transAtual]->IniciaTransicao(atual, sobra);
    }
    return transicoes[transAtual];
}

void CPIGAutomacao::LimpaTransicoes()
{
    for (auto &transicoe: transicoes)
    {
        delete transicoe;
    }
    transicoes.clear();
    transAtual = 0;
}

void CPIGAutomacao::LimpaAcoes()
{
    timelineAcoes.clear();
}

bool CPIGAutomacao::TemAcoes() const
{
    return !timelineAcoes.empty();
}

int CPIGAutomacao::InsereAcao(
        const PIGFuncaoSimples acao, double inicio, const double repeticao, void *param)
{
    // printf("inserindo acao no tempo %.2f com rep %.2f\n",inicio,repeticao);
    unsigned int i = 0;
    inicio += timerAcoes->GetTempoDecorrido();
    while (i < timelineAcoes.size() && timelineAcoes[i].inicio < inicio)
    {
        i++;
    }
    timelineAcoes.insert(timelineAcoes.begin() + i, {inicio, repeticao, acao, param});
    return i;
}

int CPIGAutomacao::TrataAcao()
{
    PIGAcao acaoAtual;
    while (!timelineAcoes.empty() &&
           timerAcoes->GetTempoDecorrido() >= (acaoAtual = timelineAcoes[0]).inicio)
    {
        acaoAtual.acao(idDono, acaoAtual.param);
        // printf("exec acao no tempo %.2f\n",acaoAtual.inicio);
        if (acaoAtual.tempoRepeticao > 0)
        {
            InsereAcao(
                    acaoAtual.acao, acaoAtual.tempoRepeticao, acaoAtual.tempoRepeticao,
                    acaoAtual.param); //
        }
        timelineAcoes.erase(timelineAcoes.begin());
    }
    return timelineAcoes.size();
}
