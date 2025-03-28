#include <pig/CPIGForm.h>
#include <pig/CPIGGerenciadorJanelas.h>
#include <pig/CPIGListaItemComponente.h>
#include <pig/CPIGBotaoOnOff.h>
#include <pig/CPIGCampoTextoESenha.h>
#include <pig/CPIGListBox.h>
#include <pig/CPIGDropDown.h>
#include <pig/CPIGGaugeBar.h>
#include <pig/CPIGRadioBox.h>
#include <pig/CPIGCheckBox.h>
#include <pig/CPIGGaugeCircular.h>
#include <pig/CPIGBotaoClick.h>
#include <pig/CPIGAreaDeTexto.h>

PIGEstadoEvento CPIGForm::TrataEventoMouse(PIGEvento evento)
{
    componenteMouseOver = -1;
    for (int i = 0; i < totalComponentes; i++)
    {
        PIGEstadoEvento aux = componentes[i]->TrataEventoMouse(evento);
        if (aux == PIG_COMPONENTE_TRATADO)
        {
            if (componenteComFoco != -1 && componenteComFoco != i)
            { // se já tem um outro componente com foco, ele vai perder o foco
                componentes[componenteComFoco]->SetFoco(false);
            }
            componenteComFoco = i; // anota que terá o foco
            componenteMouseOver = i; // anota que tem MouseOver
            componentes[componenteComFoco]->SetFoco(true); // faz o componente em questăo ganhar
                                                           // foco
            return aux;
        }
        if (aux == PIG_COMPONENTE_MOUSEOVER)
        {
            componenteMouseOver = i;
        }
    }
    if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO &&
        componenteComFoco != -1)
    { // se já tem um componente com foco, ele vai perder o foco
        componentes[componenteComFoco]->SetFoco(false);
        componenteComFoco = -1;
    }
    return PIG_COMPONENTE_NAOTRATADO;
}

PIGEstadoEvento CPIGForm::TrataEventoTeclado(PIGEvento evento)
{
    if (componenteComFoco != -1)
    {
        return componentes[componenteComFoco]->TrataEventoTeclado(evento);
    }

    PIGEstadoEvento resp = PIG_COMPONENTE_NAOTRATADO;

    for (int i = 0; i < totalComponentes; i++)
    {
        PIGEstadoEvento aux = componentes[i]->TrataEventoTeclado(evento);
        if (aux != PIG_COMPONENTE_NAOTRATADO)
        {
            resp = aux;
        }
    }
    return resp;
}

void CPIGForm::IniciaBase()
{
    coresBasicas[0] = PIGCor{0, 0, 0, 0};
    totalComponentes = 0;
    componenteComFoco = componenteMouseOver = -1;
    for (auto &componente: componentes)
    {
        componente = NULL;
    }
    tipo = PIG_FORM;
}

PIGTipoComponente CPIGForm::GetTipoComponente(string tipo)
{
    ranges::transform(tipo.begin(), tipo.end(), tipo.begin(), ::toupper);
    if (tipo == "BOTAOCLICK")
    {
        return PIG_BOTAOCLICK;
    }
    if (tipo == "BOTAOONOFF")
    {
        return PIG_BOTAOONOFF;
    }
    if (tipo == "CAMPODETEXTO")
    {
        return PIG_CAMPOTEXTO;
    }
    if (tipo == "AREADETEXTO")
    {
        return PIG_AREADETEXTO;
    }
    if (tipo == "CHECKBOX")
    {
        return PIG_CHECKBOX;
    }
    if (tipo == "RADIOBOX")
    {
        return PIG_RADIOBOX;
    }
    if (tipo == "LISTBOX")
    {
        return PIG_LISTBOX;
    }
    if (tipo == "DROPDOWN")
    {
        return PIG_DROPDOWN;
    }
    if (tipo == "GAUGEBAR")
    {
        return PIG_GAUGEBAR;
    }
    if (tipo == "GAUGECIRCULAR")
    {
        return PIG_GAUGECIRCULAR;
    }
    if (tipo == "SLIDEBAR")
    {
        return PIG_SLIDEBAR;
    }
    if (tipo == "ITEM")
    {
        return PIG_ITEMCOMPONENTE;
    }
    printf("componente <%s> invalido lido da linha da parametros!!!\n", tipo.c_str());
    return (PIGTipoComponente) -1;
}

