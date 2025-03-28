#include <dirent.h>

#include <algorithm>

#include <pig/PIGFuncoesBasicas.h>

thread::id PIG_MAIN_THREAD_ID = this_thread::get_id();

// separa uma string em palavras, usando os delimitadores indicados
vector<string> PIGSeparaPalavras(const string &texto, const string &delim)
{
    vector<string> resp;
    string strAtual;

    for (char i: texto)
    {

        if (delim.find(i) != std::string::npos)
        { // achou delimitadores
            resp.push_back(strAtual);

            strAtual = i;
            if (i != '\n')
            {
                resp.push_back(strAtual);
                strAtual = "";
            }
        }
        else
        {
            strAtual += i;
        }
    }

    if (!strAtual.empty())
    {
        resp.push_back(strAtual);
    }
    return resp;
}

// verifica se uma string possui apenas digitos de 0 a 9
bool PIGSomenteNumeros(const string &frase)
{
    for (char i: frase)
    {
        if (i < '0' || i > '9')
        {
            return false;
        }
    }
    return true;
}

// verifica se duas cores são iguais
bool PIGCoresIguais(const PIGCor cor1, const PIGCor cor2)
{
    return cor1.r == cor2.r && cor1.g == cor2.g && cor1.b == cor2.b && cor1.a == cor2.a;
}

bool operator==(const PIGCor cor1, const PIGCor cor2)
{
    return cor1.r == cor2.r && cor1.g == cor2.g && cor1.b == cor2.b && cor1.a == cor2.a;
}

PIGCor operator*(const PIGCor cor, const double fator)
{
    return {(uint8_t) (cor.r * fator), (uint8_t) (cor.g * fator), (uint8_t) (cor.b * fator)};
}

PIGCor operator+(const PIGCor cor1, const PIGCor cor2)
{
    return {(uint8_t) (cor1.r + cor2.r), (uint8_t) (cor1.g + cor2.g), (uint8_t) (cor1.b + cor2.b)};
}

// cria uma cor a partir de uma string com um valor hexadecimal de 8 algarismos RRGGBBAA. Ex:
// 0xFF0000FF (vermelho)
PIGCor PIGCriaCorHexa(const string &stringHexa)
{
    unsigned long total =
            strtoul(stringHexa.c_str(), 0, 16); // transforma a string em um inteiro (decimal)
    PIGCor cor;
    cor.a = total % 256;
    total /= 256;
    cor.b = total % 256;
    total /= 256;
    cor.g = total % 256;
    total /= 256;
    cor.r = total % 256;
    return cor;
}

// cria uma cor a partir de uma string com um valor hexadecimal de 8 algarismos RRGGBBAA. Ex:
// 0xFF0000FF (vermelho)
PIGCor PIGCriaCorString(const string &str)
{
    PIGCor cor;
    const char *p = strtok((char *) str.c_str(), ",");
    cor.r = stoi(p);
    p = strtok(NULL, ",");
    cor.g = stoi(p);
    p = strtok(NULL, ",");
    cor.b = stoi(p);
    p = strtok(NULL, ",");
    cor.a = stoi(p);
    return cor;
}

// troca a posição dos bytes de uma word(16bits)
uint16_t PIGTroca2Bytes(const uint16_t valor)
{
    return (valor / 256) + ((valor % 256) * 256);
}

// mistura duas cores com uma proporção entre elas
PIGCor PIGMixCor(const PIGCor iniCor, const PIGCor fimCor, const double porc)
{
    PIGCor resp;
    resp.r = fimCor.r * porc + (iniCor.r) * (1 - porc);
    resp.g = fimCor.g * porc + (iniCor.g) * (1 - porc);
    resp.b = fimCor.b * porc + (iniCor.b) * (1 - porc);
    resp.a = fimCor.a * porc + (iniCor.a) * (1 - porc);
    return resp;
}

