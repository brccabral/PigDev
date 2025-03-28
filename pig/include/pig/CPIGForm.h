#ifndef _CPIGFORM_
#define _CPIGFORM_

#include <algorithm>
#include <fstream>
#include <cstddef>
#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGErros.h>

class CPIGForm : public CPIGComponente
{

private:

    int totalComponentes = {};
    int componenteComFoco = {}, componenteMouseOver = {};
    PIGComponente componentes[PIG_MAX_COMPONENTES] = {};

    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento) override;
    void IniciaBase();
    static PIGTipoComponente GetTipoComponente(string tipo);
    static CPIGForm LeArquivo(int idForm, const string &nomeArqTexto);
    void CriaItemLista(const CPIGAtributos &atrib) const;

public:

    CPIGForm(int idForm, int altForm, int largForm, int janela = 0);
    CPIGForm(
            int idForm, int altForm, int largForm, const string &nomeArq, int retiraFundo = 1,
            int janela = 0);
    CPIGForm(int idForm, const string &nomeArqTexto);

    ~CPIGForm() override;
    int GetIdComponente(const string &label) const;
    int GetIdComponente(int indice) const;
    int GetProxIdComponente() const;
    int Desenha() override;
    int TrataEvento(const PIGEvento &evento);
    PIGComponente GetComponente(int idComponente) const;
    template<class T>
    T GetComponente(int idComponente);
    int CriaBotaoClick(int altura, int largura, const string &nomeArq, int retiraFundo = 1);
    int CriaBotaoClick(int altura, int largura);
    int CriaBotaoOnOff(int altura, int largura, const string &nomeArq, int retiraFundo = 1);
    int CriaBotaoOnOff(int altura, int largura);
    int CriaAreaDeTexto(
            int altura, int largura, const string &nomeArq, int maxCars = 200, int retiraFundo = 1);
    int CriaAreaDeTexto(int altura, int largura, int maxCars = 200);
    int CriaCampoTextoESenha(
            int altura, int largura, const string &nomeArq, int maxCars = 200,
            bool apenasNumeros = false, int retiraFundo = 1, bool campoSenha = false);
    int CriaCampoTextoESenha(
            int altura, int largura, int maxCars = 200, bool apenasNumeros = false,
            bool campoSenha = false);
    int CriaListBox(
            int larguraTotal, int alturaLinha, int altItem, int largItem, const string &nomeArq,
            int retiraFundo = 1);
    int CriaListBox(int larguraTotal, int alturaLinha, int altItem, int largItem);
    int CriaDropDown(
            int larguraTotal, int alturaLinha, int altItem, int largItem, const string &nomeArq,
            int retiraFundo = 1);
    int CriaDropDown(int larguraTotal, int alturaLinha, int altItem, int largItem);
    int CriaGaugeBar(
            int altura, int largura, const string &imgMoldura, const string &imgMarcador = "",
            int retiraFundoMoldura = 1, int retiraFundoMarcador = 1);
    int CriaGaugeBar(int altura, int largura);
    int CriaRadioBox(
            int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
            int larguraItem, const string &imagemFundo, int retiraFundo = 1);
    int CriaRadioBox(
            int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
            int larguraItem);
    int CriaCheckBox(
            int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
            int larguraItem, const string &imagemFundo, int retiraFundo = 1);
    int CriaCheckBox(
            int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
            int larguraItem);
    int CriaGaugeCircular(int altura, int largura);
    int CriaGaugeCircular(
            int altura, int largura, const string &imgTrilha, int alturaMarcador,
            int larguraMarcador, const string &imgMarcador, int retiraFundoTrilha = 1,
            int retiraFundoMarcador = 1);
    int CriaSlideBar(
            int altura, int largura, const string &imgTrilha, int alturaMarcador,
            int larguraMarcador, const string &imgMarcador, int retiraFundoTrilha = 1,
            int retiraFundoMarcador = 1);
    int CriaSlideBar(int altura, int largura, int alturaMarcador, int larguraMarcador);
    int CriaComponentePorParametro(const string &parametros);
};

template<class T>
T CPIGForm::GetComponente(int idComponente)
{
    T comp = (T) componentes[idComponente % PIG_MAX_COMPONENTES];
    if (comp == NULL)
        throw CPIGErroIndice(idComponente, "componentes");
    return comp;
}

typedef CPIGForm *PIGForm;
#endif // _CPIGFORM_
