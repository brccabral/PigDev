#include <pig/CPIGGeradorPoligonos.h>

void CPIGGeradorPoligonos::GeraPoligonoRegular(int raio, int lados, PIGCor cor)
{
    off = new CPIGOffscreenRenderer((raio * 2) + 3, (raio * 2) + 3);
    off->PintarFundo(PRETO);
    int centroX = raio + 1;
    int centroY = raio + 1;
    double ang = 90.0;
    vector<int> x(lados + 1);
    vector<int> y(lados + 1);

    for (int i = 0; i <= lados; i++, ang += 360.0 / lados)
    {
        double rad = ang * M_PI / 180;
        x[i] = cos(rad) * raio + centroX;
        y[i] = sin(rad) * raio + centroY;
        // printf("%d,%d\n",x[i],raio*2+3-y[i]);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }

    off->PintarArea(centroX, centroY, cor);
    // off->EncerrarDesenho();
    off->SalvarImagemBMP("poli.bmp");

    delete off;
}

void CPIGGeradorPoligonos::GeraRetanguloChanfrado(int altura, int largura, int chanfro, PIGCor cor)
{
    off = new CPIGOffscreenRenderer(altura, largura);
    off->PintarFundo(PRETO);

    off->DesenharRetangulo(chanfro, 0, altura, largura - (chanfro * 2), cor);
    off->DesenharRetangulo(0, chanfro, altura - (chanfro * 2), largura, cor);

    int centroX = chanfro;
    int centroY = altura - chanfro;
    int lados = 20;
    double rad, ang = 90.0;
    vector<int> x(lados + 1);
    vector<int> y(lados + 1);


    for (int i = 0; i <= lados; i++, ang += 360.0 / (lados * 4))
    {
        rad = ang * M_PI / 180;
        x[i] = cos(rad) * chanfro + centroX;
        y[i] = sin(rad) * chanfro + centroY;
        // printf("%d,%d\n",x[i],raio*2+3-y[i]);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }

    off->PintarArea(centroX - 1, centroY + 1, cor);

    centroY = chanfro + 1;
    ang = 180;
    for (int i = 0; i <= lados; i++, ang += 360.0 / (lados * 4))
    {
        rad = ang * M_PI / 180;
        x[i] = cos(rad) * chanfro + centroX;
        y[i] = sin(rad) * chanfro + centroY;
        printf("%d,%d\n", x[i], altura - y[i]);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }
    // printf("11\n");
    off->PintarArea(centroX - 1, centroY - 1, cor);
    // printf("22\n");
    ang = 270;
    centroX = largura - chanfro;
    for (int i = 0; i <= lados; i++, ang += 360.0 / (lados * 4))
    {
        rad = ang * M_PI / 180;
        x[i] = cos(rad) * chanfro + centroX;
        y[i] = sin(rad) * chanfro + centroY;
        // printf("%d,%d\n",x[i],raio*2+3-y[i]);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }

    off->PintarArea(centroX + 1, centroY - 1, cor);

    ang = 0;
    centroY = altura - chanfro;
    for (int i = 0; i <= lados; i++, ang += 360.0 / (lados * 4))
    {
        rad = ang * M_PI / 180;
        x[i] = cos(rad) * chanfro + centroX;
        y[i] = sin(rad) * chanfro + centroY;
        // printf("%d,%d\n",x[i],raio*2+3-y[i]);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }

    off->PintarArea(centroX + 1, centroY + 1, cor);
    // off->EncerrarDesenho();
    off->SalvarImagemBMP("chanfro.bmp");

    delete off;
}

void CPIGGeradorPoligonos::GeraEstrela(int raio, int pontas, PIGCor cor)
{
    int lados = 2 * pontas;
    off = new CPIGOffscreenRenderer((raio * 2) + 3, (raio * 2) + 3);
    off->PintarFundo(PRETO);
    int centroX = raio + 1;
    int centroY = raio + 1;
    double ang = 90.0;
    vector<int> x(lados + 1);
    vector<int> y(lados + 1);

    for (int i = 0; i <= lados; i++, ang += 360.0 / lados)
    {
        double rad = ang * M_PI / 180;
        x[i] = cos(rad) * (raio / (1.0 + (i % 2))) + centroX;
        y[i] = sin(rad) * (raio / (1.0 + (i % 2))) + centroY;
        // printf("%d,%d\n",x[i],raio*2+3-y[i]);
    }

    for (int i = 0; i < lados; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }

    off->PintarArea(centroX, centroY, cor);
    // off->EncerrarDesenho();
    off->SalvarImagemBMP("poli2.bmp");

    delete off;
}

void CPIGGeradorPoligonos::GeraCirculoAberto(int raio, int angulo, PIGCor cor)
{
    off = new CPIGOffscreenRenderer((raio * 2) + 3, (raio * 2) + 3);
    off->PintarFundo(PRETO);
    int centroX = raio + 1;
    int centroY = raio + 1;
    vector<int> x(angulo + 1);
    vector<int> y(angulo + 1);

    for (int ang = 0; ang <= angulo; ang++)
    {
        double rad = (ang + 90) * M_PI / 180;
        x[ang] = cos(rad) * raio + centroX;
        y[ang] = sin(rad) * raio + centroY;
        // printf("%d,%d\n",x[i],raio*2+3-y[i]);
    }

    for (int i = 0; i < angulo; i++)
    {
        off->DesenharLinha(x[i], y[i], x[i + 1], y[i + 1], cor);
    }

    off->DesenharLinha(centroX, centroY, x[0], y[0], cor);
    off->DesenharLinha(centroX, centroY, x[angulo], y[angulo], cor);

    off->PintarArea(x[0] - 1, y[0] - 2, cor);
    // off->EncerrarDesenho();
    off->SalvarImagemBMP("poli.bmp");

    delete off;
}
