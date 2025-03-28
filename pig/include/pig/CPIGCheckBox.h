#ifndef _CPIGCHECKBOX_
#define _CPIGCHECKBOX_

#include <string>
#include <vector>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGItemComponente.h>
#include <pig/CPIGListaItemComponente.h>

class CPIGCheckBox : public CPIGListaItemComponente
{

protected:

    string arqImagemIcone;

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGCheckBox LeParametros(int idComponente, CPIGAtributos atrib);
    static void AjustaFrame(PIGItemComponente item);

public:

    CPIGCheckBox(
            int idComponente, int larguraTotal, int alturaLinha, const string &imgIcone,
            int alturaIcone, int larguraIcone, const string &imgFundo, int retiraFundo = 1,
            int janela = 0);
    CPIGCheckBox(
            int idComponente, int larguraTotal, int alturaLinha, const string &imgIcone,
            int alturaIcone, int larguraIcone, int janela = 0);
    CPIGCheckBox(int idComponente, const CPIGAtributos &atrib);

    ~CPIGCheckBox() override = default;

    void CriaItem(
            const string &itemLabel, const string &arqImagemFundoItem = "",
            bool itemMarcado = false, bool itemHabilitado = true, const string &hintMsg = "",
            int retiraFundo = 1, int retiraFundoIcone = 1);
    void CriaItem(CPIGAtributos atrib) override;
    int Desenha() override;
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    void SetAcionadoTodos(bool marcado);
    int SetAcionadoItem(int indice, bool marcado) override;
    vector<int> GetItensMarcados();
    void SetDimensoes(int altura, int largura) override;
    void SetMargens(int mEsq, int mDir, int mCima, int mBaixo) override;
};

typedef CPIGCheckBox *PIGCheckBox;
#endif // _CPIGCheckBox_
