#ifndef _CPIGPARTICULA_
#define _CPIGPARTICULA_

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAnimacao.h>
#include <pig/CPIGObjeto.h>
#include <pig/CPIGGerenciadorTimers.h>


class CPIGParticula : public CPIGAnimacao
{

private:

    SDL_Rect espacoVida{};
    double hp;
    double tempoVida;
    int timer;
    bool viva;

    double ModificaHP(double valor);

public:

    CPIGParticula(
            int idParticula, PIGAnimacao base, int vida, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int idJanela = 0);
    void DefineLimites(SDL_Rect espacoMax, double tempoMax);
    ~CPIGParticula() override;
    bool ChecaViva();

    bool Colisao(PIGObjeto outro) override;
    bool Colisao(CPIGParticula *outra);
};

typedef CPIGParticula *PIGParticula;
#endif //_CPIGPARTICULA_
