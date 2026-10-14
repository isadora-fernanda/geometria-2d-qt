#ifndef JANELA_H
#define JANELA_H

#include "geo.h"

class Janela : public QWidget
{
    Q_OBJECT
public:
    map<QString,Circulo*> Circulo_map;
    map<QString,Retang*> Retangulo_map;
    map<QString,Ponto*> Ponto_map;

    map<QString,Circulo*>::iterator it_circulo;
    map<QString,Retang*>::iterator it_retangulo;
    map<QString,Ponto*>::iterator it_ponto;

    QString nome;
    double ORIGX;
    double ORIGY;
    double Zoom;

    explicit Janela(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void salvar_dados();
    void abrir_dados();
    void Insere_Circulo();
    void Insere_Retang();
    void Insere_Ponto();
    void Remove_Circulo();
    void Remove_Retang();
    void Remove_Ponto();
    void Area_Circulo();
    void Area_Retang();
    void Dist();

    void Deslocar_Orig();
    void Zoom_Mais();
    void Zoom_Menos();
    void novo();
};

#endif // JANELA_H
