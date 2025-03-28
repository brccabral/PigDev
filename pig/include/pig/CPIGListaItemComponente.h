#ifndef _CPIGLISTAITEMCOMPONENTE_
#define _CPIGLISTAITEMCOMPONENTE_

#include <string>
#include <vector>

using namespace std;

#include <pig/CPIGComponente.h>
#include <pig/CPIGItemComponente.h>

class CPIGListaItemComponente : public CPIGComponente
{

protected:

    int altBaseLista{}; // espaço vertical entre os itens
    PIGPosicaoComponente posIcones{}, posLabels{};
    vector<PIGItemComponente> itens;
    int altIcone{}, largIcone{}; // altura e largura das imagens dos itens

    static PIGPosicaoComponente GetAlinhamento(string alinhamento);
    void IniciaCoresBasicas();
    void ProcessaAtributos(CPIGAtributos atrib) override;
    void IniciaBase(int alturaLinha);
    PIGItemComponente CriaItem(
            int yItem, const string &itemLabel, const string &arqImagemIcone = "",
            const string &arqImagemFundo = "", bool itemMarcado = false, bool itemHabilitado = true,
            const string &hintMsg = "", int retiraFundo = 1, int retiraFundoIcone = 1);
    void DeslocaItens(double dx, double dy);
    CPIGListaItemComponente(
            int idComponente, int larguraTotal, int alturaLinha, const string &nomeArqFundoLista,
            int retiraFundo = 1, int janela = 0);
    CPIGListaItemComponente(int idComponente, int larguraTotal, int alturaLinha, int janela = 0);
    ~CPIGListaItemComponente() override;

public:

    virtual void CriaItem(CPIGAtributos atrib) = 0;

    void SetDimensoesIcone(int alturaIcone, int larguraIcone);
    void AlinhaLabelItens(PIGPosicaoComponente valor);
    void AlinhaIcones(PIGPosicaoComponente valor);
    int GetAcionadoItem(int indice);
    virtual int SetAcionadoItem(int indice, bool valor);
    int SetAcionadoApenasItem(int indice, bool valor);
    void SetAudioItem(int audio, int indice = -1);
    void SetCorLabelItem(PIGCor cor, int indice = -1);
    void SetCorFundoItem(PIGCor cor, int indice = -1);
    void SetFonteItem(int fonte, int indice = -1);
    int GetHabilitadoItem(int indice);
    int SetHabilitadoItem(int indice, bool valor);
    void SetVisivel(bool valor) override;
    void SetFonteHint(int fonte) override;
    void SetAudio(int audio) override;
    void SetHabilitado(bool valor) override;
    string GetLabelItem(int indice);
    void Move(double nx, double ny) override;
};

typedef CPIGListaItemComponente *PIGListaComponente;
#endif //_CPIGLISTAITEMCOMPONENTE_
