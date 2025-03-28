#include <sstream>

using namespace std;

#include <pig/PIG.h>
#include <pig/CPIGMouse.h>
#include <pig/CPIGAreaDeTexto.h>
#include <pig/CPIGGerenciadorControles.h>
#include <pig/CPIGGerenciadorLabels.h>
#include <pig/CPIGGerenciadorGDP.h>
#ifdef PIGCOMAUDIO
#include <pig/CPIGGerenciadorAudios.h>
#endif
#ifdef PIGCOMTELA
#include <pig/CPIGGerenciadorTelas.h>
#endif
#include <pig/CPIGBotaoClick.h>
#include <pig/CPIGBotaoOnOff.h>
#include <pig/CPIGCampoTextoESenha.h>
#include <pig/CPIGListBox.h>
#include <pig/CPIGDropDown.h>
#include <pig/CPIGRadioBox.h>
#include <pig/CPIGCheckBox.h>
#include <pig/CPIGGaugeCircular.h>
#include <pig/CPIGGaugeBar.h>
#include <pig/CPIGTeclado.h>

PIGJogo jogo = NULL;

void CriaJogo(const char *nomeJanela, const int cursorProprio, const int altura, const int largura)
{
    if (jogo == NULL)
    {
        jogo = new CPIGJogo(nomeJanela, cursorProprio, altura, largura);
    }
}

void SetValorIntJogo(const int indice, const int valor)
{
    jogo->SetValorInt(indice, valor);
}

void SetValorFloatJogo(const int indice, const float valor)
{
    jogo->SetValorFloat(indice, valor);
}

void SetValorStringJogo(const int indice, const char *valor)
{
    jogo->SetValorString(indice, valor);
}

void SetValorIntJogo(const char *indice, const int valor)
{
    jogo->SetValorInt(indice, valor);
}

void SetValorFloatJogo(const char *indice, const float valor)
{
    jogo->SetValorFloat(indice, valor);
}

void SetValorStringJogo(const char *indice, const char *valor)
{
    jogo->SetValorString(indice, valor);
}

int GetValorIntJogo(const int indice, int &valor)
{
    return jogo->GetValorInt(indice, valor);
}

int GetValorFloatJogo(const int indice, float &valor)
{
    return jogo->GetValorFloat(indice, valor);
}

int GetValorStringJogo(const int indice, char *valor)
{
    string str;
    const bool resp = jogo->GetValorString(indice, str);
    strcpy(valor, str.c_str());
    return resp;
}

int GetValorIntJogo(const char *indice, int &valor)
{
    return jogo->GetValorInt(indice, valor);
}

int GetValorFloatJogo(const char *indice, float &valor)
{
    return jogo->GetValorFloat(indice, valor);
}

int GetValorStringJogo(const char *indice, char *valor)
{
    string str;
    const bool resp = jogo->GetValorString(indice, str);
    strcpy(valor, str.c_str());
    return resp;
}

// int GetEstadoJogo(){
//     return jogo->GetEstado();
// }

// void SetEstadoJogo(int estado){
//     jogo->SetEstado(estado);
// }

void DefineFundo(const char *nomeArquivoImagem, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DefineFundo(nomeArquivoImagem);
}

PIGTeclado GetTeclado()
{
    return jogo->PegaTeclado();
}

PIGEvento GetEvento()
{
    return jogo->PegaEvento();
}

void PoolEventos()
{
    jogo->PoolEventos();
}

bool TeclaPressionada(SDL_Scancode tecla)
{
    return CPIGTeclado::TeclaPressionada(tecla);
}

bool TeclaLevantada(SDL_Scancode tecla)
{
    return CPIGTeclado::TeclaLevantada(tecla);
}

bool TeclaBaixa(SDL_Scancode tecla)
{
    return CPIGTeclado::TeclaBaixa(tecla);
}

bool TeclaAlta(SDL_Scancode tecla)
{
    return CPIGTeclado::TeclaAlta(tecla);
}

void IniciaDesenho(const int idJanela)
{
    CPIGJogo::IniciaDesenho(idJanela);
}

void EncerraDesenho(const int idJanela)
{
    CPIGMouse::Desenha();
    CPIGJogo::EncerraDesenho(idJanela);
}

void SalvaTela(const char *nomeArquivoBMP, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SaveScreenshot(nomeArquivoBMP, true);
}

int JogoRodando()
{
    return jogo->GetRodando();
}

void Espera(const int tempo)
{
    SDL_Delay(tempo);
}

void FinalizaJogo()
{
    delete jogo;
}

float GetFPS()
{
    return CPIGJogo::GetFPS();
}

void CarregaCursor(const char *nomeArquivoCursor, const int idJanela)
{
    CPIGMouse::CarregaCursor(nomeArquivoCursor, idJanela);
}

void CriaFrameCursor(
        const int idFrame, const int xBitmap, const int yBitmap, const int altura,
        const int largura)
{
    CPIGMouse::CriaFrameCursor(idFrame, xBitmap, yBitmap, altura, largura);
}

void CarregaFramesPorLinhaCursor(const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGMouse::CarregaFramesPorLinha(frameInicial, qtdLinhas, qtdColunas);
}

void CarregaFramesPorColunaCursor(const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGMouse::CarregaFramesPorColuna(frameInicial, qtdLinhas, qtdColunas);
}

int MudaCursor(const int idFrame)
{
    return CPIGMouse::MudaCursor(idFrame);
}

int GetEstadoBotaoMouse(const int botao)
{
    return CPIGMouse::GetEstadoBotao(botao);
}

int GetBotaoMousePressionado(const int botao)
{
    return CPIGMouse::GetBotaoPressionado(botao);
}
int GetBotaoMouseLevantado(const int botao)
{
    return CPIGMouse::GetBotaoLevantado(botao);
}
int GetBotaoMouseBaixo(const int botao)
{
    return CPIGMouse::GetBotaoBaixo(botao);
}
int GetBotaoMouseAlto(const int botao)
{
    return CPIGMouse::GetBotaoAlto(botao);
}

void ExecutaBackground(const PIGFuncaoBackground funcao, void *dados)
{
    SDL_CreateThread(funcao, "", dados);
}

int GetQtdJanelas()
{
    return CPIGGerenciadorJanelas::GetQtdJanelas();
}

int CriaJanela(const char *nomeJanela, const int altura, const int largura)
{
    return CPIGGerenciadorJanelas::CriaJanela(nomeJanela, altura, largura);
}

void FechaJanela(const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Fecha();
}

void EscondeJanela(const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Esconde();
}

void ExibeJanela(const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->Exibe();
}

void GanhaFocoJanela(const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->GanhaFoco();
}

int GetAlturaJanela(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();
}

int GetLarguraJanela(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetLargura();
}

void SetTamanhoJanela(const int altura, const int largura, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTamanho(altura, largura);
}

double SetAfastamentoCamera(const double afastamento, const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->SetAfastamento(afastamento);
}

double GetAfastamentoCamera(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAfastamento();
}

void MoveCamera(const int posicaoX, const int posicaoY, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->MoveCamera(posicaoX, posicaoY);
}

void DeslocaCamera(const int deltaX, const int deltaY, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DeslocaCamera(deltaX, deltaY);
}

