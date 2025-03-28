#ifndef _CPIGGERENCIADORJANELAS_
#define _CPIGGERENCIADORJANELAS_
//
#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGJanela.h>

class CPIGGerenciadorJanelas
{

public:

    static int qtdJanelas;
    static PIGJanela janelas[PIG_MAX_JANELAS];

    static void Inicia(const string &nome, int altura = PIG_ALT_TELA, int largura = PIG_LARG_TELA);
    static void Encerra();
    static int GetQtdJanelas();
    static int
    CriaJanela(const string &nome, int altura = PIG_ALT_TELA, int largura = PIG_LARG_TELA);
    static PIGJanela GetJanela(int idJanela);
    static void IniciaDesenho(int idJanela = -1);
    static void EncerraDesenho(int idJanela = -1);
};

#endif // _CPIGGERENCIADORJANELAS_
