#ifndef _CPIGGERENCIADORSOCKETS_
#define _CPIGGERENCIADORSOCKETS_

#include <string>

using namespace std;

#include <pig/CPIGClienteTCP.h>
#include <pig/CPIGServidorTCP.h>
#include <pig/CPIGSocketUDP.h>
#include <pig/CPIGRepositorio.h>

class CPIGGerenciadorSockets
{

private:

    static CPIGRepositorio<PIGClienteTCP> *clientes;
    static CPIGRepositorio<PIGServidorTCP> *servidores;
    static CPIGRepositorio<PIGSocketUDP> *socketsUDP;

public:

    static void Inicia();
    static void Encerra();
    static int
    CriaCliente(const string &hostname, int porta, int maxBytesPacote = PIG_MAX_MENSAGEM_REDE_TCP);
    static int InsereCliente(PIGClienteTCP socket);
    static int
    CriaServidor(int maxClientes, int porta, int maxBytesPacote = PIG_MAX_MENSAGEM_REDE_TCP);
    static int InsereServidor(PIGServidorTCP socket);
    static int CriaSocketUDP(int porta);
    static int InsereSocketUDP(PIGSocketUDP socket);
    static void DestroiCliente(int idSocket);
    static void DestroiServidor(int idSocket);
    static void DestroiSocketUDP(int idSocket);
    static PIGClienteTCP GetCliente(int idSocket);
    static PIGServidorTCP GetServidor(int idSocket);
    static PIGSocketUDP GetSocketUDP(int idSocket);
};

#endif // _CPIGGERENCIADORSOCKETS_
