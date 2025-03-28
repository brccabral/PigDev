#ifndef _CPIGTELA_
#define _CPIGTELA_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGGerenciadorSprites.h>
#include <pig/CPIGGerenciadorTimers.h>

typedef enum
{
    PIG_TELA_INEXISTENTE,
    PIG_TELA_CRIANDO,
    PIG_TELA_CRIADA,
    PIG_TELA_CARREGANDO,
    PIG_TELA_CARREGADA,
    PIG_TELA_SAINDO,
    PIG_TELA_DESCARREGADA
} PIGEstadoTela;

typedef struct
{
    int id;
    void *param;
    void *tela;
    PIGEstadoTela estadoFinal;
    PIGFuncaoSimples funcao;
} PIGStructThread;

typedef struct
{
    void *dados;
    PIGFuncaoSimples acaoCria, acaoDestroi, acaoCarrega, acaoDescarrega, acaoAtualiza, acaoDesenha;
    PIGFuncaoEvento acaoTrataEvento;
} PIGComportamentoTela;

class CPIGTela
{

protected:

    int mudarPara{};
    int id, janela;
    double tempoSaida;
    int timerSaida;
    int spriteCarrega;
    bool criaBackground, carregaBackground;
    PIGEstadoTela estado;
    PIGComportamentoTela comportamento{};
    bool destruirAoDescarregar;
    SDL_sem *sem;

public:

    static int ExecutaFuncaoBackground(void *param);
    CPIGTela(
            int idTela, const PIGComportamentoTela &comporta, bool criarBackground = false,
            bool carregarBackground = false, const string &imgLoading = "", int idJanela = 0);
    ~CPIGTela();
    PIGEstadoTela GetEstado();
    [[nodiscard]] bool GetDestruirAoDescarregar() const;
    int CarregaTela();
    int DescarregaTela();
    int TrataEvento(const PIGEvento &evento);
    void PreparaSaida(
            int outraTela, double tempo = PIG_TEMPO_SAIDA_TELA_PADRAO,
            bool destroiDescarga = false);
    int Atualiza();
    int Desenha();
    void SetComportamento(const PIGComportamentoTela &comporta);
};

typedef CPIGTela *PIGTela;
#endif // _CPIGTELA_
