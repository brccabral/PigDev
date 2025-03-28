#include <pig/CPIGGerenciadorGDP.h>

CPIGRepositorio<PIGGeradorParticulas> *CPIGGerenciadorGDP::geradores{};

PIGGeradorParticulas CPIGGerenciadorGDP::GetGerador(int idGerador)
{
    return geradores->GetElemento(idGerador);
}

void CPIGGerenciadorGDP::Inicia()
{
    geradores = new CPIGRepositorio<PIGGeradorParticulas>(PIG_MAX_GERADORPARTICULAS, "geradores");
}

void CPIGGerenciadorGDP::Encerra()
{
    delete geradores;
}

int CPIGGerenciadorGDP::CriaGeradorParticulas(
        int maxParticulas, const string &nomeArquivoBMP, int audioCriacao, int audioEncerramento,
        bool retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = geradores->ProxID();
    return geradores->Insere(new CPIGGeradorParticulas(
            id, maxParticulas, nomeArquivoBMP, audioCriacao, audioEncerramento, retiraFundo,
            corFundo, idJanela));
}

int CPIGGerenciadorGDP::CriaGeradorParticulas(
        int maxParticulas, PIGAnimacao animacaoBase, int audioCriacao, int audioEncerramento,
        bool retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = geradores->ProxID();
    return geradores->Insere(new CPIGGeradorParticulas(
            id, maxParticulas, animacaoBase, audioCriacao, audioEncerramento, retiraFundo, corFundo,
            idJanela));
}

int CPIGGerenciadorGDP::CriaGeradorParticulas(
        int maxParticulas, PIGObjeto objetoBase, int audioCriacao, int audioEncerramento,
        bool retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = geradores->ProxID();
    return geradores->Insere(new CPIGGeradorParticulas(
            id, maxParticulas, objetoBase, audioCriacao, audioEncerramento, retiraFundo, corFundo,
            idJanela));
}

int CPIGGerenciadorGDP::InsereGeradorParticulas(PIGGeradorParticulas gerador)
{
    return geradores->Insere(gerador);
}

void CPIGGerenciadorGDP::DestroiGeradorParticulas(int idGerador)
{
    geradores->Remove(idGerador);
}
