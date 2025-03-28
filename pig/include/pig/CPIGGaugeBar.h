#ifndef _CPIGGAUGEBAR_
#define _CPIGGAUGEBAR_

#include <string>

using namespace std;

#include <pig/CPIGAtributos.h>
#include <pig/CPIGGauge.h>
#include <pig/CPIGSprite.h>

class CPIGGaugeBar : public CPIGGauge
{

private:

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGGaugeBar LeParametros(int idComponente, CPIGAtributos atrib);
    void DesenhaBarraCor();
    void AtualizaMarcador() override;

public:

    CPIGGaugeBar(
            int idComponente, int altura, int largura, const string &imgMoldura,
            const string &imgMarcador, int retiraFundoTrilha = 1, int retiraFundoMarcador = 1,
            int janela = 0);
    CPIGGaugeBar(int idComponente, int altura, int largura, int janela = 0);
    ~CPIGGaugeBar() override = default;

    CPIGGaugeBar(int idComponente, const CPIGAtributos &atrib);

    int Desenha() override;
    int SetOrientacao(PIGGaugeCrescimento orientacao) override;
};

typedef CPIGGaugeBar *PIGGaugeBar;
#endif // _CPIGGAUGEBAR_
