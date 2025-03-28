#include <pig/CPIGJogo.h>
#include <pig/CPIGGerenciadorJanelas.h>
#include <pig/CPIGGerenciadorLabels.h>
#include <pig/CPIGGerenciadorSprites.h>
#include <pig/CPIGGerenciadorGDP.h>
#include <pig/CPIGGerenciadorFontes.h>
#include <pig/CPIGAssetLoader.h>
#include <pig/CPIGMouse.h>
#include <pig/CPIGTeclado.h>

#ifdef PIGCOMAUDIO
#include <pig/CPIGGerenciadorAudios.h>
#endif
#ifdef PIGCOMCONTROLE
#include <pig/CPIGGerenciadorControles.h>
#endif
#ifdef PIGCOMREDE
#include <pig/CPIGGerenciadorSockets.h>
#endif
#ifdef PIGCOMVIDEO
#include <pig/CPIGGerenciadorVideos.h>
#endif
#ifdef PIGCOMFORM
#include <pig/CPIGGerenciadorForms.h>
#endif
#ifdef PIGCOMTELA
#include <pig/CPIGGerenciadorTelas.h>
#endif

CPIGJogo::CPIGJogo(const string &nome, const int cursor, const int altura, const int largura)
{
    rodando = true;
    teclado = SDL_GetKeyboardState(NULL);
    estado = 0;

    offRenderer = NULL;

    diretorioAtual = PIGGetDiretorioAtual();
    // printf("path: %s\n",diretorioAtual);//exibir a pasta original da PIG

    // SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Nao foi possivel iniciar o SDL! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        CPIGGerenciadorJanelas::Inicia(nome, altura, largura);
        CPIGAssetLoader::Inicia();
        CPIGMouse::Inicia(cursor);
        CPIGGerenciadorSprites::Inicia();
        CPIGGerenciadorFontes::Inicia();
        CPIGGerenciadorLabels::Inicia();
        CPIGGerenciadorTimers::Inicia();
        CPIGGerenciadorGDP::Inicia();
#ifdef PIGCOMAUDIO
        CPIGGerenciadorAudios::Inicia();
#endif
#ifdef PIGCOMCONTROLE
        CPIGGerenciadorControles::Inicia();
#endif
#ifdef PIGCOMREDE
        CPIGGerenciadorSockets::Inicia();
#endif
#ifdef PIGCOMVIDEO
        CPIGGerenciadorVideos::Inicia();
#endif
#ifdef PIGCOMFORM
        CPIGGerenciadorForms::Inicia();
#endif
#ifdef PIGCOMTELA
        CPIGGerenciadorTelas::Inicia();
#endif
    }
}

CPIGJogo::~CPIGJogo()
{
    delete offRenderer;

#ifdef PIGCOMCONTROLE
    CPIGGerenciadorControles::Encerra();
#endif
#ifdef PIGCOMAUDIO
    CPIGGerenciadorAudios::Encerra();
#endif
#ifdef PIGCOMVIDEO
    CPIGGerenciadorVideos::Encerra();
#endif
#ifdef PIGCOMREDE
    CPIGGerenciadorSockets::Encerra();
#endif
#ifdef PIGCOMFORM
    CPIGGerenciadorForms::Encerra();
#endif
#ifdef PIGCOMTELA
    CPIGGerenciadorTelas::Encerra();
#endif

    CPIGGerenciadorGDP::Encerra();
    CPIGGerenciadorTimers::Encerra();
    CPIGGerenciadorLabels::Encerra();
    CPIGGerenciadorFontes::Encerra();
    CPIGGerenciadorSprites::Encerra();
    CPIGMouse::Encerra();
    CPIGAssetLoader::Encerra();
    CPIGGerenciadorJanelas::Encerra();
}

