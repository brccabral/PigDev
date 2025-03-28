#ifndef _CPIGSLIDEBAR_
#define _CPIGSLIDEBAR_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGGauge.h>

class CPIGSlideBar : public CPIGGauge
{

    int deltaRodinha, deltaTeclado;
    int altMarcador, largMarcador, xMarc{}, yMarc{};

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGSlideBar LeParametros(int idComponente, CPIGAtributos atrib);
    void AtualizaMarcador() override;
    PIGEstadoEvento TrataClickTrilha(int px, int py);
    PIGEstadoEvento TrataRodinha(const PIGEvento &evento);
    PIGEstadoEvento TrataClickMarcador(SDL_Point p);

public:

    CPIGSlideBar(
            int idComponente, int altTrilha, int largTrilha, const string &imgTrilha,
            int alturaMarcador, int larguraMarcador, const string &imgMarcador,
            int retiraFundoTrilha = 1, int retiraFundoMarcador = 1, int janela = 0);
    // CPIGSlideBar(id+2,          alt,           tamPadraoSlide, tamPadraoSlide, tamPadraoSlide,
    // idJanela);
    CPIGSlideBar(
            int idComponente, int altTrilha, int largTrilha, int alturaMarcador,
            int larguraMarcador, int janela = 0);
    CPIGSlideBar(int idComponente, const CPIGAtributos &atrib);

    ~CPIGSlideBar() override = default;

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento) override;
    void SetDeltas(int dPadrao = 1, int dRodinha = 10, int dTeclado = 10);
    int SetOrientacao(PIGGaugeCrescimento orientacao) override;
    void Desloca(double dx, double dy) override;
    void Move(double nx, double ny) override;
    int Desenha() override;
};

typedef CPIGSlideBar *PIGSlideBar;
#endif // _CPIGSLIDEBAR_
