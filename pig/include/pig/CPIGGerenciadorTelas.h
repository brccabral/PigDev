#ifndef _CPIGGERENCIADORTELAS_
#define _CPIGGERENCIADORTELAS_

#include <cstddef>
#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGTela.h>

class CPIGGerenciadorTelas
{

private:

    static int telaAtual;
    static void *dadosGerais;
    static PIGTela telas[PIG_MAX_TELAS];
    static PIGComportamentoTela comportamento[PIG_MAX_TELAS];

public:

    static void Inicia();
    static void Encerra();
    static PIGTela GetTela(int idTela);
    static void SetDadosGerais(void *dados);
    static void *GetDadosGerais();
    static int CriaTela(
            int idTela, bool criarBackground = false, bool carregarBackground = false,
            const string &imgFundo = "", int idJanela = 0);
    static int InsereTela(int idTela, PIGTela tela);
    static void SetComportamento(
            int idTela, void *dados, PIGFuncaoSimples cria, PIGFuncaoSimples destroi,
            PIGFuncaoSimples carrega, PIGFuncaoSimples descarrega, PIGFuncaoSimples atualiza,
            PIGFuncaoSimples desenha, PIGFuncaoEvento trataEvento);
    static int DestroiTela(int idTela);
    static PIGEstadoTela GetEstadoTela(int idTela);
    static int TrataEvento(const PIGEvento &evento);
    static void PreparaMudancaTela(
            int novaTela, double tempoSaida = PIG_TEMPO_SAIDA_TELA_PADRAO,
            bool destroiDescarregar = false);
    static int Atualiza();
    static int Desenha();
};

#endif // _CPIGGERENCIADORTELAS_
