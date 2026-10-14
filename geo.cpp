#include "geo.h"

GEO::GEO(QWidget *parent) : QWidget(parent)
{

}
double GEO::getX(){return x;}
double GEO::getY(){return y;}
QColor GEO::getCor(){return cor;}
QString GEO::getNome(){return Nome;}
void GEO::setCor(){
    cor = QColorDialog::getColor();
}
Circulo::Circulo(){

        QDialog dialog(this);

        QPushButton *botao = new QPushButton("Inserir cor",this);

        //cria os rotulos na frente das caixas de dialogo
        QFormLayout form(&dialog);

        //add o nome
        form.addRow(new QLabel("Dados do Circulo:"));

        //Add uma caixa de edicao para cada rotulo
        QList<QLineEdit *> fields;

        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = QString("Nome:");
        form.addRow(label, lineEdit);

        QDoubleSpinBox *value1 = new QDoubleSpinBox(&dialog);
        form.addRow("Centro X:", value1);
        value1->setRange(-2000,2000);
        value1->value();

        QDoubleSpinBox *value2 = new QDoubleSpinBox(&dialog);
        form.addRow("Centro Y:", value2);
        value2->setRange(-2000,2000);
        value2->value();
\
        QSpinBox *value3 = new QSpinBox(&dialog);
        form.addRow("Raio:", value3);
        value3->setRange(0,2000);
        value3->value();

        form.addRow(botao);
        connect(botao, SIGNAL(clicked()), this, SLOT(setCor()));

        fields << lineEdit;

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);

        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

        if (dialog.exec() == QDialog::Accepted) {

            foreach(QLineEdit * lineEdit, fields) {
                Nome = lineEdit->text();
                x = value1->value();
                y = value2->value();
                r = value3->value();
            }
        }
};
Circulo::Circulo(QString A, double b, double c, int d, QColor e){
    Nome = A;
    x = b;
    y = c;
    r = d;
    cor = e;
}
void Circulo::Area(){area = r*r*PI;}
int Circulo::getR(){return r;}
double Circulo::getArea(){Area(); return area;}
Retang::Retang(){
        QDialog dialog(this);
        QPushButton *botao = new QPushButton("Inserir cor",this);
        //cria os rotulos na frente das caixas de dialogo
        QFormLayout form(&dialog);

        //add o nome
        form.addRow(new QLabel("Dados do Circulo:"));

        //Add uma caixa de edicao para cada rotulo
        QList<QLineEdit *> fields;

        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = QString("Nome:");
        form.addRow(label, lineEdit);

        QDoubleSpinBox *value1 = new QDoubleSpinBox(&dialog);
        form.addRow("X1:", value1);
        value1->setRange(-2000,2000);
        value1->value();

        QDoubleSpinBox *value2 = new QDoubleSpinBox(&dialog);
        form.addRow("Y1:", value2);
        value2->setRange(-2000,2000);
        value2->value();

        QDoubleSpinBox *value3 = new QDoubleSpinBox(&dialog);
        form.addRow("X2:", value3);
        value3->setRange(-2000,2000);
        value3->value();

        QDoubleSpinBox *value4 = new QDoubleSpinBox(&dialog);
        form.addRow("Y2:", value4);
        value4->setRange(-2000,2000);
        value4->value();

        form.addRow(botao);
        connect(botao, SIGNAL(clicked()), this, SLOT(setCor()));

        fields << lineEdit;

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

        if (dialog.exec() == QDialog::Accepted) {

            foreach(QLineEdit * lineEdit, fields) {
                Nome = lineEdit->text();
                x = value1->value();
                y = value2->value();
                x2 = value3->value();
                y2 = value4->value();
            }
        }
};
Retang::Retang(QString A, double B, double C, double D, double E, QColor F){
    Nome = A;
    x = B;
    y = C;
    x2 = D;
    y2 = E;
    cor = F;
}
void Retang::Area(){area = (x - x2) * (y - y2);}
double Retang::getX2(){return x2;}
double Retang::getY2(){return y2;}
double Retang::getArea(){Area();    return area;}
Ponto::Ponto(){
    QDialog dialog(this);
    QPushButton *botao = new QPushButton("Inserir botao",this);
    //cria os rotulos na frente das caixas de dialogo
    QFormLayout form(&dialog);

    //add o nome
    form.addRow(new QLabel("Dados do Circulo:"));

    //Add uma caixa de edicao para cada rotulo
    QList<QLineEdit *> fields;

    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QString label = QString("Nome:");
    form.addRow(label, lineEdit);

    QDoubleSpinBox *value1 = new QDoubleSpinBox(&dialog);
    form.addRow("X:", value1);
    value1->setRange(-2000,2000);
    value1->value();

    QDoubleSpinBox *value2 = new QDoubleSpinBox(&dialog);
    form.addRow("Y:", value2);
    value2->setRange(-2000,2000);
    value2->value();

    form.addRow(botao);
    connect(botao, SIGNAL(clicked()), this, SLOT(setCor()));

    fields << lineEdit;

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {

        foreach(QLineEdit * lineEdit, fields) {
            Nome = lineEdit->text();
            x = value1->value();
            y = value2->value();
        }
    }
}
Ponto::Ponto(QString A, double B, double C,QColor D){
    Nome = A;
    x = B;
    y = C;
    cor = D;
}
QString Ponto::getNome(){return Nome;}
QColor Ponto::getCor(){return cor;}
double Ponto::getX(){return x;}
double Ponto::getY(){return y;}
double Ponto::getDist(Ponto *a){
   return sqrt(pow((x - a->getX()),2) + pow(y - a->getY(),2));}
double Ponto::getDist(Circulo *a){
   return sqrt(pow((x - a->getX()),2) + pow((y - a->getY()),2));
}
void Ponto::setCor(){cor = QColorDialog::getColor();}