void GetXYCamera(int *posicaoX, int *posicaoY, const int idJanela)
{
    const SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetPosicaoCamera();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void PreparaCameraMovel(const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraMovel();
}

void PreparaCameraFixa(const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->PreparaCameraFixa();
}

void ConverteCoordenadaDaTelaParaMundo(
        const int telaX, const int telaY, int *mundoX, int *mundoY, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaScreenWorld(
            telaX, telaY, *mundoX, *mundoY);
}

void ConverteCoordenadaDoMundoParaTela(
        const int mundoX, const int mundoY, int *telaX, int *telaY, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->ConverteCoordenadaWorldScreen(
            mundoX, mundoY, *telaX, *telaY);
}

void GetTituloJanela(char *tituloJanela, const int idJanela)
{
    strcpy(tituloJanela, CPIGGerenciadorJanelas::GetJanela(idJanela)->GetTitulo().c_str());
}

void SetTituloJanela(const char *novoTitulo, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetTitulo(novoTitulo);
}

PIGCor GetCorFundoJanela(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetCorFundo();
}

void SetCorFundoJanela(const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetCorFundo(cor);
}

float GetOpacidadeJanela(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetOpacidade();
}

void SetOpacidadeJanela(const float nivelOpacidade, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetOpacidade(nivelOpacidade);
}

void SetPosicaoJanela(const int posicaoX, const int posicaoY, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetPosicao(posicaoX, posicaoY);
}

void GetPosicaoJanela(int *posicaoX, int *posicaoY, const int idJanela)
{
    const SDL_Point p = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void SetBordaJanela(const int valor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetBorda(valor);
}

void SetModoJanela(const int modo, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->SetModo(modo);
}

int GetModoJanela(const int idJanela)
{
    return CPIGGerenciadorJanelas::GetJanela(idJanela)->GetModo();
}

#ifdef PIGCOMCONTROLE

int BotaoPressionadoControle(const int idControle, int botao)
{
    return CPIGGerenciadorControles::GetControle(idControle)->BotaoPressionado(botao);
}

int EixoAcionadoControle(const int idControle, int eixo)
{
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionado(eixo);
}

float EixoAcionadoPercentualControle(const int idControle, int eixo)
{
    return CPIGGerenciadorControles::GetControle(idControle)->EixoAcionadoPercentual(eixo);
}

int GetQtdEixosControle(const int idControle)
{
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdEixos();
}

int GetQtdBotoesControle(const int idControle)
{
    return CPIGGerenciadorControles::GetControle(idControle)->GetQtdBotoes();
}

void GetNomeControle(const int idControle, char *nomeControle)
{
    strcpy(nomeControle, CPIGGerenciadorControles::GetControle(idControle)->GetNome().c_str());
}

#endif // PIGCOMCONTROLE

void DesenhaLinhaSimples(
        const int pontoX1, const int pontoY1, const int pontoX2, const int pontoY2,
        const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhaSimples(
            pontoX1, pontoY1, pontoX2, pontoY2, cor);
}

void DesenhaLinhasDisjuntas(
        int pontosX[], int pontosY[], const int qtdPontos, const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasDisjuntas(
            pontosX, pontosY, qtdPontos, cor);
}

void DesenhaLinhasSequencia(
        int pontosX[], int pontosY[], const int qtdPontos, const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaLinhasSequencia(
            pontosX, pontosY, qtdPontos, cor);
}

void DesenhaRetangulo(
        const int posicaoX, const int posicaoY, const int altura, const int largura,
        const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetangulo(
            posicaoX, posicaoY, altura, largura, cor);
}

void DesenhaRetanguloVazado(
        const int posicaoX, const int posicaoY, const int altura, const int largura,
        const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaRetanguloVazado(
            posicaoX, posicaoY, altura, largura, cor);
}

void DesenhaPoligono(
        int pontosX[], int pontosY[], const int qtdPontos, const PIGCor cor, const int idJanela)
{
    CPIGGerenciadorJanelas::GetJanela(idJanela)->DesenhaPoligono(pontosX, pontosY, qtdPontos, cor);
}

void PreparaOffScreenRenderer(const int altura, const int largura)
{
    jogo->PreparaOffScreenRenderer(altura, largura);
}

void SalvaOffScreenBMP(const char *nomeArquivoBMP)
{
    jogo->GetOffScreenRender()->SalvarImagemBMP(nomeArquivoBMP);
}

void SalvaOffScreenPNG(const char *nomeArquivoPNG)
{
    jogo->GetOffScreenRender()->SalvarImagemPNG(nomeArquivoPNG);
}

void PintaAreaOffScreen(const int posicaoX, const int posicaoY, const PIGCor cor)
{
    jogo->GetOffScreenRender()->PintarArea(posicaoX, posicaoY, cor);
}

void DefineFuncaoPintarAreaOffscreen(const PIGFuncaoPintarArea funcao)
{
    jogo->GetOffScreenRender()->DefineFuncaoPintarArea(funcao);
}

void MoveCanetaOffscreen(const double novoX, const double novoY)
{
    jogo->GetOffScreenRender()->MoveCanetaPara(novoX, novoY);
}

void AvancaCanetaOffscreen(const double distancia)
{
    jogo->GetOffScreenRender()->AvancaCaneta(distancia);
}

void MudaCorCanetaOffscreen(const PIGCor novaCor)
{
    jogo->GetOffScreenRender()->MudaCorAtualCaneta(novaCor);
}

void GiraCanetaHorarioOffscreen(const double angulo)
{
    jogo->GetOffScreenRender()->GiraCanetaHorario(angulo);
}

void GiraCanetaAntiHorarioOffscreen(const double angulo)
{
    jogo->GetOffScreenRender()->GiraCanetaAntiHorario(angulo);
}

void GiraCanetaAnguloFixoOffscreen(const double angulo)
{
    jogo->GetOffScreenRender()->GiraAnguloFixo(angulo);
}

double GetAnguloAtualOffscreen()
{
    return jogo->GetOffScreenRender()->GetAngAtual();
}

int GetXCanetaOffscreen()
{
    return jogo->GetOffScreenRender()->GetXCaneta();
}

int GetYCanetaOffscreen()
{
    return jogo->GetOffScreenRender()->GetYCaneta();
}

void PintaFundoOffScreen(const PIGCor cor)
{
    jogo->GetOffScreenRender()->PintarFundo(cor);
}

void DesenhaRetanguloOffScreen(
        const int x1, const int y1, const int altura, const int largura, const PIGCor cor)
{
    jogo->GetOffScreenRender()->DesenharRetangulo(x1, y1, altura, largura, cor);
}

void DesenhaRetanguloVazadoOffScreen(
        const int x1, const int y1, const int altura, const int largura, const PIGCor cor)
{
    jogo->GetOffScreenRender()->DesenharRetanguloVazado(x1, y1, altura, largura, cor);
}

void DesenhaLinhaSimplesOffScreen(
        const int x1, const int y1, const int x2, const int y2, const PIGCor cor)
{
    jogo->GetOffScreenRender()->DesenharLinha(x1, y1, x2, y2, cor);
}

void DesenhaLinhasDisjuntasOffScreen(
        int pontosX[], int pontosY[], const int qtdPontos, const PIGCor cor)
{
    jogo->GetOffScreenRender()->DesenhaLinhasDisjuntas(pontosX, pontosY, qtdPontos, cor);
}

void DesenhaLinhasSequenciaOffScreen(
        int pontosX[], int pontosY[], const int qtdPontos, const PIGCor cor)
{
    jogo->GetOffScreenRender()->DesenhaLinhasSequencia(pontosX, pontosY, qtdPontos, cor);
}

int CriaFonteNormal(
        const char *nome, const int tamanho, const PIGCor corLetra, const int contorno,
        const PIGCor corContorno, const PIGEstilo estilo, const int idJanela)
{
    return CPIGGerenciadorFontes::CriaFonteNormal(
            nome, tamanho, estilo, corLetra, contorno, corContorno, idJanela);
}

int CriaFonteNormal(
        const char *nome, const int tamanho, const PIGCor corLetra, const PIGEstilo estilo,
        const int idJanela)
{
    return CPIGGerenciadorFontes::CriaFonteNormal(nome, tamanho, estilo, corLetra, idJanela);
}

int CriaFonteDinamica(const char *nome, const int tamanho, const int idJanela)
{
    return CPIGGerenciadorFontes::CriaFonteDinamica(nome, tamanho, idJanela);
}

int CriaFonteFundo(
        const char *nome, const int tamanho, const char *arquivoFundo, const int contorno,
        const PIGCor corContorno, const PIGEstilo estilo, const int idJanela)
{
    return CPIGGerenciadorFontes::CriaFonteFundo(
            nome, tamanho, estilo, arquivoFundo, contorno, corContorno, idJanela);
}

int CriaFonteFundo(
        const char *nome, const int tamanho, const char *arquivoFundo, const PIGEstilo estilo,
        const int idJanela)
{
    return CPIGGerenciadorFontes::CriaFonteFundo(nome, tamanho, estilo, arquivoFundo, idJanela);
}

int CriaFonteNormalOffscreen(
        const char *nome, const int tamanho, const PIGCor corLetra, const int contorno,
        const PIGCor corContorno, const PIGEstilo estilo)
{
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(
            nome, tamanho, estilo, corLetra, contorno, corContorno, jogo->GetOffScreenRender(), 0);
}

int CriaFonteNormalOffscreen(
        const char *nome, const int tamanho, const PIGCor corLetra, const PIGEstilo estilo)
{
    return CPIGGerenciadorFontes::CriaFonteNormalOffScreen(
            nome, tamanho, estilo, jogo->GetOffScreenRender(), corLetra, 0);
}

int CriaFonteFundoOffscreen(
        const char *nome, const int tamanho, const char *arquivoFundo, const int contorno,
        const PIGCor corContorno, const PIGEstilo estilo)
{
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(
            nome, tamanho, estilo, arquivoFundo, contorno, corContorno, jogo->GetOffScreenRender(),
            0);
}

int CriaFonteFundoOffscreen(
        const char *nome, const int tamanho, const char *arquivoFundo, const PIGEstilo estilo)
{
    return CPIGGerenciadorFontes::CriaFonteFundoOffScreen(
            nome, tamanho, estilo, arquivoFundo, jogo->GetOffScreenRender(), 0);
}

int CalculaLarguraPixels(const char *str, const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraPixelsString(str);
}

void EscreverDireita(
        const char *str, const int posicaoX, const int posicaoY, const PIGCor cor,
        const int numFonte, const float angulo)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str, posicaoX, posicaoY, cor, PIG_TEXTO_DIREITA, angulo);
}

void EscreverEsquerda(
        const char *str, const int posicaoX, const int posicaoY, const PIGCor cor,
        const int numFonte, const float angulo)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str, posicaoX, posicaoY, cor, PIG_TEXTO_ESQUERDA, angulo);
}

void EscreverCentralizada(
        const char *str, const int posicaoX, const int posicaoY, const PIGCor cor,
        const int numFonte, const float angulo)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str, posicaoX, posicaoY, cor, PIG_TEXTO_CENTRO, angulo);
}

void EscreverLongaEsquerda(
        const char *str, const int posicaoX, const int posicaoY, const int largMax,
        const int espacoEntreLinhas, const PIGCor cor, const int numFonte, const float angulo)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(
            str, posicaoX, posicaoY, largMax, espacoEntreLinhas, cor, PIG_TEXTO_ESQUERDA, angulo);
}

void EscreverLongaDireita(
        const char *str, const int posicaoX, const int posicaoY, const int largMax,
        const int espacoEntreLinhas, const PIGCor cor, const int numFonte, const float angulo)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(
            str, posicaoX, posicaoY, largMax, espacoEntreLinhas, cor, PIG_TEXTO_DIREITA, angulo);
}

void EscreverLongaCentralizada(
        const char *str, const int posicaoX, const int posicaoY, const int largMax,
        const int espacoEntreLinhas, const PIGCor cor, const int numFonte, const float angulo)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->EscreveLonga(
            str, posicaoX, posicaoY, largMax, espacoEntreLinhas, cor, PIG_TEXTO_CENTRO, angulo);
}

void EscreveInteiroEsquerda(
        const int valor, const int x, const int y, const PIGCor cor, const int numFonte,
        const float angulo)
{
    stringstream str;
    str << valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str.str(), x, y, cor, PIG_TEXTO_ESQUERDA, angulo);
}

void EscreveInteiroDireita(
        const int valor, const int x, const int y, const PIGCor cor, const int numFonte,
        const float angulo)
{
    stringstream str;
    str << valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str.str(), x, y, cor, PIG_TEXTO_DIREITA, angulo);
}

void EscreveInteiroCentralizado(
        const int valor, const int x, const int y, const PIGCor cor, const int numFonte,
        const float angulo)
{
    stringstream str;
    str << valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str.str(), x, y, cor, PIG_TEXTO_CENTRO, angulo);
}

void EscreveDoubleEsquerda(
        const double valor, const int casas, const int x, const int y, const PIGCor cor,
        const int numFonte, const float angulo)
{
    stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str << std::setprecision(casas) << valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str.str(), x, y, cor, PIG_TEXTO_ESQUERDA, angulo);
}

void EscreveDoubleDireita(
        const double valor, const int casas, const int x, const int y, const PIGCor cor,
        const int numFonte, const float angulo)
{
    stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str << std::setprecision(casas) << valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str.str(), x, y, cor, PIG_TEXTO_DIREITA, angulo);
}

void EscreveDoubleCentralizado(
        const double valor, const int casas, const int x, const int y, const PIGCor cor,
        const int numFonte, const float angulo)
{
    stringstream str;
    str.setf(std::ios_base::fixed, std::ios_base::floatfield);
    str << std::setprecision(casas) << valor;
    CPIGGerenciadorFontes::GetFonte(numFonte)->Escreve(
            str.str(), x, y, cor, PIG_TEXTO_CENTRO, angulo);
}

PIGMetricasFonte GetMetricas(const char letra, const PIGEstilo estilo, const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetMetricasLetra(letra, estilo);
}

int GetLarguraLetra(const char letra, const PIGEstilo estilo, const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLarguraLetra(letra, estilo);
}

int GetTamanhoBaseFonte(const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetTamanhoBaseFonte();
}

int GetFonteDescent(const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteDescent();
}

int GetFonteAscent(const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetFonteAscent();
}

int GetFonteLineSkip(const int numFonte)
{
    return CPIGGerenciadorFontes::GetFonte(numFonte)->GetLineSkip();
}

void SubstituiCaractere(
        const char caractere, const char *nomeArquivo, const int largNova, const int x, const int y,
        const int altura, const int largura, const int numFonte)
{
    CPIGGerenciadorFontes::GetFonte(numFonte)->SubstituiGlyph(
            nomeArquivo, caractere, largNova, x, y, altura, largura);
}

int CriaLabel(const char *texto, const PIGCor corFonte, const int numFonte, const int idJanela)
{
    return CPIGGerenciadorLabels::CriaLabel(texto, corFonte, numFonte, idJanela);
}

void DestroiLabel(const int idLabel)
{
    CPIGGerenciadorLabels::DestroiLabel(idLabel);
}

void SetTextoLabel(const int idLabel, const char *texto)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetTexto(texto);
}

void GetTextoLabel(const int idLabel, char *texto)
{
    strcpy(texto, CPIGGerenciadorLabels::GetLabel(idLabel)->GetTexto().c_str());
}

void GetXYLabel(const int idLabel, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorLabels::GetLabel(idLabel)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void MoveLabel(const int idLabel, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->Move(posicaoX, posicaoY);
}

void DeslocaLabel(const int idLabel, const int deltaX, const int deltaY)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->Desloca(deltaX, deltaY);
}

void SetAnguloLabel(const int idLabel, const float angulo)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetAngulo(angulo);
}

float GetAnguloLabel(const int idLabel)
{
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetAngulo();
}

void SetPivoAbsolutoLabel(const int idLabel, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetPivoAbsoluto(
            {(double) posicaoX, (double) posicaoY});
}

void SetPivoProporcionalLabel(const int idLabel, const float relX, const float relY)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetPivoProporcional({relX, relY});
}

void GetPivoLabel(const int idLabel, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorLabels::GetLabel(idLabel)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void SetFlipLabel(const int idLabel, const PIGFlip valor)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetFlip(valor);
}

PIGFlip GetFlipLabel(const int idLabel)
{
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetFlip();
}

