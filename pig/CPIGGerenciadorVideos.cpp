#include <pig/CPIGGerenciadorVideos.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <libavdevice/avdevice.h>

#ifdef __cplusplus
}
#endif

CPIGRepositorio<PIGVideo> *CPIGGerenciadorVideos::videos{};

void CPIGGerenciadorVideos::Inicia()
{
    avdevice_register_all();
    avformat_network_init();

    videos = new CPIGRepositorio<PIGVideo>(PIG_MAX_VIDEOS, "videos");
}

void CPIGGerenciadorVideos::Encerra()
{
    delete videos;
    avformat_network_deinit();
}

int CPIGGerenciadorVideos::CriaVideo(const string &nomeArquivo, int idJanela)
{
    return videos->Insere(new CPIGVideo(nomeArquivo, idJanela));
}

int CPIGGerenciadorVideos::InsereVideo(PIGVideo video)
{
    return videos->Insere(video);
}

void CPIGGerenciadorVideos::DestroiVideo(int idVideo)
{
    videos->Remove(idVideo);
}

PIGVideo CPIGGerenciadorVideos::GetVideo(int idVideo)
{
    return videos->GetElemento(idVideo);
}
