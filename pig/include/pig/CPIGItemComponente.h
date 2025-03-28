/**************************************************
A classe CPIGItemComponente descreve o código dos items que compõem certos componentes como
checkbox, radiobox, listbox e dropdown. Todos esses componentes se caracterizam por possuir diversos
itens e por se poder marcar/selecionar um ou mais desses itens. Os elementos principais da classe
CPIGItemComponente são: o texto do item (label, obrigatório), a imagem de fundo (textura básica do
componente, opcional) e um ícone (imagem extra, opcional). Além disso, os objetos da classe possuem
um ponteiro para função que permite que o frame do ícone seja alterado externamente. O ícone pode
ser alterado para representar a marcação ou não do item dentro de um checkbox ou radiobox. O label é
posicionado sempre internamente, mas pode estar alinhado à direita (com ou sem a presença do ícone),
à esquerda (com ou sem a presença do ícone) ou centralizado (com ou sem a presença do ícone).
**************************************************/

#ifndef _CPIGITEMCOMPONENTE_
#define _CPIGITEMCOMPONENTE_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGSprite.h>

class CPIGItemComponente : public CPIGComponente
{

private:

    void (*AjustaFrame)(CPIGItemComponente *){}; // ponteiro para funçăo que será chamada sempre que
                                                 // algum estado do item mudar
    PIGSprite icone{};
    int altIcone{}, largIcone{};
    PIGPosicaoComponente posIcone{}, posRelativaLabel{};
    bool habilitadoPorSi{};

    PIGEstadoEvento OnMouseClick();
    void IniciaBase(
            const string &labelItem, const string &arqImagemIcone = "", int alturaIcone = 0,
            int larguraIcone = 0, int retiraFundoIcone = 1);

public:

    // item com icone e com fundo
    CPIGItemComponente(
            int idComponente, int alturaIcone, int larguraIcone, const string &arqImagemIcone,
            const string &arqImagemFundo, const string &labelItem, int larguraLista,
            int alturaItemLista, int retiraFundo = 1, int retiraFundoIcone = 1, int janela = 0);
    // item com icone e sem fundo
    CPIGItemComponente(
            int idComponente, int alturaIcone, int larguraIcone, const string &arqImagemIcone,
            const string &labelItem, int larguraLista, int alturaItemLista,
            int retiraFundoIcone = 1, int janela = 0);
    // item sem icone e com fundo
    CPIGItemComponente(
            int idComponente, const string &arqImagemFundo, const string &labelItem,
            int larguraLista, int alturaItemLista, int retiraFundo = 1, int janela = 0);
    // item sem icone e sem fundo
    CPIGItemComponente(
            int idComponente, const string &labelItem, int larguraLista, int alturaItemLista,
            int retiraFundo = 1, int janela = 0);
    ~CPIGItemComponente() override;
    void SetAcionado(bool valor) override;
    void SetHabilitado(bool valor) override;
    void SetHabilitadoLista(bool valor);
    void SetMouseOver(bool valor) override;
    void DefineFuncaoAjusteFrame(void (*funcao)(CPIGItemComponente *));
    int Desenha() override;
    void SetDimensoesIcone(int alturaIcone, int larguraIcone);
    void AlinhaLabel(PIGPosicaoComponente valor);
    void AlinhaIcone(PIGPosicaoComponente valor);
    // define a posiçăo do label (dentre posiçőes pré-estabelecidas)
    void SetPosicaoPadraoLabel(PIGPosicaoComponente pos) override;
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;
    void Move(double nx, double ny) override;
    void Desloca(double dx, double dy) override;
    PIGSprite GetIcone();
    void SetCorFundo(PIGCor cor);
};

typedef CPIGItemComponente *PIGItemComponente;
#endif //_CPIGITEMCOMPONENTE_