void GetDimensoesLabel(const int idLabel, int &altura, int &largura)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->GetDimensoes(altura, largura);
}

void SetCorFonteLabel(const int idLabel, const PIGCor cor)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetCorFonte(cor);
}

PIGCor GetCorFonteLabel(const int idLabel)
{
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetCorFonte();
}

void SetNumeroFonteLabel(const int idLabel, const int numFonte)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetFonte(numFonte);
}

int GetNumeroFonteLabel(const int idLabel)
{
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetFonte();
}

void SetOpacidadeLabel(const int idLabel, const int valor)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->SetOpacidade(valor);
}

int GetOpacidadeLabel(const int idLabel)
{
    return CPIGGerenciadorLabels::GetLabel(idLabel)->GetOpacidade();
}

void DesenhaLabel(const int idLabel)
{
    CPIGGerenciadorLabels::GetLabel(idLabel)->Desenha();
}

int CriaSprite(
        const char *nomeArquivo, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaSprite(nomeArquivo, retiraFundo, corFundo, idJanela);
}

int CriaSprite(
        const int idSprite, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaSprite(idSprite, retiraFundo, corFundo, idJanela);
}

int CriaSpriteOffScreen(const int retiraFundo, const PIGCor *corFundo)
{
    return CPIGGerenciadorSprites::CriaSpriteOffScreen(
            jogo->GetOffScreenRender(), retiraFundo, corFundo);
}

void DestroiSprite(const int idSprite)
{
    CPIGGerenciadorSprites::DestroiSprite(idSprite);
}

void CarregaArquivoFramesSprite(const int idSprite, const char *nomeArq)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->CarregaArquivoFrames(nomeArq);
}

void CarregaFramesPorLinhaSprite(
        const int idSprite, const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorLinha(
            frameInicial, qtdLinhas, qtdColunas);
}

void CarregaFramesPorColunaSprite(
        const int idSprite, const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->CriaFramesAutomaticosPorColuna(
            frameInicial, qtdLinhas, qtdColunas);
}

void GetXYSprite(const int idSprite, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void MoveSprite(const int idSprite, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->Move(posicaoX, posicaoY);
}

void DeslocaSprite(const int idSprite, const int deltaX, const int deltaY)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desloca(deltaX, deltaY);
}

void SetAnguloSprite(const int idSprite, const float angulo)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetAngulo(angulo);
}

float GetAnguloSprite(const int idSprite)
{
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetAngulo();
}

void SetPivoAbsolutoSprite(const int idSprite, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoAbsoluto(
            {(double) posicaoX, (double) posicaoY});
}

void SetPivoProporcionalSprite(const int idSprite, const float relX, const float relY)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetPivoProporcional({relX, relY});
}

void GetPivoSprite(const int idSprite, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorSprites::GetSprite(idSprite)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void SetFlipSprite(const int idSprite, const PIGFlip valor)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetFlip(valor);
}

PIGFlip GetFlipSprite(const int idSprite)
{
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFlip();
}

void SetDimensoesSprite(const int idSprite, const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetDimensoes(altura, largura);
}

void GetDimensoesSprite(const int idSprite, int &altura, int &largura)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoes(altura, largura);
}

void GetDimensoesOriginaisSprite(const int idSprite, int &altura, int &largura)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->GetDimensoesOriginais(altura, largura);
}

void RestauraDimensoesOriginaisSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->RestauraDimensoesOriginais();
}

void CriaFrameSprite(
        const int idSprite, const int idFrame, const int xBitmap, const int yBitmap,
        const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineFrame(
            idFrame, {xBitmap, yBitmap, largura, altura});
}

void CriaFramesSprite(const int idSprite, const SDL_Rect *r, const size_t count)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineFrames(r, count);
}

int MudaFrameSprite(const int idSprite, const int idFrame)
{
    return CPIGGerenciadorSprites::GetSprite(idSprite)->MudaFrameAtual(idFrame);
}

int GetFrameAtualSprite(const int idSprite)
{
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetFrameAtual();
}

void SetColoracaoSprite(const int idSprite, const PIGCor cor)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetColoracao(cor);
}

void SetOpacidadeSprite(const int idSprite, const int valor)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->SetOpacidade(valor);
}

int GetOpacidadeSprite(const int idSprite)
{
    return CPIGGerenciadorSprites::GetSprite(idSprite)->GetOpacidade();
}

void DesenhaSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->Desenha();
}

void DesenhaSpriteOffScreen(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

void DesenhaSpriteSimples(
        const char *nomeArq, const int x, const int y, const int retiraFundo, const int idJanela)
{
    CPIGGerenciadorSprites::DesenhaSprite(nomeArq, x, y, retiraFundo, idJanela);
}

void InsereTransicaoSprite(
        const int idSprite, const double tempo, const int deltaX, const int deltaY,
        const int deltaAltura, const int deltaLargura, const double deltaAngulo,
        const PIGCor corFinal, const int deltaOpacidade)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereTransicao(
            tempo,
            {deltaX, deltaY, deltaAltura, deltaLargura, deltaAngulo, corFinal, deltaOpacidade});
}

int ExecutandoTransicaoSprite(const int idSprite)
{
    return CPIGGerenciadorSprites::GetSprite(idSprite)->ExecutandoTransicao();
}

void LeArquivoTransicaoSprite(const int idSprite, const char *nomeArq)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->LeTransicoes(nomeArq);
}

void IniciaAutomacaoSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->IniciaAutomacao();
}

void TrataAutomacaoSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->TrataAutomacao();
}

void PausaAutomacaoSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->PausaAutomacao();
}

void DespausaAutomacaoSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->DespausaAutomacao();
}

void DefineTipoTransicaoSprite(const int idSprite, const PIGTipoTransicao valor)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->DefineTipoTransicao(valor);
}

void LimpaTransicoesSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaTransicoes();
}

void InsereAcaoSprite(
        const int idSprite, const double tempo, const double repeticao, const PIGFuncaoSimples acao,
        void *param)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->InsereAcao(tempo, repeticao, acao, param);
}

void LimpaAcoesSprite(const int idSprite)
{
    CPIGGerenciadorSprites::GetSprite(idSprite)->LimpaAcoes();
}

int CriaObjeto(
        const char *nomeArquivo, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaObjeto(nomeArquivo, retiraFundo, corFundo, idJanela);
}

int CriaObjeto(
        const int idObjeto, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaObjeto(idObjeto, retiraFundo, corFundo, idJanela);
}

int CriaObjetoOffScreen(const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaObjetoOffScreen(
            jogo->GetOffScreenRender(), retiraFundo, corFundo, idJanela);
}

int GetFrameAtualObjeto(const int idObjeto)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFrameAtual();
}

void DestroiObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::DestroiObjeto(idObjeto);
}

void SetValorIntObjeto(const int idObjeto, const int indice, const int valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice, valor);
}

void SetValorFloatObjeto(const int idObjeto, const int indice, const float valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice, valor);
}

void SetValorStringObjeto(const int idObjeto, const int indice, const char *valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice, valor);
}

void SetValorIntObjeto(const int idObjeto, const char *indice, const int valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorInt(indice, valor);
}

void SetValorFloatObjeto(const int idObjeto, const char *indice, const float valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorFloat(indice, valor);
}

void SetValorStringObjeto(const int idObjeto, const char *indice, const char *valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetValorString(indice, valor);
}

int GetValorIntObjeto(const int idObjeto, const int indice, int &valor)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice, valor);
}

int GetValorFloatObjeto(const int idObjeto, const int indice, float &valor)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice, valor);
}

int GetValorStringObjeto(const int idObjeto, const int indice, char *valor)
{
    string str;
    const bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice, str);
    strcpy(valor, str.c_str());
    return resp;
}

int GetValorIntObjeto(const int idObjeto, const char *indice, int &valor)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorInt(indice, valor);
}

int GetValorFloatObjeto(const int idObjeto, const char *indice, float &valor)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorFloat(indice, valor);
}

int GetValorStringObjeto(const int idObjeto, const char *indice, char *valor)
{
    string str;
    const bool resp = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetValorString(indice, str);
    strcpy(valor, str.c_str());
    return resp;
}

void GetXYObjeto(const int idObjeto, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void MoveObjeto(const int idObjeto, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Move(posicaoX, posicaoY);
}

void DeslocaObjeto(const int idObjeto, const int deltaX, const int deltaY)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desloca(deltaX, deltaY);
}

void SetAnguloObjeto(const int idObjeto, const float angulo)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetAngulo(angulo);
}

float GetAnguloObjeto(const int idObjeto)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetAngulo();
}

void SetPivoAbsolutoObjeto(const int idObjeto, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoAbsoluto(
            {(double) posicaoX, (double) posicaoY});
}

void SetPivoProporcionalObjeto(const int idObjeto, const float relX, const float relY)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetPivoProporcional({relX, relY});
}

void GetPivoObjeto(const int idObjeto, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void SetFlipObjeto(const int idObjeto, const PIGFlip valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetFlip(valor);
}

PIGFlip GetFlipObjeto(const int idObjeto)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetFlip();
}

void SetDimensoesObjeto(const int idObjeto, const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetDimensoes(altura, largura);
}

void GetDimensoesObjeto(const int idObjeto, int &altura, int &largura)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoes(altura, largura);
}

void GetDimensoesOriginaisObjeto(const int idObjeto, int &altura, int &largura)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetDimensoesOriginais(altura, largura);
}

void RestauraDimensoesOriginaisObjeto(const int idObjeto, const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->RestauraDimensoesOriginais();
}

void CriaFrameObjeto(
        const int idObjeto, const int idFrame, const int xBitmap, const int yBitmap,
        const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineFrame(
            idFrame, {xBitmap, yBitmap, largura, largura});
}

void CarregaArquivoFramesObjeto(const int idObjeto, const char *nomeArq)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CarregaArquivoFrames(nomeArq);
}

void CarregaFramesPorLinhaObjeto(
        const int idObjeto, const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorLinha(
            frameInicial, qtdLinhas, qtdColunas);
}

void CarregaFramesPorColunaObjeto(
        const int idObjeto, const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->CriaFramesAutomaticosPorColuna(
            frameInicial, qtdLinhas, qtdColunas);
}

int MudaFrameObjeto(const int idObjeto, const int idFrame)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->MudaFrameAtual(idFrame);
}

void SetColoracaoObjeto(const int idObjeto, const PIGCor cor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetColoracao(cor);
}

void SetOpacidadeObjeto(const int idObjeto, const int valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetOpacidade(valor);
}

int GetOpacidadeObjeto(const int idObjeto)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetOpacidade();
}

void DesenhaObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->Desenha();
}

void DesenhaObjetoOffScreen(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DesenhaOffScreen(jogo->GetOffScreenRender());
}

int TestaColisaoObjetos(const int idObjeto1, const int idObjeto2)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto1)->Colisao(
                   CPIGGerenciadorSprites::GetObjeto(idObjeto2)) &&
           CPIGGerenciadorSprites::GetObjeto(idObjeto2)->Colisao(
                   CPIGGerenciadorSprites::GetObjeto(idObjeto1));
}

void DefineAreaColisaoObjeto(const int idObjeto, int pontosX[], int pontosY[], const int qtdPontos)
{
    vector<PIGPonto2D> vertices;

    vertices.reserve(qtdPontos);
    for (int i = 0; i < qtdPontos; i++)
    {
        vertices.push_back({(double) pontosX[i], (double) pontosY[i]});
    }

    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetVertices(vertices);
}

void DefineRaioColisaoObjeto(const int idObjeto, const float raio)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetRaioColisaoCircular(raio);
}

void DefineTipoColisaoObjeto(const int idObjeto, const PIGModoColisao modo)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->SetModoColisao(modo);
}

PIGCor *GetPixelsObjeto(const int idObjeto)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->GetPixels();
}

