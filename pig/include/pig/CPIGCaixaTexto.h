#ifndef _CPIGCaixaTexto_
#define _CPIGCaixaTexto_

#include <cstddef>
#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGTimer.h>

class CPIGCaixaTexto : public CPIGComponente
{

private:

    bool cursorExibido{};
    size_t maxCaracteres{};
    PIGTimer timer{};

protected:

    void IniciaCoresBasicas();
    void ProcessaAtributos(CPIGAtributos atrib) override;
    // checa se o ponteiro do mouse está sobre o componente
    int ChecaMouseOver(SDL_Point pMouse) override;
    // desenha o cursor
    void DesenhaCursor();
    // trata teclas de movimentaçăo do cursor
    virtual PIGEstadoEvento TrataTeclasEspeciais(PIGEvento evento);
    // trata os diversos tipos de eventos de teclado que podem ocorrer
    PIGEstadoEvento TrataEventoTeclado(PIGEvento evento) override;
    string texto;
    int fonteTexto{};
    int posCursor{};
    int xTexto{}, yTexto{}, xCursor{}, yCursor{};
    int altLetra{};

    virtual void AjustaPosicaoTextoCursor() = 0; // pure virtual, porque cada classe derivada vai
                                                 // fazer ajustes diferentes

    virtual int SobeCursor() = 0;

    virtual int DesceCursor() = 0;

    virtual int PulaLinha() = 0;

    virtual string GetTextoVisivel() = 0; // pure virtual, porque cada classe derivada vai retornar
                                          // um texto de forma diferente

    // posiciona o cursor uma posiçăo pra frente
    int AvancaCursor();
    // posiciona o cursor uma posiçăo atrás
    int VoltaCursor();
    // reira um caracter com a tecla backspace
    int RetiraTextoBackSpace();
    // retira um caracter com a tecla delete
    int RetiraTextoDelete();
    // adiciona um texto (caracter ou string) na posiçăo indicada pelo cursor (se possível)
    virtual int AdicionaTexto(const string &frase);
    // converte caracteres especiais, como acentos por exemplo
    static string ConverteString(const char *str);
    int CalculaPosicaoCursor(const string &linha, int xMouse) const;
    // o botao esquerdo faz com que a ediçăo do trexto comece ou que o cursor seja reposicionado
    virtual PIGEstadoEvento TrataMouseBotaoEsquerdo(SDL_Point p);
    virtual PIGEstadoEvento TrataMouseBotaoEsquerdo(SDL_Point p, int inicioLinha);
    void IniciaBase(int maxCars);
    void SetFoco(bool valor) override;
    CPIGCaixaTexto(
            int idComponente, int altura, int largura, const string &nomeArq,
            int maxCars = PIG_MAX_CARS_CAIXATEXTO, int retiraFundo = 1, int janela = 0);
    CPIGCaixaTexto(
            int idComponente, int altura, int largura, int maxCars = PIG_MAX_CARS_CAIXATEXTO,
            int janela = 0);
    ~CPIGCaixaTexto() override;

public:

    // define o texto a ser mostrado no componente
    virtual int SetTexto(const string &frase);
    // deifne a fonte de texto
    virtual void SetFonteTexto(int fonte);
    // recupera o texto armazenado no componente
    string GetTexto();
    // define a cor do fundo
    void SetCorFundo(PIGCor cor);
    // define a cor da fonte
    void SetCorFonte(PIGCor cor);
    // define a cor do cursor
    void SetCorCursor(PIGCor cor);
    // reposiciona o componente
    void Move(double nx, double ny) override;
    // define as margens do componente
    void SetMargens(int mEsq, int mDir, int mCima, int mBaixo) override;
};

typedef CPIGCaixaTexto *PIGCaixaTexto;
#endif // _CPIGCAIXATEXTO_
