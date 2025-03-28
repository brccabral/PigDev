#include <pig/CPIGAreaDeTexto.h>
#include <pig/CPIGGerenciadorFontes.h>

void CPIGAreaDeTexto::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGCaixaTexto::ProcessaAtributos(atrib);

    int valorInt = atrib.GetInt("espacoEntreLinhas", 0);
    if (valorInt > 0)
    {
        SetEspacoEntreAsLinhas(valorInt);
    }

    valorInt = atrib.GetInt("linhasVisiveis", 0);
    if (valorInt != 0)
    {
        SetLinhasAbaixoTexto(valorInt);
    }

    string valorStr = atrib.GetString("corLinhas", "");
    if (!valorStr.empty())
    {
        SetCorLinhas(PIGCriaCorString(valorStr));
    }
}

CPIGAreaDeTexto CPIGAreaDeTexto::LeParametros(const int idComponente, CPIGAtributos atrib)
{
    CPIGAreaDeTexto *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGAreaDeTexto(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("maxCaracters", 200),
                atrib.GetInt("retiraFundo", 1), atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGAreaDeTexto(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetInt("maxCaracters", 200), atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

// Recupera todo o texto da área
string CPIGAreaDeTexto::GetTextoVisivel()
{
    return GetTexto();
}

int CPIGAreaDeTexto::GetLarguraLinhaMaior()
{
    int tamMaior = 0;
    int temp = 0;
    for (const string &linha: linhas)
    {
        temp = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(linha);
        tamMaior = (temp > tamMaior) ? (temp) : (tamMaior);
    }
    return tamMaior;
}

void CPIGAreaDeTexto::AjustaSlideVerticalPeloCursor()
{
    int alturaTotalTexto = linhas.size() * (espacoEntreLinhas + altLetra);

    slideVerticalAtivado = alturaTotalTexto > (alt - margemCima + margemBaixo);

    // printf("vett ativado %d\n",slideVerticalAtivado);
    if (slideVerticalAtivado)
    {
        slideVertical->SetValorMax(alturaTotalTexto - (alt - margemCima - margemBaixo));
        int deltaY = 0;
        if (yCursor < pos.y + margemBaixo)
        {
            deltaY = pos.y + margemBaixo - yCursor;
            // printf("posy %d marg %d yC %d",(int)pos.y,margemVertBaixo,yCursor);
        }
        else if (yCursor + altLetra > pos.y + alt - margemCima)
        {
            deltaY = (pos.y + alt - margemCima) - (yCursor + altLetra);
            // printf("posy %d alt %d marg %d yC
            // %d",(int)pos.y,alt,margemVertCima,yCursor+altLetra);
        }
        // printf(" deltaY %d\n",deltaY);
        yCursor += deltaY;
        yTexto += deltaY;
        slideVertical->AvancaMarcador(deltaY);
    }
}

// Desenha um contorno baseado nas dimensoes reais da área(somando a área em si e a scroll bar)
// void DesenhaMarcacaoMargem(){
//     CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(pos.x+margemHorEsq,pos.y+margemVertBaixo,alt-margemVertBaixo-margemVertCima-1,larg-margemHorDir-margemHorEsq,coresBasicas[2]);
// }

void CPIGAreaDeTexto::IniciaPosicaoTexto()
{
    yTexto = pos.y + alt - altLetra - margemCima;
    xTexto = pos.x + margemEsq;
}

// Ajusta o alinhamento do texto quando ocorre alguma modificaçăo
void CPIGAreaDeTexto::AjustaPosicaoTextoCursor()
{
    string textoBase = GetTextoVisivel();
    string aux;

    linhas = CPIGGerenciadorFontes::GetFonte(fonteTexto)
                     ->ExtraiLinhas(textoBase, larg - (margemEsq + margemDir));

    int linhaPos = GetLinhaDeUmaPos(posCursor);
    int posInicial = GetPosInicialDeUmaLinha(linhaPos);

    aux.assign(textoBase, posInicial, posCursor - posInicial);

    // posição inicial do texto
    IniciaPosicaoTexto();

    if (slideVerticalAtivado)
    {
        yTexto += slideVertical->GetValorAtual();
    }

    // definir a posição do cursor
    yCursor =
            yTexto - ((espacoEntreLinhas + altLetra) *
                      GetLinhaDeUmaPos(posCursor)); // descobrindo em qual das linhas o cursor está
    xCursor = xTexto + CPIGGerenciadorFontes::GetFonte(fonteTexto)
                               ->GetLarguraPixelsString(
                                       aux); // descobrindo em qual posição horizontal o cursor está
}

PIGEstadoEvento CPIGAreaDeTexto::PosicionaCursorLinha(const int linha, const int xLinha)
{
    if (linha < 0 || (!linhas.empty() && linha >= (int) linhas.size()))
    {
        return PIG_COMPONENTE_NAOTRATADO;
    }

    int posInicial = GetPosInicialDeUmaLinha(linha);
    // printf("posInicial %d\n",posInicial);

    posCursor = posInicial;
    if (!linhas.empty())
    {
        posCursor += CalculaPosicaoCursor(linhas[linha], xLinha);
    }
    // printf("posCursor %d\n",posCursor);

    AjustaPosicaoTextoCursor();
    AjustaSlideVerticalPeloCursor();
    return PIG_COMPONENTE_TRATADO;
}

int CPIGAreaDeTexto::MouseSobreSlide(const SDL_Point p)
{
    return (p.x > pos.x + larg && p.x < pos.x + larg + tamPadraoSlide && p.y > pos.y &&
            p.y < pos.y + alt);
}

// trata o evento do botao esquerdo
PIGEstadoEvento CPIGAreaDeTexto::TrataMouseBotaoEsquerdo(const SDL_Point p)
{
    return TrataMouseBotaoEsquerdo(p, 0);
}

// trata o evento do botao esquerdo
PIGEstadoEvento CPIGAreaDeTexto::TrataMouseBotaoEsquerdo(const SDL_Point p, int inicioLinha)
{
    int linha = GetLinhaPonto(p);
    return PosicionaCursorLinha(linha, p.x);
}

// retorna o número da linha a partir de um ponto
int CPIGAreaDeTexto::GetLinhaPonto(const SDL_Point p)
{
    if (linhas.empty())
    {
        return 0;
    }

    int deltaLinha = yTexto + altLetra + espacoEntreLinhas - p.y;

    int resp = deltaLinha / (altLetra + espacoEntreLinhas);
    // printf("deltaY %d div %d resp %d\n",deltaLinha,(altLetra+espacoEntreLinhas),resp);

    if (resp >= (int) linhas.size())
    {
        resp = linhas.size() - 1;
    }
    return resp;
}

// retorna a posição da string texto, na qual uma linha inicia
int CPIGAreaDeTexto::GetPosInicialDeUmaLinha(const unsigned int linha)
{
    if (linhas.empty())
    {
        return 0;
    }
    if (linha >= linhas.size())
    {
        return texto.size();
    }

    int resp = 0;
    for (unsigned int i = 0; i < linha; i++)
    {
        resp += linhas[i].size();
    }

    return resp;
}

// retorna em que linha está qualquer uma das posições da string texto
int CPIGAreaDeTexto::GetLinhaDeUmaPos(const int pos)
{
    if (linhas.empty())
    {
        return 0;
    }
    int qntPosicoes = 0;

    for (unsigned int i = 0; i < linhas.size(); i++)
    {
        qntPosicoes += linhas[i].size();

        if (qntPosicoes >= pos)
        {
            return i;
        }
    }

    return 0;
}

//
void CPIGAreaDeTexto::DesenhaLinhasHorizontais()
{
    int yLinha = yTexto;
    int xLinha = pos.x + margemEsq;

    while (yLinha >= pos.y + margemBaixo)
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(
                xLinha, yLinha, xLinha + larg - margemDir, yLinha, coresBasicas[2]);
        yLinha -= (espacoEntreLinhas + altLetra);
    }
}

// move o cursor uma linha para cima
int CPIGAreaDeTexto::SobeCursor()
{
    int linhaCursor = GetLinhaDeUmaPos(posCursor);

    if (linhaCursor > 0)
    {
        return PosicionaCursorLinha(
                linhaCursor - 1, xCursor); // posiciona na linha acima, o mais próximo possível no
                                           // eixo x de onde estava na linha de baixo
    }
    return 0;
}

// move o cursor uma linha para baixo
int CPIGAreaDeTexto::DesceCursor()
{
    int linhaCursor = GetLinhaDeUmaPos(posCursor);

    if (linhaCursor < (int) linhas.size() - 1)
    {
        return PosicionaCursorLinha(
                linhaCursor + 1, xCursor); // posiciona na linha abaixo, o mais próximo possível no
                                           // eixo x de onde estava na linha de baixo
    }
    return 0;
}

// PulaLinha com Enter
int CPIGAreaDeTexto::PulaLinha()
{
    string aux;
    string auxB;

    aux.assign(texto, 0, posCursor);
    auxB += aux;
    auxB += '\n';
    aux.assign(texto, posCursor, texto.size() - posCursor);
    auxB += aux;

    texto = auxB;
    AvancaCursor();
    AjustaSlideVerticalPeloCursor();
    return 1;
}

void CPIGAreaDeTexto::IniciaBase()
{
    espacoEntreLinhas = 0;
    linhasPauta = false;
    slideVerticalAtivado = false;
    tamPadraoSlide = 20;

    slideVertical =
            new CPIGSlideBar(id + 2, alt, tamPadraoSlide, tamPadraoSlide, tamPadraoSlide, idJanela);
    slideVertical->Move(((int) pos.x) + larg, (int) pos.y);
    slideVertical->SetOrientacao(PIG_GAUGE_CIMA_BAIXO);
    AjustaPosicaoTextoCursor();
    CPIGCaixaTexto::IniciaCoresBasicas();
    coresBasicas[3] = AZUL;
    tipo = PIG_AREADETEXTO;
}

CPIGAreaDeTexto::CPIGAreaDeTexto(
        const int idComponente, const int altura, const int largura, const string &nomeArq,
        const int maxCars, const int retiraFundo, const int janela)
    : CPIGCaixaTexto(idComponente, altura, largura, nomeArq, maxCars, retiraFundo, janela)
{
    IniciaBase();
}

CPIGAreaDeTexto::CPIGAreaDeTexto(
        const int idComponente, const int altura, const int largura, const int maxCars,
        const int janela)
    : CPIGCaixaTexto(idComponente, altura, largura, maxCars, janela)
{
    IniciaBase();
}

CPIGAreaDeTexto::CPIGAreaDeTexto(const int idComponente, const CPIGAtributos &atrib)
    : CPIGAreaDeTexto(LeParametros(idComponente, atrib))
{}

CPIGAreaDeTexto::~CPIGAreaDeTexto()
{
    linhas.clear();
    delete slideVertical;
}

void CPIGAreaDeTexto::Move(const double nx, const double ny)
{
    int dx = nx - pos.x;
    int dy = ny - pos.y;
    Desloca(dx, dy);
}

void CPIGAreaDeTexto::Desloca(const double dx, const double dy)
{
    CPIGCaixaTexto::Desloca(dx, dy);
    slideVertical->Desloca(dx, dy);
}

void CPIGAreaDeTexto::SetDimensoes(const int altura, const int largura)
{
    CPIGComponente::SetDimensoes(altura, largura);
    slideVertical->Move(((int) pos.x) + largura, (int) pos.y);
    slideVertical->SetDimensoes(altura, tamPadraoSlide);
    PosicionaLabel();
    AjustaPosicaoTextoCursor();
    AjustaSlideVerticalPeloCursor();
}

int CPIGAreaDeTexto::Desenha()
{
    if (!visivel)
    {
        return 0;
    }

    // imagem de fundo
    if (imagemPropria)
    {
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }

    // DesenhaMarcacaoMargem();
    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(
            pos.x + margemEsq, pos.y + margemBaixo, alt - (margemBaixo + margemCima),
            larg - (margemEsq + margemDir));

    DesenhaCursor(); // desenha o cursor (se estiver em ediçăo)
    CPIGGerenciadorFontes::GetFonte(fonteTexto)
            ->EscreveLonga(
                    texto, xTexto, yTexto, larg - (margemEsq + margemDir),
                    (espacoEntreLinhas + altLetra), coresBasicas[1], PIG_TEXTO_ESQUERDA);

    // desbloqueia o desenho fora da area do componente
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

    if (linhasPauta)
    {
        DesenhaLinhasHorizontais();
    }

    if (slideVerticalAtivado)
    {
        slideVertical->Desenha();
    }

    return CPIGComponente::Desenha();
}

void CPIGAreaDeTexto::SetFonteTexto(const int fonte)
{
    CPIGCaixaTexto::SetFonteTexto(fonte);
    AjustaPosicaoTextoCursor();
    AjustaSlideVerticalPeloCursor();
}

// define se as linhas horizontais serao visiveis
void CPIGAreaDeTexto::SetLinhasAbaixoTexto(const bool visivel)
{
    linhasPauta = visivel;
}

// define a cor da linhas horizontais
void CPIGAreaDeTexto::SetCorLinhas(const PIGCor cor)
{
    coresBasicas[3] = cor;
}

PIGEstadoEvento CPIGAreaDeTexto::TrataEventoMouse(const PIGEvento evento)
{
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    SDL_Point p = GetPosicaoMouse();
    ChecaMouseOver(p);

    if (slideVerticalAtivado && MouseSobreSlide(p))
    {
        ((PIGComponente) slideVertical)->SetFoco(true);
        PIGEstadoEvento resp = slideVertical->TrataEventoMouse(evento);
        ((PIGComponente) slideVertical)->SetFoco(false);
        if (resp == PIG_COMPONENTE_TRATADO)
        {
            AjustaPosicaoTextoCursor();
            return resp;
        }
        if (evento.tipoEvento == PIG_EVENTO_MOUSE && evento.mouse.acao == PIG_MOUSE_RODINHA)
        {
            if (evento.mouse.relY > 0)
                SobeCursor();
            else if (evento.mouse.relY < 0)
                DesceCursor();
            return PIG_COMPONENTE_TRATADO;
        }
    }

    if (mouseOver)
    {
        if (evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO)
        {
            return TrataMouseBotaoEsquerdo(p);
        }
        return PIG_COMPONENTE_MOUSEOVER;
    }

    return PIG_COMPONENTE_NAOTRATADO;
}

// define o espaçamento entre as linhas
void CPIGAreaDeTexto::SetEspacoEntreAsLinhas(const int espaco)
{
    espacoEntreLinhas = espaco;
    AjustaPosicaoTextoCursor();
    AjustaSlideVerticalPeloCursor();
}

int CPIGAreaDeTexto::SetTexto(const string &frase)
{
    CPIGCaixaTexto::SetTexto(frase);
    AjustaPosicaoTextoCursor();
    AjustaSlideVerticalPeloCursor();
    return texto.size();
}

int CPIGAreaDeTexto::AdicionaTexto(const string &frase)
{
    CPIGCaixaTexto::AdicionaTexto(frase);
    AjustaSlideVerticalPeloCursor();
    AjustaPosicaoTextoCursor();
    return texto.size();
}

// recupera o texto separado em linhas
vector<string> CPIGAreaDeTexto::GetLinhasTexto()
{
    return linhas;
}
