#ifndef _CPIGAREADETEXTO_
#define _CPIGAREADETEXTO_

#include <string>
#include <vector>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGCaixaTexto.h>
#include <pig/CPIGComponente.h>
#include <pig/CPIGSlideBar.h>

class CPIGAreaDeTexto : public CPIGCaixaTexto
{

private:

    int espacoEntreLinhas{};
    bool linhasPauta{};
    PIGSlideBar slideVertical{};
    bool slideVerticalAtivado{};
    int tamPadraoSlide{};
    vector<string> linhas;

    void ProcessaAtributos(CPIGAtributos atrib) override;
    static CPIGAreaDeTexto LeParametros(int idComponente, CPIGAtributos atrib);
    // Recupera todo o texto da área
    string GetTextoVisivel() override;
    int GetLarguraLinhaMaior();
    void AjustaSlideVerticalPeloCursor();
    // Desenha um contorno baseado nas dimensoes reais da área(somando a área em si e a scroll bar)
    // void DesenhaMarcacaoMargem(){
    //     CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(pos.x+margemHorEsq,pos.y+margemVertBaixo,alt-margemVertBaixo-margemVertCima-1,larg-margemHorDir-margemHorEsq,coresBasicas[2]);
    // }

    void IniciaPosicaoTexto();
    // Ajusta o alinhamento do texto quando ocorre alguma modificaçăo
    void AjustaPosicaoTextoCursor() override;
    PIGEstadoEvento PosicionaCursorLinha(int linha, int xLinha);
    int MouseSobreSlide(SDL_Point p);
    // trata o evento do botao esquerdo
    PIGEstadoEvento TrataMouseBotaoEsquerdo(SDL_Point p) override;
    PIGEstadoEvento TrataMouseBotaoEsquerdo(SDL_Point p, int inicioLinha) override;
    // retorna o número da linha a partir de um ponto
    int GetLinhaPonto(SDL_Point p);
    // retorna a posição da string texto, na qual uma linha inicia
    int GetPosInicialDeUmaLinha(unsigned int linha);
    // retorna em que linha está qualquer uma das posições da string texto
    int GetLinhaDeUmaPos(int pos);

    void DesenhaLinhasHorizontais();
    // move o cursor uma linha para cima
    int SobeCursor() override;
    // move o cursor uma linha para baixo
    int DesceCursor() override;
    // PulaLinha com Enter
    int PulaLinha() override;
    void IniciaBase();

public:

    CPIGAreaDeTexto(
            int idComponente, int altura, int largura, const string &nomeArq,
            int maxCars = PIG_MAX_CARS_CAIXATEXTO, int retiraFundo = 1, int janela = 0);
    CPIGAreaDeTexto(
            int idComponente, int altura, int largura, int maxCars = PIG_MAX_CARS_CAIXATEXTO,
            int janela = 0);
    CPIGAreaDeTexto(int idComponente, const CPIGAtributos &atrib);

    ~CPIGAreaDeTexto() override;
    void Move(double nx, double ny) override;
    void Desloca(double dx, double dy) override;
    void SetDimensoes(int altura, int largura) override;
    int Desenha() override;
    void SetFonteTexto(int fonte) override;
    // define se as linhas horizontais serao visiveis
    void SetLinhasAbaixoTexto(bool visivel);
    // define a cor da linhas horizontais
    void SetCorLinhas(PIGCor cor);
    PIGEstadoEvento TrataEventoMouse(PIGEvento evento) override;

    // define o espaçamento entre as linhas
    void SetEspacoEntreAsLinhas(int espaco);
    int SetTexto(const string &frase) override;
    int AdicionaTexto(const string &frase) override;
    // recupera o texto separado em linhas
    vector<string> GetLinhasTexto();
};

typedef CPIGAreaDeTexto *PIGAreaDeTexto;
#endif // _CPIGAREADETEXTO_
