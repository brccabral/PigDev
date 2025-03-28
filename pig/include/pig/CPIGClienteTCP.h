#ifndef _CPIGClienteTCP_
#define _CPIGClienteTCP_

#include <string>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGSocketTCP.h>

class CPIGClienteTCP : public CPIGSocketTCP
{

private:

    SDL_Thread *thread;

    void CriaEventoMensagem(PIGTipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados);

public:

    CPIGClienteTCP(int idSocket, const string &host, int porta, int maxBytesPacote);
    ~CPIGClienteTCP() override;
    static int thread_code(void *data);
};

typedef CPIGClienteTCP *PIGClienteTCP;
#endif // _CPIGClienteTCP_
