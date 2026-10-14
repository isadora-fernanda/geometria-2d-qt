#ifndef GEO_H
#define GEO_H

#include <QWidget>
#include <QColor>
#include <QColorDialog>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <qdebug.h>
#include <math.h>
#include <QSpinBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QBrush>
#include <QFileDialog>
#include <QPen>
#include <QStringList>
#include <string>
#include <QFile>
#include <QPushButton>

#define TAM_JAN 500
#define PI 3.14159265

using namespace std;

class GEO : public QWidget{
    Q_OBJECT
protected:
        QString Nome;
        double x;
        double y;
        double area;
        QColor cor;
public:
    virtual void Area() = 0;
    QString getNome();
    double getX();
    double getY();
    QColor getCor();
    explicit GEO(QWidget *parent = nullptr);
signals:

public slots:
        void setCor();
};
class Circulo : public GEO{

    Q_OBJECT
    int r;
public:
    Circulo();
    Circulo(QString, double, double, int, QColor);
    void Area();
    int getR();
    double getArea();
signals:

public slots:
};
class Retang : public GEO{

    Q_OBJECT
    double x2;
    double y2;

public:
    Retang();
    Retang(QString,double,double,double,double,QColor);
    double getX2();
    double getY2();
    double getArea();
signals:

public slots:
    void Area();
};
class Ponto: public QWidget{
    Q_OBJECT
    QString Nome;
    double x;
    double y;
    QColor cor;
public:
    Ponto();
    Ponto(QString, double, double,QColor);
    double getX();
    double getY();
    QColor getCor();
    QString getNome();
    double getDist(Ponto *);
    double getDist(Circulo *);
signals:

public slots:
    void setCor();

};

#endif // GEO_H