void AtualizaPixelsObjeto(const int idObjeto, const int retiraFundo)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->AtualizaPixels(retiraFundo);
}

void InsereTransicaoObjeto(
        const int idObjeto, const double tempo, const int deltaX, const int deltaY,
        const int deltaAltura, const int deltaLargura, const double deltaAngulo,
        const PIGCor corFinal, const int deltaOpacidade)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereTransicao(
            tempo,
            {deltaX, deltaY, deltaAltura, deltaLargura, deltaAngulo, corFinal, deltaOpacidade});
}

int ExecutandoTransicaoObjeto(const int idObjeto)
{
    return CPIGGerenciadorSprites::GetObjeto(idObjeto)->ExecutandoTransicao();
}

void LeArquivoTransicaoObjeto(const int idObjeto, const char *nomeArq)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LeTransicoes(nomeArq);
}

void IniciaAutomacaoObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->IniciaAutomacao();
}

void TrataAutomacaoObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->TrataAutomacao();
}

void PausaAutomacaoObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->PausaAutomacao();
}

void DespausaAutomacaoObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DespausaAutomacao();
}

void DefineTipoTransicaoObjeto(const int idObjeto, const PIGTipoTransicao valor)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->DefineTipoTransicao(valor);
}

void LimpaTransicoesObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaTransicoes();
}

void InsereAcaoObjeto(
        const int idObjeto, const double tempo, const double repeticao, const PIGFuncaoSimples acao,
        void *param)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->InsereAcao(tempo, repeticao, acao, param);
}

void LimpaAcoesObjeto(const int idObjeto)
{
    CPIGGerenciadorSprites::GetObjeto(idObjeto)->LimpaAcoes();
}

int CriaGeradorParticulas(
        const int maxParticulas, const char *nomeArquivo, const int audioCriacao,
        const int audioEncerramento, const int retiraFundo, const PIGCor *corFundo,
        const int idJanela)
{
    return CPIGGerenciadorGDP::CriaGeradorParticulas(
            maxParticulas, nomeArquivo, audioCriacao, audioEncerramento, retiraFundo, corFundo,
            idJanela);
}

int CriaGeradorParticulasPorAnimacao(
        const int maxParticulas, const int idAnimacao, const int audioCriacao,
        const int audioEncerramento, const int retiraFundo, const PIGCor *corFundo,
        const int idJanela)
{
    return CPIGGerenciadorGDP::CriaGeradorParticulas(
            maxParticulas, CPIGGerenciadorSprites::GetAnimacao(idAnimacao), audioCriacao,
            audioEncerramento, retiraFundo, corFundo, idJanela);
}

int CriaGeradorParticulasPorObjeto(
        const int maxParticulas, const int idObjeto, const int audioCriacao,
        const int audioEncerramento, const int retiraFundo, const PIGCor *corFundo,
        const int idJanela)
{
    return CPIGGerenciadorGDP::CriaGeradorParticulas(
            maxParticulas, CPIGGerenciadorSprites::GetObjeto(idObjeto), audioCriacao,
            audioEncerramento, retiraFundo, corFundo, idJanela);
}

void DestroiGeradorParticulas(const int idGerador)
{
    CPIGGerenciadorGDP::DestroiGeradorParticulas(idGerador);
}

void MoveGeradorParticulas(const int idGerador, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->Move(posicaoX, posicaoY);
}

void DeslocaGeradorParticulas(const int idGerador, const int deltaX, const int deltaY)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desloca(deltaX, deltaY);
}

// void MudaDirecaoParticulas(int idGerador,int valorX,int valorY){
// CPIGGerenciadorParticulas::GetGerador(idGerador)->MudaDirecao(valorX,valorY);
//}

void InsereTransicaoParticulas(
        const int idGerador, const double tempo, const int deltaX, const int deltaY, int deltaAlt,
        int deltaLarg, double deltaAng, const PIGCor corFinal, const int deltaOpacidade)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicao(
            tempo, {deltaX, deltaY, deltaAlt, deltaLarg, deltaAng, corFinal, deltaOpacidade});
}

void DefineTipoTransicaoParticulas(const int idGerador, const PIGTipoTransicao valor)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicao(valor);
}

void LimpaTransicoesParticulas(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoes();
}

void InsereTransicaoGDP(
        const int idGerador, const double tempo, const int deltaX, const int deltaY, int deltaAlt,
        int deltaLarg, double deltaAng, const PIGCor corFinal, const int deltaOpacidade)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereTransicaoGDP(
            tempo, {deltaX, deltaY, deltaAlt, deltaLarg, deltaAng, corFinal, deltaOpacidade});
}

void LeTransicoesGDP(const int idGerador, const string &nomeArq)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->LeTransicoesGDP(nomeArq);
}

void IniciaAutomacaoGDP(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->IniciaAutomacaoGDP();
}

void LimpaTransicoesGDP(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaTransicoesGDP();
}

bool ExecutandoTransicaoGDP(const int idGerador)
{
    return CPIGGerenciadorGDP::GetGerador(idGerador)->ExecutandoTransicaoGDP();
}

void TrataAutomacaoGDP(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->TrataAutomacaoGDP();
}

void PausaAutomacaoGDP(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->PausaAutomacao();
}

void DespausaAutomacaoGDP(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->DespausaAutomacao();
}

void InsereAcaoGDP(
        const int idGerador, const double tempo, const double repeticao,
        const PIGFuncaoSimples acao, void *param)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->InsereAcaoGDP(tempo, repeticao, acao, param);
}

void LimpaAcoesGDP(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->LimpaAcoes();
}

void DefineTipoTransicaoGDP(const int idGerador, PIGTipoTransicao tipo)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineTipoTransicaoGDP(tipo);
}

void SetAnguloParticulas(const int idGerador, const double angulo)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetAngulo(angulo);
}

void SetCorParticulas(const int idGerador, const PIGCor cor)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetColoracao(cor);
}

void SetOpacidadeParticulas(const int idGerador, int opacidade)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetOpacidade(opacidade);
}

void SetDimensoesParticulas(const int idGerador, const int altura, const int largura)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetDimensoes(altura, largura);
}

void SetPivoAbsolutoParticulas(const int idGerador, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoAbsoluto(
            {(double) posicaoX, (double) posicaoY});
}

void SetPivoProporcionalParticulas(const int idGerador, const float relX, const float relY)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->SetPivoProporcional({relX, relY});
}

int CriaParticula(const int idGerador)
{
    return CPIGGerenciadorGDP::GetGerador(idGerador)->CriaParticula();
}

void DefineLimitesParticula(
        const int idGerador, int minX, int minY, int maxX, int maxY, double maxTempo)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->DefineLimites({minX, minY, maxX, maxY}, maxTempo);
}

int QuantidadeParticulasAtivas(const int idGerador)
{
    return CPIGGerenciadorGDP::GetGerador(idGerador)->GetQtdAtivas();
}

void DesenhaParticulas(const int idGerador)
{
    CPIGGerenciadorGDP::GetGerador(idGerador)->Desenha();
}

int TestaColisaoParticulasObjeto(const int idGerador, const int idObjeto)
{
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(
            CPIGGerenciadorSprites::GetObjeto(idObjeto));
}

int TestaColisaoParticulasAnimacao(const int idGerador, const int idAnimacao)
{
    return CPIGGerenciadorGDP::GetGerador(idGerador)->Colisao(
            CPIGGerenciadorSprites::GetAnimacao(idAnimacao));
}

int CriaTimer(const int congelado)
{
    return CPIGGerenciadorTimers::CriaTimer(congelado);
}

double TempoDecorrido(const int idTimer)
{
    return CPIGGerenciadorTimers::GetTimer(idTimer)->GetTempoDecorrido();
}

void PausaTimer(const int idTimer)
{
    CPIGGerenciadorTimers::GetTimer(idTimer)->Pausa();
}

void PausaTudo()
{
    CPIGGerenciadorTimers::PausaTodos();
}

void DespausaTimer(const int idTimer)
{
    CPIGGerenciadorTimers::GetTimer(idTimer)->Despausa();
}

void DespausaTudo()
{
    CPIGGerenciadorTimers::DespausaTodos();
}

void ReiniciaTimer(const int idTimer, const int congelado)
{
    CPIGGerenciadorTimers::GetTimer(idTimer)->Reinicia(congelado);
}

void DestroiTimer(const int idTimer)
{
    CPIGGerenciadorTimers::DestroiTimer(idTimer);
}

int AssociaGrupoTimer(const int idTimer, const int idGrupo)
{
    return CPIGGerenciadorTimers::AssociaTimerGrupo(idTimer, idGrupo);
}

int DesassociaGrupoTimer(const int idTimer, const int idGrupo)
{
    return CPIGGerenciadorTimers::DesassociaTimerGrupo(idTimer, idGrupo);
}

int PausaGrupoTimers(const int idGrupo)
{
    return CPIGGerenciadorTimers::PausaGrupo(idGrupo);
}

int DespausaGrupoTimers(const int idGrupo)
{
    return CPIGGerenciadorTimers::DespausaGrupo(idGrupo);
}

int ReiniciaGrupoTimers(const int idGrupo, const int congelado)
{
    return CPIGGerenciadorTimers::ReiniciaGrupo(idGrupo, congelado);
}

int CriaAnimacao(
        const char *nomeArquivo, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaAnimacao(nomeArquivo, retiraFundo, corFundo, idJanela);
}

int CriaAnimacao(
        const int idAnimacao, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaAnimacao(
            CPIGGerenciadorSprites::GetAnimacao(idAnimacao), retiraFundo, corFundo, idJanela);
}

int CriaAnimacaoDeObjeto(
        const int idObjeto, const int retiraFundo, const PIGCor *corFundo, const int idJanela)
{
    return CPIGGerenciadorSprites::CriaAnimacao(
            CPIGGerenciadorSprites::GetObjeto(idObjeto), retiraFundo, corFundo, idJanela);
}

void DestroiAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::DestroiSprite(idAnimacao);
}

void CriaFrameAnimacao(
        const int idAnimacao, const int codigoFrame, const int xBitmap, const int yBitmap,
        const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->DefineFrame(codigoFrame, {xBitmap, yBitmap, largura, altura});
}

void CarregaArquivoFramesAnimacao(const int idAnimacao, const char *nomeArq)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CarregaArquivoFrames(nomeArq);
}

void CarregaFramesPorLinhaAnimacao(
        const int idAnimacao, const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->CriaFramesAutomaticosPorLinha(frameInicial, qtdLinhas, qtdColunas);
}

void CarregaFramesPorColunaAnimacao(
        const int idAnimacao, const int frameInicial, const int qtdLinhas, const int qtdColunas)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->CriaFramesAutomaticosPorColuna(frameInicial, qtdLinhas, qtdColunas);
}

void CriaModoAnimacao(const int idAnimacao, const int codigoModo, const int loop)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->CriaModo(codigoModo, loop);
}

void InsereFrameAnimacao(
        const int idAnimacao, const int codigoModo, const int codigoFrame, const float tempo,
        const int idAudio, const int alturaAnimacao, const int larguraAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->InsereFrame(codigoModo, codigoFrame, tempo, idAudio, alturaAnimacao, larguraAnimacao);
}

void InsereAudioFrameAnimacao(
        const int idAnimacao, const int codigoModo, const int indiceFrame, const int idAudio)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->SetAudioFrame(codigoModo, indiceFrame, idAudio);
}

void MudaModoAnimacao(
        const int idAnimacao, const int codigoModo, const int indiceFrame, const int forcado)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->MudaModo(codigoModo, indiceFrame, forcado);
}

int GetModoAtualAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetModoAtual();
}

int GetFrameAtualAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFrameAtual();
}

