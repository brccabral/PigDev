#ifndef _CPIGLISTBOX_
#define _CPIGLISTBOX_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGListaItemComponente.h>

class CPIGListBox : public CPIGListaItemComponente
{

protected:

    int itemDestaque;

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGListBox LeParametros(int idComponente, CPIGAtributos atrib);

private:

    void DesenhaRetanguloMarcacao();

public:

    CPIGListBox(
            int idComponente, int larguraTotal, int alturaLinha, int alturaItem = 0,
            int larguraItem = 0, const string &nomeArqFundo = "", int retiraFundo = 1,
            int janela = 0);
    CPIGListBox(
            int idComponente, int larguraTotal, int alturaLinha, int alturaItem = 0,
            int larguraItem = 0, int janela = 0);
    CPIGListBox(int idComponente, const CPIGAtributos &atrib);

    ~CPIGListBox() override = default;

    int GetItemDestaque() const;
    int SetAcionadoItem(int indice, bool valor) override;
    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento) override;
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    void CriaItem(
            const string &itemLabel, const string &arqImagemIcone = "",
            const string &arqImagemFundoItem = "", bool itemMarcado = false,
            bool itemHabilitado = true, const string &hintMsg = "", int retiraFundo = 1,
            int retiraFundoIcone = 1);
    void CriaItem(CPIGAtributos atrib) override;
    int Desenha() override;
    void SetCorDestaque(PIGCor cor);
    void SetDimensoes(int altura, int largura) override;
    void SetMargens(int mEsq, int mDir, int mCima, int mBaixo) override;
};

typedef CPIGListBox *PIGListBox;
#endif // _CPIGLISTBOX_