// retorna o diretorio onde está o executável
string PIGGetDiretorioAtual()
{
    char *dir = SDL_GetBasePath();
    if (dir)
    {
        string resp(dir);
        CHDIR(dir);
        free(dir);
        return resp;
    }
    return "./";
}

// retorna "valor" limitado entre [vMin, vMax]
int PIGLimitaValor(const int valor, const int minimo, const int maximo)
{
    if (valor < minimo)
    {
        return minimo; // valor não pode ficar menor que o mínimo informado
    }
    if (valor > maximo)
    {
        return maximo; // valor não pode ficar maior que o máximo informado
    }
    return valor;
}

// retorna "valor" limitado entre [vMin, vMax]
double PIGLimitaValor(const double valor, const double minimo, const double maximo)
{
    if (valor < minimo)
    {
        return minimo; // valor não pode ficar menor que o mínimo informado
    }
    if (valor > maximo)
    {
        return maximo; // valor não pode ficar maior que o máximo informado
    }
    return valor;
}

// cria uma lista de strings contendo o nome do arquivos de um diret�rio
vector<string> PIGListaArquivosDiretorio(const string &path)
{
    vector<string> resp;
    DIR *dir = opendir(path.c_str());

    if (dir != NULL)
    {
        dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            resp.emplace_back(entry->d_name);
        }
        closedir(dir);
    }
    return resp;
}

void PIGCalculaBoundingBox(
        const int px[], const int py[], const int lados, int *altura, int *largura, int *centroX,
        int *centroY)
{
    int minX = INT_MAX, maxX = -1, minY = INT_MAX, maxY = -1;
    *centroX = 0, *centroY = 0;

    // calcula o bounding-box do poligono
    for (int i = 0; i < lados; i++)
    {
        minX = std::min(px[i], minX);
        minY = std::min(py[i], minY);
        maxX = std::max(px[i], maxX);
        maxY = std::max(py[i], maxY);
        *centroX += px[i]; // centro do poligono
        *centroY += py[i]; // centro do poligono
    }
    *centroX /= lados; // centro do poligono
    *centroY /= lados; // centro do poligono

    *altura = maxY - minY + 1; // altura absoluta do poligono
    *largura = maxX - minX + 1; // altura absoluta do poligono
}

int PIGArredondaProximo(const float valor)
{
    const int resultado = (int) valor;
    if (valor - resultado >= 0.5)
    {
        return valor + 1;
    }
    return valor;
}

double PIGProjecaoY(const double coefAngular, const PIGPonto2D p)
{
    if (std::isinf(coefAngular))
    {
        return (double) p.y;
    }
    return (coefAngular * (-p.x)) + p.y;
}

double PIGProjecaoX(const double coefAngular, const PIGPonto2D p)
{
    if (std::isinf(coefAngular))
    {
        return (double) p.x;
    }
    /*if (!swapei){
        char str[100]="";
        sprintf(str,"PIGPROJX %f %f %f %f\n",coefAngular,coefAngular*p.x,-p.y + (coefAngular *
    p.x),(-p.y + (coefAngular * p.x)) / coefAngular); vet.push_back(str);
    }*/
    return (-p.y + (coefAngular * p.x)) / coefAngular;
}

double PIGMinVetor(const double vetor[], const int tamVetor)
{
    double menor = vetor[0];
    for (int i = 1; i < tamVetor; i++)
    {
        menor = std::min(vetor[i], menor);
    }
    return menor;
}

double PIGMaxVetor(const double vetor[], const int tamVetor)
{
    double maior = vetor[0];
    for (int i = 1; i < tamVetor; i++)
    {
        maior = std::max(vetor[i], maior);
    }
    return maior;
}

double PIGDistancia(const PIGPonto2D a, const PIGPonto2D b)
{
    const double deltaX = (b.x - a.x);
    const double deltaY = (b.y - a.y);
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

bool PIGValorEntre(const int x, const int a, const int b)
{
    return (((x > a) && (x < b)) || ((x < a) && (x > b)));
}
