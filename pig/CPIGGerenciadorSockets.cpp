#include <pig/CPIGGerenciadorSockets.h>

CPIGRepositorio<PIGClienteTCP> *CPIGGerenciadorSockets::clientes{};
CPIGRepositorio<PIGServidorTCP> *CPIGGerenciadorSockets::servidores{};
CPIGRepositorio<PIGSocketUDP> *CPIGGerenciadorSockets::socketsUDP{};

void CPIGGerenciadorSockets::Inicia()
{
    SDLNet_Init();
    clientes = new CPIGRepositorio<PIGClienteTCP>(PIG_MAX_SOCKETS_CLIENTES_TCP, "clientesTCP");
    servidores =
            new CPIGRepositorio<PIGServidorTCP>(PIG_MAX_SOCKETS_SERVIDORES_TCP, "servidoresTCP");
    socketsUDP = new CPIGRepositorio<PIGSocketUDP>(PIG_MAX_SOCKETS_UDP, "socketsUDP");
}

void CPIGGerenciadorSockets::Encerra()
{
    delete clientes;
    delete servidores;
    delete socketsUDP;
    SDLNet_Quit();
}

int CPIGGerenciadorSockets::CriaCliente(const string &hostname, int porta, int maxBytesPacote)
{
    int resp = clientes->ProxID();
    PIGClienteTCP cliente = new CPIGClienteTCP(resp, hostname, porta, maxBytesPacote);
    if (cliente->GetAtivo())
    {
        clientes->Insere(cliente);
        return resp;
    }

    printf("ERRP: detectei o erro clienteTCP id %d\n", resp);
    delete cliente;
    return -1;
}

int CPIGGerenciadorSockets::InsereCliente(PIGClienteTCP socket)
{
    return clientes->Insere(socket);
}

int CPIGGerenciadorSockets::CriaServidor(int maxClientes, int porta, int maxBytesPacote)
{
    int resp = servidores->ProxID();
    PIGServidorTCP servidor = new CPIGServidorTCP(resp, maxClientes, porta, maxBytesPacote);
    if (servidor->GetAtivo())
    {
        servidores->Insere(servidor);
        return resp;
    }

    printf("ERRO:detectei o erro servidorTCP id %d\n", resp);
    delete servidor;
    return -1;
}

int CPIGGerenciadorSockets::InsereServidor(PIGServidorTCP socket)
{
    return servidores->Insere(socket);
}

int CPIGGerenciadorSockets::CriaSocketUDP(int porta)
{
    int resp = servidores->ProxID();
    PIGSocketUDP socketUDP = new CPIGSocketUDP(resp, porta);
    if (socketUDP->GetAtivo())
    {
        socketsUDP->Insere(socketUDP);
        return resp;
    }

    printf("ERRO: detectei o erro socketUDP id %d\n", resp);
    delete socketUDP;
    return -1;
}

int CPIGGerenciadorSockets::InsereSocketUDP(PIGSocketUDP socket)
{
    return socketsUDP->Insere(socket);
}

void CPIGGerenciadorSockets::DestroiCliente(int idSocket)
{
    clientes->Remove(idSocket);
}

void CPIGGerenciadorSockets::DestroiServidor(int idSocket)
{
    servidores->Remove(idSocket);
}

void CPIGGerenciadorSockets::DestroiSocketUDP(int idSocket)
{
    socketsUDP->Remove(idSocket);
}

PIGClienteTCP CPIGGerenciadorSockets::GetCliente(int idSocket)
{
    return clientes->GetElemento(idSocket);
}

PIGServidorTCP CPIGGerenciadorSockets::GetServidor(int idSocket)
{
    return servidores->GetElemento(idSocket);
}

PIGSocketUDP CPIGGerenciadorSockets::GetSocketUDP(int idSocket)
{
    return socketsUDP->GetElemento(idSocket);
}
