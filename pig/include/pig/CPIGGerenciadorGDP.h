#ifndef _CPIGGERENCIADORGDP_
#define _CPIGGERENCIADORGDP_

#include <cstdlib>
#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAnimacao.h>
#include <pig/CPIGObjeto.h>
#include <pig/CPIGRepositorio.h>
#include <pig/CPIGGeradorParticulas.h>

class CPIGGerenciadorGDP
{

private:

    static CPIGRepositorio<PIGGeradorParticulas> *geradores;

public:

    static PIGGeradorParticulas GetGerador(int idGerador);
    static void Inicia();
    static void Encerra();
    static int CriaGeradorParticulas(
            int maxParticulas, const string &nomeArquivoBMP, int audioCriacao,
            int audioEncerramento, bool retiraFundo = true, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int CriaGeradorParticulas(
            int maxParticulas, PIGAnimacao animacaoBase, int audioCriacao, int audioEncerramento,
            bool retiraFundo = true, const PIGCor *corFundo = NULL, int idJanela = 0);
    static int CriaGeradorParticulas(
            int maxParticulas, PIGObjeto objetoBase, int audioCriacao, int audioEncerramento,
            bool retiraFundo = true, const PIGCor *corFundo = NULL, int idJanela = 0);
    static int InsereGeradorParticulas(PIGGeradorParticulas gerador);
    static void DestroiGeradorParticulas(int idGerador);
};

#endif //_CPIGGERENCIADORGDP_
