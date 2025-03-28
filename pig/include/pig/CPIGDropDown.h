#ifndef _CPIGDROPDOWN_
#define _CPIGDROPDOWN_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGListaItemComponente.h>

class CPIGDropDown : public CPIGListaItemComponente
{

private:

    bool recolhida{};
    int itemDestaque;

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGDropDown LeParametros(int idComponente, CPIGAtributos atrib);
    void SetFoco(bool valor) override;
    void SetRecolhida(bool valor);
    int ChecaMouseOver(SDL_Point pMouse) override;
    void DesenhaItemDestaque();
    void DesenhaListaItens();

public:

    CPIGDropDown(
            int idComponente, int larguraTotal, int alturaLinha, int alturaItem = 0,
            int larguraItem = 0, const string &nomeArqFundo = "", int retiraFundo = 1,
            int janela = 0);
    CPIGDropDown(
            int idComponente, int larguraTotal, int alturaLinha, int alturaItem = 0,
            int larguraItem = 0, int janela = 0);
    CPIGDropDown(int idComponente, const CPIGAtributos &atrib);

    ~CPIGDropDown() override = default;

    [[nodiscard]] int GetItemDestaque() const;
    int SetAcionadoItem(int indice, bool valor) override;
    void CriaItem(
            const string &itemLabel, const string &arqImagemIcone = "",
            const string &arqImagemFundoItem = "", bool itemHabilitado = true,
            const string &hintMsg = "", int retiraFundo = 1, int retiraFundoIcone = 1);
    void CriaItem(CPIGAtributos atrib) override;
    int Desenha() override;
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;

    void SetMargens(int mEsq, int mDir, int mCima, int mBaixo) override;
};

typedef CPIGDropDown *PIGDropDown;
#endif // _CPIGDROPDOWN_
