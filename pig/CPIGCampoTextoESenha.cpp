#include <pig/CPIGCampoTextoESenha.h>
#include <pig/CPIGGerenciadorFontes.h>

void CPIGCampoTextoESenha::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGCaixaTexto::ProcessaAtributos(atrib);

    string valorStr = atrib.GetString("mascara", "");
    if (!valorStr.empty())
    {
        SetMascara(valorStr[0]);
    }
}

#define MAXCARACTERS 200

CPIGCampoTextoESenha CPIGCampoTextoESenha::LeParametros(int idComponente, CPIGAtributos atrib)
{
    CPIGCampoTextoESenha *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGCampoTextoESenha(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("maxCaracters", MAXCARACTERS),
                atrib.GetInt("apenasNumeros", 0) != 0, atrib.GetInt("campoSenha", 0) != 0,
                atrib.GetInt("retiraFundo", 1), atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGCampoTextoESenha(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetInt("maxCaracters", MAXCARACTERS), atrib.GetInt("apenasNumeros", 0) != 0,
                atrib.GetInt("campoSenha", 0) != 0, atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

// retorna o texto com a quantidade de símbolos (máscara) igual ao tamanho da string com textobase
string CPIGCampoTextoESenha::GetTextoMask()
{
    string resp;
    resp.assign(texto.size(), mascara);
    return resp;
}

// recupera a string com o texto visível (com máscara de senha ou năo)
string CPIGCampoTextoESenha::GetTextoVisivel()
{
    return (this->*GetTextoVisivelPtr)();
}

void CPIGCampoTextoESenha::IniciaPosicaoTexto()
{
    yTexto = pos.y + margemBaixo;
    xTexto = pos.x + margemEsq;
}

// ajusta o alinhamento do cursor
void CPIGCampoTextoESenha::AjustaPosicaoTextoCursor()
{
    string textoBase = GetTextoVisivel();
    int largTextoTotal =
            CPIGGerenciadorFontes::GetFonte(fonteTexto)
                    ->GetLarguraPixelsString(textoBase); // largura total do texto todo (em pixels)

    IniciaPosicaoTexto();

    string aux;
    aux.assign(textoBase, 0, posCursor); // pega a string apenas do início até onde o cursor está
    int largTextoAteCursor =
            CPIGGerenciadorFontes::GetFonte(fonteTexto)
                    ->GetLarguraPixelsString(aux); // largura (em pixels) até o ponto do cursor

    if (largTextoTotal > larg - margemDir - margemEsq)
    { // não cabe todo dentro da caixa
        xTexto = (pos.x + larg - margemDir) - largTextoTotal;
        int deltaCursor = pos.x + margemEsq - (xTexto + largTextoAteCursor);
        if (deltaCursor > 0)
        {
            xTexto += deltaCursor;
        }
    }
    else
    {
        xTexto = pos.x + margemEsq;
    }

    xCursor = xTexto + largTextoAteCursor;
    yCursor = yTexto;
    // printf("xc: %d\n",xCursor);
}

int CPIGCampoTextoESenha::SobeCursor()
{
    return 1;
} // năo usa o SobeCursor

int CPIGCampoTextoESenha::DesceCursor()
{
    return 1;
} // năo usa o DesceCursor

int CPIGCampoTextoESenha::PulaLinha()
{
    return 1;
} // năo usa o PulaLinha

void CPIGCampoTextoESenha::IniciaBase(bool campoSenha, bool apenasNumero)
{
    mascara = '*';
    somenteNumeros = apenasNumero;
    if (campoSenha)
    {
        GetTextoVisivelPtr = &CPIGCampoTextoESenha::CPIGCampoTextoESenha::GetTextoMask;
    }
    else
    {
        GetTextoVisivelPtr = &CPIGCampoTextoESenha::GetTexto;
    }
    CPIGCaixaTexto::IniciaCoresBasicas();
    tipo = PIG_CAMPOTEXTO;
}

CPIGCampoTextoESenha::CPIGCampoTextoESenha(
        int idComponente, int altura, int largura, const string &nomeArq, int maxCars,
        bool apenasNumeros, bool campoSenha, int retiraFundo, int janela)
    : CPIGCaixaTexto(idComponente, altura, largura, nomeArq, maxCars, retiraFundo, janela)
{
    IniciaBase(campoSenha, apenasNumeros);
}

CPIGCampoTextoESenha::CPIGCampoTextoESenha(
        int idComponente, int altura, int largura, int maxCars, bool apenasNumeros, bool campoSenha,
        int janela)
    : CPIGCaixaTexto(idComponente, altura, largura, maxCars, janela)
{
    IniciaBase(campoSenha, apenasNumeros);
}

CPIGCampoTextoESenha::CPIGCampoTextoESenha(int idComponente, const CPIGAtributos &atrib)
    : CPIGCampoTextoESenha(LeParametros(idComponente, atrib))
{}

// desenha o componente completo
int CPIGCampoTextoESenha::Desenha()
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

    CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(
            (int) pos.x + margemEsq, (int) pos.y + margemBaixo, alt - (margemBaixo + margemCima),
            larg - (margemEsq + margemDir));

    CPIGGerenciadorFontes::GetFonte(fonteTexto)
            ->Escreve(GetTextoVisivel(), xTexto, yTexto, coresBasicas[1], PIG_TEXTO_ESQUERDA);
    DesenhaCursor(); // desenha o cursor (se estiver em ediçăo)

    // desbloqueia o desenho fora da area do componente
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

    return CPIGComponente::Desenha();
}

PIGEstadoEvento CPIGCampoTextoESenha::TrataEventoMouse(PIGEvento evento)
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

void CPIGCampoTextoESenha::SetMascara(char c)
{
    mascara = c;
}

int CPIGCampoTextoESenha::AdicionaTexto(const string &frase)
{
    if (somenteNumeros && !PIGSomenteNumeros(frase))
    {
        return 0; // năo é número
    }
    return CPIGCaixaTexto::AdicionaTexto(frase);
}
