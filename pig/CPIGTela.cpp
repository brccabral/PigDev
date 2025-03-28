#include <pig/CPIGTela.h>
#include <pig/CPIGGerenciadorJanelas.h>

int CPIGTela::ExecutaFuncaoBackground(void *param)
{
    PIGStructThread *st = (PIGStructThread *) param;
    CPIGTela *tela = (CPIGTela *) st->tela;

    st->funcao(st->id, st->param);

    tela->estado = st->estadoFinal;

    if (tela->estado == PIG_TELA_CARREGADA)
    {
        SDL_SemPost(tela->sem);
    }

    free(param);
    // printf("terminei background\n");
    return 0;
}

CPIGTela::CPIGTela(
        const int idTela, const PIGComportamentoTela &comporta, const bool criarBackground,
        const bool carregarBackground, const string &imgLoading, const int idJanela)
{
    sem = SDL_CreateSemaphore(0);

    id = idTela;
    janela = idJanela;
    comportamento = comporta;
    tempoSaida = PIG_TEMPO_SAIDA_TELA_PADRAO;
    timerSaida = CPIGGerenciadorTimers::CriaTimer(true);
    criaBackground = criarBackground;
    carregaBackground = carregarBackground;
    spriteCarrega = -1;
    if (!imgLoading.empty())
    {
        spriteCarrega = CPIGGerenciadorSprites::CriaSprite(imgLoading, 1, NULL, janela);
        CPIGGerenciadorSprites::GetSprite(spriteCarrega)->SetDimensoes(PIG_ALT_TELA, PIG_LARG_TELA);
    }

    destruirAoDescarregar = false;
    if (comportamento.acaoCria != NULL)
    {
        if (criaBackground)
        {
            estado = PIG_TELA_CRIANDO;
            // ExecutaFuncaoBackground frees st
            PIGStructThread *st = (PIGStructThread *) malloc(sizeof(PIGStructThread));
            st->funcao = comportamento.acaoCria;
            st->id = id;
            st->param = comportamento.dados;
            st->tela = this;
            st->estadoFinal = PIG_TELA_CRIADA;
            SDL_CreateThread(ExecutaFuncaoBackground, "", st);
        }
        else
        {
            comportamento.acaoCria(id, comportamento.dados);
            estado = PIG_TELA_CRIADA;
        }
    }
    else
    {
        estado = PIG_TELA_CRIADA;
    }

    // printf("%d terminei o construtor\n",id);
}

CPIGTela::~CPIGTela()
{
    while (estado == PIG_TELA_CRIANDO || estado == PIG_TELA_CARREGANDO)
    {
        SDL_Delay(10);
    }
    CPIGGerenciadorTimers::DestroiTimer(timerSaida);
    if (comportamento.acaoDestroi != NULL)
    {
        comportamento.acaoDestroi(id, comportamento.dados);
    }
}

PIGEstadoTela CPIGTela::GetEstado()
{
    return estado;
}

bool CPIGTela::GetDestruirAoDescarregar() const
{
    return destruirAoDescarregar;
}

int CPIGTela::CarregaTela()
{
    if (estado == PIG_TELA_CARREGADA || estado == PIG_TELA_CARREGANDO || estado == PIG_TELA_CRIANDO)
    {
        // printf("Tela %d com erro carregamento: estado %d\n",id,estado);
        return -1;
    }
    mudarPara = -1;
    CPIGGerenciadorTimers::GetTimer(timerSaida)->Reinicia(true);
    if (comportamento.acaoCarrega != NULL)
    {
        if (carregaBackground)
        {
            estado = PIG_TELA_CARREGANDO;
            // ExecutaFuncaoBackground frees st
            PIGStructThread *st = (PIGStructThread *) malloc(sizeof(PIGStructThread));
            st->funcao = comportamento.acaoCarrega;
            st->id = id;
            st->param = comportamento.dados;
            st->tela = this;
            st->estadoFinal = PIG_TELA_CARREGADA;
            SDL_CreateThread(ExecutaFuncaoBackground, "", st);
        }
        else
        {
            comportamento.acaoCarrega(id, comportamento.dados);
            estado = PIG_TELA_CARREGADA;
            SDL_SemPost(sem);
        }
    }
    else
    {
        estado = PIG_TELA_CARREGADA;
    }
    return 1;
}

int CPIGTela::DescarregaTela()
{
    if (estado != PIG_TELA_SAINDO)
    {
        return -1;
    }
    estado = PIG_TELA_DESCARREGADA;
    if (comportamento.acaoDescarrega != NULL)
    {
        return comportamento.acaoDescarrega(id, comportamento.dados);
    }
    return 0;
}

int CPIGTela::TrataEvento(const PIGEvento &evento)
{
    if (estado != PIG_TELA_CARREGADA)
    {
        return -1; // PIG_COMPONENTE_NAOTRATADO;
    }
    if (comportamento.acaoTrataEvento != NULL)
    {
        return comportamento.acaoTrataEvento(id, evento, comportamento.dados);
    }
    return -1; // PIG_COMPONENTE_NAOTRATADO;
}

void CPIGTela::PreparaSaida(const int outraTela, const double tempo, const bool destroiDescarga)
{
    while (estado == PIG_TELA_CRIANDO || estado == PIG_TELA_CARREGANDO)
    {
        SDL_Delay(10);
    }
    estado = PIG_TELA_SAINDO;
    tempoSaida = tempo;
    CPIGGerenciadorTimers::GetTimer(timerSaida)->Despausa();
    mudarPara = outraTela;
    destruirAoDescarregar = destroiDescarga;
}

int CPIGTela::Atualiza()
{
    if (estado == PIG_TELA_CRIANDO || estado == PIG_TELA_CARREGANDO)
    {
        // printf("%d erro atualiza %d\n",id,estado);
        return -1;
    }

    // o método atualiza só é chamado para a telaAtual. Logo, se essa é a tela atual, precisa ser
    // carregada primeiro
    if (estado == PIG_TELA_CRIADA)
    {
        CarregaTela();
    }

    if (estado == PIG_TELA_CARREGADA && comportamento.acaoAtualiza != NULL)
    {
        comportamento.acaoAtualiza(id, comportamento.dados);
    }

    // se já passou o tempo de sair, sinaliza para qual tela o gerenciador tem que mudar
    if (CPIGGerenciadorTimers::GetTimer(timerSaida)->GetTempoDecorrido() > tempoSaida)
    {
        return mudarPara;
    }
    return -1;
}

int CPIGTela::Desenha()
{
    if (spriteCarrega != -1 && (estado == PIG_TELA_CRIANDO || estado == PIG_TELA_CARREGANDO))
    {
        CPIGGerenciadorJanelas::GetJanela(janela)->PreparaCameraFixa();
        CPIGGerenciadorSprites::GetSprite(spriteCarrega)->Desenha();
    }

    int resp = 0;
    if ((estado == PIG_TELA_CARREGADA || estado == PIG_TELA_SAINDO) &&
        comportamento.acaoDesenha != NULL)
    {
        SDL_SemWait(sem);
        resp = comportamento.acaoDesenha(id, comportamento.dados);
        SDL_SemPost(sem);
    }
    return resp;
}

void CPIGTela::SetComportamento(const PIGComportamentoTela &comporta)
{
    comportamento = comporta;
}
