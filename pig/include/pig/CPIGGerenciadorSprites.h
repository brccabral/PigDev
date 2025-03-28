#ifndef _CPIGGERENCIADORSPRITES_
#define _CPIGGERENCIADORSPRITES_

#include <string>
#include <unordered_map>

using namespace std;

#include <pig/PIGTipos.h>
#include <pig/CPIGSprite.h>
#include <pig/CPIGObjeto.h>
#include <pig/CPIGAnimacao.h>
#include <pig/CPIGOffscreenRenderer.h>
#include <pig/CPIGRepositorio.h>

class CPIGGerenciadorSprites
{

private:

    static unordered_map<string, int> spritesSimples;
    static CPIGRepositorio<PIGSprite> *sprites;
    static CPIGRepositorio<PIGObjeto> *objetos;
    static CPIGRepositorio<PIGAnimacao> *animacoes;

public:

    static PIGSprite GetSprite(int idSprite);
    static PIGObjeto GetObjeto(int idObjeto);
    static PIGAnimacao GetAnimacao(int idAnimacao);
    static void Inicia();
    static void Encerra();
    static int CriaSprite(
            const string &nomeArquivoBMP, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int CriaSprite(
            int idSpriteBase, int retiraFundo = 1, const PIGCor *corFundo = NULL, int idJanela = 0);
    static int CriaSpriteOffScreen(
            PIGOffscreenRenderer offRenderer, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int InsereSprite(PIGSprite sprite);
    static int CriaObjeto(
            const string &nomeArquivoBMP, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int CriaObjeto(
            int idObjetoBase, int retiraFundo = 1, const PIGCor *corFundo = NULL, int idJanela = 0);
    static int CriaObjetoOffScreen(
            PIGOffscreenRenderer offRenderer, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int InsereObjeto(PIGObjeto objeto);
    static int CriaAnimacao(
            const string &nomeArquivoBMP, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int CriaAnimacao(
            PIGAnimacao animaBase, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int CriaAnimacao(
            PIGObjeto objetoBase, int retiraFundo = 1, const PIGCor *corFundo = NULL,
            int idJanela = 0);
    static int InsereAnimacao(PIGAnimacao animacao);
    static int GetProxIndiceSprite();
    static int GetProxIndiceObjeto();
    static int GetProxIndiceAnimacao();
    static void DestroiSprite(int idSprite);
    static void DestroiObjeto(int idObjeto);
    static void DestroiAnimacao(int idAnimacao);
    static void
    DesenhaSprite(const string &nomeArq, int x, int y, int retiraFundo = 1, int idJanela = 0);
};

#endif //_CPIGGERENCIADORSPRITES_
