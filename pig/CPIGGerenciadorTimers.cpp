#include <pig/CPIGGerenciadorTimers.h>

CPIGRepositorio<PIGTimer> *CPIGGerenciadorTimers::timers{};
vector<int> CPIGGerenciadorTimers::grupos[PIG_MAX_GRUPOS_TIMERS]{};

void CPIGGerenciadorTimers::Inicia()
{
    timers = new CPIGRepositorio<PIGTimer>(PIG_MAX_TIMERS, "timers");
}

void CPIGGerenciadorTimers::Encerra()
{
    delete timers;
}

PIGTimer CPIGGerenciadorTimers::GetTimer(int idTimer)
{
    return timers->GetElemento(idTimer);
}

int CPIGGerenciadorTimers::CriaTimer(bool congelado)
{
    return timers->Insere(new CPIGTimer(congelado));
}

int CPIGGerenciadorTimers::InsereTimer(PIGTimer timer)
{
    return timers->Insere(timer);
}

void CPIGGerenciadorTimers::DestroiTimer(int idTimer)
{
    timers->Remove(idTimer);
}

void CPIGGerenciadorTimers::PausaTodos()
{
    PIGTimer t = timers->GetPrimeiroElemento();
    while (t != NULL)
    {
        t->PausaGeral();
        t = timers->GetProximoElemento();
    }
}

void CPIGGerenciadorTimers::DespausaTodos()
{
    PIGTimer t = timers->GetPrimeiroElemento();
    while (t != NULL)
    {
        t->DespausaGeral();
        t = timers->GetProximoElemento();
    }
}

int CPIGGerenciadorTimers::AssociaTimerGrupo(int idTimer, int idGrupo)
{
    if (idGrupo < 0 || idGrupo >= PIG_MAX_GRUPOS_TIMERS)
    {
        return 0;
    }
    timers->GetElemento(idTimer); // apenas para checar se o idTimer é valido
    grupos[idGrupo].push_back(idTimer);
    return 1;
}

int CPIGGerenciadorTimers::DesassociaTimerGrupo(int idTimer, int idGrupo)
{
    if (idGrupo < 0 || idGrupo >= PIG_MAX_GRUPOS_TIMERS)
    {
        return 0;
    }
    timers->GetElemento(idTimer); // apenas para checar se o idTimer é valido
    vector<int>::iterator it =
            ranges::find(grupos[idGrupo].begin(), grupos[idGrupo].end(), idTimer);
    if (it != grupos[idGrupo].end())
    {
        grupos[idGrupo].erase(it);
        return 1;
    }
    return 0;
}

int CPIGGerenciadorTimers::PausaGrupo(int idGrupo)
{
    if (idGrupo < 0 || idGrupo >= PIG_MAX_GRUPOS_TIMERS)
    {
        return -1;
    }
    int cont = 0;
    for (int i: grupos[idGrupo])
    {
        PIGTimer t = timers->GetElemento(i);
        if (t)
        {
            t->Pausa();
        }
        cont++;
    }
    return cont;
}

int CPIGGerenciadorTimers::DespausaGrupo(int idGrupo)
{
    if (idGrupo < 0 || idGrupo >= PIG_MAX_GRUPOS_TIMERS)
    {
        return -1;
    }
    int cont = 0;
    for (int i: grupos[idGrupo])
    {
        PIGTimer t = timers->GetElemento(i);
        if (t)
        {
            t->Despausa();
        }
        cont++;
    }
    return cont;
}

int CPIGGerenciadorTimers::ReiniciaGrupo(int idGrupo, bool valor)
{
    if (idGrupo < 0 || idGrupo >= PIG_MAX_GRUPOS_TIMERS)
    {
        return -1;
    }
    int cont = 0;
    for (int i: grupos[idGrupo])
    {
        PIGTimer t = timers->GetElemento(i);
        if (t)
        {
            t->Reinicia(valor);
        }
        cont++;
    }
    return cont;
}