PIGEvento CPIGJogo::PegaEvento()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            rodando = false;
        }
        // if (event.type) printf("Tipo: %d\n",event.type);
        switch (event.type)
        {
            case SDL_QUIT:
                rodando = false;
                break;

            case SDL_USEREVENT:
                if (event.user.code == PIG_EVENTO_AUDIO)
                {
                    ultimoEvento.tipoEvento = PIG_EVENTO_AUDIO;
                    ultimoEvento.audio.audioId = *((int *) event.user.data1);
                }
                else if (event.user.code == PIG_EVENTO_REDE)
                {
                    ultimoEvento.tipoEvento = PIG_EVENTO_REDE;
                    ultimoEvento.rede = *((PIGInfoEventoRede *) event.user.data1);
                }
                free(event.user.data1);
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ultimoEvento.tipoEvento = PIG_EVENTO_MOUSE;
                // MOUSE_PRESSIONADO(SDL_MOUSEBUTTODOWN) ou
                // MOUSELIBERADO(SDL_MOUSEBUTTONUP);
                ultimoEvento.mouse.acao = (SDL_EventType) event.type;
                ultimoEvento.mouse.botao = event.button.button;
                ultimoEvento.mouse.numeroJanela = event.window.windowID - PIG_JANELA_INICIAL;
                ultimoEvento.mouse.cliques = event.button.clicks;
                // ultimoEvento.mouse.posX = event.button.x;
                SDL_GetMouseState(&ultimoEvento.mouse.posX, &ultimoEvento.mouse.posY);
                // ultimoEvento.mouse.posY =
                // CGerenciadorJanelas::GetAltura(ultimoEvento.mouse.numeroJanela) -
                // event.button.y-1;
                ultimoEvento.mouse.posY =
                        CPIGGerenciadorJanelas::GetJanela(ultimoEvento.mouse.numeroJanela)
                                ->GetAltura() -
                        ultimoEvento.mouse.posY - 1;
                // CGerenciadorJanelas::GetJanela(ultimoEvento.mouse.numeroJanela)->GetCamera()->ConverteCoordenadaWorldScreen(ultimoEvento.mouse.posX,ultimoEvento.mouse.posY,&ultimoEvento.mouse.worldX,&ultimoEvento.mouse.worldY);
                CPIGMouse::ProcessaEvento(ultimoEvento);
                break;

            case SDL_MOUSEMOTION:
                ultimoEvento.tipoEvento = PIG_EVENTO_MOUSE;
                ultimoEvento.mouse.acao = PIG_MOUSE_MOVIDO;
                ultimoEvento.mouse.numeroJanela = event.window.windowID - PIG_JANELA_INICIAL;
                SDL_GetMouseState(&ultimoEvento.mouse.posX, &ultimoEvento.mouse.posY);
                // ultimoEvento.mouse.posX = event.motion.x;
                ultimoEvento.mouse.posY =
                        CPIGGerenciadorJanelas::GetJanela(ultimoEvento.mouse.numeroJanela)
                                ->GetAltura() -
                        ultimoEvento.mouse.posY - 1;
                ultimoEvento.mouse.relX = event.motion.xrel;
                ultimoEvento.mouse.relY = -event.motion.yrel;
                // printf("%d\n",ultimoEvento.mouse.numeroJanela);
                // CGerenciadorJanelas::GetJanela(ultimoEvento.mouse.numeroJanela)->GetCamera()->ConverteCoordenadaScreenWorld(ultimoEvento.mouse.posX,ultimoEvento.mouse.posY,&ultimoEvento.mouse.worldX,&ultimoEvento.mouse.worldY);
                // int mx,my;
                // SDL_GetMouseState(&ultimoEvento.mouse.posX,&ultimoEvento.mouse.posY);
                // printf("y %d  my %d\n",event.motion.y,my);
                CPIGMouse::ProcessaEvento(ultimoEvento);
                // CMouse::Move(ultimoEvento.mouse.posX, ultimoEvento.mouse.posY);
                break;

            case SDL_MOUSEWHEEL:
                ultimoEvento.tipoEvento = PIG_EVENTO_MOUSE;
                ultimoEvento.mouse.acao = PIG_MOUSE_RODINHA;
                ultimoEvento.mouse.numeroJanela = event.window.windowID - PIG_JANELA_INICIAL;
                ultimoEvento.mouse.relX = event.wheel.x;
                ultimoEvento.mouse.relY = event.wheel.y;
                CPIGMouse::ProcessaEvento(ultimoEvento);
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                ultimoEvento.tipoEvento = PIG_EVENTO_TECLADO;
                // TECLA_PRESSIONADA(SDL_KEYDOWN) ou
                // TECLA_LIBERADA(SDL_KEYUP);
                ultimoEvento.teclado.acao = (SDL_EventType) event.type;
                ultimoEvento.teclado.tecla = event.key.keysym.scancode;
                ultimoEvento.teclado.repeticao = event.key.repeat;
                CPIGTeclado::ProcessaEvento(ultimoEvento);
                break;

            case SDL_TEXTEDITING:
                ultimoEvento.tipoEvento = PIG_EVENTO_TECLADO;
                ultimoEvento.teclado.acao = PIG_TECLA_EDICAO;
                ultimoEvento.teclado.inicio = event.edit.start;
                ultimoEvento.teclado.tamanhoSelecao = event.edit.length;
                strcpy(ultimoEvento.teclado.texto, event.edit.text);
                break;

            case SDL_TEXTINPUT:
                ultimoEvento.tipoEvento = PIG_EVENTO_TECLADO;
                ultimoEvento.teclado.acao = PIG_TECLA_INPUT;
                strcpy(ultimoEvento.teclado.texto, event.edit.text);
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == PIG_JANELA_FECHADA)
                {
                    CPIGGerenciadorJanelas::GetJanela(event.window.windowID - PIG_JANELA_INICIAL)
                            ->Fecha();
                }
                ultimoEvento.tipoEvento = PIG_EVENTO_JANELA;
                ultimoEvento.janela.acao = (SDL_WindowEventID) event.window.event;
                ultimoEvento.janela.numeroJanela = event.window.windowID - PIG_JANELA_INICIAL;
                ultimoEvento.janela.dado1 = event.window.data1;
                ultimoEvento.janela.dado2 = event.window.data2;
                break;

            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
                ultimoEvento.tipoEvento = PIG_EVENTO_CONTROLADOR;
                // CONTROLADOR_BOTAO_PRESSIONADO(SDL_CONTROLLERBUTTONDOWN) ou
                // CONTROLADOR_BOTAO_LIBERADO(SDL_CONTROLLERBUTTONUP);
                ultimoEvento.controlador.acao = (SDL_EventType) event.type;
                ultimoEvento.controlador.botao = event.cbutton.button;
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;

            case SDL_CONTROLLERAXISMOTION:
                // case SDL_JOYAXISMOTION:
                ultimoEvento.tipoEvento = PIG_EVENTO_CONTROLADOR;
                ultimoEvento.controlador.acao = PIG_CONTROLADOR_EIXO_MOVIDO;
                ultimoEvento.controlador.eixo = event.caxis.axis;
                ultimoEvento.controlador.valor = event.caxis.value;
                ultimoEvento.controlador.percentualEixo =
                        1.0F * ultimoEvento.controlador.valor / (1 << 15);
                ultimoEvento.controlador.idControlador = event.cdevice.which;
                SDL_PollEvent(&event);
                break;
            default:
                break;
                /*default:
                        if (event.type){
                            printf("Evento: %d\n",event.type);
                        }
                */
        }
    }
    else
    {
        ultimoEvento.tipoEvento = PIG_EVENTO_NULO;
    }
    return ultimoEvento;
}

