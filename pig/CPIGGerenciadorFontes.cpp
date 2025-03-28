#include <SDL_ttf.h>
#include <pig/CPIGGerenciadorFontes.h>
#include <pig/CPIGFonteDinamica.h>

CPIGRepositorio<PIGFonte> *CPIGGerenciadorFontes::fontes{};

PIGFonte CPIGGerenciadorFontes::GetFonte(int idFonte)
{
    return fontes->GetElemento(idFonte);
}

void CPIGGerenciadorFontes::Inicia()
{
    TTF_Init();

    // fontes[0] = new
    // CPIGPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0);
    // fontes[0] = new
    // CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,PIG_FONTE_PADRAO_COR,0,VERDE,0);
    // fontes[0] = new
    // CPIGMapaCaracteres(PIG_FONTE_PADRAO_NOME,PIG_FONTE_PADRAO_TAM,ESTILO_NORMAL,"desenho.bmp",0,BRANCO,0);
    // fontes[0] = new CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0);

    fontes = new CPIGRepositorio<PIGFonte>(PIG_MAX_FONTES, "fontes");
    fontes->Insere(new CPIGFonte(
            PIG_FONTE_PADRAO_NOME, PIG_FONTE_PADRAO_TAM, PIG_ESTILO_NORMAL, PIG_FONTE_PADRAO_COR,
            0));
    // fontes->Insere(new
    // CPIGMapaCaracteresDinamicos("..//fontes//arial.ttf",PIG_FONTE_PADRAO_TAM,0));
}

void CPIGGerenciadorFontes::Encerra()
{
    delete fontes;

    TTF_Quit();
}

int CPIGGerenciadorFontes::CriaFonteFundo(
        const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo, int contorno,
        PIGCor corContorno, int idJanela)
{
    return fontes->Insere(new CPIGFonte(
            nome, tamanho, estilo, arquivoFundo, contorno, corContorno, idJanela, NULL));
}

int CPIGGerenciadorFontes::CriaFonteFundo(
        const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo, int idJanela)
{
    return fontes->Insere(new CPIGFonte(nome, tamanho, estilo, arquivoFundo, idJanela, NULL));
}

int CPIGGerenciadorFontes::CriaFonteNormal(
        const string &nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno,
        PIGCor corContorno, int idJanela)
{
    return fontes->Insere(
            new CPIGFonte(nome, tamanho, estilo, corLetra, contorno, corContorno, idJanela, NULL));
}

int CPIGGerenciadorFontes::CriaFonteNormal(
        const string &nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int idJanela)
{
    return fontes->Insere(new CPIGFonte(nome, tamanho, estilo, corLetra, idJanela, NULL));
}

int CPIGGerenciadorFontes::CriaFonteFundoOffScreen(
        const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo, int contorno,
        PIGCor corContorno, PIGOffscreenRenderer off, int layer)
{
    return fontes->Insere(new CPIGFonte(
            nome, tamanho, estilo, arquivoFundo, contorno, corContorno, -1,
            off->GetLayer(layer)->render));
}

int CPIGGerenciadorFontes::CriaFonteFundoOffScreen(
        const string &nome, int tamanho, PIGEstilo estilo, const string &arquivoFundo,
        PIGOffscreenRenderer off, int layer)
{
    return fontes->Insere(
            new CPIGFonte(nome, tamanho, estilo, arquivoFundo, -1, off->GetLayer(layer)->render));
}

int CPIGGerenciadorFontes::CriaFonteNormalOffScreen(
        const string &nome, int tamanho, PIGEstilo estilo, PIGCor corLetra, int contorno,
        PIGCor corContorno, PIGOffscreenRenderer off, int layer)
{
    return fontes->Insere(new CPIGFonte(
            nome, tamanho, estilo, corLetra, contorno, corContorno, -1,
            off->GetLayer(layer)->render));
}

int CPIGGerenciadorFontes::CriaFonteNormalOffScreen(
        const string &nome, int tamanho, PIGEstilo estilo, PIGOffscreenRenderer off,
        PIGCor corLetra, int layer)
{
    return fontes->Insere(
            new CPIGFonte(nome, tamanho, estilo, corLetra, -1, off->GetLayer(layer)->render));
}

int CPIGGerenciadorFontes::CriaFonteDinamica(const string &nome, int tamanho, int idJanela)
{
    return fontes->Insere(new CPIGFonteDinamica(nome, tamanho, idJanela));
}

int CPIGGerenciadorFontes::InsereFonte(PIGFonte fonte)
{
    return fontes->Insere(fonte);
}

void CPIGGerenciadorFontes::DestroiFonte(int idFonte)
{
    fontes->Remove(idFonte);
}

// static SDL_Surface *GetSurface(char *str, PIGCor cor,int idFonte=0){
// return fontes->GetElemento(idFonte)->GetSurface(str,cor);
//}
