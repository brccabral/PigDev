#include <pig/CPIGGerenciadorAudios.h>

CPIGRepositorio<PIGAudio> *CPIGGerenciadorAudios::audios{};
int CPIGGerenciadorAudios::audioIds[PIG_QTD_CANAIS_PADRAO]{};
Mix_Music *CPIGGerenciadorAudios::background{};
int CPIGGerenciadorAudios::volumeBackground{};
PIGStatusAudio CPIGGerenciadorAudios::statusBackground{};

void CPIGGerenciadorAudios::TrataParadaAudio(int canal)
{
    SDL_Event eventoAudio;
    eventoAudio.type = SDL_USEREVENT;
    eventoAudio.user.code = PIG_EVENTO_AUDIO;
    eventoAudio.user.data1 = (int *) malloc(sizeof(int));
    *((int *) eventoAudio.user.data1) = audioIds[canal];
    SDL_PushEvent(&eventoAudio);
    audioIds[canal] = -1;
}

void CPIGGerenciadorAudios::TrataParadaBackground()
{
    SDL_Event eventoAudio;
    eventoAudio.type = SDL_USEREVENT;
    eventoAudio.user.code = PIG_EVENTO_AUDIO;
    eventoAudio.user.data1 = (int *) malloc(sizeof(int) * 1);
    *((int *) eventoAudio.user.data1) = PIG_AUDIO_BACKGROUND;
    SDL_PushEvent(&eventoAudio);
}

void CPIGGerenciadorAudios::Inicia()
{
    Mix_OpenAudio(PIG_FREQ_AUDIO_PADRAO, MIX_DEFAULT_FORMAT, 2, PIG_TAMANHO_CHUNK);

    Mix_AllocateChannels(PIG_QTD_CANAIS_PADRAO);

    audios = new CPIGRepositorio<PIGAudio>(PIG_MAX_AUDIOS, "audios");
    for (int &audioId: audioIds)
    {
        audioId = -1;
    }

    Mix_ChannelFinished(TrataParadaAudio);
    background = NULL;
    volumeBackground = PIG_VOLUME_PADRAO;
    statusBackground = PIG_AUDIO_PARADO;
    Mix_HookMusicFinished(TrataParadaBackground);
}

void CPIGGerenciadorAudios::Encerra()
{
    StopTudo();

    delete audios;
    if (background)
    {
        Mix_FreeMusic(background);
    }
    Mix_CloseAudio();
}

PIGAudio CPIGGerenciadorAudios::GetAudio(int idAudio)
{
    return audios->GetElemento(idAudio);
}

void CPIGGerenciadorAudios::CarregaBackground(const string &nomeArquivo)
{
    if (background)
    {
        Mix_FreeMusic(background);
    }
    background = Mix_LoadMUS(nomeArquivo.c_str());
}

void CPIGGerenciadorAudios::PlayBackground(int nVezes)
{
    if (background)
    {
        Mix_PlayMusic(background, nVezes);
        statusBackground = PIG_AUDIO_TOCANDO;
    }
}

void CPIGGerenciadorAudios::StopBackground()
{
    if (background)
    {
        Mix_HaltMusic();
        statusBackground = PIG_AUDIO_PARADO;
    }
}

void CPIGGerenciadorAudios::PauseBackground()
{
    if (background)
    {
        Mix_PauseMusic();
        statusBackground = PIG_AUDIO_PAUSADO;
    }
}

void CPIGGerenciadorAudios::ResumeBackground()
{
    if (background)
    {
        Mix_ResumeMusic();
        statusBackground = PIG_AUDIO_TOCANDO;
    }
}

PIGStatusAudio CPIGGerenciadorAudios::GetStatusBackground()
{
    return statusBackground;
}

void CPIGGerenciadorAudios::SetVolumeBackground(int valor)
{
    volumeBackground = valor;
    Mix_VolumeMusic(volumeBackground);
}

int CPIGGerenciadorAudios::GetVolumeBackground()
{
    return volumeBackground;
}

int CPIGGerenciadorAudios::CriaAudio(const string &nomeArquivo, int nLoops, int tempoExecucao)
{
    return audios->Insere(new CPIGAudio(nomeArquivo, nLoops, tempoExecucao));
}

int CPIGGerenciadorAudios::InsereAudio(PIGAudio audio)
{
    return audios->Insere(audio);
}

void CPIGGerenciadorAudios::DestroiAudio(int idAudio)
{
    audios->Remove(idAudio);
}

void CPIGGerenciadorAudios::SetVolumeTudo(int volume)
{
    Mix_Volume(-1, volume);

    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio)
    {
        audio->SetVolume(volume);
        audio = audios->GetProximoElemento();
    }
}

void CPIGGerenciadorAudios::Play(int idAudio)
{
    PIGAudio audio = GetAudio(idAudio);
    int c = audio->Play();
    audioIds[c] = idAudio;
}

void CPIGGerenciadorAudios::StopTudo()
{
    Mix_HaltChannel(-1);

    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio)
    {
        audio->Stop();
        audio = audios->GetProximoElemento();
    }
}

void CPIGGerenciadorAudios::PauseTudo()
{
    Mix_Pause(-1);

    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio)
    {
        audio->Pause();
        audio = audios->GetProximoElemento();
    }
}

void CPIGGerenciadorAudios::ResumeTudo()
{
    Mix_Resume(-1);

    PIGAudio audio = audios->GetPrimeiroElemento();
    while (audio)
    {
        audio->Resume();
        audio = audios->GetProximoElemento();
    }
}