/**
 * \c PoolEventos() processa todos os eventos na fila. Para processar um a um veja \c PegaEvento()
 */
void CPIGJogo::PoolEventos()
{
    CPIGTeclado::AtualizaEstadoAnterior();
    CPIGMouse::AtualizaEstadoAnterior();
    PIGEvento evento = PegaEvento();
    while (evento.tipoEvento != PIG_EVENTO_NULO)
    {
        evento = PegaEvento();
    }
}

PIGTeclado CPIGJogo::PegaTeclado()
{
    return teclado;
}

void CPIGJogo::IniciaInputTextoTela()
{
    SDL_StartTextInput();
}

void CPIGJogo::EncerraInputTextoTela()
{
    SDL_StopTextInput();
}

void CPIGJogo::IniciaDesenho(const int idJanela)
{
    CPIGGerenciadorJanelas::IniciaDesenho(idJanela);
}

void CPIGJogo::EncerraDesenho(const int idJanela)
{
    CPIGGerenciadorJanelas::EncerraDesenho(idJanela);
}

[[nodiscard]] bool CPIGJogo::GetRodando() const
{
    return rodando;
}

void CPIGJogo::SetEstado(const int valor)
{
    estado = valor;
}

float CPIGJogo::GetFPS(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetFPS();
}

void CPIGJogo::PreparaOffScreenRenderer(const int altura, const int largura)
{
    delete offRenderer;
    offRenderer = new CPIGOffscreenRenderer(altura, largura);
}

PIGOffscreenRenderer CPIGJogo::GetOffScreenRender()
{
    if (offRenderer == NULL)
    {
        throw CPIGErroPonteiro(
                "OffScreenRenderer(Necessario definir primeiro o tamanho do renderizador)");
    }
    return offRenderer;
}
