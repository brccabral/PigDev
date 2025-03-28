#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGSlideBar.h>
#include <pig/CPIGGerenciadorJanelas.h>
#include <pig/CPIGMouse.h>

void CPIGSlideBar::ProcessaAtributos(CPIGAtributos atrib)
{
    CPIGGauge::ProcessaAtributos(atrib);
}

CPIGSlideBar CPIGSlideBar::LeParametros(int idComponente, CPIGAtributos atrib)
{
    CPIGSlideBar *resp;

    if (!atrib.GetString("nomeArq", "").empty())
    {
        resp = new CPIGSlideBar(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetString("nomeArq", ""), atrib.GetInt("alturaMarcador", 0),
                atrib.GetInt("larguraMarcador", 0), atrib.GetString("nomeArqMarcador", ""),
                atrib.GetInt("retiraFundo", 1), atrib.GetInt("retiraFundoMarcador", 1),
                atrib.GetInt("janela", 0));
    }
    else
    {
        resp = new CPIGSlideBar(
                idComponente, atrib.GetInt("altura", 0), atrib.GetInt("largura", 0),
                atrib.GetInt("alturaMarcador", 0), atrib.GetInt("larguraMarcador", 0),
                atrib.GetInt("janela", 0));
    }

    resp->ProcessaAtributos(atrib);

    return *resp;
}

void CPIGSlideBar::AtualizaMarcador()
{
    CPIGGauge::AtualizaMarcador();

    switch (orientacaoCrescimento)
    {
        case PIG_GAUGE_ESQ_DIR:
            xMarc = pos.x + margemEsq +
                    (int) (porcentagemConcluida * (larg - margemEsq - margemDir - largMarcador));
            yMarc = pos.y + margemBaixo;
            break;
        case PIG_GAUGE_DIR_ESQ:
            xMarc = pos.x + larg - margemDir - largMarcador -
                    (int) ((porcentagemConcluida) * (larg - margemEsq - margemDir - largMarcador));
            yMarc = pos.y + margemBaixo;
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            xMarc = pos.x + margemEsq;
            yMarc = pos.y + margemBaixo +
                    (int) (porcentagemConcluida * (alt - margemBaixo - margemCima - altMarcador));
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            xMarc = pos.x + margemEsq;
            yMarc = pos.y + alt - margemCima - altMarcador -
                    (int) ((porcentagemConcluida) * (alt - margemBaixo - margemCima - altMarcador));
            break;
        default:
            break;
    }

    // xMarc += margemEsq;
    // yMarc += margemBaixo;
    if (marcador)
    {
        // printf("%d,%d  %d
        // %d\n",xMarc,yMarc,altMarcador-(margemBaixo+margemCima),largMarcador-(margemEsq+margemDir));
        marcador->Move(xMarc, yMarc);
        marcador->SetDimensoes(
                altMarcador,
                largMarcador); //-(margemBaixo+margemCima),largMarcador-(margemEsq+margemDir));
    }
}

PIGEstadoEvento CPIGSlideBar::TrataClickTrilha(int px, int py)
{
    double perc = 0;
    int minx = (int) pos.x + margemEsq + (largMarcador / 2);
    int maxx = (int) pos.x + larg - margemDir - (largMarcador / 2);
    int miny = (int) pos.y + margemBaixo + (altMarcador / 2);
    int maxy = (int) pos.y + alt - margemCima - (altMarcador / 2);
    px = PIGLimitaValor(px, minx, maxx);
    py = PIGLimitaValor(py, miny, maxy);

    switch (orientacaoCrescimento)
    {
        case PIG_GAUGE_ESQ_DIR:
            perc = 1.0 * (px - minx) / (maxx - minx);
            break;
        case PIG_GAUGE_DIR_ESQ:
            perc = 1.0 - 1.0 * (px - minx) / (maxx - minx);
            break;
        case PIG_GAUGE_BAIXO_CIMA:
            perc = 1.0 * (py - miny) / (maxy - miny);
            break;
        case PIG_GAUGE_CIMA_BAIXO:
            perc = 1.0 - 1.0 * (py - miny) / (maxy - miny);
            break;
        default:
            break;
    }
    // printf("(%d %d %d) (%d %d %d ) vou definir perc %f\n",minx,px,maxx,miny,py,maxy,perc);
    SetPorcentagemConcluida(perc);

    return PIG_COMPONENTE_TRATADO;
}