CPIGForm CPIGForm::LeArquivo(int idForm, const string &nomeArqTexto)
{
    CPIGForm *resp = NULL;

    ifstream arq(nomeArqTexto);
    if (!arq.is_open())
    {
        printf("Erro abrir arquivo <%s> para construir form\n", nomeArqTexto.c_str());
        exit(1);
    }

    string linha;
    getline(arq, linha);

    CPIGAtributos atrib = CPIGAtributos::GetAtributos(linha);

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGForm(
                idForm, atrib.GetInt("altura", PIG_ALT_TELA),
                atrib.GetInt("largura", PIG_LARG_TELA), atrib.GetString("nomeArq", ""),
                atrib.GetInt("retiraFundo", 1), atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGForm(
                idForm, atrib.GetInt("altura", PIG_ALT_TELA),
                atrib.GetInt("largura", PIG_LARG_TELA), atrib.GetInt("janela", 0));
    }

    int px = atrib.GetInt("px", 0);
    int py = atrib.GetInt("py", 0);
    resp->Move(px, py);

    while (!arq.eof())
    {
        getline(arq, linha);
        if (!linha.empty() && linha[0] != '#')
        {
            resp->CriaComponentePorParametro(linha);
        }
    }

    arq.close();

    return *resp;
}

void CPIGForm::CriaItemLista(const CPIGAtributos &atrib) const
{
    PIGListaComponente comp = (PIGListaComponente) componentes[totalComponentes - 1];
    comp->CriaItem(atrib);
}

CPIGForm::CPIGForm(int idForm, int altForm, int largForm, int janela)
    : CPIGComponente(idForm, altForm, largForm, janela)
{
    IniciaBase();
}

CPIGForm::CPIGForm(
        int idForm, int altForm, int largForm, const string &nomeArq, int retiraFundo, int janela)
    : CPIGComponente(idForm, altForm, largForm, nomeArq, retiraFundo, janela)
{
    IniciaBase();
}

CPIGForm::CPIGForm(int idForm, const string &nomeArqTexto)
    : CPIGForm(LeArquivo(idForm, nomeArqTexto))
{}


CPIGForm::~CPIGForm()
{
    for (int i = 0; i < totalComponentes; i++)
    {
        delete componentes[i];
    }
}

int CPIGForm::GetIdComponente(const string &label) const
{
    for (int i = 0; i < totalComponentes; i++)
    {
        if (componentes[i]->GetLabel() == label)
        {
            return componentes[i]->GetId();
        }
    }
    return -1;
}

int CPIGForm::GetIdComponente(int indice) const
{
    if (indice < 0 || indice >= totalComponentes)
    {
        throw CPIGErroIndice(indice, "componentes");
    }
    return (id * PIG_MAX_COMPONENTES) + indice;
}

int CPIGForm::GetProxIdComponente() const
{
    return (id * PIG_MAX_COMPONENTES) + totalComponentes;
}

int CPIGForm::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    if (imagemPropria)
    {
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }

    // desenha primeiro os componentes fora do mouse
    for (int i = 0; i < totalComponentes; i++)
    {
        if (i != componenteMouseOver)
        {
            componentes[i]->Desenha();
        }
    }
    // desenha o componente sob o mouse para que o hint fique por cima dos demais
    if (componenteMouseOver != -1)
    {
        componentes[componenteMouseOver]->Desenha();
    }

    return CPIGComponente::Desenha();
}

int CPIGForm::TrataEvento(const PIGEvento &evento)
{
    if (evento.tipoEvento == PIG_EVENTO_MOUSE)
    {
        return TrataEventoMouse(evento);
    }
    if (evento.tipoEvento == PIG_EVENTO_TECLADO)
    {
        return TrataEventoTeclado(evento);
    }
    return 0;
}

