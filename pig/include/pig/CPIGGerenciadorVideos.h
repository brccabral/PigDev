#ifndef _CPIGGERENCIADORVIDEOS_
#define _CPIGGERENCIADORVIDEOS_

#include <string>

using namespace std;

#include <pig/CPIGVideo.h>
#include <pig/CPIGRepositorio.h>

class CPIGGerenciadorVideos
{

private:

    static CPIGRepositorio<PIGVideo> *videos;

public:

    static void Inicia();
    static void Encerra();
    static int CriaVideo(const string &nomeArquivo, int idJanela = 0);
    static int InsereVideo(PIGVideo video);
    static void DestroiVideo(int idVideo);
    static PIGVideo GetVideo(int idVideo);
};

#endif // _CPIGGERENCIADORVIDEOS_
