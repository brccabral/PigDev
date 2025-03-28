#ifndef _CPIGOBJETO_
#define _CPIGOBJETO_

#include <string>
#include <vector>

using namespace std;

#include <SDL.h>

#include <pig/PIGTipos.h>
#include <pig/PIGFuncoesBasicas.h>
#include <pig/CPIGSprite.h>
#include <pig/CPIGAtributos.h>
#include <pig/CPIGOffscreenRenderer.h>


typedef enum
{
    PIG_COLISAO_NENHUMA,
    PIG_COLISAO_OOBB,
    PIG_COLISAO_POLIGONO,
    PIG_COLISAO_CIRCULAR
} PIGModoColisao;

class CPIGObjeto : public CPIGSprite, public CPIGAtributos
{

protected:

    PIGPonto2D bb[4] = {};
    int raio = {};
    PIGModoColisao modo = {};

    vector<PIGPonto2D> vertices;
    vector<PIGPonto2D> verticesOriginais;
    bool bbAlterado;

    void DesenhaBB();
    void DesenhaPoligono(PIGCor cor);
    void DesenhaCircular(PIGCor cor) const;
    void AtualizaBB();
    void AtualizaVertices();
    void Atualiza();
    bool ColisaoCirculoPoligono(vector<PIGPonto2D> vertices) const;

public:

    CPIGObjeto(
            int idObjeto, const string &nomeArquivo, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int janela = 0);
    CPIGObjeto(
            int idObjeto, PIGOffscreenRenderer offRender, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int janela = 0);
    CPIGObjeto(
            int idObjeto, const CPIGObjeto *objBase, int retiraFundo = 1,
            const PIGCor *corFundo = NULL, int janela = 0);
    ~CPIGObjeto() override;

    void SetVertices(const vector<PIGPonto2D> &verts);
    void SetAngulo(double a) override;
    void SetRaioColisaoCircular(int raio);
    void SetModoColisao(PIGModoColisao valor);
    PIGPonto2D GetBB(int i) const;
    vector<PIGPonto2D> GetVertices();
    int GetRaio() const;
    PIGModoColisao GetModoColisao() const;
    void Move(double nx, double ny) override;
    void Desloca(double dx, double dy) override;
    int Desenha() override;
    virtual bool Colisao(CPIGObjeto *outro);
    bool PontoDentro(PIGPonto2D p);

private:

    static bool Intersecao(int i, int f, const vector<PIGPonto2D> &v, PIGPonto2D p);
    bool ColisaoCircular(CPIGObjeto *outro) const;
    bool ColisaoOOBB(const CPIGObjeto *outro);
    bool ColisaoPoligono(const vector<PIGPonto2D> &vertices);
};

typedef CPIGObjeto *PIGObjeto;
#endif // _CPIGOBJETO_
