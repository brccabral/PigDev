#include <pig/CPIGCaixaTexto.h>
#include <pig/CPIGGerenciadorJanelas.h>
#include <pig/CPIGGerenciadorAudios.h>
#include <pig/CPIGGerenciadorFontes.h>

void CPIGCaixaTexto::IniciaCoresBasicas()
{
    coresBasicas[0] = CINZA;
    coresBasicas[1] = BRANCO;
    coresBasicas[2] = PRETO;
}

void CPIGCaixaTexto::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGComponente::ProcessaAtributos(atrib);

    int valorInt = atrib.GetInt("fonte", -1);
    if (valorInt >= 0)
    {
        SetFonteTexto(valorInt);
    }

    string valorStr = atrib.GetString("texto", "");
    if (!valorStr.empty())
    {
        SetTexto(valorStr);
    }

    valorStr = atrib.GetString("corFundo", "");
    if (!valorStr.empty())
    {
        SetCorFundo(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corFonte", "");
    if (!valorStr.empty())
    {
        SetCorFonte(PIGCriaCorString(valorStr));
    }

    valorStr = atrib.GetString("corCursor", "");
    if (!valorStr.empty())
    {
        SetCorCursor(PIGCriaCorString(valorStr));
    }
}

// checa se o ponteiro do mouse está sobre o componente
int CPIGCaixaTexto::ChecaMouseOver(const SDL_Point pMouse)
{
    if (!visivel)
    {
        return -1;
    }

    SDL_Rect r = {
            (int) pos.x + margemEsq, ((int) pos.y) + margemBaixo, larg - (margemDir + margemEsq),
            alt - (margemBaixo + margemCima)};

    SetMouseOver(SDL_PointInRect(&pMouse, &r));
    return mouseOver;
}

// desenha o cursor
void CPIGCaixaTexto::DesenhaCursor()
{
    if (temFoco)
    {
        if (cursorExibido)
        {
            CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(
                    xCursor, yCursor, xCursor, yCursor + altLetra, coresBasicas[2]);
        }
        if (timer && timer->GetTempoDecorrido() > 1)
        {
            cursorExibido = !cursorExibido;
            timer->Reinicia(false);
        }
    }
}

// trata teclas de movimentaçăo do cursor
PIGEstadoEvento CPIGCaixaTexto::TrataTeclasEspeciais(const PIGEvento evento)
{
    switch (evento.teclado.tecla)
    {
        case PIG_TECLA_BACKSPACE:
            RetiraTextoBackSpace();
            break;
        case PIG_TECLA_DELETE:
            RetiraTextoDelete();
            break;
        case PIG_TECLA_DIREITA:
            AvancaCursor();
            break;
        case PIG_TECLA_ESQUERDA:
            VoltaCursor();
            break;
        case PIG_TECLA_CIMA:
            SobeCursor();
            break;
        case PIG_TECLA_BAIXO:
            DesceCursor();
            break;
        case PIG_TECLA_ENTER:
            PulaLinha();
            break;
        default:
            break;
    }
    return OnAction();
}

// trata os diversos tipos de eventos de teclado que podem ocorrer
PIGEstadoEvento CPIGCaixaTexto::TrataEventoTeclado(const PIGEvento evento)
{
    if (!temFoco)
    {
        return PIG_COMPONENTE_SEMFOCO;
    }
    if (!habilitado)
    {
        return PIG_COMPONENTE_DESABILITADO;
    }
    if (!visivel)
    {
        return PIG_COMPONENTE_INVISIVEL;
    }

    if (evento.teclado.acao == PIG_TECLA_EDICAO)
    {
        return PIG_COMPONENTE_TRATADO;
    }

    if (evento.teclado.acao == PIG_TECLA_INPUT)
    { // caracteres normais
        string s = ConverteString(evento.teclado.texto);
        if (AdicionaTexto(s))
        {
            return OnAction();
        }
        return PIG_COMPONENTE_NAOTRATADO;
    }

    if (evento.teclado.acao == PIG_TECLA_PRESSIONADA)
    { // teclas especiais
        return TrataTeclasEspeciais(evento);
    }
    return PIG_COMPONENTE_NAOTRATADO;
}

// posiciona o cursor uma posiçăo ŕ frente
int CPIGCaixaTexto::AvancaCursor()
{
    if (posCursor >= (int) texto.size())
    {
        return 0; // năo tem caracter na frente do cursor
    }
    posCursor++;
    AjustaPosicaoTextoCursor();
    return 1;
}

// posiciona o cursor uma posiçăo atrás
int CPIGCaixaTexto::VoltaCursor()
{
    if (posCursor == 0)
    {
        return 0; // năo tem caractere atrés do cursor
    }
    posCursor--;
    AjustaPosicaoTextoCursor();
    return 1;
}

// reira um caracter com a tecla backspace
int CPIGCaixaTexto::RetiraTextoBackSpace()
{
    if (texto.empty() || posCursor == 0)
    {
        return 0; // năo tem caractere atrés do cursor
    }

    texto.erase(
            posCursor - 1,
            1); // retira o caracter imediatamente atrás do cursor e retrocede com ele
    VoltaCursor();
#ifdef PIGCOMAUDIO
    if (audioComponente >= 0)
    {
        CPIGGerenciadorAudios::Play(audioComponente);
    }
#endif
    return 1;
}

// retira um caracter com a tecla delete
int CPIGCaixaTexto::RetiraTextoDelete()
{
    if (texto.empty() || posCursor >= (int) texto.size())
    {
        return 0; // năo tem caracter na frente do cursor
    }

    texto.erase(posCursor, 1); // retira o caracter imediatamente a frente do cursor

#ifdef PIGCOMAUDIO
    if (audioComponente >= 0)
    {
        CPIGGerenciadorAudios::Play(audioComponente);
    }
#endif
    return 1;
}

// adiciona um texto (caracter ou string) na posiçăo indicada pelo cursor (se possível)
int CPIGCaixaTexto::AdicionaTexto(const string &frase)
{
    if (texto.size() + frase.size() > maxCaracteres)
    {
        return 0; // ultrapassa o limite máximo de carcteres
    }
    // if (somenteNumeros&&!PIGSomenteNumeros(frase)) return 0;//năo é número

    texto.insert(posCursor, frase);

    AvancaCursor();
    return 1;
}

// converte caracteres especiais, como acentos por exemplo
string CPIGCaixaTexto::ConverteString(const char *str)
{
    string resp(str);
    if (strlen(str) > 1)
    {
        if ((uint8_t) str[0] == 195)
        {
            resp = str[1];
        } /*else if ((uint8_t)str[0]==194){
             resp = str[1];
         }*/
    }
    return resp;
}

int CPIGCaixaTexto::CalculaPosicaoCursor(const string &linha, const int xMouse) const
{
    int delta = xMouse - xTexto;
    int largParcial = 0, largUltimaLetra = 0;

    for (unsigned int i = 0; i < linha.size(); i++)
    {
        string aux;

        aux.assign(linha, 0, i + 1);

        largParcial = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetLarguraPixelsString(aux);

        // printf("aux: <%s> %d %d\n",aux.c_str(),largParcial,delta);

        if (delta < largParcial)
        {
            if (delta - largUltimaLetra < largParcial - delta)
            {
                return i;
            }
            return i + 1;
            // if (linha[resp]=='\n')
            //     resp--;
        }
        largUltimaLetra = largParcial;
    }

    return linha.size();
}

// o botao esquerdo faz com que a ediçăo do trexto comece ou que o cursor seja reposicionado
PIGEstadoEvento CPIGCaixaTexto::TrataMouseBotaoEsquerdo(const SDL_Point p)
{
    return TrataMouseBotaoEsquerdo(p, 0);
}
// o botao esquerdo faz com que a ediçăo do trexto comece ou que o cursor seja reposicionado
PIGEstadoEvento CPIGCaixaTexto::TrataMouseBotaoEsquerdo(const SDL_Point p, int inicioLinha)
{
    posCursor = CalculaPosicaoCursor(GetTextoVisivel(), p.x);
    AjustaPosicaoTextoCursor();
    return PIG_COMPONENTE_TRATADO;
}

void CPIGCaixaTexto::IniciaBase(const int maxCars)
{
    margemEsq = margemDir = margemCima = margemBaixo = 5;
    posLabel = PIG_POSICAO_ESQ_BAIXO; // posiçăo padrăo do label
    posCursor = 0; // cursor no início do texto
    cursorExibido = true;
    timer = new CPIGTimer(false); // o timer do cursor que só será exibido quando estiver editando
    SetFonteTexto(0);
    maxCaracteres = maxCars;
    IniciaCoresBasicas();
    AjustaPosicaoTextoCursor();
}

void CPIGCaixaTexto::SetFoco(const bool valor)
{
    CPIGComponente::SetFoco(valor);
    if (temFoco)
    {
        SDL_StartTextInput();
    }
    else
    {
        SDL_StopTextInput();
    }
}

CPIGCaixaTexto::CPIGCaixaTexto(
        const int idComponente, const int altura, const int largura, const string &nomeArq,
        const int maxCars, const int retiraFundo, const int janela)
    : CPIGComponente(idComponente, altura, largura, nomeArq, retiraFundo, janela)
{
    IniciaBase(maxCars);
}

CPIGCaixaTexto::CPIGCaixaTexto(
        const int idComponente, const int altura, const int largura, const int maxCars,
        const int janela)
    : CPIGComponente(idComponente, altura, largura, janela)
{
    IniciaBase(maxCars);
}

CPIGCaixaTexto::~CPIGCaixaTexto()
{
    delete timer;
}

// define o texto a ser mostrado no componente
int CPIGCaixaTexto::SetTexto(const string &frase)
{
    texto = frase;
    posCursor = 0;
    AjustaPosicaoTextoCursor();
    return 1;
}

// deifne a fonte de texto
void CPIGCaixaTexto::SetFonteTexto(const int fonte)
{
    fonteTexto = fonte;
    altLetra = CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetTamanhoBaseFonte() +
               CPIGGerenciadorFontes::GetFonte(fonteTexto)->GetFonteDescent();
    AjustaPosicaoTextoCursor();
}

// recupera o texto armazenado no componente
string CPIGCaixaTexto::GetTexto()
{
    return texto;
}

// define a cor do fundo
void CPIGCaixaTexto::SetCorFundo(const PIGCor cor)
{
    coresBasicas[0] = cor;
}

// define a cor da fonte
void CPIGCaixaTexto::SetCorFonte(const PIGCor cor)
{
    coresBasicas[1] = cor;
}

// define a cor do cursor
void CPIGCaixaTexto::SetCorCursor(const PIGCor cor)
{
    coresBasicas[2] = cor;
}

// reposiciona o componente
void CPIGCaixaTexto::Move(const double nx, const double ny)
{
    int dx = nx - pos.x;
    int dy = ny - pos.y;
    CPIGComponente::Desloca(dx, dy);
    xCursor += dx;
    yCursor += dy;
    xTexto += dx;
    yTexto += dy;
}

// define as margens do componente
void CPIGCaixaTexto::SetMargens(const int mEsq, const int mDir, const int mCima, const int mBaixo)
{
    CPIGComponente::SetMargens(mEsq, mDir, mCima, mBaixo);
    AjustaPosicaoTextoCursor();
}
