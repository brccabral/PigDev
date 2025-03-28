#ifndef _CPIGSERVIDORTCP_
#define _CPIGSERVIDORTCP_

#include <unordered_map>
#include <vector>

using namespace std;

#include <SDL_net.h>

#include <pig/PIGTipos.h>
#include <pig/CPIGSocketTCP.h>

class CPIGServidorTCP : public CPIGSocketTCP
{

private:

    SDLNet_SocketSet clienteSet;
    size_t maxConexoes;
    int portaLocal;
    SDL_Thread *threadAccept, *threadReceive;

    vector<size_t> posLivres;
    unordered_map<int, PIGSocketTCP> clientesTCP;

    void CriaEventoMensagem(
            PIGTipoMensagemRede tipoMensagem, const void *buffer, int tamanhoDados, int indiceSlot);
    void RegistraBytesRecebidos(int qtdBytes) override;
    void RegistraBytesEnviados(int qtdBytes) override;
    void InicializaValoresBasicos(int valorId, int maxBytesPacote) override;
    PIGSocketTCP GetCliente(int indice);
    int AbreConexao();
    void FechaConexao(int indice);

public:

    CPIGServidorTCP(int idSocket, int maximoConexoes, int porta, int maxBytesPacote);
    ~CPIGServidorTCP() override;
    int GetPortaLocal() const;
    int GetMaximoConexoes() const;
    int GetQuantidadeConexoes();
    int EnviaDados(const void *buffer, int tamanhoBuffer, int indiceSlot);
    static int accept_code(void *data);
    static int receive_code(void *data);
};

typedef CPIGServidorTCP *PIGServidorTCP;
#endif // _CPIGSERVIDORTCP_
