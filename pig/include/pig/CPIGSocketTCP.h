#ifndef _CPIGSOCKETTCP_
#define _CPIGSOCKETTCP_

#include <string>

using namespace std;

#include <SDL_net.h>

class CPIGSocketTCP
{

protected:

    int id{};
    TCPsocket socket;
    SDLNet_SocketSet socketSet{};
    string hostRemoto;
    string hostLocal;
    int portaRemota;
    int tamPacote{};
    long tempoPacoteRecebido{};
    long qtdPacotesRecebidos{};
    long qtdBytesRecebidos{};
    long tempoPacoteEnviado{};
    long qtdPacotesEnviados{};
    long qtdBytesEnviados{};
    bool ativo;
    bool liberaSocketSet; // usado para saber se o socketSet deve ser liberado

    virtual void RegistraBytesRecebidos(int qtdBytes);
    virtual void RegistraBytesEnviados(int qtdBytes);
    virtual void InicializaValoresBasicos(int valorId, int maxBytesPacote);

public:

    CPIGSocketTCP(int id, const string &host, int porta, int maxBytesPacote);
    CPIGSocketTCP(
            int id, TCPsocket serverSocket, int maxBytesPacote, SDLNet_SocketSet socketSetClientes);
    virtual ~CPIGSocketTCP();
    [[nodiscard]] int GetId() const;
    [[nodiscard]] bool GetAtivo() const;
    string GetHostRemoto();
    string GetHostLocal();
    [[nodiscard]] int GetPortaRemota() const;
    [[nodiscard]] int GetTamanhoPacote() const;
    int MudaSet(SDLNet_SocketSet socketSetNovo);
    [[nodiscard]] long GetBytesEnviados() const;
    [[nodiscard]] long GetBytesRecebidos() const;
    [[nodiscard]] long GetPacotesEnviados() const;
    [[nodiscard]] long GetPacotesRecebidos() const;
    [[nodiscard]] long GetTempoUltimoRecebido() const;
    [[nodiscard]] long GetTempoUltimoEnviado() const;
    int RecebeDados(void *buffer);
    int EnviaDados(const void *buffer, int tamanhoBuffer);
};

typedef CPIGSocketTCP *PIGSocketTCP;
#endif // _CPIGSOCKETTCP_
