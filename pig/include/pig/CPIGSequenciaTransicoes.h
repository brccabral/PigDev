#ifndef _CPIGSEQUENCIATRANSICOES_
#define _CPIGSEQUENCIATRANSICOES_

#include <vector>

using namespace std;

#include <pig/CPIGTransicao.h>

typedef enum
{
    PIG_TRANSICAO_NORMAL,
    PIG_TRANSICAO_LOOP,
    PIG_TRANSICAO_INVERTIDA
} PIG_TipoTransicao;

class CPIGSequenciaTransicoes
{

private:

    PIG_TipoTransicao tipo;
    int transAtual;
    vector<PIGTransicao> trans;

public:

    CPIGSequenciaTransicoes();
    ~CPIGSequenciaTransicoes();
    bool TemTransicoes();
    void Insere(PIGTransicao t);
    void SetTipoTransicao(PIG_TipoTransicao valor);
    void IniciaTransicoes();
    PIGTransicao GetTransicaoAtual();
};

typedef CPIGSequenciaTransicoes *PIGSequenciaTransicoes;
#endif // _CPIGSEQUENCIATRANSICOES_