int TestaColisaoAnimacoes(const int idAnimacao1, const int idAnimacao2)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao1)
            ->Colisao(CPIGGerenciadorSprites::GetAnimacao(idAnimacao2));
}

int TestaColisaoAnimacaoObjeto(const int idAnimacao, const int idObjeto)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->Colisao(CPIGGerenciadorSprites::GetObjeto(idObjeto));
}

void DefineAreaColisaoAnimacao(
        const int idAnimacao, int pontosX[], int pontosY[], const int qtdPontos)
{
    vector<PIGPonto2D> vertices;

    vertices.reserve(qtdPontos);
    for (int i = 0; i < qtdPontos; i++)
    {
        vertices.push_back({(double) pontosX[i], (double) pontosY[i]});
    }

    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetVertices(vertices);
}

void DefineRaioColisaoAnimacao(const int idAnimacao, const float raio)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetRaioColisaoCircular(raio);
}

void DefineTipoColisaoAnimacao(const int idAnimacao, const PIGModoColisao modo)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetModoColisao(modo);
}

int DesenhaAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desenha();
}

void MoveAnimacao(const int idAnimacao, const int x, const int y)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Move(x, y);
}

void DeslocaAnimacao(const int idAnimacao, const int deltaX, const int deltaY)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Desloca(deltaX, deltaY);
}

void SetLoopModoAnimacao(const int idAnimacao, const int modo, const int loop)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetLoopModo(modo, loop);
}

void SetTempoFrameAnimacao(
        const int idAnimacao, const int modo, const int indiceFrame, const float tempo)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetTempoFrame(modo, indiceFrame, tempo);
}

void SetAudioFrameAnimacao(
        const int idAnimacao, const int modo, const int indiceFrame, const int idAudio)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAudioFrame(modo, indiceFrame, idAudio);
}

int GetLoopModoAnimacao(const int idAnimacao, const int modo)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetLoopModo(modo);
}

int GetAudioFrameAnimacao(const int idAnimacao, const int modo, const int indiceFrame)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAudioFrame(modo, indiceFrame);
}

float GetTempoFrameAnimacao(const int idAnimacao, const int modo, const int indiceFrame)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetTempoFrame(modo, indiceFrame);
}

void PausaAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Pausa();
}

void DesausaAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->Despausa();
}

void SetOpacidadeAnimacao(const int idAnimacao, const int valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetOpacidade(valor);
}

int GetOpacidadeAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetOpacidade();
}

void SetColoracaoAnimacao(const int idAnimacao, const PIGCor cor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetColoracao(cor);
}

void SetFlipAnimacao(const int idAnimacao, const PIGFlip valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetFlip(valor);
}

PIGFlip GetFlipAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetFlip();
}

void SetAnguloAnimacao(const int idAnimacao, const double angulo)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetAngulo(angulo);
}

double GetAnguloAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetAngulo();
}

void SetPivoAbsolutoAnimacao(const int idAnimacao, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->SetPivoAbsoluto({(double) posicaoX, (double) posicaoY});
}

void SetPivoProporcionalAnimacao(const int idAnimacao, const float relX, const float relY)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetPivoProporcional({relX, relY});
}

void GetPivoAnimacao(const int idAnimacao, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void SetDimensoesAnimacao(const int idAnimacao, const int altura, const int largura)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetDimensoes(altura, largura);
}

void GetDimensoesAnimacao(const int idAnimacao, int &altura, int &largura)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetDimensoes(altura, largura);
}

void SetValorIntAnimacao(const int idAnimacao, const int indice, const int valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice, valor);
}

void SetValorFloatAnimacao(const int idAnimacao, const int indice, const float valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice, valor);
}

void SetValorStringAnimacao(const int idAnimacao, const int indice, const char *valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice, valor);
}

void SetValorIntAnimacao(const int idAnimacao, const char *indice, const int valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorInt(indice, valor);
}

void SetValorFloatAnimacao(const int idAnimacao, const char *indice, const float valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorFloat(indice, valor);
}

void SetValorStringAnimacao(const int idAnimacao, const char *indice, const char *valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->SetValorString(indice, valor);
}

int GetValorIntAnimacao(const int idAnimacao, const int indice, int &valor)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice, valor);
}

int GetValorFloatAnimacao(const int idAnimacao, const int indice, float &valor)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice, valor);
}

int GetValorStringAnimacao(const int idAnimacao, const int indice, char *valor)
{
    string str;
    const bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice, str);
    strcpy(valor, str.c_str());
    return resp;
}

int GetValorIntAnimacao(const int idAnimacao, const char *indice, int &valor)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorInt(indice, valor);
}

int GetValorFloatAnimacao(const int idAnimacao, const char *indice, float &valor)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorFloat(indice, valor);
}

int GetValorStringAnimacao(const int idAnimacao, const char *indice, char *valor)
{
    string str;
    const bool resp = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetValorString(indice, str);
    strcpy(valor, str.c_str());
    return resp;
}

void GetXYAnimacao(const int idAnimacao, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void InsereTransicaoAnimacao(
        const int idAnimacao, const double tempo, const int deltaX, const int deltaY,
        const int deltaAltura, const int deltaLargura, const double deltaAngulo,
        const PIGCor corFinal, const int deltaOpacidade)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)
            ->InsereTransicao(
                    tempo, {deltaX, deltaY, deltaAltura, deltaLargura, deltaAngulo, corFinal,
                            deltaOpacidade});
}

int ExecutandoTransicaoAnimacao(const int idAnimacao)
{
    return CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->ExecutandoTransicao();
}

void LeArquivoTransicaoAnimacao(const int idAnimacao, const char *nomeArq)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LeTransicoes(nomeArq);
}

void IniciaAutomacaoAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->IniciaAutomacao();
}

void TrataAutomacaoAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->TrataAutomacao();
}

void PausaAutomacaoAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->PausaAutomacao();
}

void DespausaAutomacaoAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DespausaAutomacao();
}

void DefineTipoTransicaoAnimacao(const int idAnimacao, const PIGTipoTransicao valor)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->DefineTipoTransicao(valor);
}

void LimpaTransicoesAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaTransicoes();
}

void InsereAcaoAnimacao(
        const int idAnimacao, const double tempo, const double repeticao,
        const PIGFuncaoSimples acao, void *param)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->InsereAcao(tempo, repeticao, acao, param);
}

void LimpaAcoesAnimacao(const int idAnimacao)
{
    CPIGGerenciadorSprites::GetAnimacao(idAnimacao)->LimpaAcoes();
}

#ifdef PIGCOMAUDIO

int CriaAudio(const char *nomeArquivo, const int nLoops, const int tempoExecucao)
{
    return CPIGGerenciadorAudios::CriaAudio(nomeArquivo, nLoops, tempoExecucao);
}

void DestroiAudio(const int idAudio)
{
    CPIGGerenciadorAudios::DestroiAudio(idAudio);
}

void CarregaBackground(const char *nomeArquivo)
{
    CPIGGerenciadorAudios::CarregaBackground(nomeArquivo);
}

void PlayBackground(const int nVezes)
{
    CPIGGerenciadorAudios::PlayBackground(nVezes);
}

void StopBackground()
{
    CPIGGerenciadorAudios::StopBackground();
}

void PauseBackground()
{
    CPIGGerenciadorAudios::PauseBackground();
}

void ResumeBackground()
{
    CPIGGerenciadorAudios::ResumeBackground();
}

PIGStatusAudio GetStatusBackground()
{
    return CPIGGerenciadorAudios::GetStatusBackground();
}

void SetVolumeBackground(const int valor)
{
    CPIGGerenciadorAudios::SetVolumeBackground(valor);
}

int GetVolumeBackground()
{
    return CPIGGerenciadorAudios::GetVolumeBackground();
}

void SetVolume(const int idAudio, const int volume)
{
    CPIGGerenciadorAudios::GetAudio(idAudio)->SetVolume(volume);
}

int GetVolume(const int idAudio)
{
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetVolume();
}

void SetVolumeTudo(const int volume)
{
    CPIGGerenciadorAudios::SetVolumeTudo(volume);
}

void PlayAudio(const int idAudio)
{
    CPIGGerenciadorAudios::Play(idAudio);
}

void PauseAudio(const int idAudio)
{
    CPIGGerenciadorAudios::GetAudio(idAudio)->Pause();
}

void ResumeAudio(const int idAudio)
{
    CPIGGerenciadorAudios::GetAudio(idAudio)->Resume();
}

void StopAudio(const int idAudio)
{
    CPIGGerenciadorAudios::GetAudio(idAudio)->Stop();
}

PIGStatusAudio GetStatusAudio(const int idAudio)
{
    return CPIGGerenciadorAudios::GetAudio(idAudio)->GetStatus();
}

void StopTudoAudio()
{
    CPIGGerenciadorAudios::StopTudo();
}

void PauseTudoAudio()
{
    CPIGGerenciadorAudios::PauseTudo();
}

void ResumeTudoAudio()
{
    CPIGGerenciadorAudios::ResumeTudo();
}

#endif // PIGCOMAUDIO

#ifdef PIGCOMREDE

int CriaSocketCliente(const char *hostname, const int porta, const int maxBytesPacote)
{
    return CPIGGerenciadorSockets::CriaCliente(hostname, porta, maxBytesPacote);
}

int CriaSocketServidor(const int maxClientes, const int porta, const int maxBytesPacote)
{
    return CPIGGerenciadorSockets::CriaServidor(maxClientes, porta, maxBytesPacote);
}

int CriaSocketUDP(const int porta)
{
    return CPIGGerenciadorSockets::CriaSocketUDP(porta);
}

void DestroiSocketCliente(const int idSocket)
{
    CPIGGerenciadorSockets::DestroiCliente(idSocket);
}

void DestroiSocketServidor(const int idSocket)
{
    CPIGGerenciadorSockets::DestroiServidor(idSocket);
}

void DestroiSocketUDP(const int idSocket)
{
    CPIGGerenciadorSockets::DestroiSocketUDP(idSocket);
}

int GetAtivoSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetAtivo();
}

int GetAtivoSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetAtivo();
}

int GetAtivoSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetAtivo();
}

long GetBytesEnviadosSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesEnviados();
}

long GetBytesRecebidosSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetBytesRecebidos();
}

long GetPacotesEnviadosSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

long GetPacotesRecebidosSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

long GetTempoUltimoRecebidoSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoRecebido();
}

long GetTempoUltimoEnviadoSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTempoUltimoEnviado();
}

long GetBytesEnviadosSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesEnviados();
}

long GetBytesRecebidosSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetBytesRecebidos();
}

long GetPacotesEnviadosSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesEnviados();
}

long GetPacotesRecebidosSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPacotesRecebidos();
}

long GetTempoUltimoRecebidoSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoRecebido();
}

long GetTempoUltimoEnviadoSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTempoUltimoEnviado();
}

long GetBytesEnviadosSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesEnviados();
}

long GetBytesRecebidosSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetBytesRecebidos();
}

long GetPacotesEnviadosSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesEnviados();
}

long GetPacotesRecebidosSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPacotesRecebidos();
}

long GetTempoUltimoRecebidoSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoRecebido();
}

long GetTempoUltimoEnviadoSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetTempoUltimoEnviado();
}

int GetPortaRemotaSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetPortaRemota();
}

int GetPortaLocalSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetPortaLocal();
}

int GetPortaLocalSocketUDP(const int idSocket)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetPortaLocal();
}

void GetHostRemotoSocketCliente(const int idSocket, char *hostname)
{
    strcpy(hostname, CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostRemoto().c_str());
}

void GetHostLocalSocketCliente(const int idSocket, char *hostname)
{
    strcpy(hostname, CPIGGerenciadorSockets::GetCliente(idSocket)->GetHostLocal().c_str());
}

void GetHostLocalSocketServidor(const int idSocket, char *hostname)
{
    strcpy(hostname, CPIGGerenciadorSockets::GetServidor(idSocket)->GetHostLocal().c_str());
}

