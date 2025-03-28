#ifndef _CPIGBOTAO_
#define _CPIGBOTAO_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>

class CPIGBotao : public CPIGComponente
{

protected:

    int tecla;

    void ProcessaAtributos(CPIGAtributos atrib) override;
    void SetAcionado(bool valor) override;
    void SetMouseOver(bool valor) override;
    void SetHabilitado(bool valor) override;
    virtual void AjustaFrame() = 0;

    CPIGBotao(
            int idComponente, int alt, int larg, const string &nomeArq, int retiraFundo = 1,
            int janela = 0);
    CPIGBotao(int idComponente, int alt, int larg, int janela = 0);
    ~CPIGBotao() override = default;

public:

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento) override;
    void DefineAtalho(int teclaAtalho);
    int Desenha() override;
};

typedef CPIGBotao *PIGBotao;
#endif // _CPIGBOTAO_
