#ifndef _CPIGRADIOBOX_
#define _CPIGRADIOBOX_

#include <string>

using namespace std;

#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGItemComponente.h>
#include <pig/CPIGListaItemComponente.h>

class CPIGRadioBox : public CPIGListaItemComponente
{

protected:

    int itemDestaque;
    string arqImagemIcone;

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGRadioBox LeParametros(int idComponente, CPIGAtributos atrib);
    static void AjustaFrame(PIGItemComponente item);

public:

    CPIGRadioBox(
            int idComponente, int larguraTotal, int alturaLinha, const string &imgIcone,
            int alturaIcone, int larguraIcone, const string &imgFundo, int retiraFundo = 1,
            int janela = 0);
    CPIGRadioBox(
            int idComponente, int larguraTotal, int alturaLinha, const string &imgIcone,
            int alturaIcone, int larguraIcone, int janela = 0);
    CPIGRadioBox(int idComponente, const CPIGAtributos &atrib);

    ~CPIGRadioBox() override = default;

    int GetItemDestaque() const;
    int SetAcionadoItem(int indice, bool valor) override;
    void CriaItem(
            const string &itemLabel, const string &arqImagemFundoItem = "",
            bool itemHabilitado = true, const string &hintMsg = "", int retiraFundo = 1,
            int retiraFundoIcone = 1);
    void CriaItem(CPIGAtributos atrib) override;
    int Desenha() override;
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    void SetDimensoes(int altura, int largura) override;
    void SetMargens(int mEsq, int mDir, int mCima, int mBaixo) override;
};

typedef CPIGRadioBox *PIGRadioBox;
#endif // _CPIGRADIOBOX_
