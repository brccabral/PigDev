#ifndef _CPIGSOCKETUDP_
#define _CPIGSOCKETUDP_

#include <ctime>
#include <string>

using namespace std;

#include <SDL_net.h>

#include <pig/PIGTipos.h>
#include <pig/PIGFuncoesBasicas.h>

class CPIGSocketUDP
{

private:

    int portaLocal;
    char hostLocal[PIG_TAMANHO_MAXIMO_HOSTNAME]{};
    int id;
    int ativo;
    long tempoPacoteRecebido;
    long qtdPacotesRecebidos;
    long qtdBytesRecebidos;
    long tempoPacoteEnviado;
    long qtdPacotesEnviados;
    long qtdBytesEnviados;
    UDPsocket socket;
    UDPpacket *pacoteEnvio, *pacoteRecebimento;
    SDL_Thread *thread;

    void CriaEventoMensagem(PIGTipoMensagemRede tipoMensagem, const UDPpacket *pacoteRecebido);

public:

    CPIGSocketUDP(int idSocket, int porta);
    virtual ~CPIGSocketUDP();
    bool EnviaDados(const void *buffer, int tamanhoBuffer, const string &host, int porta);
    [[nodiscard]] int GetId() const;
    [[nodiscard]] bool GetAtivo() const;
    [[nodiscard]] int GetPortaLocal() const;
    string GetHostLocal();
    [[nodiscard]] long GetBytesEnviados() const;
    [[nodiscard]] long GetBytesRecebidos() const;
    [[nodiscard]] long GetPacotesEnviados() const;
    [[nodiscard]] long GetPacotesRecebidos() const;
    [[nodiscard]] long GetTempoUltimoRecebido() const;
    [[nodiscard]] long GetTempoUltimoEnviado() const;
    static int thread_code(void *data);
};

typedef CPIGSocketUDP *PIGSocketUDP;
#endif // _CPIGSOCKETUDP_
