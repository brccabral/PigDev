#ifndef _CPIGBOTAOCLICK_
#define _CPIGBOTAOCLICK_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGBotao.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGTimer.h>

class CPIGBotaoClick : public CPIGBotao
{

protected:

    PIGTimer timer = {};
    double tempoRepeticao = {}, tempoAcionamento = {};

    void IniciaCoresBasicas();
    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGBotaoClick LeParametros(int idComponente, CPIGAtributos atrib);
    void AjustaFrame() override;
    void TrataTimer();
    PIGEstadoEvento OnAction() override;
    void IniciaBase();

public:

    CPIGBotaoClick(
            int idComponente, int alt, int larg, const string &nomeArq, int retiraFundo = 1,
            int janela = 0);
    CPIGBotaoClick(int idComponente, int alt, int larg, int janela = 0);
    CPIGBotaoClick(int idComponente, const CPIGAtributos &atrib);

    ~CPIGBotaoClick() override;
    void DefineTempoRepeticao(double segundos);
    void DefineTempoAcionamento(double segundos);
    int Desenha() override;
    void SetCorNormal(PIGCor cor);
    void SetCorMouseSobre(PIGCor cor);
    void SetCorAcionado(PIGCor cor);
    void SetCorDesabilitado(PIGCor cor);
};

typedef CPIGBotaoClick *PIGBotaoClick;
#endif // _CPIGBOTAOCLICK_