PIGEstadoEvento CPIGSlideBar::TrataRodinha(const PIGEvento &evento)
{
    if (evento.mouse.relY > 0)
    {
        AvancaMarcador(deltaRodinha);
        return PIG_COMPONENTE_TRATADO;
    }
    if (evento.mouse.relY < 0)
    {
        AvancaMarcador(-deltaRodinha);
        return PIG_COMPONENTE_TRATADO;
    }
    return PIG_COMPONENTE_NAOTRATADO;
}

PIGEstadoEvento CPIGSlideBar::TrataClickMarcador(SDL_Point p)
{
    SDL_Rect r = {xMarc, yMarc, largMarcador, altMarcador};
    if (SDL_PointInRect(&p, &r))
    {
        if (orientacaoCrescimento == PIG_GAUGE_DIR_ESQ ||
            orientacaoCrescimento == PIG_GAUGE_ESQ_DIR)
        {
            p.y = yMarc;
        }
        else
        {
            p.x = xMarc;
        }
        return TrataClickTrilha(p.x, p.y);
    }
    return PIG_COMPONENTE_NAOTRATADO;
}

CPIGSlideBar::CPIGSlideBar(
        int idComponente, int altTrilha, int largTrilha, const string &imgTrilha,
        int alturaMarcador, int larguraMarcador, const string &imgMarcador, int retiraFundoTrilha,
        int retiraFundoMarcador, int janela)
    : CPIGGauge(idComponente, altTrilha, largTrilha, imgTrilha, retiraFundoTrilha, janela)
{
    deltaTeclado = deltaRodinha = 10;
    altMarcador = alturaMarcador;
    largMarcador = larguraMarcador;
    tipo = PIG_SLIDEBAR;
    marcador = new CPIGSprite(-1, imgMarcador, retiraFundoMarcador, NULL, janela);
    CPIGSlideBar::AtualizaMarcador();
}

CPIGSlideBar::CPIGSlideBar(
        int idComponente, int altTrilha, int largTrilha, int alturaMarcador, int larguraMarcador,
        int janela)
    : CPIGGauge(idComponente, altTrilha, largTrilha, janela)
{
    deltaTeclado = deltaRodinha = 10;
    altMarcador = alturaMarcador;
    largMarcador = larguraMarcador;
    tipo = PIG_SLIDEBAR;
    CPIGSlideBar::AtualizaMarcador();
    IniciaCoresBasicas();
}

CPIGSlideBar::CPIGSlideBar(int idComponente, const CPIGAtributos &atrib)
    : CPIGSlideBar(LeParametros(idComponente, atrib))
{}

PIGEstadoEvento CPIGSlideBar::TrataEventoMouse(PIGEvento evento)
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
        if (evento.mouse.acao == PIG_MOUSE_RODINHA)
        {
            return TrataRodinha(evento);
        }

        if ((evento.mouse.acao == PIG_MOUSE_PRESSIONADO &&
             evento.mouse.botao == PIG_MOUSE_ESQUERDO) ||
            (temFoco && CPIGMouse::GetEstadoBotao(PIG_MOUSE_ESQUERDO) == PIG_MOUSE_PRESSIONADO))
        {
            return TrataClickTrilha(p.x, p.y);
        }

        return PIG_COMPONENTE_MOUSEOVER;
    }

    if ((evento.mouse.acao == PIG_MOUSE_PRESSIONADO && evento.mouse.botao == PIG_MOUSE_ESQUERDO) ||
        (temFoco && CPIGMouse::GetEstadoBotao(PIG_MOUSE_ESQUERDO) == PIG_MOUSE_PRESSIONADO))
        return TrataClickMarcador(p);
    return PIG_COMPONENTE_NAOTRATADO;
}

