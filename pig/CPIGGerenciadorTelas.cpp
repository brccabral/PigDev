#include <pig/CPIGGerenciadorTelas.h>

int CPIGGerenciadorTelas::telaAtual{};
void *CPIGGerenciadorTelas::dadosGerais{};
PIGComportamentoTela CPIGGerenciadorTelas::comportamento[PIG_MAX_TELAS]{};
PIGTela CPIGGerenciadorTelas::telas[PIG_MAX_TELAS]{};

void CPIGGerenciadorTelas::Inicia()
{
    telaAtual = -1;
    for (int i = 0; i < PIG_MAX_TELAS; i++)
    {
        telas[i] = NULL;
        comportamento[i].dados = NULL;
        comportamento[i].acaoCria = NULL;
        comportamento[i].acaoDestroi = NULL;
        comportamento[i].acaoCarrega = NULL;
        comportamento[i].acaoDescarrega = NULL;
        comportamento[i].acaoAtualiza = NULL;
        comportamento[i].acaoDesenha = NULL;
        comportamento[i].acaoTrataEvento = NULL;
    }
}

void CPIGGerenciadorTelas::Encerra()
{
    for (auto &tela: telas)
    {
        delete tela;
    }
}

PIGTela CPIGGerenciadorTelas::GetTela(int idTela)
{
    if (idTela < 0 || idTela >= PIG_MAX_TELAS || telas[idTela] == NULL)
    {
        throw CPIGErroIndice(idTela, "telas");
    }
    return telas[idTela];
}

void CPIGGerenciadorTelas::SetDadosGerais(void *dados)
{
    dadosGerais = dados;
}

void *CPIGGerenciadorTelas::GetDadosGerais()
{
    return dadosGerais;
}

int CPIGGerenciadorTelas::CriaTela(
        int idTela, bool criarBackground, bool carregarBackground, const string &imgFundo,
        int idJanela)
{
    if (idTela >= 0 && idTela < PIG_MAX_TELAS)
    {
        if (telas[idTela] != NULL)
        {
            printf("Tela %d criada novamente\n", idTela);
            return 0;
        }

        telas[idTela] = new CPIGTela(
                idTela, comportamento[idTela], criarBackground, carregarBackground, imgFundo,
                idJanela);

        if (telaAtual == -1)
        { // se for a primeira tela criada, ela será considerada telaAtual
            telaAtual = idTela;
        }
        return 1;
    }
    return -1;
}

int CPIGGerenciadorTelas::InsereTela(int idTela, PIGTela tela)
{
    if (idTela >= 0 && idTela < PIG_MAX_TELAS)
    {
        if (telas[idTela] != NULL)
        {
            printf("Tela %d criada novamente\n", idTela);
            return 0;
        }

        telas[idTela] = tela;

        if (telaAtual == -1)
        { // se for a primeira tela criada, ela será considerada telaAtual
            telaAtual = idTela;
        }
        return 1;
    }
    return -1;
}

void CPIGGerenciadorTelas::SetComportamento(
        int idTela, void *dados, PIGFuncaoSimples cria, PIGFuncaoSimples destroi,
        PIGFuncaoSimples carrega, PIGFuncaoSimples descarrega, PIGFuncaoSimples atualiza,
        PIGFuncaoSimples desenha, PIGFuncaoEvento trataEvento)
{
    if (idTela >= 0 && idTela < PIG_MAX_TELAS)
    {
        PIGComportamentoTela comporta = {dados,      cria,     destroi, carrega,
                                         descarrega, atualiza, desenha, trataEvento};
        comportamento[idTela] = comporta;
        if (telas[idTela])
        {
            telas[idTela]->SetComportamento(comporta);
        }
    }
}

int CPIGGerenciadorTelas::DestroiTela(int idTela)
{
    if (idTela < 0 || idTela >= PIG_MAX_TELAS || telas[idTela] == NULL)
    {
        throw CPIGErroIndice(idTela, "telas");
    }
    delete telas[idTela];
    telas[idTela] = NULL;
    return 1;
}

PIGEstadoTela CPIGGerenciadorTelas::GetEstadoTela(int idTela)
{
    if (idTela < 0 || idTela >= PIG_MAX_TELAS)
    {
        throw CPIGErroIndice(idTela, "telas");
    }
    if (telas[idTela] == NULL)
    {
        return PIG_TELA_INEXISTENTE;
    }
    return telas[idTela]->GetEstado();
}

int CPIGGerenciadorTelas::TrataEvento(const PIGEvento &evento)
{
    return GetTela(telaAtual)->TrataEvento(evento);
}

void CPIGGerenciadorTelas::PreparaMudancaTela(
        int novaTela, double tempoSaida, bool destroiDescarregar)
{
    GetTela(telaAtual)->PreparaSaida(novaTela, tempoSaida, destroiDescarregar);
}

int CPIGGerenciadorTelas::Atualiza()
{
    PIGTela atual = GetTela(telaAtual);
    int novaTela = atual->Atualiza();
    if (novaTela >= 0)
    {
        // printf("mudando para %d\n",novaTela);
        atual->DescarregaTela();
        if (atual->GetDestruirAoDescarregar())
        {
            DestroiTela(telaAtual);
        }
        // printf("descarreg %d\n",novaTela);
        telaAtual = novaTela;
        atual = GetTela(telaAtual);
        if (atual->CarregaTela() > 0)
        {
            // printf("carregando %d\n",novaTela);
            return atual->Atualiza();
        }
        return telaAtual;
    }
    return -1;
}

int CPIGGerenciadorTelas::Desenha()
{
    return GetTela(telaAtual)->Desenha();
}