PIGComponente CPIGForm::GetComponente(int idComponente) const
{
    if (componentes[idComponente % PIG_MAX_COMPONENTES] == NULL)
    {
        throw CPIGErroIndice(idComponente, "componentes");
    }
    return componentes[idComponente % PIG_MAX_COMPONENTES];
}

int CPIGForm::CriaBotaoClick(int altura, int largura, const string &nomeArq, int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] =
            new CPIGBotaoClick(idComponente, altura, largura, nomeArq, retiraFundo, idJanela);
    return idComponente;
}

int CPIGForm::CriaBotaoClick(int altura, int largura)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGBotaoClick(idComponente, altura, largura, idJanela);
    return idComponente;
}

int CPIGForm::CriaBotaoOnOff(int altura, int largura, const string &nomeArq, int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] =
            new CPIGBotaoOnOff(idComponente, altura, largura, nomeArq, retiraFundo, idJanela);
    return idComponente;
}

int CPIGForm::CriaBotaoOnOff(int altura, int largura)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente, altura, largura, idJanela);
    return idComponente;
}

int CPIGForm::CriaAreaDeTexto(
        int altura, int largura, const string &nomeArq, int maxCars, int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGAreaDeTexto(
            idComponente, altura, largura, nomeArq, maxCars, retiraFundo, idJanela);
    return idComponente;
}

int CPIGForm::CriaAreaDeTexto(int altura, int largura, int maxCars)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] =
            new CPIGAreaDeTexto(idComponente, altura, largura, maxCars, idJanela);
    return idComponente;
}

int CPIGForm::CriaCampoTextoESenha(
        int altura, int largura, const string &nomeArq, int maxCars, bool apenasNumeros,
        int retiraFundo, bool campoSenha)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGCampoTextoESenha(
            idComponente, altura, largura, nomeArq, maxCars, apenasNumeros, campoSenha, retiraFundo,
            idJanela);
    return idComponente;
}

int CPIGForm::CriaCampoTextoESenha(
        int altura, int largura, int maxCars, bool apenasNumeros, bool campoSenha)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGCampoTextoESenha(
            idComponente, altura, largura, maxCars, apenasNumeros, campoSenha, idJanela);
    return idComponente;
}

int CPIGForm::CriaListBox(
        int larguraTotal, int alturaLinha, int altItem, int largItem, const string &nomeArq,
        int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGListBox(
            idComponente, larguraTotal, alturaLinha, altItem, largItem, nomeArq, retiraFundo,
            idJanela);
    return idComponente;
}

int CPIGForm::CriaListBox(int larguraTotal, int alturaLinha, int altItem, int largItem)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] =
            new CPIGListBox(idComponente, larguraTotal, alturaLinha, altItem, largItem, idJanela);
    return idComponente;
}

int CPIGForm::CriaDropDown(
        int larguraTotal, int alturaLinha, int altItem, int largItem, const string &nomeArq,
        int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGDropDown(
            idComponente, larguraTotal, alturaLinha, altItem, largItem, nomeArq, retiraFundo,
            idJanela);
    return idComponente;
}

int CPIGForm::CriaDropDown(int larguraTotal, int alturaLinha, int altItem, int largItem)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] =
            new CPIGDropDown(idComponente, larguraTotal, alturaLinha, altItem, largItem, idJanela);
    return idComponente;
}

int CPIGForm::CriaGaugeBar(
        int altura, int largura, const string &imgMoldura, const string &imgMarcador,
        int retiraFundoMoldura, int retiraFundoMarcador)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGGaugeBar(
            idComponente, altura, largura, imgMoldura, imgMarcador, retiraFundoMoldura,
            retiraFundoMarcador, idJanela);
    return idComponente;
}

int CPIGForm::CriaGaugeBar(int altura, int largura)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGGaugeBar(idComponente, altura, largura, idJanela);
    return idComponente;
}

int CPIGForm::CriaRadioBox(
        int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
        int larguraItem, const string &imagemFundo, int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGRadioBox(
            idComponente, larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem,
            imagemFundo, retiraFundo, idJanela);
    return idComponente;
}

