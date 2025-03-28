#ifndef _CPIGFONTEDINAMICA_
#define _CPIGFONTEDINAMICA_

#include <string>
#include <vector>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGFonte.h>
#include <pig/CPIGStringFormatada.h>

class CPIGFonteDinamica : public CPIGFonte
{

private:

    // processa uma string para transformá-la em StringFormatada
    // faz o processamento, utilizando uma máquina de estados finitos
    CPIGStringFormatada Processa(const string &textoOrig, PIGCor corInicial = PIG_FONTE_PADRAO_COR);

public:

    // construtor com o nome do arquivo da fonte, o tamanha e a janela
    CPIGFonteDinamica(const string &nomeFonte, int tamanhoFonte, int janela);
    // escreve uma string já formatada, alinhada com o ponto x,y e o parâmetro pos
    void
    Escreve(CPIGStringFormatada formatada, int x, int y, PIGPosTexto pos = PIG_TEXTO_ESQUERDA,
            float ang = 0, int alvoTextura = 0);
    // escreve uma string normal, alinha com o ponto x,y e o parâmetro pos
    void Escreve(const string &texto, int x, int y) override;
    void Escreve(const string &texto, int x, int y, PIGCor corFonte, PIGPosTexto pos) override;
    void
    Escreve(const string &texto, int x, int y, PIGCor corFonte, PIGPosTexto pos,
            float ang) override;
    void
    Escreve(const string &texto, int x, int y, PIGCor corFonte, PIGPosTexto pos, float ang,
            int alvoTextura) override;

    void Escreve(const string &texto, SDL_Texture *textura, PIGCor cor) override;

    // escreve uma string longa (múltiplas linhas), incluindo formataçăo interna, alinhada de acordo
    // com o ponto x,y e o parâmetro pos
    void
    EscreveLonga(const string &texto, int x, int y, int largMax, int espacoEntreLinhas) override;
    // escreve uma string longa (múltiplas linhas), com formataçăo já processada e fornecida,
    // alinhada de acordo com o ponto x,y e o parâmetro pos
    void EscreveLonga(
            const string &texto, int x, int y, int largMax, int espacoEntreLinhas, PIGCor corFonte,
            PIGPosTexto pos) override;
    // escreve uma string longa (múltiplas linhas), incluindo formataçăo interna, alinhada de acordo
    // com o ponto x,y e o parâmetro pos
    void EscreveLonga(
            const string &texto, int x, int y, int largMax, int espacoEntreLinhas, PIGCor corFonte,
            PIGPosTexto pos, float angulo) override;

    void
    EscreveLonga(const vector<CPIGStringFormatada> &linhas, int x, int y, int espacoEntreLinhas);
    void EscreveLonga(
            const vector<CPIGStringFormatada> &linhas, int x, int y, int espacoEntreLinhas,
            PIGPosTexto pos, float angulo);

    // retorna a largura em pixels da string fornecida (faz a formataçăo internamente)
    int GetLarguraPixelsString(const string &texto) override;
    // retorna as linhas já formatadas e organizadas pela largura máxima fornecida
    vector<CPIGStringFormatada> ExtraiLinhas(const string &texto, int largMax);
};

typedef CPIGFonteDinamica *PIGFonteDinamica;
#endif //_CPIGFONTEDINAMICA_
