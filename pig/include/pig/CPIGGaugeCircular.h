#ifndef _CPIGGAUGECIRCULAR_
#define _CPIGGAUGECIRCULAR_

#include <string>

using namespace std;

#include <pig/CPIGAtributos.h>
#include <pig/CPIGGauge.h>
#include <pig/CPIGSprite.h>

class CPIGGaugeCircular : public CPIGGauge
{

private:

    double angBase{}, deltaAng{};
    int raioInterno{};

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGGaugeCircular LeParametros(int idComponente, CPIGAtributos atrib);
    void AtualizaTextura() override;
    void AtualizaMarcador() override;
    void IniciaBase() override;

public:

    CPIGGaugeCircular(int idComponente, int altura, int largura, int janela = 0);
    CPIGGaugeCircular(
            int idComponente, int altura, int largura, const string &imgTrilha, int alturaMarcador,
            int larguraMarcador, const string &imgMarcador, int retiraFundoTrilha = 1,
            int retiraFundoMarcador = 1, int janela = 0);
    CPIGGaugeCircular(int idComponente, const CPIGAtributos &atrib);

    ~CPIGGaugeCircular() override = default;

    int Desenha() override;
    int SetOrientacao(PIGGaugeCrescimento orientacao) override;
    void SetRaioInterno(int valorRaio);
    void SetAnguloBase(double novoAng);
    void SetDeltaAngulo(double novoDelta);
};

typedef CPIGGaugeCircular *PIGGaugeCircular;
#endif // _CPIGGAUGECIRCULAR_