PIGEstadoEvento CPIGSlideBar::TrataEventoTeclado(PIGEvento evento)
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

    if (evento.teclado.acao == PIG_TECLA_PRESSIONADA)
    {
        switch (orientacaoCrescimento)
        {
            case PIG_GAUGE_ESQ_DIR:
                if (evento.teclado.tecla == PIG_TECLA_DIREITA)
                {
                    AvancaMarcador(deltaTeclado);
                }
                if (evento.teclado.tecla == PIG_TECLA_ESQUERDA)
                {
                    AvancaMarcador(-deltaTeclado);
                }
                break;
            case PIG_GAUGE_DIR_ESQ:
                if (evento.teclado.tecla == PIG_TECLA_DIREITA)
                {
                    AvancaMarcador(-deltaTeclado);
                }
                if (evento.teclado.tecla == PIG_TECLA_ESQUERDA)
                {
                    AvancaMarcador(deltaTeclado);
                }
                break;
            case PIG_GAUGE_BAIXO_CIMA:
                if (evento.teclado.tecla == PIG_TECLA_CIMA)
                {
                    AvancaMarcador(deltaTeclado);
                }
                if (evento.teclado.tecla == PIG_TECLA_BAIXO)
                {
                    AvancaMarcador(-deltaTeclado);
                }
                break;
            case PIG_GAUGE_CIMA_BAIXO:
                if (evento.teclado.tecla == PIG_TECLA_CIMA)
                {
                    AvancaMarcador(-deltaTeclado);
                }
                if (evento.teclado.tecla == PIG_TECLA_BAIXO)
                {
                    AvancaMarcador(deltaTeclado);
                }
                break;
            default:
                break;
        }
        return PIG_COMPONENTE_TRATADO;
    }
    return PIG_COMPONENTE_NAOTRATADO;
}

void CPIGSlideBar::SetDeltas(int dPadrao, int dRodinha, int dTeclado)
{
    delta = dPadrao;
    deltaRodinha = dRodinha;
    deltaTeclado = dTeclado;
}

int CPIGSlideBar::SetOrientacao(PIGGaugeCrescimento orientacao)
{
    if (orientacao == PIG_GAUGE_HORARIO || orientacao == PIG_GAUGE_ANTIHORARIO)
    {
        return 0;
    }

    orientacaoCrescimento = orientacao;
    marcadorAtualizado = false;

    return 1;
}

void CPIGSlideBar::Desloca(double dx, double dy)
{
    CPIGGauge::Desloca(dx, dy);
    xMarc += dx;
    yMarc += dy;
}

void CPIGSlideBar::Move(double nx, double ny)
{
    Desloca(nx - pos.x, ny - pos.y);
}

int CPIGSlideBar::Desenha()
{

    if (!visivel)
    {
        return 0;
    }

    if (!marcadorAtualizado)
    {
        AtualizaMarcador();
    }

    // CPIGGerenciadorJanelas::GetJanela(idJanela)->BloqueiaArea(pos.x,pos.y,alt,larg);

    if (imagemPropria)
    {
        CPIGComponente::Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                (int) pos.x, (int) pos.y, alt, larg, coresBasicas[0]);
    }


    if (marcador)
    {
        marcador->Desenha();
    }
    else
    {
        CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
                xMarc, yMarc, altMarcador, largMarcador, coresBasicas[1]);
    }
    // CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(xMarc,yMarc,altMarcador,largMarcador,VERDE);

    // CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado((int)pos.x,(int)pos.y,alt,larg,AMARELO);
    // CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado((int)pos.x+margemEsq,(int)pos.y+margemBaixo,alt-(margemBaixo+margemCima),larg-(margemEsq+margemDir),VERMELHO);

    // CPIGGerenciadorJanelas::GetJanela(idJanela)->DesbloqueiaArea();

    return CPIGComponente::Desenha();
}
