#ifndef _CPIGAUTOMACAO_
#define _CPIGAUTOMACAO_

#include <vector>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGTimer.h>
#include <pig/CPIGTransicao.h>

typedef struct tipoacao
{
    double inicio;
    double tempoRepeticao;
    PIGFuncaoSimples acao;
    void *param;
} PIGAcao;

typedef enum
{
    PIG_TRANSICAO_NORMAL,
    PIG_TRANSICAO_LOOP,
    PIG_TRANSICAO_VAIVEM
} PIGTipoTransicao;

class CPIGAutomacao
{

private:

    PIGTipoTransicao tipo;
    int transAtual, somaTrans;
    vector<PIGTransicao> transicoes;
    vector<PIGAcao> timelineAcoes;
    PIGTimer timerAcoes;
    int idDono;
    bool iniciado;

public:

    explicit CPIGAutomacao(int idProprietario);
    CPIGAutomacao(int idProprietario, const CPIGAutomacao *outro);
    virtual ~CPIGAutomacao();
    [[nodiscard]] bool TemTransicoes() const;
    void InsereTransicao(CPIGTransicao *t);
    void SetTipoTransicao(PIGTipoTransicao valor);
    void IniciaAutomacao(const PIGEstadoTransicao &inicial);
    void PausaAutomacao() const;
    void DespausaAutomacao() const;
    [[nodiscard]] bool ExecutandoTransicao() const;
    PIGTransicao GetTransicaoAtual();
    void LimpaTransicoes();
    void LimpaAcoes();
    [[nodiscard]] bool TemAcoes() const;
    int InsereAcao(PIGFuncaoSimples acao, double inicio, double repeticao, void *param);
    int TrataAcao();
};

typedef CPIGAutomacao *PIGAutomacao;

#endif // _CPIGAUTOMACAO_
