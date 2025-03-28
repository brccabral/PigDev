#include <pig/CPIGGerenciadorJanelas.h>
#include <pig/CPIGErros.h>

int CPIGGerenciadorJanelas::qtdJanelas{};
PIGJanela CPIGGerenciadorJanelas::janelas[PIG_MAX_JANELAS]{};

void CPIGGerenciadorJanelas::Inicia(const string &nome, int altura, int largura)
{
    janelas[qtdJanelas++] = new CPIGJanela(nome, qtdJanelas, altura, largura);
}

void CPIGGerenciadorJanelas::Encerra()
{
    for (int i = 0; i < qtdJanelas; i++)
    {
        if (janelas[i])
        {
            delete janelas[i];
        }
    }
}

int CPIGGerenciadorJanelas::GetQtdJanelas()
{
    int resp = qtdJanelas;
    for (int i = 0; i < qtdJanelas; i++)
    {
        if (GetJanela(i)->GetFechada())
        {
            resp--;
        }
    }
    return resp;
}

int CPIGGerenciadorJanelas::CriaJanela(const string &nome, int altura, int largura)
{
    if (qtdJanelas == PIG_MAX_JANELAS)
    {
        return -1;
    }
    janelas[qtdJanelas++] = new CPIGJanela(nome, qtdJanelas, altura, largura);
    return qtdJanelas - 1; // foi incrementada logo acima
}

PIGJanela CPIGGerenciadorJanelas::GetJanela(int idJanela)
{
    if (idJanela < 0 || idJanela >= qtdJanelas || janelas[idJanela] == NULL)
    {
        throw CPIGErroIndice(idJanela, "janelas");
    }
    return janelas[idJanela];
}

void CPIGGerenciadorJanelas::IniciaDesenho(int idJanela)
{
    if (idJanela > -1)
    {
        GetJanela(idJanela)->IniciaDesenho();
    }
    else
    {
        for (int i = 0; i < qtdJanelas; i++)
        {
            GetJanela(i)->IniciaDesenho();
        }
    }
}

void CPIGGerenciadorJanelas::EncerraDesenho(int idJanela)
{
    if (idJanela > -1)
    {
        GetJanela(idJanela)->EncerraDesenho();
    }
    else
    {
        for (int i = 0; i < qtdJanelas; i++)
        {
            GetJanela(i)->EncerraDesenho();
        }
    }
}
