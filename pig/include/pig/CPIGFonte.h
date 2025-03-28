#ifndef _CMAPACARACTERES_
#define _CMAPACARACTERES_

#include <string>
#include <vector>

using namespace std;

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGGerenciadorJanelas.h>

typedef enum
{
    PIG_TEXTO_ESQUERDA,
    PIG_TEXTO_DIREITA,
    PIG_TEXTO_CENTRO
} PIGPosTexto;

class CPIGFonte
{

protected:

    static string delimitadores;

    int alturaExtra[PIG_TOTALESTILOS][PIG_ULTIMO_CAR - PIG_PRIMEIRO_CAR] = {};
    int larguraLetra[PIG_TOTALESTILOS][PIG_ULTIMO_CAR - PIG_PRIMEIRO_CAR] = {};
    int idJanela{};
    int fontDescent{};
    int estiloFixo{};

    SDL_Renderer *render = NULL;
    SDL_Texture *glyphsT[PIG_TOTALESTILOS][PIG_ULTIMO_CAR - PIG_PRIMEIRO_CAR] = {};
    TTF_Font *font{};

    string nome{};
    int tamFonte{};

    static Uint16 ConvChar(Uint16 letra);
    // converte cada caractere da string no índice correpondente do vetor de glifos
    static vector<int> Converte(const string &original);
    // pega a altura da janela ou do renderizador
    [[nodiscard]] int GetAlturaAtualJanela() const;
    // cria o conjunto de glifos das letras com as características fornecidas
    void CriaLetrasSurface(
            PIGEstilo estilo, int nivelOutline, PIGCor corOutline, SDL_Surface *fundo,
            PIGCor corFonte = BRANCO);
    // inicia os atributos da classe
    void IniciaBase(
            const string &nomeFonte, int tamanhoFonte, PIGEstilo estilo, int janela,
            SDL_Renderer *renderer = NULL);

public:

    CPIGFonte(
            const string &nomeFonte, int tamanhoFonte, PIGEstilo estilo, const string &nomeFundo,
            int janela = 0, SDL_Renderer *renderer = NULL);
    CPIGFonte(
            const string &nomeFonte, int tamanhoFonte, PIGEstilo estilo, const string &nomeFundo,
            int outline, PIGCor corOutline, int janela = 0, SDL_Renderer *renderer = NULL);
    CPIGFonte(
            const string &nomeFonte, int tamanhoFonte, PIGEstilo estilo, PIGCor corFonte,
            int outline, PIGCor corOutline, int janela = 0, SDL_Renderer *renderer = NULL);
    CPIGFonte(
            const string &nomeFonte, int tamanhoFonte, PIGEstilo estilo, PIGCor corFonte,
            int janela = 0, SDL_Renderer *renderer = NULL);
    virtual ~CPIGFonte();
    void SubstituiGlyph(
            const string &nomeArq, uint16_t glyph, int largNova, int x, int y, int alt, int larg);
    [[nodiscard]] int GetFonteDescent() const;
    int GetFonteAscent();
    [[nodiscard]] PIGMetricasFonte GetMetricasLetra(Uint16 letra, int estilo = 0) const;
    [[nodiscard]] int GetTamanhoBaseFonte() const;
    int GetLineSkip();
    [[nodiscard]] int GetLarguraLetra(Uint16 letra, int estilo = 0) const;
    vector<string>
    ExtraiLinhas(const string &texto, int largMax, const string &delim = delimitadores);
    virtual int GetLarguraPixelsString(const string &texto);
    virtual void Escreve(const string &texto, int x, int y);
    virtual void Escreve(const string &texto, int x, int y, PIGCor corFonte, PIGPosTexto pos);
    virtual void
    Escreve(const string &texto, int x, int y, PIGCor corFonte, PIGPosTexto pos, float ang);
    virtual void
    Escreve(const string &texto, int x, int y, PIGCor corFonte, PIGPosTexto pos, float ang,
            int alvoTextura);
    virtual void Escreve(const string &texto, SDL_Texture *textura, PIGCor cor);
    virtual void
    EscreveLonga(const string &texto, int x, int y, int largMax, int espacoEntreLinhas);
    virtual void EscreveLonga(
            const string &texto, int x, int y, int largMax, int espacoEntreLinhas, PIGCor corFonte,
            PIGPosTexto pos);
    virtual void EscreveLonga(
            const string &texto, int x, int y, int largMax, int espacoEntreLinhas, PIGCor corFonte,
            PIGPosTexto pos, float angulo);

    SDL_Surface *GetGlyph(const Uint16 *emoji, PIGCor cor = BRANCO);
};

typedef CPIGFonte *PIGFonte;

#endif // _CMAPACARACTERES_