int CPIGForm::CriaRadioBox(
        int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
        int larguraItem)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGRadioBox(
            idComponente, larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem, idJanela);
    return idComponente;
}

int CPIGForm::CriaCheckBox(
        int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
        int larguraItem, const string &imagemFundo, int retiraFundo)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGCheckBox(
            idComponente, larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem,
            imagemFundo, retiraFundo, idJanela);
    return idComponente;
}

int CPIGForm::CriaCheckBox(
        int larguraTotal, int alturaLinha, const string &imagemItem, int alturaItem,
        int larguraItem)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGCheckBox(
            idComponente, larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem, idJanela);
    return idComponente;
}

int CPIGForm::CriaGaugeCircular(int altura, int largura)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] =
            new CPIGGaugeCircular(idComponente, altura, largura, idJanela);
    return idComponente;
}

int CPIGForm::CriaGaugeCircular(
        int altura, int largura, const string &imgTrilha, int alturaMarcador, int larguraMarcador,
        const string &imgMarcador, int retiraFundoTrilha, int retiraFundoMarcador)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGGaugeCircular(
            idComponente, altura, largura, imgTrilha, alturaMarcador, larguraMarcador, imgMarcador,
            retiraFundoTrilha, retiraFundoMarcador, idJanela);
    return idComponente;
}

int CPIGForm::CriaSlideBar(
        int altura, int largura, const string &imgTrilha, int alturaMarcador, int larguraMarcador,
        const string &imgMarcador, int retiraFundoTrilha, int retiraFundoMarcador)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGSlideBar(
            idComponente, altura, largura, imgTrilha, alturaMarcador, larguraMarcador, imgMarcador,
            retiraFundoTrilha, retiraFundoMarcador, idJanela);
    return idComponente;
}

int CPIGForm::CriaSlideBar(int altura, int largura, int alturaMarcador, int larguraMarcador)
{
    int idComponente = GetProxIdComponente();
    componentes[totalComponentes++] = new CPIGSlideBar(
            idComponente, altura, largura, alturaMarcador, larguraMarcador, idJanela);
    return idComponente;
}

int CPIGForm::CriaComponentePorParametro(const string &parametros)
{
    int idComponente = GetProxIdComponente();

    CPIGAtributos atrib = CPIGAtributos::GetAtributos(parametros);

    switch (GetTipoComponente(atrib.GetString("tipo", "")))
    {
        case PIG_BOTAOCLICK:
            componentes[totalComponentes++] = new CPIGBotaoClick(idComponente, atrib);
            break;
        case PIG_BOTAOONOFF:
            componentes[totalComponentes++] = new CPIGBotaoOnOff(idComponente, atrib);
            break;
        case PIG_AREADETEXTO:
            componentes[totalComponentes++] = new CPIGAreaDeTexto(idComponente, atrib);
            break;
        case PIG_CAMPOTEXTO:
            componentes[totalComponentes++] = new CPIGCampoTextoESenha(idComponente, atrib);
            break;
        case PIG_RADIOBOX:
            componentes[totalComponentes++] = new CPIGRadioBox(idComponente, atrib);
            break;
        case PIG_CHECKBOX:
            componentes[totalComponentes++] = new CPIGCheckBox(idComponente, atrib);
            break;
        case PIG_LISTBOX:
            componentes[totalComponentes++] = new CPIGListBox(idComponente, atrib);
            break;
        case PIG_DROPDOWN:
            componentes[totalComponentes++] = new CPIGDropDown(idComponente, atrib);
            break;
        case PIG_GAUGEBAR:
            componentes[totalComponentes++] = new CPIGGaugeBar(idComponente, atrib);
            break;
        case PIG_SLIDEBAR:
            componentes[totalComponentes++] = new CPIGSlideBar(idComponente, atrib);
            break;
        case PIG_GAUGECIRCULAR:
            componentes[totalComponentes++] = new CPIGGaugeCircular(idComponente, atrib);
            break;
        case PIG_ITEMCOMPONENTE:
            CriaItemLista(atrib);
        default:
            break;
            ;
    }

    return idComponente;
}
