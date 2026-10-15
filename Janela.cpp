#include "Janela.h"

Janela::Janela(QWidget *parent):QWidget(parent){

    setFixedSize(TAM_JAN,TAM_JAN);
    setWindowTitle("GEOGEBRA_CHH");
    ORIGX = TAM_JAN/2;
    ORIGY = TAM_JAN/2;
    Zoom = 1;

    QMenuBar *barra = new QMenuBar(this);

    QMenu *arquivo = new QMenu ("&Arquivo", this);
    QMenu *inserir = new QMenu ("Inserir", this);
    QMenu *remover = new QMenu ("Remover", this);
    QMenu *info = new QMenu ("Informacoes",this);
    QMenu *layout = new QMenu ("Layout", this);
    QMenu *area = new QMenu ("Area",this);
    QMenu *zoom = new QMenu ("Zoom", this);

    barra->addMenu(arquivo);
    barra->addMenu(inserir);
    barra->addMenu(remover);
    barra->addMenu(info);
        info->addMenu(area);
    barra->addMenu(layout);
        layout->addMenu(zoom);

    QAction *sair = new QAction ("&Sair", this);
    QAction *salvar = new QAction("Salvar",this);
    QAction *abrir = new QAction("Abrir",this);
    QAction *novo = new QAction("Novo",this);

    QAction *circulo = new QAction("Circulo",this);
    QAction *retangulo = new QAction ("Retangulo", this);
    QAction *ponto = new QAction ("Ponto", this);

    QAction *remove_circulo = new QAction ("Circulo", this);
    QAction *remove_retangulo = new QAction ("Retangulo", this);
    QAction *remove_ponto = new QAction ("Ponto", this);

    QAction *deslocar_orig = new QAction ("Deslocar Origem",this);

    QAction *AreaCirculo = new QAction("Circulo",this);
    QAction *AreaRetangulo = new QAction ("Retangulo", this);
    QAction *distancia = new QAction ("Distancia",this);

    QAction *maisZoom = new QAction ("+",this);
    QAction *menosZoom = new QAction ("-",this);

    sair->setShortcut(tr("CTRL+Q"));
    salvar->setShortcut(tr("CTRL+S"));
    abrir->setShortcut(tr("CTRL+O"));
    maisZoom->setShortcut(tr("CTRL++"));
    menosZoom->setShortcut(tr("CTRL+-"));
    novo->setShortcut(tr("CTRL+N"));

    arquivo->addAction(abrir);
    arquivo->addSeparator();
    arquivo->addAction(salvar);
    arquivo->addSeparator();
    arquivo->addAction(sair);
    arquivo->addSeparator();
    arquivo->addAction(novo);

    layout->addAction(deslocar_orig);

    inserir->addAction(circulo);
    inserir->addSeparator();
    inserir->addAction(retangulo);
    inserir->addSeparator();
    inserir->addAction(ponto);

    remover->addAction(remove_circulo);
    remover->addSeparator();
    remover->addAction(remove_retangulo);
    remover->addSeparator();
    remover->addAction(remove_ponto);

    area->addAction(AreaCirculo);
    area->addSeparator();
    area->addAction(AreaRetangulo);
    area->addSeparator();

    zoom->addAction(maisZoom);
    zoom->addSeparator();
    zoom->addAction(menosZoom);

    info->addSeparator();
    info->addAction(distancia);

    connect(sair,SIGNAL(triggered(bool)),this, SLOT(close()) );
    connect(salvar,SIGNAL(triggered(bool)),this,SLOT(salvar_dados()));
    connect(abrir,SIGNAL(triggered(bool)),this,SLOT(abrir_dados()));
    connect(novo,SIGNAL(triggered(bool)),this,SLOT(novo()));

    connect(circulo,SIGNAL(triggered(bool)),this,SLOT(Insere_Circulo()));
    connect(retangulo,SIGNAL(triggered(bool)),this,SLOT(Insere_Retang()));
    connect(ponto,SIGNAL(triggered(bool)),this,SLOT(Insere_Ponto()));

    connect(remove_circulo,SIGNAL(triggered(bool)),this,SLOT(Remove_Circulo()));
    connect(remove_retangulo,SIGNAL(triggered(bool)),this,SLOT(Remove_Retang()));
    connect(remove_ponto,SIGNAL(triggered(bool)),this,SLOT(Remove_Ponto()));

    connect(AreaRetangulo,SIGNAL(triggered(bool)),this,SLOT(Area_Retang()));
    connect(AreaCirculo,SIGNAL(triggered(bool)),this,SLOT(Area_Circulo()));
    connect(distancia,SIGNAL(triggered(bool)),this,SLOT(Dist()));

    connect(deslocar_orig,SIGNAL(triggered(bool)),this,SLOT(Deslocar_Orig()));
    connect(maisZoom,SIGNAL(triggered(bool)),this,SLOT(Zoom_Mais()));
    connect(menosZoom,SIGNAL(triggered(bool)),this,SLOT(Zoom_Menos()));

}
void Janela::paintEvent(QPaintEvent *){

    QPainter P(this);
    QPen pen;
    QString s;

    P.setPen(Qt::gray);
    P.drawLine(ORIGY,0,ORIGY,TAM_JAN);
    P.drawLine(0,ORIGX,TAM_JAN,ORIGX);
    //imprime as linhas e legenda      só incrementa usando o zoom se o zoom for pequeno

    (Zoom > 4 )?(Zoom = 4):(Zoom);
    (Zoom < 1/4 )?(Zoom = 1/4):(Zoom);

    for(int i = -2000; i < 2000 ;i += 100/Zoom){
        s.setNum(i/Zoom);
            P.drawText(ORIGX + i - 5,ORIGY + 10,s);
    }

    for(int i = -2000; i < 2000 ;i += 100/Zoom){
        s.setNum(i/Zoom);
        if(s != "0")
            P.drawText(ORIGY + 10,ORIGX + i + 5,s);
    }

    if(!Circulo_map.empty()){
        for(it_circulo=Circulo_map.begin();it_circulo != Circulo_map.end();it_circulo++){
            P.setPen(Qt::black);
            P.drawText(it_circulo->second->getX()-cos(45)*(it_circulo->second->getR())*Zoom + ORIGX - 10,it_circulo->second->getY()-sin(45)*(it_circulo->second->getR())*Zoom + ORIGY - 10,it_circulo->first);

            pen.setColor(it_circulo->second->getCor());
            pen.setWidth(2);

            P.setPen(pen);
                                         //origem em x                                                     origem em y
            P.drawEllipse((it_circulo->second->getX() + ORIGX) - (it_circulo->second->getR())*Zoom,it_circulo->second->getY()+ORIGY - (it_circulo->second->getR())*Zoom,Zoom*it_circulo->second->getR()*2,Zoom*it_circulo->second->getR()*2);
        }
    }
    if(!Retangulo_map.empty()){
        for(it_retangulo=Retangulo_map.begin();it_retangulo != Retangulo_map.end();it_retangulo++){
            P.setPen(Qt::black);
            P.drawText(it_retangulo->second->getX()*Zoom - 5 + ORIGX,it_retangulo->second->getY()*Zoom - 5 + ORIGY,it_retangulo->first);

            pen.setColor(it_retangulo->second->getCor());
            pen.setWidth(2);

            //o -5 desloca o texto para a esquerda
            P.setPen(pen);
            P.drawRect(it_retangulo->second->getX()*Zoom + ORIGX,it_retangulo->second->getY()*Zoom + ORIGY,Zoom*(it_retangulo->second->getX2() - it_retangulo->second->getX()),Zoom*(it_retangulo->second->getY2()-it_retangulo->second->getY()));
        }
    }
    if(!Ponto_map.empty()){
        for(it_ponto=Ponto_map.begin();it_ponto != Ponto_map.end();it_ponto++){
            P.setPen(Qt::black);
            P.drawText(it_ponto->second->getX()*Zoom - 5 + ORIGX,it_ponto->second->getY()*Zoom - 5 + ORIGY,it_ponto->first);

            pen.setColor(it_ponto->second->getCor());
            QBrush B(it_ponto->second->getCor());

            P.setPen(pen);
            P.setBrush(B);

            P.drawEllipse((it_ponto->second->getX())*Zoom-3 + ORIGX,(it_ponto->second->getY())*Zoom -3 + ORIGY,6,6);
        }
    }
}
void Janela::salvar_dados(){
    nome =  QFileDialog::getSaveFileName(this);

    const char *A;
    int R,G,B;
    int num_circulo = Circulo_map.size(),
        num_retangulo = Retangulo_map.size(),
        num_ponto = Ponto_map.size();

    FILE *file = fopen(nome.toUtf8(),"w");
    fprintf(file,"%d %d %d\n",num_circulo,num_retangulo,num_ponto);

    if(!Circulo_map.empty()){
        for(it_circulo = Circulo_map.begin(); it_circulo != Circulo_map.end(); it_circulo++){
            A = it_circulo->first.toUtf8();
            it_circulo->second->getCor().getRgb(&R,&G,&B);
            fprintf(file,"%s %lf %lf %d %d %d %d\n", A, it_circulo->second->getX(),it_circulo->second->getY(),it_circulo->second->getR(),R,G,B);
        }
    }
    if(!Retangulo_map.empty()){
        for(it_retangulo = Retangulo_map.begin(); it_retangulo != Retangulo_map.end(); it_retangulo++){
            A = it_retangulo->first.toUtf8();
            it_retangulo->second->getCor().getRgb(&R,&G,&B);
            fprintf(file,"%s %lf %lf %lf %lf %d %d %d\n", A, it_retangulo->second->getX(),it_retangulo->second->getY(),it_retangulo->second->getX2(),it_retangulo->second->getY2(),R,G,B);
        }
    }
    if(!Ponto_map.empty()){
        for(it_ponto = Ponto_map.begin(); it_ponto != Ponto_map.end(); it_ponto++){
            A = it_ponto->first.toUtf8();
            it_ponto->second->getCor().getRgb(&R,&G,&B);
            fprintf(file,"%s %lf %lf %d %d %d\n", A,it_ponto->second->getX(),it_ponto->second->getY(),R,G,B);
        }
    }

    fclose(file);
}
void Janela::abrir_dados(){
    char a[100];
    int R,G,B;
    double b;
    double c;
    double d;
    double e;
    int f;
    int num_circulo,
        num_retangulo,
        num_ponto;

    nome = QFileDialog::getOpenFileName(this);

    FILE *file = fopen(nome.toUtf8(), "r");

    fscanf(file,"%d %d %d\n", &num_circulo, &num_retangulo, &num_ponto);
    while (num_circulo--) {
        fscanf(file,"%s %lf %lf %d %d %d %d\n", a, &b, &c, &f,&R,&G,&B);
        nome = nome.fromUtf8(a);
        QColor color(R,G,B);

        qDebug() << R << G << B;
        Circulo *A = new Circulo(nome,b,c,f,color);
        Circulo_map[nome] = A;
    }
    while (num_retangulo--) {
        fscanf(file,"%s %lf %lf %lf %lf %d %d %d\n", a, &b, &c, &d, &e,&R,&G,&B);
        nome = nome.fromUtf8(a);
        QColor color(R,G,B);
        Retang *A = new Retang(nome,b,c,d,e,color);
        Retangulo_map[nome] = A;
    }
    while (num_ponto--) {
        fscanf(file,"%s %lf %lf %d %d %d\n", a, &b, &c,&R,&G,&B);
        nome = nome.fromUtf8(a);
        QColor color(R,G,B);
        Ponto *A = new Ponto(nome,b,c,color);
        Ponto_map[nome] = A;
    }

    fclose(file);
}
void Janela::Insere_Circulo(){
    int j = 0;

    Circulo *A = new Circulo();
    nome = A->getNome();

    try {
        for(it_circulo = Circulo_map.begin(); it_circulo != Circulo_map.end(); it_circulo++)
            if(nome == it_circulo->first)
                throw "Ja existe um Circulo com o mesmo nome.";
        for(it_ponto = Ponto_map.begin(); it_ponto != Ponto_map.end(); it_ponto++)
            if(nome == it_ponto->first)
                throw "Ja existe um Ponto com o mesmo nome.";
        for(it_retangulo = Retangulo_map.begin();it_retangulo != Retangulo_map.end();it_retangulo++)
            if(nome == it_retangulo->first)
                throw "Ja existe um Retangulo com o mesmo nome.";

        if(nome[0] == '\0') {
            throw "Nome em branco.";
        }
        for(int i = 0; i < nome.length();i++)
            if (nome[i] == ' ')
                    j++;
        if (j == nome.length())
                throw "Nome em branco.";

        Circulo_map[nome] = A;

    } catch (const char *erro) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Icon::Critical);
        msg.setWindowTitle("Erro!");
        msg.setText(erro);
        msg.exec();
    }
}
void Janela::Insere_Retang(){

    int j = 0;
    Retang *A = new Retang();
    nome = A->getNome();
    try{
        for(it_circulo = Circulo_map.begin(); it_circulo != Circulo_map.end(); it_circulo++)
            if(nome == it_circulo->first)
                throw "Ja existe um Circulo com o mesmo nome.";
        for(it_ponto = Ponto_map.begin(); it_ponto != Ponto_map.end(); it_ponto++)
            if(nome == it_ponto->first)
                throw "Ja existe um Ponto com o mesmo nome.";
        for(it_retangulo = Retangulo_map.begin();it_retangulo != Retangulo_map.end();it_retangulo++)
            if(nome == it_retangulo->first)
                throw "Ja existe um Retangulo com o mesmo nome.";
        if(nome[0] == '\0') {
            throw "Nome em branco.";
        }
        for(int i = 0; i < nome.length();i++){
            if (nome[i] == ' ') {
                    j++;}}
                    if (j == nome.length()) {
                    throw "Nome em branco.";}

        Retangulo_map[nome] = A;

    } catch (const char *erro) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Icon::Critical);
        msg.setWindowTitle("Erro!");
        msg.setText(erro);
        msg.exec();
    }
}
void Janela::Insere_Ponto(){
    int j = 0;
    Ponto *A = new Ponto();
    nome=A->getNome();
    try{
        for(it_circulo = Circulo_map.begin(); it_circulo != Circulo_map.end(); it_circulo++)
            if(nome == it_circulo->first)
                throw "Ja existe um Circulo com o mesmo nome.";
        for(it_ponto = Ponto_map.begin(); it_ponto != Ponto_map.end(); it_ponto++)
            if(nome == it_ponto->first)
                throw "Ja existe um Ponto com o mesmo nome.";
        for(it_retangulo = Retangulo_map.begin();it_retangulo != Retangulo_map.end();it_retangulo++)
            if(nome == it_retangulo->first)
                throw "Ja existe um Retangulo com o mesmo nome.";

        if(nome[0] == '\0') {
            throw "Nome em branco.";
        }
        for(int i = 0; i < nome.length();i++)
            if (nome[i] == ' ')
                    j++;
        if (j == nome.length())
             throw "Nome em branco.";

        Ponto_map[nome] = A;

    } catch (const char *erro) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Icon::Critical);
        msg.setWindowTitle("Erro!");
        msg.setText(erro);
        msg.exec();

    }
}
void Janela::Remove_Circulo(){
    QStringList items;
    bool ok;

    for(it_circulo=Circulo_map.begin();it_circulo != Circulo_map.end();it_circulo++)
          items << it_circulo->first;

    nome = QInputDialog::getItem(this," ", "Circulo:",items,0,true,&ok);

    if(ok)
    Circulo_map.erase(nome);
}
void Janela::Remove_Retang(){
    QStringList items;
    bool ok;

    for(it_retangulo = Retangulo_map.begin();it_retangulo != Retangulo_map.end();it_retangulo++)
          items << it_retangulo->first;

    nome = QInputDialog::getItem(this," ", "Retangulo:",items,0,true,&ok);

    if(ok)
    Retangulo_map.erase(nome);
}
void Janela::Remove_Ponto(){
    QStringList items;
    bool ok;

    for(it_ponto=Ponto_map.begin();it_ponto != Ponto_map.end();it_ponto++)
          items << it_ponto->first;

    nome = QInputDialog::getItem(this," ", "Ponto:",items,0,true,&ok);

    if(ok)
    Ponto_map.erase(nome);
}
void Janela::Deslocar_Orig(){

    QDialog dialog(this);

    QFormLayout form(&dialog);

    form.addRow(new QLabel("Deslocar origem:"));


    QDoubleSpinBox *value1 = new QDoubleSpinBox(&dialog);
    form.addRow("X:", value1);
    value1->setRange(-2000,2000);
    value1->value();

    QDoubleSpinBox *value2 = new QDoubleSpinBox(&dialog);
    form.addRow("Y:", value2);
    value2->setRange(-2000,2000);
    value2->value();

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
            ORIGX = value1->value();
            ORIGY = value2->value();
    }
}
void Janela::Area_Retang(){
    bool ok;
    QStringList items;
    QMessageBox msg(this);
    QString s;
    QString c;

    for(it_retangulo = Retangulo_map.begin();it_retangulo != Retangulo_map.end();it_retangulo++)
          items << it_retangulo->first;

    nome = QInputDialog::getItem(this," ", "Ponto:",items,0,true,&ok);

    if (ok) {
        s.append("Area ");
        s.append(c.setNum(Retangulo_map[nome]->getArea()));
        s.append(": ");
        msg.setText(s);
        msg.exec();
    }
}
void Janela::Area_Circulo(){
    bool ok;
    QStringList items;
    QMessageBox msg(this);
    QString s;
    QString c;

    msg.setWindowTitle("Area Elipse");

    for(it_circulo = Circulo_map.begin();it_circulo != Circulo_map.end();it_circulo++)
          items << it_circulo->first;

    nome = QInputDialog::getItem(this," ", "Ponto:",items,0,true,&ok);

    if (ok) {
    s.append("Area ");
    s.append(c.setNum(Circulo_map[nome]->getArea()));
    s.append(": ");
    msg.setText(s);
    msg.exec();
    }
}
void Janela::Zoom_Mais(){Zoom *= 2; update();}
void Janela::Zoom_Menos(){Zoom /= 2; update();}
void Janela::Dist(){
    QMessageBox msg(this);
    QString s;
    QString c;
    double distancia;
    QStringList items;

    for(it_ponto=Ponto_map.begin();it_ponto != Ponto_map.end();it_ponto++)
          items << it_ponto->first;

    nome = QInputDialog::getItem(this,"Distancia", "Distancia de:",items);
    items.removeOne(nome);

    for(it_circulo=Circulo_map.begin();it_circulo != Circulo_map.end();it_circulo++)
          items << it_circulo->first;

    QString nome2 = QInputDialog::getItem(this," ","para:",items);

    s.append("Distancia de ");
    s.append(nome);
    s.append(" a ");
    s.append(nome2);
    s.append(": ");
    for(it_circulo=Circulo_map.begin();it_circulo != Circulo_map.end();it_circulo++)
        if(nome2 == it_circulo->first){
            distancia = Ponto_map[nome]->getDist(Circulo_map[nome2]);
            if(it_circulo->second->getR() < distancia)
                distancia -= it_circulo->second->getR();
            else
                distancia = 0;
        }
    for(it_ponto=Ponto_map.begin();it_ponto != Ponto_map.end();it_ponto++)
        if(nome2 == it_ponto->first)
            distancia = Ponto_map[nome]->getDist(Ponto_map[nome2]);
    s.append(c.setNum(distancia));
    msg.setText(s);
    msg.exec();
}
void Janela::novo(){
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Os dados serão perdidos. Deseja salva-los?"));
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {

        salvar_dados();

        Circulo_map.clear();
        Retangulo_map.clear();
        Ponto_map.clear();
    }
}