void GetHostLocalSocketUDP(const int idSocket, char *hostname)
{
    strcpy(hostname, CPIGGerenciadorSockets::GetSocketUDP(idSocket)->GetHostLocal().c_str());
}

int GetTamanhoPacoteSocketCliente(const int idSocket)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->GetTamanhoPacote();
}

int GetTamanhoPacoteSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetTamanhoPacote();
}

int GetMaximoConexoesSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetMaximoConexoes();
}

int GetQuantidadeConexoesSocketServidor(const int idSocket)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->GetQuantidadeConexoes();
}

int EnviaDadosSocketCliente(const int idSocket, const void *buffer, const int tamanhoBuffer)
{
    return CPIGGerenciadorSockets::GetCliente(idSocket)->EnviaDados(buffer, tamanhoBuffer);
}

int EnviaDadosSocketServidor(
        const int idSocket, int socketSecundario, const void *buffer, const int tamanhoBuffer)
{
    return CPIGGerenciadorSockets::GetServidor(idSocket)->EnviaDados(
            buffer, tamanhoBuffer, socketSecundario);
}

int EnviaDadosSocketUDP(
        const int idSocket, const void *buffer, const int tamanhoBuffer, const char *hostRemoto,
        const int porta)
{
    return CPIGGerenciadorSockets::GetSocketUDP(idSocket)->EnviaDados(
            buffer, tamanhoBuffer, hostRemoto, porta);
}

#endif // PIGCOMREDE

#ifdef PIGCOMVIDEO

int CriaVideo(const char *nomeArquivo, const int idJanela)
{
    return CPIGGerenciadorVideos::CriaVideo(nomeArquivo, idJanela);
}

void DestroiVideo(const int idVideo)
{
    CPIGGerenciadorVideos::DestroiVideo(idVideo);
}

void SetSeekVideo(const int idVideo, const double incremento)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetSeek(incremento);
}

void PlayVideo(const int idVideo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->Play();
}

void StopVideo(const int idVideo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->Stop();
}

void PauseVideo(const int idVideo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->Pause();
}

void ResumeVideo(const int idVideo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->Resume();
}

int DesenhaVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->Desenha();
}

void SetVolumeVideo(const int idVideo, const double valor)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetVolume(valor);
}

double GetVolumeVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetVolume();
}

void GetNomeArquivoVideo(const int idVideo, char *nome)
{
    strcpy(nome, CPIGGerenciadorVideos::GetVideo(idVideo)->GetNomeArquivo().c_str());
}

double GetTempoAtualVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtual();
}

void GetTempoAtualVideo(const int idVideo, char *str)
{
    strcpy(str, CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoAtualString().c_str());
}

double GetTempoTotalVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotal();
}

void GetTempoTotalVideo(const int idVideo, char *str)
{
    strcpy(str, CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoTotalString().c_str());
}

double GetTempoFrameVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetTempoFrame();
}

double GetFPSVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFPS();
}

void SetAnguloVideo(const int idVideo, const float angulo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetAngulo(angulo);
}

double GetAnguloVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetAngulo();
}

void SetFlipVideo(const int idVideo, const PIGFlip valor)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetFlip(valor);
}

PIGFlip GetFlipVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetFlip();
}

void SetPivoAbsolutoVideo(const int idVideo, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoAbsoluto(
            {(double) posicaoX, (double) posicaoY});
}

void SetPivoProporcionalVideo(const int idVideo, const float relX, const float relY)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetPivoProporcional({relX, relY});
}

void GetPivoVideo(const int idVideo, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorVideos::GetVideo(idVideo)->GetPivo();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void MoveVideo(const int idVideo, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->Move(posicaoX, posicaoY);
}

void SetDimensoesVideo(const int idVideo, const int altura, const int largura)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetDimensoes(altura, largura);
}

void GetDimensoesVideo(const int idVideo, int &altura, int &largura)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetDimensoes(altura, largura);
}

void GetDimensoesOriginaisVideo(const int idVideo, int &altura, int &largura)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->GetResolucao(altura, largura);
}

void OcupaJanelaInteiraVideo(const int idVideo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->OcupaJanelaInteira();
}

void UsaResolucaoOriginalVideo(const int idVideo)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->UsaResolucaoOriginal();
}

void SetColoracaoVideo(const int idVideo, const PIGCor cor)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetColoracao(cor);
}

void SetOpacidadeVideo(const int idVideo, const int valor)
{
    CPIGGerenciadorVideos::GetVideo(idVideo)->SetOpacidade(valor);
}

int GetOpacidadeVideo(const int idVideo)
{
    return CPIGGerenciadorVideos::GetVideo(idVideo)->GetOpacidade();
}

#endif

#ifdef PIGCOMFORM

int PIGCriaForm(const int altura, const int largura, const int idJanela)
{
    return CPIGGerenciadorForms::CriaForm(altura, largura, idJanela);
}

int PIGCriaForm(
        const int altura, const int largura, const char *nomeArquivo, const int retiraFundo,
        const int idJanela)
{
    return CPIGGerenciadorForms::CriaForm(altura, largura, nomeArquivo, retiraFundo, idJanela);
}

int PIGCriaForm(const char *nomeArqTexto)
{
    return CPIGGerenciadorForms::CriaForm(nomeArqTexto);
}

int PIGFormTrataEvento(const int idForm, const PIGEvento &evento)
{
    return CPIGGerenciadorForms::GetForm(idForm)->TrataEvento(evento);
}

int PIGFormDesenha(const int idForm)
{
    return CPIGGerenciadorForms::GetForm(idForm)->Desenha();
}

void PIGFormMove(const int idForm, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorForms::GetForm(idForm)->Move(posicaoX, posicaoY);
}

void PIGDestroiForm(const int idForm)
{
    CPIGGerenciadorForms::DestroiForm(idForm);
}

int PIGFormGetIdPorComponente(const int idComponente)
{
    return CPIGGerenciadorForms::GetFormComponente(idComponente)->GetId();
}

int PIGFormGetIdComponenteLabel(const int idForm, const char *label)
{
    return CPIGGerenciadorForms::GetForm(idForm)->GetIdComponente(label);
}

int PIGFormGetIdComponenteIndice(const int idForm, const int indice)
{
    return CPIGGerenciadorForms::GetForm(idForm)->GetIdComponente(indice);
}

int PIGCriaComponentePorParametro(const int idForm, const char *parametros)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaComponentePorParametro(parametros);
}

void PIGComponentesDefineAcao(
        const int idComponente, const PIGFuncaoSimples funcao, void *parametro)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->DefineAcao(funcao, parametro);
}

void PIGComponentesSetLabel(const int idComponente, const char *novoLabel)
{
    CPIGGerenciadorForms::GetFormComponente(idComponente)
            ->GetComponente(idComponente)
            ->SetLabel(novoLabel);
}

void PIGComponentesGetLabel(const int idComponente, char *label)
{
    strcpy(label,
           (char *) (CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetLabel())
                   .c_str());
}

void PIGComponentesSetFonteLabel(const int idComponente, const int fonte)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetFonteLabel(fonte);
}

int PIGComponentesGetFonteLabel(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetFonteLabel();
}

void PIGComponentesSetCorLabel(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetCorLabel(cor);
}

PIGCor PIGComponentesGetCorLabel(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetCorLabel();
}

void PIGComponentesSetHint(const int idComponente, const char *hint)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetHint(hint);
}

void PIGComponentesGetHint(const int idComponente, char *hint)
{
    strcpy(hint,
           (char *) (CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetHint())
                   .c_str());
}

void PIGComponentesSetFonteHint(const int idComponente, const int fonte)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetFonteHint(fonte);
}

int PIGComponentesGetFonteHint(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetFonteHint();
}

void PIGComponentesSetCorHint(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetCorHint(cor);
}

PIGCor PIGComponentesGetCorHint(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetCorHint();
}

void PIGComponentesSetAudio(const int idComponente, const int idAudio)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetAudio(idAudio);
}

int PIGComponentesGetAudio(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetAudio();
}

void PIGComponentesMove(const int idComponente, const int posicaoX, const int posicaoY)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->Move(posicaoX, posicaoY);
}

void PIGComponentesGetXY(const int idComponente, int *posicaoX, int *posicaoY)
{
    const PIGPonto2D p = CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetXY();
    *posicaoX = p.x;
    *posicaoY = p.y;
}

void PIGComponentesDesloca(const int idComponente, const int x, const int y)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->Desloca(x, y);
}

void PIGComponentesSetDimensoes(const int idComponente, const int altura, const int largura)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetDimensoes(altura, largura);
}

void PIGComponentesGetDimensoes(const int idComponente, int &altura, int &largura)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetDimensoes(altura, largura);
}

void PIGComponentesSetPosicaoPadraoLabel(const int idComponente, const PIGPosicaoComponente pos)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetPosicaoPadraoLabel(pos);
}

void PIGComponentesSetPosicaoPersonalizadaLabel(const int idComponente, const int x, const int y)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)
            ->SetPosicaoPersonalizadaLabel(x, y);
}

void PIGComponentesSetHabilitado(const int idComponente, const int valor)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetHabilitado(valor);
}

int PIGComponentesGetHabilitado(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetHabilitado();
}

void PIGComponentesSetVisivel(const int idComponente, const int valor)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->SetVisivel(valor);
}

int PIGComponentesGetVisivel(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetVisivel();
}

int PIGComponentesGetAcionado(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetAcionado();
}

int PIGComponentesGetMouseOver(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetMouseOver();
}

PIGTipoComponente PIGComponenteGetTipo(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)->GetTipo();
}

void PIGComponentesSetMargens(
        const int idComponente, const int margemEsq, const int margemDir, const int margemBaixo,
        const int margemCima)
{
    CPIGGerenciadorForms::GetComponente<PIGComponente>(idComponente)
            ->SetMargens(margemEsq, margemDir, margemBaixo, margemCima);
}

int PIGCriaBotaoClick(
        const int idForm, const int altura, const int largura, const char *nomeArq,
        const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoClick(
            altura, largura, nomeArq, retiraFundo);
}

int PIGCriaBotaoClick(const int idForm, const int altura, const int largura)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoClick(altura, largura);
}

void PIGBotaoClickDefineAtalho(const int idComponente, const int teclaAtalho)
{
    CPIGGerenciadorForms::GetComponente<PIGBotaoClick>(idComponente)->DefineAtalho(teclaAtalho);
}

void PIGBotaoClickDefineTempoRepeticao(const int idComponente, const double segundos)
{
    CPIGGerenciadorForms::GetComponente<PIGBotaoClick>(idComponente)
            ->DefineTempoRepeticao(segundos);
}

void PIGBotaoClickDefineTempoAcionamento(const int idComponente, const double segundos)
{
    CPIGGerenciadorForms::GetComponente<PIGBotaoClick>(idComponente)
            ->DefineTempoAcionamento(segundos);
}

int PIGCriaBotaoOnOff(
        const int idForm, const int altura, const int largura, const char *nomeArq,
        const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoOnOff(
            altura, largura, nomeArq, retiraFundo);
}

int PIGCriaBotaoOnOff(const int idForm, const int altura, const int largura)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaBotaoOnOff(altura, largura);
}

void PIGBotaoOnOffDefineAtalho(const int idComponente, const int teclaAtalho)
{
    CPIGGerenciadorForms::GetComponente<PIGBotaoOnOff>(idComponente)->DefineAtalho(teclaAtalho);
}

int PIGCriaAreaDeTexto(
        const int idForm, const int altura, const int largura, const char *nomeArq,
        const int maxCars, const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(
            altura, largura, nomeArq, maxCars, retiraFundo);
}

int PIGCriaAreaDeTexto(const int idForm, const int altura, const int largura, const int maxCars)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaAreaDeTexto(altura, largura, maxCars);
}

