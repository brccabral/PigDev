#include <pig/CPIGRadioBox.h>
#include <pig/CPIGGerenciadorJanelas.h>

void CPIGRadioBox::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGListaItemComponente::ProcessaAtributos(atrib);
}

CPIGRadioBox CPIGRadioBox::LeParametros(int idComponente, CPIGAtributos atrib)
{
    CPIGRadioBox *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGRadioBox(
                idComponente, atrib.GetInt("largura", 0), atrib.GetInt("alturaLinha", 0),
                atrib.GetString("nomeArqIcone", ""), atrib.GetInt("alturaIcone", 0),
                atrib.GetInt("larguraIcone", 0), atrib.GetString("nomeArq", ""),
                atrib.GetInt("retiraFundo", 1), atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGRadioBox(
                idComponente, atrib.GetInt("largura", 0), atrib.GetInt("alturaLinha", 0),
                atrib.GetString("nomeArqIcone", ""), atrib.GetInt("alturaIcone", 0),
                atrib.GetInt("larguraIcone", 0), atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

void CPIGRadioBox::AjustaFrame(PIGItemComponente item)
{
    int resp;
    if (!item->GetHabilitado())
    {
        if (item->GetAcionado())
        {
            resp = 6;
        }
        else
        {
            resp = 5;
        }
    }
    else if (item->GetMouseOver())
    {
        if (item->GetAcionado())
        {
            resp = 4;
        }
        else
        {
            resp = 3;
        }
    }
    else
    {
        if (item->GetAcionado())
        {
            resp = 2;
        }
        else
        {
            resp = 1;
        }
    }
    item->GetIcone()->MudaFrameAtual(resp);
}

CPIGRadioBox::CPIGRadioBox(
        int idComponente, int larguraTotal, int alturaLinha, const string &imgIcone,
        int alturaIcone, int larguraIcone, const string &imgFundo, int retiraFundo, int janela)
    : CPIGListaItemComponente(
              idComponente, larguraTotal, alturaLinha, imgFundo, retiraFundo, janela)
{
    arqImagemIcone = imgIcone;
    itemDestaque = -1;
    tipo = PIG_RADIOBOX;
}

CPIGRadioBox::CPIGRadioBox(
        int idComponente, int larguraTotal, int alturaLinha, const string &imgIcone,
        int alturaIcone, int larguraIcone, int janela)
    : CPIGListaItemComponente(idComponente, larguraTotal, alturaLinha, janela)
{
    arqImagemIcone = imgIcone;
    itemDestaque = -1;
    tipo = PIG_RADIOBOX;
}

CPIGRadioBox::CPIGRadioBox(int idComponente, const CPIGAtributos &atrib)
    : CPIGRadioBox(LeParametros(idComponente, atrib))
{}

int CPIGRadioBox::GetItemDestaque() const
{
    return itemDestaque;
}

int CPIGRadioBox::SetAcionadoItem(int indice, bool valor)
{
    int resp = CPIGListaItemComponente::SetAcionadoApenasItem(indice, valor);
    if (resp)
    {
        itemDestaque = indice;
    }
    return resp;
}

void CPIGRadioBox::CriaItem(
        const string &itemLabel, const string &arqImagemFundoItem, bool itemHabilitado,
        const string &hintMsg, int retiraFundo, int retiraFundoIcone)
{
    CPIGListaItemComponente::SetDimensoes(
            alt + altBaseLista, larg); // aumenta o tamanho do componente para comportar o novo item
    DeslocaItens(0, altBaseLista); // desloca todos os itens para cima, pois o novo item vai entrar
                                   // abaixo dos outros

    int yItem = pos.y + margemBaixo;
    PIGItemComponente item = CPIGListaItemComponente::CriaItem(
            yItem, itemLabel, arqImagemIcone, arqImagemFundoItem, false, itemHabilitado, hintMsg,
            retiraFundo, retiraFundoIcone);
    item->DefineFuncaoAjusteFrame(AjustaFrame);
    item->GetIcone()->CriaFramesAutomaticosPorLinha(1, 1, 6);
    AjustaFrame(item);
}

void CPIGRadioBox::CriaItem(CPIGAtributos atrib)
{
    CPIGListaItemComponente::SetDimensoes(
            alt + altBaseLista, larg); // aumenta o tamanho do componente para comportar o novo item
    DeslocaItens(0, altBaseLista); // desloca todos os itens para cima, pois o novo item vai entrar
                                   // abaixo dos outros

    int yItem = pos.y + margemBaixo;
    PIGItemComponente item = CPIGListaItemComponente::CriaItem(
            yItem, atrib.GetString("label", ""), arqImagemIcone, atrib.GetString("nomeArq", ""),
            false, atrib.GetInt("habilitado", 1), atrib.GetString("hint", ""),
            atrib.GetInt("retiraFundo", 1), atrib.GetInt("retiraFundoIcone", 1));
    item->DefineFuncaoAjusteFrame(AjustaFrame);
    item->GetIcone()->CriaFramesAutomaticosPorLinha(1, 1, 6);
    AjustaFrame(item);
}

int CPIGRadioBox::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x, pos.y, alt, larg);

    if (imagemPropria)
    { // se tiver imagem de fundo
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }

    for (PIGItemComponente i: itens)
    {
        i->Desenha();
    }

    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

    return CPIGComponente::Desenha();
}

PIGEstadoEvento CPIGRadioBox::TrataEventoMouse(PIGEvento evento)
{
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    int resp = itemDestaque;
    bool mouseOverAntes = mouseOver;

    if (ChecaMouseOver(GetPosicaoMouse()) > 0)
    {
        for (unsigned int i = 0; i < itens.size(); i++)
        {
            if (itens[i]->TrataEventoMouse(evento) == PIG_COMPONENTE_TRATADO)
            {
                if (itens[i]->GetAcionado())
                {
                    resp = i;
                }

                SetAcionadoApenasItem(resp, resp != -1);
                itemDestaque = resp;
                OnAction();
                break;
            }
        }

        if (resp > 0)
        {
            return PIG_COMPONENTE_TRATADO;
        }
        return PIG_COMPONENTE_MOUSEOVER;
    }
    else if (mouseOverAntes)
    { // mouse estava antes, mas saiu
        for (PIGItemComponente i: itens)
        {
            i->SetMouseOver(false);
        }
    }

    return PIG_COMPONENTE_NAOTRATADO;
}

void CPIGRadioBox::SetDimensoes(int altura, int largura)
{
    CPIGComponente::SetDimensoes(itens.size() * altBaseLista, largura);

    for (PIGItemComponente i: itens)
    {
        i->SetDimensoes(altIcone, largura);
    }

    Move(pos.x, pos.y);
}

void CPIGRadioBox::SetMargens(int mEsq, int mDir, int mCima, int mBaixo)
{
    CPIGListaItemComponente::SetMargens(mEsq, mDir, mCima, mBaixo);
    alt = altBaseLista * itens.size() + margemBaixo + margemCima;
}
