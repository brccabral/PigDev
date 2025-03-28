#ifndef _PIGFuncoesBasicas_
#define _PIGFuncoesBasicas_

#include <string>
#include <thread>
#include <vector>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>

vector<string> PIGSeparaPalavras(const string &texto, const string &delim);
bool PIGSomenteNumeros(const string &frase);
bool PIGCoresIguais(PIGCor cor1, PIGCor cor2);
bool operator==(PIGCor cor1, PIGCor cor2);
PIGCor operator*(PIGCor cor, double fator);
PIGCor operator+(PIGCor cor1, PIGCor cor2);
PIGCor PIGCriaCorHexa(const string &stringHexa);
PIGCor PIGCriaCorString(const string &str);
uint16_t PIGTroca2Bytes(uint16_t valor);
PIGCor PIGMixCor(PIGCor iniCor, PIGCor fimCor, double porc);
string PIGGetDiretorioAtual();
int PIGLimitaValor(int valor, int minimo, int maximo);
double PIGLimitaValor(double valor, double minimo, double maximo);
vector<string> PIGListaArquivosDiretorio(const string &path);
void PIGCalculaBoundingBox(
        const int px[], const int py[], int lados, int *altura, int *largura, int *centroX,
        int *centroY);
int PIGArredondaProximo(float valor);
double PIGProjecaoY(double coefAngular, PIGPonto2D p);
double PIGProjecaoX(double coefAngular, PIGPonto2D p);
double PIGMinVetor(const double vetor[], int tamVetor);
double PIGMaxVetor(const double vetor[], int tamVetor);
double PIGDistancia(PIGPonto2D a, PIGPonto2D b);
bool PIGValorEntre(int x, int a, int b);

extern thread::id PIG_MAIN_THREAD_ID;

#endif // _PIGFuncoesBasicas_