void PIGAreaDeTextoSetFonteTexto(const int idComponente, const int fonte)
{
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetFonteTexto(fonte);
}

void PIGAreaDeTextoSetLinhasAbaixoTexto(const int idComponente, const int visivel)
{
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)
            ->SetLinhasAbaixoTexto(visivel);
}

void PIGAreaDeTextoSetEspacoEntreAsLinhas(const int idComponente, const int espaco)
{
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)
            ->SetEspacoEntreAsLinhas(espaco);
}

void PIGAreaDeTextoSetTexto(const int idComponente, const char *frase)
{
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetTexto(frase);
}

void PIGAreaDeTextoSetCorCursor(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->SetCorCursor(cor);
}

vector<string> PIGAreaDeTextoGetLinhasTexto(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->GetLinhasTexto();
}

void PIGAreaDeTextoGetTexto(const int idComponente, char *texto)
{
    strcpy(texto,
           (char *) (CPIGGerenciadorForms::GetComponente<PIGAreaDeTexto>(idComponente)->GetTexto())
                   .c_str());
}

int PIGCriaCampoTexto(
        const int idForm, const int altura, const int largura, const char *nomeArq,
        const int maxCars, const int apenasNumeros, const int senha, const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(
            altura, largura, nomeArq, maxCars, apenasNumeros, retiraFundo, senha);
}

int PIGCriaCampoTexto(
        const int idForm, const int altura, const int largura, const int maxCars,
        const int apenasNumeros, const int senha)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(
            altura, largura, maxCars, apenasNumeros, senha);
}

void PIGCampoTextoSetTexto(const int idComponente, const char *frase)
{
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIGCampoTextoSetFonteTexto(const int idComponente, const int fonte)
{
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIGCampoTextoSetCorCursor(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}

void PIGCampoTextoSetCorTexto(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorFonte(cor);
}

void PIGCampoTextoSetCorFundo(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorFundo(cor);
}

void PIGCampoTextoSetMascara(const int idComponente, const char mascara)
{
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetMascara(mascara);
}

void PIGCampoTextoGetTexto(const int idComponente, char *texto)
{
    strcpy(texto, (char *) (CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)
                                    ->GetTexto())
                          .c_str());
}

/*int PIGCriaCampoSenha(const int idForm, const int altura, const int largura, char* nomeArq, const
int maxCars = 200, bool apenasNumeros=false, const int retiraFundo=1){ return
CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(altura,largura,nomeArq,maxCars,apenasNumeros,retiraFundo,true);
}

int PIGCriaCampoSenha(const int idForm, const int altura, const int largura, const int maxCars =
200, bool apenasNumeros=false){ return
CPIGGerenciadorForms::GetForm(idForm)->CriaCampoTextoESenha(altura,largura,maxCars,apenasNumeros,true);
}

void PIGCampoSenhaSetTexto(const int idComponente, char* frase){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetTexto(frase);
}

void PIGCampoSenhaSetFonteTexto(const int idComponente, const int fonte){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetFonteTexto(fonte);
}

void PIGCampoSenhaSetCorCursor(const int idComponente, const PIGCor cor){
    CPIGGerenciadorForms::GetComponente<PIGCampoTextoESenha>(idComponente)->SetCorCursor(cor);
}*/

int PIGCriaListBox(
        const int idForm, const int larguraTotal, const int alturaLinha, const int alturaItem,
        const int largItem, const char *nomeArq, const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(
            larguraTotal, alturaLinha, alturaItem, largItem, nomeArq, retiraFundo);
}

int PIGCriaListBox(
        const int idForm, const int larguraTotal, const int alturaLinha, const int alturaItem,
        const int largItem)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaListBox(
            larguraTotal, alturaLinha, alturaItem, largItem);
}

void PIGListBoxCriaItem(
        const int idComponente, const char *texto, const char *imagemIcone, const char *imagemFundo,
        const char *hintMsg, const int itemHabilitado, const int retiraFundoImg,
        const int retiraFundoIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->CriaItem(
                    texto, imagemIcone, imagemFundo, false, itemHabilitado, hintMsg, retiraFundoImg,
                    retiraFundoIcone);
}

int PIGListBoxSetMarcadoItem(const int idComponente, const int indice, const int marcado)
{
    return CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->SetAcionadoItem(indice, marcado);
}

int PIGListBoxGetMarcadoItem(const int idComponente, const int indice)
{
    return CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->GetAcionadoItem(indice);
}

int PIGListBoxGetHabilitadoItem(const int idComponente, const int item)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetHabilitadoItem(item);
}

int PIGListBoxSetHabilitadoItem(const int idComponente, const int item, const int habilitado)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->SetHabilitadoItem(item, habilitado);
}

void PIGListBoxSetFonteItem(const int idComponente, const int fonte, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetFonteItem(fonte, item);
}

void PIGListBoxSetAudioItem(const int idComponente, const int audio, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetAudioItem(item, audio);
}

void PIGListBoxSetCorLabelItem(const int idComponente, const PIGCor cor, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->SetCorLabelItem(cor, item);
}

void PIGListBoxAlinhaLabelDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGListBoxAlinhaLabelEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGListBoxAlinhaLabelCentro(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGListBoxAlinhaIconeDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGListBoxAlinhaIconeEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGListBoxDefineDimensaoIconeItem(
        const int idComponente, const int alturaIcone, const int larguraIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
            ->SetDimensoesIcone(alturaIcone, larguraIcone);
}

void PIGListBoxGetLabelItem(const int idComponente, const int indice, char *label)
{
    strcpy(label, CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)
                          ->GetLabelItem(indice)
                          .c_str());
}

int PIGListBoxGetItemDestaque(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGListBox>(idComponente)->GetItemDestaque();
}

int PIGCriaDropDown(
        const int idForm, const int larguraTotal, const int alturaLinha, const int alturaItem,
        const int larguraItem, const char *nomeArq, const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(
            larguraTotal, alturaLinha, alturaItem, larguraItem, nomeArq, retiraFundo);
}

int PIGCriaDropDown(
        const int idForm, const int larguraTotal, const int alturaLinha, const int alturaItem,
        const int larguraItem)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaDropDown(
            larguraTotal, alturaLinha, alturaItem, larguraItem);
}

void PIGDropDownCriaItem(
        const int idComponente, const char *texto, const char *imagemIcone, const char *imagemFundo,
        const char *hintMsg, const int itemHabilitado, const int retiraFundoImg,
        const int retiraFundoIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->CriaItem(
                    texto, imagemIcone, imagemFundo, itemHabilitado, hintMsg, retiraFundoImg,
                    retiraFundoIcone);
}

int PIGDropDownSetMarcadoItem(const int idComponente, const int indice, const int marcado)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->SetAcionadoItem(indice, marcado);
}

int PIGDropDownGetMarcadoItem(const int idComponente, const int indice)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetAcionadoItem(indice);
}

int PIGDropDownGetHabilitadoItem(const int idComponente, const int item)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetHabilitadoItem(item);
}

int PIGDropDownSetHabilitadoItem(const int idComponente, const int item, const int habilitado)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->SetHabilitadoItem(item, habilitado);
}

void PIGDropDownSetFonteItem(const int idComponente, const int fonte, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetFonteItem(fonte, item);
}

void PIGDropDownSetAudioItem(const int idComponente, const int audio, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetAudioItem(item, audio);
}

void PIGDropDownSetCorLabelItem(const int idComponente, const PIGCor cor, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->SetCorLabelItem(cor, item);
}

void PIGDropDownAlinhaLabelDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGDropDownAlinhaLabelEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGDropDownAlinhaLabelCentro(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGDropDownAlinhaIconeDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGDropDownAlinhaIconeEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGDropDownDefineDimensaoIconeItem(
        const int idComponente, const int alturaIcone, const int larguraIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
            ->SetDimensoesIcone(alturaIcone, larguraIcone);
}

void PIGDropDownGetLabelItem(const int idComponente, const int indice, char *label)
{
    strcpy(label, CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)
                          ->GetLabelItem(indice)
                          .c_str());
}

int PIGDropDownGetItemDestaque(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGDropDown>(idComponente)->GetItemDestaque();
}

int PIGCriaRadioBox(
        const int idForm, const int larguraTotal, const int alturaLinha, const char *imagemItem,
        const int alturaItem, const int larguraItem, const char *imagemFundo, const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(
            larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem, imagemFundo,
            retiraFundo);
}

int PIGCriaRadioBox(
        const int idForm, const int larguraTotal, const int alturaLinha, const char *imagemItem,
        const int alturaItem, const int larguraItem)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaRadioBox(
            larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem);
}

void PIGRadioBoxCriaItem(
        const int idComponente, const char *itemLabel, const char *imagemFundo, const char *hintMsg,
        const int itemHabilitado, const int retiraFundo, const int retiraFundoIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->CriaItem(
                    itemLabel, imagemFundo, itemHabilitado, hintMsg, retiraFundo, retiraFundoIcone);
}

int PIGRadioBoxSetMarcadoItem(const int idComponente, const int indice, const int marcado)
{
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->SetAcionadoItem(indice, marcado);
}

int PIGRadioBoxGetMarcadoItem(const int idComponente, const int indice)
{
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetAcionadoItem(indice);
}

int PIGRadioBoxGetHabilitadoItem(const int idComponente, const int item)
{
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetHabilitadoItem(item);
}

int PIGRadioBoxSetHabilitadoItem(const int idComponente, const int item, const int habilitado)
{
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->SetHabilitadoItem(item, habilitado);
}

void PIGRadioBoxSetAudioItem(const int idComponente, const int item, const int audio)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetAudioItem(item, audio);
}

void PIGRadioBoxSetFonteItem(const int idComponente, const int fonte, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetFonteItem(fonte, item);
}

void PIGRadioBoxSetCorLabelItem(const int idComponente, const PIGCor cor, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->SetCorLabelItem(cor, item);
}

void PIGRadioBoxAlinhaLabelDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGRadioBoxAlinhaLabelEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGRadioBoxAlinhaLabelCentro(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGRadioBoxAlinhaIconeDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGRadioBoxAlinhaIconeEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGRadioBoxDefineDimensaoIconeItem(
        const int idComponente, const int alturaIcone, const int larguraIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
            ->SetDimensoesIcone(alturaIcone, larguraIcone);
}

int PIGRadioBoxGetItemDestaque(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)->GetItemDestaque();
}

void PIGRadioBoxGetLabelItem(const int idComponente, const int indice, char *label)
{
    strcpy(label, CPIGGerenciadorForms::GetComponente<PIGRadioBox>(idComponente)
                          ->GetLabelItem(indice)
                          .c_str());
}

int PIGCriaCheckBox(
        const int idForm, const int larguraTotal, const int alturaLinha, const char *imagemItem,
        const int alturaItem, const int larguraItem, const char *imagemFundo, const int retiraFundo)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(
            larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem, imagemFundo,
            retiraFundo);
}

int PIGCriaCheckBox(
        const int idForm, const int larguraTotal, const int alturaLinha, const char *imagemItem,
        const int alturaItem, const int larguraItem)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaCheckBox(
            larguraTotal, alturaLinha, imagemItem, alturaItem, larguraItem);
}

void PIGCheckBoxCriaItem(
        const int idComponente, const char *itemLabel, const char *imagemFundo, const char *hintMsg,
        const int itemMarcado, const int itemHabilitado, const int retiraFundo,
        const int retiraFundoIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->CriaItem(
                    itemLabel, imagemFundo, itemMarcado, itemHabilitado, hintMsg, retiraFundo,
                    retiraFundoIcone);
}

int PIGCheckBoxSetMarcadoItem(const int idComponente, const int indice, const int marcado)
{
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->SetAcionadoItem(indice, marcado);
}

int PIGCheckBoxGetMarcadoItem(const int idComponente, const int indice)
{
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetAcionadoItem(indice);
}

