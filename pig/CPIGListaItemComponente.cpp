#include <algorithm>
using namespace std;

#include <pig/CPIGListaItemComponente.h>

PIGPosicaoComponente CPIGListaItemComponente::GetAlinhamento(string alinhamento)
{
    ranges::transform(alinhamento.begin(), alinhamento.end(), alinhamento.begin(), ::toupper);
    if (alinhamento == "ESQ_CENTRO")
    {
        return PIG_POSICAO_ESQ_CENTRO;
    }
    if (alinhamento == "DIR_CENTRO")
    {
        return PIG_POSICAO_DIR_CENTRO;
    }
    if (alinhamento == "CENTRO_CENTRO")
    {
        return PIG_POSICAO_CENTRO_CENTRO;
    }
    return PIG_POSICAO_ESQ_CENTRO;
}

void CPIGListaItemComponente::IniciaCoresBasicas()
{
    coresBasicas[0] = CINZA;
    coresBasicas[1] = AZUL;
}

void CPIGListaItemComponente::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGComponente::ProcessaAtributos(atrib);

    string valorStr = atrib.GetString("alinhamentoLabels", "");
    if (!valorStr.empty())
    {
        AlinhaLabelItens(GetAlinhamento(valorStr));
    }

    valorStr = atrib.GetString("alinhamentoIcones", "");
    if (!valorStr.empty())
    {
        AlinhaIcones(GetAlinhamento(valorStr));
    }
}

void CPIGListaItemComponente::IniciaBase(int alturaLinha)
{
    SetPosicaoPadraoLabel(PIG_POSICAO_CIMA_CENTRO); // posiçăo padrăo do label
    altBaseLista = alturaLinha;
    altIcone = largIcone = alturaLinha;
    posIcones = PIG_POSICAO_ESQ_CENTRO; // só pode ser posicionamento à esquerda ou à direita
    IniciaCoresBasicas();
}

PIGItemComponente CPIGListaItemComponente::CriaItem(
        int yItem, const string &itemLabel, const string &arqImagemIcone,
        const string &arqImagemFundo, bool itemMarcado, bool itemHabilitado, const string &hintMsg,
        int retiraFundo, int retiraFundoIcone)
{
    PIGItemComponente item;
    if (arqImagemFundo.empty())
    {
        if (arqImagemIcone.empty())
        {
            item = new CPIGItemComponente(
                    itens.size(), itemLabel, larg - (margemEsq + margemDir), altBaseLista,
                    retiraFundo, idJanela);
        }
        else
        {
            item = new CPIGItemComponente(
                    itens.size(), altIcone, largIcone, arqImagemIcone, itemLabel,
                    larg - (margemEsq + margemDir), altBaseLista, retiraFundoIcone, idJanela);
        }
    }
    else
    {
        if (arqImagemIcone.empty())
        {
            item = new CPIGItemComponente(
                    itens.size(), arqImagemFundo, itemLabel, larg - (margemEsq + margemDir),
                    altBaseLista, retiraFundo, idJanela);
        }
        else
        {
            item = new CPIGItemComponente(
                    itens.size(), altIcone, largIcone, arqImagemIcone, arqImagemFundo, itemLabel,
                    larg - (margemEsq + margemDir), altBaseLista, retiraFundo, retiraFundoIcone,
                    idJanela);
        }
    }
    item->Move(pos.x + margemEsq, yItem);
    item->SetHint(hintMsg);
    item->SetAudio(audioComponente);
    item->SetAcionado(itemMarcado);
    item->SetHabilitado(itemHabilitado);
    // item->SetMargens(margemEsq,margemDir,margemCima,margemBaixo);
    item->AlinhaIcone(posIcones);
    item->AlinhaLabel(posLabels);

    itens.push_back(item);
    return item;
}

void CPIGListaItemComponente::DeslocaItens(double dx, double dy)
{
    for (auto &iten: itens)
    {
        iten->Desloca(dx, dy);
    }
}

CPIGListaItemComponente::CPIGListaItemComponente(
        int idComponente, int larguraTotal, int alturaLinha, const string &nomeArqFundoLista,
        int retiraFundo, int janela)
    : CPIGComponente(idComponente, 0, larguraTotal, nomeArqFundoLista, retiraFundo, janela)
{
    IniciaBase(alturaLinha);
}

CPIGListaItemComponente::CPIGListaItemComponente(
        int idComponente, int larguraTotal, int alturaLinha, int janela)
    : CPIGComponente(idComponente, 0, larguraTotal, janela)
{
    IniciaBase(alturaLinha);
}

CPIGListaItemComponente::~CPIGListaItemComponente()
{
    for (PIGItemComponente i: itens)
    {
        delete i;
    }
    itens.clear();
}

