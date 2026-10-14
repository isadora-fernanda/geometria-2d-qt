#include <QApplication>
#include "Janela.h"

int main(int argc, char **argv){
    QApplication app(argc,argv);
    Janela j;

    j.show();

    return app.exec();
}