int PIGCheckBoxGetHabilitadoItem(const int idComponente, const int item)
{
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetHabilitadoItem(item);
}

int PIGCheckBoxSetHabilitadoItem(const int idComponente, const int item, const int habilitado)
{
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->SetHabilitadoItem(item, habilitado);
}

void PIGCheckBoxSetAudioItem(const int idComponente, const int item, const int audio)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetAudioItem(item, audio);
}

void PIGCheckBoxSetFonteItem(const int idComponente, const int fonte, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetFonteItem(fonte, item);
}

void PIGCheckBoxSetCorLabelItem(const int idComponente, const PIGCor cor, const int item)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetCorLabelItem(cor, item);
}

void PIGCheckBoxAlinhaLabelDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_DIR_CENTRO);
}

void PIGCheckBoxAlinhaLabelEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_ESQ_CENTRO);
}

void PIGCheckBoxAlinhaLabelCentro(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->AlinhaLabelItens(PIG_POSICAO_CENTRO_CENTRO);
}

void PIGCheckBoxAlinhaIconeDireita(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_DIR_CENTRO);
}

void PIGCheckBoxAlinhaIconeEsquerda(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->AlinhaIcones(PIG_POSICAO_ESQ_CENTRO);
}

void PIGCheckBoxDefineDimensaoIconeItem(
        const int idComponente, const int alturaIcone, const int larguraIcone)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
            ->SetDimensoesIcone(alturaIcone, larguraIcone);
}

void PIGCheckBoxSetMarcadoTodos(const int idComponente, const int marcado)
{
    CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->SetAcionadoTodos(marcado);
}

void PIGCheckBoxGetLabelItem(const int idComponente, const int indice, char *label)
{
    strcpy(label, CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)
                          ->GetLabelItem(indice)
                          .c_str());
}

vector<int> PIGCheckBoxGetItensMarcados(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGCheckBox>(idComponente)->GetItensMarcados();
}

int PIGCriaGaugeBar(
        const int idForm, const int altura, const int largura, const char *imgMoldura,
        const char *imgMarcador, const int retiraFundoMoldura, const int retiraFundoMarcador)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeBar(
            altura, largura, imgMoldura, imgMarcador, retiraFundoMoldura, retiraFundoMarcador);
}

int PIGCriaGaugeBar(const int idForm, const int altura, const int largura)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeBar(altura, largura);
}

void PIGGaugeBarSetDelta(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetDelta(valor);
}

void PIGGaugeBarAvancaDelta(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->AvancaDelta();
}

double PIGGaugeBarGetPorcentagemConcluida(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)
            ->GetPorcentagemConcluida();
}

void PIGGaugeBarSetPorcentagemConcluida(const int idComponente, const double porcentagem)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)
            ->SetPorcentagemConcluida(porcentagem);
}

void PIGGaugeBarMinimizaValor(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->MinimizaValorAtual();
}

void PIGGaugeBarMaximizaValor(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->MaximizaValorAtual();
}

void PIGGaugeBarSetValorMin(const int idComponente, const double minimo)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetValorMin(minimo);
}

void PIGGaugeBarSetValorMax(const int idComponente, const double maximo)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetValorMax(maximo);
}

double PIGGaugeBarGetValorAtual(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetValorAtual();
}

void PIGGaugeBarSetValorAtual(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetValorAtual(valor);
}

void PIGGaugeBarAvancaBarra(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->AvancaMarcador(valor);
}

int PIGGaugeBarGetValorMax(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetValorMax();
}

int PIGGaugeBarGetValorMin(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->GetValorMin();
}

void PIGGaugeBarSetOrientacao(const int idComponente, const PIGGaugeCrescimento orientacao)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetOrientacao(orientacao);
}

void PIGGaugeBarSetMarcadorFrente(const int idComponente, const int frente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetMarcadorFrente(frente);
}

void PIGGaugeBarSetCorInicial(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetCorInicial(cor);
}

void PIGGaugeBarSetCorFinal(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetCorFinal(cor);
}

void PIGGaugeBarSetCorTrilha(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeBar>(idComponente)->SetCorTrilha(cor);
}

int PIGCriaGaugeCircular(const int idForm, const int altura, const int largura)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeCircular(altura, largura);
}

int PIGCriaGaugeCircular(
        const int idForm, const int altura, const int largura, const string &imgTrilha,
        const int alturaMarcador, const int larguraMarcador, const string &imgMarcador,
        const int retiraFundoTrilha, const int retiraFundoMarcador)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaGaugeCircular(
            altura, largura, imgTrilha, alturaMarcador, larguraMarcador, imgMarcador,
            retiraFundoTrilha, retiraFundoMarcador);
}

void PIGGaugeCircularSetDelta(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetDelta(valor);
}

void PIGGaugeCircularAvancaDelta(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->AvancaDelta();
}

double PIGGaugeCircularGetPorcentagemConcluida(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)
            ->GetPorcentagemConcluida();
}

void PIGGaugeCircularSetPorcentagemConcluida(const int idComponente, const double porcentagem)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)
            ->SetPorcentagemConcluida(porcentagem);
}

void PIGGaugeCircularMinimizaValor(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->MinimizaValorAtual();
}

void PIGGaugeCircularMaximizaValor(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->MaximizaValorAtual();
}

void PIGGaugeCircularSetValorMax(const int idComponente, const double novoValor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetValorMax(novoValor);
}

void PIGGaugeCircularSetValorMin(const int idComponente, const double novoValor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetValorMin(novoValor);
}

int PIGGaugeCircularGetValorAtual(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetValorAtual();
}

void PIGGaugeCircularSetValorAtual(const int idComponente, const int novoValor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetValorAtual(novoValor);
}

void PIGGaugeCircularAvancaBarra(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->AvancaMarcador(valor);
}

int PIGGaugeCircularGetValorMax(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetValorMax();
}

int PIGGaugeCircularGetValorMin(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->GetValorMin();
}

void PIGGaugeCircularSetOrientacao(const int idComponente, const PIGGaugeCrescimento orientacao)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetOrientacao(orientacao);
}

void PIGGaugeCircularSetMarcadorFrente(const int idComponente, const int frente)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetMarcadorFrente(frente);
}

void PIGGaugeCircularSetCorInicial(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetCorInicial(cor);
}

void PIGGaugeCircularSetCorFinal(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetCorFinal(cor);
}

void PIGGaugeCircularSetCorTrilha(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetCorTrilha(cor);
}

void PIGGaugeCircularSetRaioInterno(const int idComponente, const int valorRaio)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetRaioInterno(valorRaio);
}

void PIGGaugeCircularSetAnguloBase(const int idComponente, const double novoAng)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetAnguloBase(novoAng);
}

void PIGGaugeCircularSetDeltaAngulo(const int idComponente, const double novoDelta)
{
    CPIGGerenciadorForms::GetComponente<PIGGaugeCircular>(idComponente)->SetDeltaAngulo(novoDelta);
}

int PIGCriaSlideBar(
        const int idForm, const int altura, const int largura, const string &imgTrilha,
        const int alturaMarcador, const int larguraMarcador, const string &imgMarcador,
        const int retiraFundoTrilha, const int retiraFundoMarcador)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaSlideBar(
            altura, largura, imgTrilha, alturaMarcador, larguraMarcador, imgMarcador,
            retiraFundoTrilha, retiraFundoMarcador);
}

int PIGCriaSlideBar(
        const int idForm, const int altura, const int largura, const int alturaMarcador,
        const int larguraMarcador)
{
    return CPIGGerenciadorForms::GetForm(idForm)->CriaSlideBar(
            altura, largura, alturaMarcador, larguraMarcador);
}

void PIGSlideBarSetDelta(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetDelta(valor);
}

void PIGSlideBarAvancaDelta(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->AvancaDelta();
}

double PIGSlideBarGetPorcentagemConcluida(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)
            ->GetPorcentagemConcluida();
}

void PIGSlideBarSetPorcentagemConcluida(const int idComponente, const double porcentagem)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)
            ->SetPorcentagemConcluida(porcentagem);
}

void PIGSlideBarMinimizaValor(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->MinimizaValorAtual();
}

void PIGSlideBarMaximizaValor(const int idComponente)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->MaximizaValorAtual();
}

void PIGSlideBarSetValorMin(const int idComponente, const double minimo)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetValorMin(minimo);
}

void PIGSlideBarSetValorMax(const int idComponente, const double maximo)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetValorMax(maximo);
}

double PIGSlideBarGetValorAtual(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetValorAtual();
}

void PIGSlideBarSetValorAtual(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetValorAtual(valor);
}

void PIGSlideBarAvancaBarra(const int idComponente, const double valor)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->AvancaMarcador(valor);
}

int PIGSlideBarGetValorMax(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetValorMax();
}

int PIGSlideBarGetValorMin(const int idComponente)
{
    return CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->GetValorMin();
}

void PIGSlideBarSetOrientacao(const int idComponente, const PIGGaugeCrescimento orientacao)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetOrientacao(orientacao);
}

void PIGSlideBarSetMarcadorFrente(const int idComponente, const int frente)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetMarcadorFrente(frente);
}

void PIGSlideBarSetCorInicial(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetCorInicial(cor);
}

void PIGSlideBarSetCorFinal(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetCorFinal(cor);
}

void PIGSlideBarSetCorTrilha(const int idComponente, const PIGCor cor)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)->SetCorTrilha(cor);
}

void PIGSlideBarSetDeltas(
        const int idComponente, const int deltaPadrao, const int deltaRodinha,
        const int deltaTeclado)
{
    CPIGGerenciadorForms::GetComponente<PIGSlideBar>(idComponente)
            ->SetDeltas(deltaPadrao, deltaRodinha, deltaTeclado);
}

#endif // PIGCOMFORM

#ifdef PIGCOMTELA

void PIGCriaTela(
        const int idTela, const int backgroundCriar, const int backgroundCarregar,
        const char *nomeArqCarregamento, const int janela)
{
    CPIGGerenciadorTelas::CriaTela(
            idTela, backgroundCriar, backgroundCarregar, nomeArqCarregamento, janela);
}

void PIGDestroiTela(const int idTela)
{
    CPIGGerenciadorTelas::DestroiTela(idTela);
}

void PIGDefineComportamentoTela(
        const int idTela, void *dados, const PIGFuncaoSimples criar,
        const PIGFuncaoSimples destruir, const PIGFuncaoSimples carregar,
        const PIGFuncaoSimples descarregar, const PIGFuncaoSimples atualizar,
        const PIGFuncaoSimples desenhar, const PIGFuncaoEvento tratarEvento)
{
    CPIGGerenciadorTelas::SetComportamento(
            idTela, dados, criar, destruir, carregar, descarregar, atualizar, desenhar,
            tratarEvento);
}

void PIGTrataEventoTelaAtual(const PIGEvento &evento)
{
    CPIGGerenciadorTelas::TrataEvento(evento);
}

int PIGAtualizaTelaAtual()
{
    return CPIGGerenciadorTelas::Atualiza();
}

int PIGDesenhaTelaAtual()
{
    return CPIGGerenciadorTelas::Desenha();
}

void PIGMudaTelaAtual(const int idTela, const double tempoSaida, const bool destroiDescarregar)
{
    CPIGGerenciadorTelas::PreparaMudancaTela(idTela, tempoSaida, destroiDescarregar);
}

void PIGSetDadosGeraisTelas(void *param)
{
    CPIGGerenciadorTelas::SetDadosGerais(param);
}

void *PIGGetDadosGeraisTelas()
{
    return CPIGGerenciadorTelas::GetDadosGerais();
}

PIGEstadoTela PIGGetEstadoTela(const int idTela)
{
    return CPIGGerenciadorTelas::GetEstadoTela(idTela);
}

#endif // PIGCOMTELA
