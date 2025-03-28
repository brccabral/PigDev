#ifndef _CPIGSPRITE_
#define _CPIGSPRITE_

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGAutomacao.h>
#include <pig/CPIGOffscreenRenderer.h>
#include <pig/CPIGTransicao.h>

class CPIGSprite
{

protected:

    int alt = {}, larg = {}, altOriginal = {}, largOriginal = {};
    int id{}, idJanela = {}, altJanela = {};
    PIGPonto2D pos = {}, proporcaoPivo = {}, pivoAbs = {};
    SDL_Point pivoInteiro = {};
    bool usaPivoRelativo = {};
    double angulo = {};
    SDL_Rect dest = {};
    int frameAtual = {};
    unordered_map<int, SDL_Rect> frames{};
    SDL_Texture *texture = {};
    SDL_Renderer *renderer = {};
    SDL_RendererFlip flip = {};
    SDL_Surface *surface{};
    PIGCor coloracao = {};
    PIGCor *pixels{};
    int opacidade = {};
    string nomeArquivo{};
    PIGAutomacao automacao = {};
    int tipoFixo = {};
    vector<CPIGSprite *> filhos{};
    bool precisaAtualizar{};

private:

    void CarregaImagem(const string &nomeArq);
    void IniciaBase(int altura, int largura, int janela);
    void ExtraiPixels();
    // Atributos relativos à coloração e textura do Sprite
    void IniciaCor();
    // Atributos relativos à janela do Sprite
    void IniciaJanela(int janela);
    // Atributos relativos ao tamanho do Sprite
    void IniciaDimensoes(int altura, int largura);
    // Atributos relativos à rotação do Sprite
    void IniciaOrientacao();

protected:

    void AplicaTransicao(const PIGEstadoTransicao &estado);
    virtual void AtualizaTextura();

public:

    int GetId() const;
    // Construtor para arquivos de vídeo ou Componentes
    CPIGSprite(int idSprite, int altura, int largura, const string &nomeArq, int janela = 0);
    // Construtor básico para leitura de imagens digitais
    CPIGSprite(
            int idSprite, const string &nomeArq, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int janela = 0);
    // Construtor para imagens provenientes do renderizador offscreen
    CPIGSprite(
            int idSprite, PIGOffscreenRenderer offRender, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int janela = 0);
    // Construtor para Sprite "copiado" de outro Sprite
    CPIGSprite(
            int idSprite, const CPIGSprite *spriteBase, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int janela = 0);
    // Construtor para sprite "vazio", cuja imagem será gerada posteriormente
    explicit CPIGSprite(int janela);
    void PreparaTextura(int retiraFundo, const PIGCor *corFundo = NULL);
    int RecebeFilho(CPIGSprite *filho, int fixo);
    int Retirafilho(const CPIGSprite *filho);
    void InsereTransicao(PIGTransicao t, PIGAutomacao automaExt = NULL);
    void
    InsereTransicao(double tempo, const PIGEstadoTransicao &estado, PIGAutomacao automaExt = NULL);
    void LeTransicoes(const string &nomeArq, PIGAutomacao automaExt = NULL);
    void IniciaAutomacao(PIGAutomacao automaExt = NULL);
    void LimpaTransicoes(PIGAutomacao automaExt = NULL);
    bool ExecutandoTransicao(PIGAutomacao automaExt = NULL);
    void TrataAutomacao(PIGAutomacao automaExt = NULL);
    void PausaAutomacao(PIGAutomacao automaExt = NULL);
    void DespausaAutomacao(PIGAutomacao automaExt = NULL);
    void InsereAcao(
            double tempo, double repeticao, PIGFuncaoSimples acao, void *param,
            PIGAutomacao automaExt = NULL);
    void LimpaAcoes(PIGAutomacao automaExt = NULL);
    void DefineTipoTransicao(PIGTipoTransicao tipo, PIGAutomacao automaExt = NULL);
    // Destrutor para todos os tipos de Sprites
    virtual ~CPIGSprite();
    int GetIdJanela() const;
    void DefineFrame(int idFrame, SDL_Rect r);
    void DefineFrames(const SDL_Rect *r, size_t count);
    PIGPonto2D GetXY();
    void SetColoracao(PIGCor cor);
    PIGCor GetColoracao();
    void Rotaciona(double px, double py, double graus);
    virtual void SetAngulo(double a);
    double GetAngulo() const;
    void SetFlip(PIGFlip valor);
    PIGFlip GetFlip();
    // Pivô relativo ao ponto (0,0) por meio de soma
    void SetPivoAbsoluto(PIGPonto2D pivo);
    // Pivo relativo ao ponto (0,0) por meio de multiplicação
    void SetPivoProporcional(PIGPonto2D pivo);
    // recupera o ponto pivô
    PIGPonto2D GetPivo();
    virtual void Move(double nx, double ny);
    virtual void Desloca(double dx, double dy);
    virtual void SetDimensoes(int altura, int largura);
    virtual void GetDimensoes(int &altura, int &largura);
    void GetDimensoesOriginais(int &altura, int &largura) const;
    void SetOpacidade(int valor);
    void RestauraDimensoesOriginais();
    int GetOpacidade() const;
    int MudaFrameAtual(int novoFrame);
    int GetFrameAtual() const;
    void CarregaArquivoFrames(const string &nomeArq);
    void CriaFramesAutomaticosPorLinha(int idFrameInicial, int qtdLinhas, int qtdColunas);
    void CriaFramesAutomaticosPorColuna(int idFrameInicial, int qtdLinhas, int qtdColunas);
    virtual int Desenha();
    void DesenhaOffScreen(PIGOffscreenRenderer offRender);
    void AtualizaPixels(int retiraFundo = 1, int opacidadeObj = 255);
    PIGCor *GetPixels();
    string GetNomeArquivo();
};
typedef CPIGSprite *PIGSprite;
#endif // _CPIGSPRITE_