void CPIGListaItemComponente::SetDimensoesIcone(int alturaIcone, int larguraIcone)
{
    for (auto &iten: itens)
    {
        iten->SetDimensoesIcone(alturaIcone, larguraIcone);
    }
}

void CPIGListaItemComponente::AlinhaLabelItens(PIGPosicaoComponente valor)
{
    if (posLabels != valor)
    { // se os labels estăo ŕ direita do botőes, inverte
        posLabels = valor;
        for (PIGItemComponente i: itens)
        {
            i->AlinhaLabel(posLabels);
        }
    }
}

void CPIGListaItemComponente::AlinhaIcones(PIGPosicaoComponente valor)
{
    if (posIcones != valor)
    { // se os labels estăo à direita do botőes, inverte
        posIcones = valor;
        for (PIGItemComponente i: itens)
        {
            i->AlinhaIcone(posIcones);
        }
    }
}

int CPIGListaItemComponente::GetAcionadoItem(int indice)
{
    if (indice < 0 || indice >= (int) itens.size())
    {
        return -1;
    }
    return itens[indice]->GetAcionado();
}

int CPIGListaItemComponente::SetAcionadoItem(int indice, bool valor)
{
    if (indice < 0 || indice >= (int) itens.size())
    {
        return 0;
    }
    itens[indice]->SetAcionado(valor);
    return 1;
}

int CPIGListaItemComponente::SetAcionadoApenasItem(int indice, bool valor)
{
    if (indice < 0 || indice >= (int) itens.size())
    {
        return 0;
    }
    if (valor)
    {
        for (PIGItemComponente i: itens)
        {
            i->SetAcionado(false);
        }
    }
    itens[indice]->SetAcionado(valor);
    return 1;
}

void CPIGListaItemComponente::SetAudioItem(int audio, int indice)
{
    if (indice == -1)
    {
        for (PIGItemComponente item: itens)
        {
            item->SetAudio(audio);
        }
    }
    else if (indice >= 0 && indice < (int) itens.size())
    {
        itens[indice]->SetAudio(audio);
    }
}

void CPIGListaItemComponente::SetCorLabelItem(PIGCor cor, int indice)
{
    if (indice == -1)
    {
        for (PIGItemComponente item: itens)
        {
            item->SetCorLabel(cor);
        }
    }
    else if (indice >= 0 && indice < (int) itens.size())
    {
        itens[indice]->SetCorLabel(cor);
    }
}

void CPIGListaItemComponente::SetCorFundoItem(PIGCor cor, int indice)
{
    if (indice == -1)
    {
        for (PIGItemComponente item: itens)
        {
            item->SetCorFundo(cor);
        }
    }
    else if (indice >= 0 && indice < (int) itens.size())
    {
        itens[indice]->SetCorFundo(cor);
    }
}

void CPIGListaItemComponente::SetFonteItem(int fonte, int indice)
{
    if (indice == -1)
    {
        for (PIGItemComponente item: itens)
        {
            item->SetFonteLabel(fonte);
        }
    }
    else if (indice >= 0 && indice < (int) itens.size())
    {
        itens[indice]->SetFonteLabel(fonte);
    }
}

int CPIGListaItemComponente::GetHabilitadoItem(int indice)
{
    if (indice < 0 || indice >= (int) itens.size())
    {
        return -1;
    }
    return itens[indice]->GetHabilitado();
}

int CPIGListaItemComponente::SetHabilitadoItem(int indice, bool valor)
{
    if (indice < 0 || indice >= (int) itens.size())
    {
        return -1;
    }
    itens[indice]->SetHabilitado(valor);
    return 1;
}

void CPIGListaItemComponente::SetVisivel(bool valor)
{
    visivel = valor;
    for (PIGItemComponente i: itens)
    {
        i->SetVisivel(visivel);
    }
}

void CPIGListaItemComponente::SetFonteHint(int fonte)
{
    for (PIGItemComponente i: itens)
    {
        i->SetFonteHint(fonte);
    }
}

void CPIGListaItemComponente::SetAudio(int audio)
{
    audioComponente = audio;
    for (PIGItemComponente i: itens)
    {
        i->SetAudio(audio);
    }
}

void CPIGListaItemComponente::SetHabilitado(bool valor)
{
    CPIGComponente::SetHabilitado(valor);
    for (PIGItemComponente i: itens)
    {
        i->SetHabilitadoLista(habilitado);
    }
}

string CPIGListaItemComponente::GetLabelItem(int indice)
{
    if (indice < 0 || indice >= (int) itens.size())
    {
        return "";
    }
    return itens[indice]->GetLabel();
}

void CPIGListaItemComponente::Move(double nx, double ny)
{
    double dx = nx - pos.x;
    double dy = ny - pos.y;

    CPIGComponente::Desloca(dx, dy);
    PosicionaLabel();

    DeslocaItens(dx, dy);
}
