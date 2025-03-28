#include <pig/CPIGGerenciadorSprites.h>

unordered_map<string, int> CPIGGerenciadorSprites::spritesSimples{};
CPIGRepositorio<PIGSprite> *CPIGGerenciadorSprites::sprites{};
CPIGRepositorio<PIGObjeto> *CPIGGerenciadorSprites::objetos{};
CPIGRepositorio<PIGAnimacao> *CPIGGerenciadorSprites::animacoes{};

PIGSprite CPIGGerenciadorSprites::GetSprite(int idSprite)
{
    return sprites->GetElemento(idSprite);
}

PIGObjeto CPIGGerenciadorSprites::GetObjeto(int idObjeto)
{
    return objetos->GetElemento(idObjeto);
}

PIGAnimacao CPIGGerenciadorSprites::GetAnimacao(int idAnimacao)
{
    return animacoes->GetElemento(idAnimacao);
}

void CPIGGerenciadorSprites::Inicia()
{
    sprites = new CPIGRepositorio<PIGSprite>(PIG_MAX_SPRITES, "sprites");
    objetos = new CPIGRepositorio<PIGObjeto>(PIG_MAX_OBJETOS, "objetos");
    animacoes = new CPIGRepositorio<PIGAnimacao>(PIG_MAX_ANIMACOES, "animacoes");
}

void CPIGGerenciadorSprites::Encerra()
{
    delete sprites;
    delete objetos;
    delete animacoes;
}

int CPIGGerenciadorSprites::CriaSprite(
        const string &nomeArquivoBMP, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = sprites->ProxID();
    return sprites->Insere(new CPIGSprite(id, nomeArquivoBMP, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::CriaSprite(
        int idSpriteBase, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = sprites->ProxID();
    return sprites->Insere(
            new CPIGSprite(id, GetSprite(idSpriteBase), retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::CriaSpriteOffScreen(
        PIGOffscreenRenderer offRenderer, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = sprites->ProxID();
    return sprites->Insere(new CPIGSprite(id, offRenderer, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::InsereSprite(PIGSprite sprite)
{
    return sprites->Insere(sprite);
}

int CPIGGerenciadorSprites::CriaObjeto(
        const string &nomeArquivoBMP, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = objetos->ProxID();
    return objetos->Insere(new CPIGObjeto(id, nomeArquivoBMP, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::CriaObjeto(
        int idObjetoBase, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = objetos->ProxID();
    return objetos->Insere(
            new CPIGObjeto(id, GetObjeto(idObjetoBase), retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::CriaObjetoOffScreen(
        PIGOffscreenRenderer offRenderer, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = objetos->ProxID();
    return objetos->Insere(new CPIGObjeto(id, offRenderer, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::InsereObjeto(PIGObjeto objeto)
{
    return objetos->Insere(objeto);
}

int CPIGGerenciadorSprites::CriaAnimacao(
        const string &nomeArquivoBMP, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = animacoes->ProxID();
    return animacoes->Insere(new CPIGAnimacao(id, nomeArquivoBMP, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::CriaAnimacao(
        PIGAnimacao animaBase, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = animacoes->ProxID();
    return animacoes->Insere(new CPIGAnimacao(id, animaBase, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::CriaAnimacao(
        PIGObjeto objetoBase, int retiraFundo, const PIGCor *corFundo, int idJanela)
{
    int id = animacoes->ProxID();
    return animacoes->Insere(new CPIGAnimacao(id, objetoBase, retiraFundo, corFundo, idJanela));
}

int CPIGGerenciadorSprites::InsereAnimacao(PIGAnimacao animacao)
{
    return animacoes->Insere(animacao);
}

int CPIGGerenciadorSprites::GetProxIndiceSprite()
{
    return sprites->ProxID();
}

int CPIGGerenciadorSprites::GetProxIndiceObjeto()
{
    return objetos->ProxID();
}

int CPIGGerenciadorSprites::GetProxIndiceAnimacao()
{
    return animacoes->ProxID();
}

void CPIGGerenciadorSprites::DestroiSprite(int idSprite)
{
    sprites->Remove(idSprite);
}

void CPIGGerenciadorSprites::DestroiObjeto(int idObjeto)
{
    objetos->Remove(idObjeto);
}

void CPIGGerenciadorSprites::DestroiAnimacao(int idAnimacao)
{
    animacoes->Remove(idAnimacao);
}

void CPIGGerenciadorSprites::DesenhaSprite(
        const string &nomeArq, int x, int y, int retiraFundo, int idJanela)
{
    int id;
    unordered_map<string, int>::iterator it = spritesSimples.find(nomeArq);
    if (it == spritesSimples.end())
    { // não achou
        int next = sprites->ProxID();
        id = sprites->Insere(new CPIGSprite(next, nomeArq, retiraFundo, NULL, idJanela));
        spritesSimples[nomeArq] = id;
    }
    else
    {
        id = it->second;
    }
    PIGSprite sprite = sprites->GetElemento(id);
    if (sprite)
    {
        sprite->Move(x, y);
        sprite->Desenha();
    }
}
