#ifndef _CPIGGERADORPARTICULAS_
#define _CPIGGERADORPARTICULAS_

#include <cstddef>
#include <string>
#include <vector>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAnimacao.h>
#include <pig/CPIGParticula.h>
#include <pig/CPIGAutomacao.h>
#include <pig/CPIGObjeto.h>
#include <pig/CPIGTransicao.h>

class CPIGGeradorParticulas : public CPIGAnimacao
{

private:

    size_t maxParticulas{}; // qtd de partículas vivas e máximo de partículas vivas
    vector<PIGParticula> parts;
    double hpParticulas{}, maxTempo{};
    SDL_Rect maxEspaco{};
    int audioInicio{}, audioFim{};
    const PIGCor *corFundoImagem{};
    bool retiraFundoImagem{};
    PIGAutomacao automacaoGDP{};

    void IniciaBase(
            int maximoParticulas, int audioCriacao, int audioEncerramento, const PIGCor *corFundo,
            bool retiraFundo);
    void AtualizaParticulas();

public:

    CPIGGeradorParticulas(
            int idGerador, int maximoParticulas, PIGObjeto objBase, int audioCriacao,
            int audioEncerramento, bool retiraFundo, const PIGCor *corFundo, int idJanela);
    CPIGGeradorParticulas(
            int idGerador, int maximoParticulas, PIGAnimacao animaBase, int audioCriacao,
            int audioEncerramento, bool retiraFundo, const PIGCor *corFundo, int idJanela);
    CPIGGeradorParticulas(
            int idGerador, int maximoParticulas, const string &nomeArqImagem, int audioCriacao,
            int audioEncerramento, bool retiraFundo, const PIGCor *corFundo, int idJanela);
    ~CPIGGeradorParticulas() override = default;

    void DefineLimites(SDL_Rect espacoMax, double tempoMax);
    int CriaParticula();
    void MudaHP(int novoValor);
    int Desenha() override;
    bool Colisao(PIGObjeto outro) override;
    bool Colisao();
    int GetQtdAtivas();
    void InsereTransicaoGDP(PIGTransicao t);
    void InsereTransicaoGDP(double tempo, const PIGEstadoTransicao &estado);
    void LeTransicoesGDP(const string &nomeArq);
    void IniciaAutomacaoGDP();
    void LimpaTransicoesGDP();
    bool ExecutandoTransicaoGDP();
    void TrataAutomacaoGDP();
    void InsereAcaoGDP(double tempo, double repeticao, PIGFuncaoSimples acao, void *param);
    void DefineTipoTransicaoGDP(PIGTipoTransicao tipo);
};

typedef CPIGGeradorParticulas *PIGGeradorParticulas;
#endif // _CPIGGERADORPARTICULAS_
