#include "UVEditeur.h"
#include <QMessageBox>

UVEditeurNew::UVEditeurNew(QSqlDatabase &db,QWidget *parent):mydb(db){
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    creditsLabel = new QLabel("credits",this);
    categorieLabel = new QLabel("categorie",this);
    ouvertureLabel = new QLabel("ouverture",this);
    // création des composants éditables
    code = new QLineEdit;
    titre = new QTextEdit;
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    categorie=new QComboBox(this);
    for(Categorie cat = Categorie::CS; cat != Categorie::END; cat = static_cast<Categorie>(static_cast<int>(cat) + 1))
       categorie->addItem(CategorieToString(cat));
    categorie->setCurrentIndex(0);
    saison=new QComboBox(this);
    for(Saison sais = Saison::Automne; sais!= Saison::END; sais = static_cast<Saison>(static_cast<int>(sais) + 1))
       saison->addItem(SaisonToString(sais));
    saison->setCurrentIndex(0);
    sauver= new QPushButton("Sauver", this);
    annuler= new QPushButton("Annuler", this);

    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(saison);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);
    //coucheH4->addWidget(modifier);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    //Connection du slot au signal QUIT
    connect(sauver,  &QPushButton::clicked,[this]{sauverUV(mydb);});
   // QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV(QSqlDatabase&)));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
    // creation des labels

}

void UVEditeurNew::sauverUV(QSqlDatabase& db){
    QString c=code->text();
    QString t=titre->toPlainText();
    unsigned int nbc=credits->value();
    Categorie cat=Categorie(categorie->currentIndex());
    Saison sais=Saison(saison->currentIndex());
    UVManager& man=UVManager::getInstance();
    man.ajouter(c,t,nbc,cat,sais,db);
    //void ajouter(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p) {stratUV->ajouterUV(*this,c,t,nbc,cat,a,p);}
    QMessageBox::information(this, "Sauvegarde", "UV sauvegardée...");

}



UVEditeur::UVEditeur(UV& uvToEdit, QWidget *parent) :
QWidget(parent),uv(uvToEdit){
this->setWindowTitle(QString("Edition de l’UV ")+uv.getCode());
// creation des labelscodeLabel = new QLabel("code",this);
titreLabel = new QLabel("titre",this);
creditsLabel = new QLabel("credits",this);
categorieLabel = new QLabel("categorie",this);
ouvertureLabel = new QLabel("ouverture",this);
// création des composants éditables
code = new QLineEdit(uv.getCode(),this);
titre = new QTextEdit(uv.getTitre(),this);
credits=new QSpinBox(this);
credits->setRange(1,8);
credits->setValue(uv.getNbCredits());
categorie=new QComboBox(this);
for(Categorie cat = Categorie::CS; cat != Categorie::SP; cat = static_cast<Categorie>(static_cast<int>(cat) + 1))
categorie->addItem(CategorieToString(cat));
categorie->setCurrentIndex(int(uv.getCategorie()));
automne=new QCheckBox("automne",this);
automne->setChecked(uv.ouvertureAutomne());
printemps=new QCheckBox("printemps",this);
printemps->setChecked(uv.ouverturePrintemps());
sauver= new QPushButton("Sauver", this);
annuler= new QPushButton("Annuler", this);
// diposition des couches
coucheH1 = new QHBoxLayout;
coucheH1->addWidget(codeLabel);
coucheH1->addWidget(code);
coucheH1->addWidget(categorieLabel);
coucheH1->addWidget(categorie);
coucheH1->addWidget(creditsLabel);
coucheH1->addWidget(credits);
coucheH2 = new QHBoxLayout;
coucheH2->addWidget(titreLabel);
coucheH2->addWidget(titre);
coucheH3 = new QHBoxLayout;
coucheH3->addWidget(ouvertureLabel);
coucheH3->addWidget(automne);
coucheH3->addWidget(printemps);
coucheH4 = new QHBoxLayout;
coucheH4->addWidget(annuler);
coucheH4->addWidget(sauver);
couche = new QVBoxLayout;
couche->addLayout(coucheH1);
couche->addLayout(coucheH2);
couche->addLayout(coucheH3);
couche->addLayout(coucheH4);
setLayout(couche);
}

    /*
UVEditeur::UVEditeur(UV& uvToEdit, QWidget *parent) :UVEditeur(parent),uv(uvToEdit)
{
this->setWindowTitle(QString("Edition de l’UV ")+uv.getCode());

    //Connection du slot au signal QUIT
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
    // creation des labels
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    creditsLabel = new QLabel("credits",this);
    categorieLabel = new QLabel("categorie",this);
    ouvertureLabel = new QLabel("ouverture",this);
    // création des composants éditables

    code = new QLineEdit(uv.getCode(),this);
    titre = new QTextEdit(uv.getTitre(),this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    credits->setValue(uv.getNbCredits());
    categorie=new QComboBox(this);
    //for(CategorieIterator it=CategorieIterator::getFirst(); !it.isDone(); it.next())
    //categorie->addItem(CategorieToString(*it));
    categorie->setCurrentIndex(int(uv.getCategorie()));
    automne=new QCheckBox("automne",this);
    automne->setChecked(uv.ouvertureAutomne());
    printemps=new QCheckBox("printemps",this);
    printemps->setChecked(uv.ouverturePrintemps());
    sauver= new QPushButton("Sauver", this);
    annuler= new QPushButton("Annuler", this);

    // diposition des couches
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);
    //coucheH4->addWidget(modifier);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    //Desactiver le bouton sauver au début
    //save->setEnabled(false);
}

void UVEditeur::sauverUV(){
uv.setCode(code->text());
uv.setTitre(titre->toPlainText());
uv.setNbCredits(credits->value());
uv.setCategorie(Categorie(categorie->currentIndex()));
uv.setOuverturePrintemps(printemps->isChecked());
uv.setOuvertureAutomne(automne->isChecked());
QMessageBox::information(this, "Sauvegarde", "UV sauvegardée...");
}

 void UVEditeur::annulerUV(){
 }

*/




