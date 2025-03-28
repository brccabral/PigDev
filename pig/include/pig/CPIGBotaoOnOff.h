#ifndef _CPIGBOTAOONOFF_
#define _CPIGBOTAOONOFF_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGBotao.h>
#include <pig/CPIGComponente.h>

class CPIGBotaoOnOff : public CPIGBotao
{

protected:

    void IniciaCoresBasicas();
    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGBotaoOnOff LeParametros(int idComponente, CPIGAtributos atrib);
    void AjustaFrame() override;
    PIGEstadoEvento OnAction() override;

public:

    CPIGBotaoOnOff(
            int idComponente, int alt, int larg, const string &nomeArq, int retiraFundo = 1,
            int janela = 0);
    CPIGBotaoOnOff(int idComponente, int alt, int larg, int janela = 0);
    CPIGBotaoOnOff(int idComponente, const CPIGAtributos &atrib);

    void SetCorNormalOff(PIGCor cor);
    void SetCorMouseSobreOff(PIGCor cor);
    void SetCorDesabilitadoOff(PIGCor cor);
    void SetCorNormalOn(PIGCor cor);
    void SetCorMouseSobreOn(PIGCor cor);
    void SetCorDesabilitadoOn(PIGCor cor);
};

typedef CPIGBotaoOnOff *PIGBotaoOnOff;
#endif // _CPIGBOTAOONOFF_
