#ifndef _CPIGGERENCIADORFONTES_
#define _CPIGGERENCIADORFONTES_

#include <string>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGFonte.h>
#include <pig/CPIGRepositorio.h>
#include <pig/CPIGOffscreenRenderer.h>

class CPIGGerenciadorFontes
{

private:

    static CPIGRepositorio<PIGFonte> *fontes;

public:

    static PIGFonte GetFonte(int idFonte);
    static void Inicia();
    static void Encerra();
    static int CriaFonteFundo(
            const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo,
            int contorno, PIGCor corContorno, int idJanela = 0);
    static int CriaFonteFundo(
            const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo,
            int idJanela = 0);
    static int CriaFonteNormal(
            const string &nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno,
            PIGCor corContorno, int idJanela = 0);
    static int CriaFonteNormal(
            const string &nome, int tamanho, PIGEstilo estilo,
            PIGCor corLetra = PIG_FONTE_PADRAO_COR, int idJanela = 0);
    static int CriaFonteFundoOffScreen(
            const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo,
            int contorno, PIGCor corContorno, PIGOffscreenRenderer off, int layer = 0);
    static int CriaFonteFundoOffScreen(
            const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo,
            PIGOffscreenRenderer off, int layer = 0);
    static int CriaFonteNormalOffScreen(
            const string &nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno,
            PIGCor corContorno, PIGOffscreenRenderer off, int layer = 0);
    static int CriaFonteNormalOffScreen(
            const string &nome, int tamanho, PIGEstilo estilo, PIGOffscreenRenderer off,
            PIGCor corLetra = PIG_FONTE_PADRAO_COR, int layer = 0);
    static int CriaFonteDinamica(const string &nome, int tamanho, int idJanela = 0);
    static int InsereFonte(PIGFonte fonte);
    static void DestroiFonte(int idFonte);
    // static SDL_Surface *GetSurface(char *str, PIGCor cor,int idFonte=0){
    // return fontes->GetElemento(idFonte)->GetSurface(str,cor);
    //}
};

#endif // _CPIGGERENCIADORFONTES_
