#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <random>


using namespace std;

#define LOUP 'L'
#define MOUTON 'M'
#define SELS '#'
#define HERBE '.'
#define EMPTY ' '
#define NONE '0'


typedef vector<pair<int, int>> VecteurPaires;
typedef vector<vector<class Case>> MatriceCases;

// Classe Entite représentant une entité


class Entite {

    char type;      
    int vie = 0; 
    int max_vie;
    int faim = 0;     
    int max_faim; 
    char predateur; 
    char nourriture;
    char genre;
    bool reproduction = false;
    bool sestReproduit = false;
    bool action = false;

public:

    // Constructeur de la classe Entite

    Entite(char type_) : type(type_) {

        switch (type)
        {
            case LOUP:
                setLoup(0);
                
                break;
                
            case MOUTON:
                setMouton(0);
                break;

            case HERBE:
                setHerbe();
                break;

            case EMPTY:
                reset();
                break;

        }

    }

    // Constructeur pour instancier une entité vide 

    Entite(){reset();}

    // Opérateur d'affectation

    void operator=(const Entite& ent){

        type = ent.type;
        vie = ent.vie;
        max_vie = ent.max_vie;
        faim = ent.faim;
        max_faim = ent.max_faim;
        predateur = ent.predateur;
        nourriture = ent.nourriture;
        genre = ent.genre;
        reproduction = ent.reproduction;
        sestReproduit = ent.sestReproduit;
        action = ent.action;

    }

    void reset(){

        type = EMPTY;
        vie = 0;
        max_vie = 0;
        faim = 0;
        max_faim = 0;
        predateur = EMPTY;
        nourriture = EMPTY;
        reproduction = false;
        sestReproduit = false;
        action = false;

    }

    void setHerbe(){

        type = HERBE;
        vie = 0;
        max_vie = 0;
        faim = 0;
        max_faim = 0;
        predateur = MOUTON;
        nourriture = EMPTY;
        reproduction = false;
        sestReproduit = false;
        action = false;

    }

    void setSels(){

        type = SELS;
        vie = 0;
        max_vie = 0;
        faim = 0;
        max_faim = 0;
        predateur = EMPTY;
        nourriture = EMPTY;
        reproduction = false;
        sestReproduit = false;
        action = false;

    }

    void setMouton(bool naissance){

        type = MOUTON;
        vie = 0;
        faim = 0;
        max_vie = 50;
        max_faim = 5;
        predateur = LOUP;
        nourriture = HERBE;
        if(rand() % 2)
            genre = 'F';
        else 
            genre = 'M';
        reproduction = false;
        if(naissance){
            sestReproduit = true;
            action = true;
        }
        else{
            sestReproduit = false;
            action = false;
        }
    }

    void setLoup(bool naissance){

        type = LOUP;
        vie = 0;
        max_vie = 60;
        faim = 0;
        max_faim = 10;
        predateur = NONE;
        nourriture = MOUTON;
        if(rand() % 2)
            genre = 'F';
        else 
            genre = 'M';
        reproduction = false;
        if(naissance){
            sestReproduit = true;
            action = true;
        }
        else{
            sestReproduit = false;
            action = false;
        }

    }

    char getType() const{
        return type;
    }

    int getVie() const{
        return vie;
    }

    int getMaxVie() const{
        return max_vie;
    }

    int getFaim() const{
        return faim;
    }

    int getMaxFaim() const{
        return max_faim;
    }

    char getGenre() const{
        return genre;
    }

    void incVie(){
        vie++;
    }

    void incFaim(){ 
        faim++;
    }

    char getNourriture() const{
        return nourriture;
    }

    char getPredateur() const{
        return predateur;
    }

    bool getReproduction() const{
        return reproduction;
    }

    bool getSestReproduit() const{
        return sestReproduit;
    }

    bool getAction() const{
        return action;
    }

    void setFaim(int faim_){
        faim = faim_;
    }

    void setReproduction(bool reproduction_){
        reproduction = reproduction_;
    }

    void setSestReproduit(bool sestReproduit_){
        sestReproduit = sestReproduit_;
    }

    void setGenre(char genre_){
        genre = genre_;
    }

    void setAction(bool action_){
        action = action_;
    }

};




// Classe Case représentant une case


class Case {

    int x;
    int y;
    bool herbe = true;
    
public:
    Entite animal;
  

    // Constructeur de la classe Case

    Case(Entite a) {animal = a;}

    // Surchage permettant l'affichage

    friend ostream& operator <<(ostream& out, const Case& in){

        out << ' ' << in.animal.getType() << ' ';
        return out;
    }

    // Modification des coordonnées de la case

    void setXY(int a, int b){

        x = a;
        y = b;
    }

    int getX() const{
        return x;
    }

    int getY() const{
        return y;
    }


    void action(MatriceCases& mat)
    {
        if(animal.getAction()){return;}

        // Herbe pousse 

        if(animal.getType() == SELS){
            animal.setHerbe();
            herbe = true;
            printf("[%d:%d] De l'herbe repousse !\n", x+1, y+1);
            return;
        }

        // Vieillissement

        if(!(animal.getType() == MOUTON || animal.getType() == LOUP)){return;}
        animal.incVie();
        animal.incFaim();

        // Mort (naturelle) de l'animal

        if(animal.getFaim() == animal.getMaxFaim() || animal.getVie() == animal.getMaxVie()){

            string mort;

            if(animal.getVie() == animal.getMaxVie())
                mort = "vieilesse";
            else 
                mort = "faim";
                

            if(animal.getType() == LOUP){
                if(animal.getGenre() == 'F') 
                    printf("[%d:%d] Une louve meurt de %s...\n", x+1, y+1, mort.c_str()); 
                else if(animal.getGenre() == 'M')
                    printf("[%d:%d] Un loup meurt de %s...\n", x+1, y+1, mort.c_str()); 
            }   

            if(animal.getType() == MOUTON){
                if(animal.getGenre() == 'F'){
                    printf("[%d:%d] Une brebis meurt de %s...\n", x+1, y+1, mort.c_str()); 
                }
                else if(animal.getGenre() == 'M')
                    printf("[%d:%d] Un bélier meurt de %s...\n", x+1, y+1, mort.c_str());        
            }

            // Dépôt de sels minéraux

            animal.setSels();
            herbe = false;
            return;
        }        
        
        // Débloque les animaux qui viennent de procréer

        if(animal.getSestReproduit()){
            animal.setSestReproduit(false);
        }

        reproduire(mat);
        if(animal.getSestReproduit()){return;}
        deplacer(mat);

    }




    void deplacer(MatriceCases& mat) {

        if(animal.getReproduction()) return;

        VecteurPaires partenaires, proies, autres;
        casesDisponibles(mat, partenaires, proies, autres);

        // Priorité 1 : reproduction
        
        //printf("partenaires : %ld\n", partenaires.size());

        if(partenaires.size() > 0 && !(animal.getSestReproduit())){
            
            // Partenaire choisi aléatoirement

            pair<int, int> p = partenaires[rand() % partenaires.size()];

            mat[p.first][p.second].animal.setReproduction(true);
            mat[p.first][p.second].animal.setAction(true);

            animal.setReproduction(true);
            animal.setAction(true);

            printf("[%d:%d]❤[%d:%d] Reproduction en cours...\n", x+1, y+1, p.first+1, p.second+1);
            return;
        }

        // Priorité 2 : manger
        
        //printf("proies : %ld\n", proies.size());

        if(proies.size() > 0){

            // Proie choisie aléatoirement

            pair<int, int> p = proies[rand() % proies.size()];
            manger(mat[p.first][p.second]);
            return;
        }

        // Cas par défaut : déplacement
        
        //printf("autres : %ld\n", autres.size());
        if(autres.size() > 0){

            pair<int, int> p = autres[rand() % autres.size()];
            Case& a = mat[p.first][p.second];

            if(animal.getType() == LOUP){
                if(animal.getGenre() == 'F') 
                    printf("[%d:%d] Une louve s'est déplacée en [%d:%d].\n", x+1, y+1, p.first+1, p.second+1); 
                else if(animal.getGenre() == 'M')
                    printf("[%d:%d] Un loup s'est déplacé en [%d:%d].\n", x+1, y+1, p.first+1, p.second+1); 
            }   

            if(animal.getType() == MOUTON){
                if(animal.getGenre() == 'F'){
                    printf("[%d:%d] Une brebis s'est déplacée en [%d:%d].\n", x+1, y+1, p.first+1, p.second+1); 
                }
                else if(animal.getGenre() == 'M')
                    printf("[%d:%d] Un bélier s'est déplacé en [%d:%d].\n", x+1, y+1, p.first+1, p.second+1); 
            } 

            a.animal = animal;
            a.animal.setAction(true);

            if(herbe)
                animal.setHerbe();
            else 
                animal.reset();


        }

        // En cas d'impossibilité de mouvement

        else{

            if(animal.getType() == LOUP){
                if(animal.getGenre() == 'F') 
                    printf("[%d:%d] Une louve est restée immobile.\n", x+1, y+1); 
                else if(animal.getGenre() == 'M')
                    printf("[%d:%d] Un loup est resté immobile.\n", x+1, y+1); 
            }   

            if(animal.getType() == MOUTON){
                if(animal.getGenre() == 'F'){
                    printf("[%d:%d] Une brebis est restée immobile.\n", x+1, y+1); 
                }
                else if(animal.getGenre() == 'M')
                    printf("[%d:%d] Un bélier est resté immobile.\n", x+1, y+1); 
            }
        }

    }

    void casesDisponibles(const MatriceCases& mat, VecteurPaires& partenaires, VecteurPaires& proies, VecteurPaires& autres){

        int rows = mat.size();
        int cols = mat[0].size();
        char animalType = animal.getType();

        // Parcours des 9 cases 
        for (int i = this -> x - 1; i <= this -> x + 1; i++) {
            for (int j = this -> y - 1; j <= this -> y + 1; j++) {

                // Si c'est en dehors des limites de la matrice, on ne fait rien
                if(!(i >= 0 && i < rows && j >= 0 && j < cols && !(i == x && j == y))) continue;

                const Case& caseAdjacente = mat[i][j];
                char adjacenteType = caseAdjacente.animal.getType();

                // Vérifie si il y a un partenaire potentiel 
                    // ne l'ajoute qu'à un certain niveau de faim et un certain âge

                if(adjacenteType == animalType && animal.getFaim() <= animal.getMaxFaim()*0.75 && animal.getVie() >= animal.getMaxVie()*0.01){ 

                    if(caseAdjacente.animal.getGenre() == animal.getGenre()) continue;
                    if(caseAdjacente.animal.getReproduction()) continue;
                    if(caseAdjacente.animal.getSestReproduit()) continue;
                    if(animal.getSestReproduit()) continue;
                    if(animal.getReproduction()) continue;
                    partenaires.push_back(make_pair(i,j));
                    continue;
                }

                // Vérifie si il y a une proie potentielle

                if(adjacenteType == animal.getNourriture() && animal.getFaim() >= animal.getMaxFaim()/2){

                    proies.push_back(make_pair(i,j));
                    continue;
                }

                if(adjacenteType == MOUTON || adjacenteType == LOUP) continue;
                    autres.push_back(make_pair(i,j));
                
            }

        }
        return;
    }

    void reproduire(MatriceCases& mat){

        // Sil'animal s'est déjà reproduit

        if(!animal.getReproduction()) return;
        animal.setReproduction(false);
        animal.setSestReproduit(true);

        // Nouveau-né généré près de la mère seulement

        if(animal.getGenre() == 'M'){
            return;
        }

        // Parcours des 9 cases 
        int rows = mat.size();
        int cols = mat[0].size();
        VecteurPaires casesLibres;
        for (int i = this -> x - 1; i <= this -> x + 1; i++) {
            for (int j = this -> y - 1; j <= this -> y + 1; j++) {
                // Si c'est en dehors des limites de la matrice, on ne fait rien
                if(!(i >= 0 && i < rows && j >= 0 && j < cols && !(i == x && j == y))) continue;

                Case& caseAdjacente = mat[i][j];
                char adjacenteType = caseAdjacente.animal.getType();

                if(!(adjacenteType == HERBE || adjacenteType == SELS || adjacenteType == EMPTY)) continue;
                casesLibres.push_back(make_pair(i, j));
            }
        }
        if(casesLibres.size() > 0){

            // Nouveau-né sur une case aléatoire autour de la mère

            pair<int, int> p = casesLibres[rand() % casesLibres.size()];

            if(animal.getType() == LOUP){
                mat[p.first][p.second].animal.setLoup(1);
                printf("[%d:%d] Nouveau-né (%c). Bravo les loups.\n", p.first+1, p.second+1, mat[p.first][p.second].animal.getGenre());
            }
            if(animal.getType() == MOUTON){
                mat[p.first][p.second].animal.setMouton(1);
                printf("[%d:%d] Nouveau-né (%c). Bravo les moutons.\n", p.first+1, p.second+1, mat[p.first][p.second].animal.getGenre());

            }
            return;
            
        }

        // Si aucune case n'a été disponible pour la mise bas

        if(animal.getType() == MOUTON){

            printf("[%d:%d] Mort-né. Minute de silence pour les moutons.\n", x+1, y+1);
        }
        else if(animal.getType() == LOUP){

            printf("[%d:%d] Mort-né. Minute de silence pour les loups.\n", x+1, y+1);
        }

    }

    void manger(Case& a){
        if(animal.getType() == LOUP){
            if(animal.getGenre() == 'F') 
                printf("[%d:%d] Une louve se régale d'un mouton.\n", a.x+1, a.y+1); 
            else if(animal.getGenre() == 'M')
                printf("[%d:%d] Un loup se régale d'un mouton.\n", a.x+1, a.y+1);
        }   

        if(animal.getType() == MOUTON){
            if(animal.getGenre() == 'F'){
                printf("[%d:%d] Une brebis broute de l'herbe.\n", a.x+1, a.y+1);
            }
            else if(animal.getGenre() == 'M')
                printf("[%d:%d] Un bélier broute de l'herbe.\n", a.x+1, a.y+1);
            a.herbe = false;
        }        

        animal.setFaim(0);
        a.animal = animal;
        
        a.animal.setAction(true);

        if(herbe)
            animal.setHerbe();
        else 
            animal.reset();

    }

};

void printFirstLine(int y) {
    for (int i = 0; i < y; i++)
        printf("  %d  ", i+1);
    printf("\n");
}

void printLine(int y) {
    for (int i = 0; i < y; i++)
        printf("-----");
    printf("\n");
}

void affichage(vector<vector<Case>> mat, int x, int y) { // Y et X sont inversés
    printf("   "); 
    printFirstLine(y);
    for (int i = 0; i < x; i++) {
        cout<< "   ";
        printLine(y);
        printf(" %d ", i+1);
        for (int j = 0; j < y; j++) {
            cout << "|" << mat[i][j]<< "|";
        }
        printf("\n");
    }
    cout<< "   ";
    printLine(y);
}

bool caseLibre(Case& a){

    return (a.animal.getType() != LOUP && a.animal.getType() != MOUTON);
}

bool xyValides(MatriceCases& mat, int i, int j){

    int rows = mat.size();
    int cols = mat[0].size();
    return (i >= 0 && i < rows && j >= 0 && j < cols);

}

bool mondeMort(MatriceCases& mat){

    int rows = mat.size();
    int cols = mat[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(caseLibre(mat[i][j]) == false)
                return false;
        }
    }
    return true;
}

// Case& AnimalTrouve(MatriceCases& mat){

//     int rows = mat.size();
//     int cols = mat[0].size();
//     Case& a = mat[0][0];

//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             if(mat[i][j].animal.getType() == LOUP || mat[i][j].animal.getType() == MOUTON){
//                 a = mat[i][j];
//                 return a;
//             }
//         }
//     }
//     return a;
// }

// bool MemeEspece(MatriceCases& mat, Case a){

//     int rows = mat.size();
//     int cols = mat[0].size();
//     if(a.animal.getType() != LOUP && a.animal.getType() != MOUTON) return true;

//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             if((mat[i][j].animal.getType() == a.animal.getType()) && i != a.getX() && j != a.getY()){
//                 return true;
//             }
//         }
//     }
//     return false;
// }


void simulation(MatriceCases& matrice, VecteurPaires vecteurXY, int rows, int cols, int loups, int moutons, int sleep){

    // Définition coordonnées de chaque case

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrice[i][j].setXY(i, j);
            vecteurXY.push_back(make_pair(i, j));

        }
    }

    printf("\n\n*********************\n\nDébut de simulation :\n\n*********************\n\n");

    auto rd = random_device{};
    auto rng = default_random_engine { rd() }; 

    int i = 0;

    // Placement aléatoire des animaux

    while(i < loups){

        int newX = rand() % rows;
        int newY = rand() % cols;

        if(caseLibre(matrice[newX][newY]) && xyValides(matrice,newX,newY)){
            matrice[newX][newY].animal.setLoup(0);
            i++;
        }
    }

    i = 0;

    while(i < moutons){

        int newX = rand() % rows;
        int newY = rand() % cols;

        if(caseLibre(matrice[newX][newY]) && xyValides(matrice,newX,newY)){
            matrice[newX][newY].animal.setMouton(0);
            i++;
        }
    }


    affichage(matrice, rows, cols);

    int ite = 0;

    while(!mondeMort(matrice)){

        printf("Jour %d\n\n", ite+1);
        printf("_________________________________________\n\n");

        usleep(sleep);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrice[i][j].animal.setAction(false); 
            }
        }
        shuffle(begin(vecteurXY), end(vecteurXY), rng);

        for(int i = 0; i < int(vecteurXY.size()); i++){
            matrice[vecteurXY[i].first][vecteurXY[i].second].action(matrice);
        }

        printf("_________________________________________\n\n");
        affichage(matrice, rows, cols);
        printf("\n\n");
        ite++;

    }
    
    printf("La simulation s'est finie après %d jours.", ite);


}

int main() {

    srand(time(0));

    int rows = 7;
    int cols = 7;
    // int loups = 3;
    // int moutons = 2;

    // int rows;
    // int cols;
    int loups;
    int moutons;

    do{
        // cout << "\nNombre de lignes : ";
        // cin >> rows;
        // cout << "Nombre de colonnes : ";
        // cin >> cols;    
        cout << "Nombre de moutons : ";
        cin >> moutons;
        cout << "Nombre de loups : ";
        cin >> loups;
        if(moutons + loups > rows*cols) printf("\nVeuillez entrer un nombre d'entités n'éxédant pas la capacité de l'écosystème.\n");

    }while(moutons + loups > rows*cols);

    //Création du vecteur qui contiendra les coordonnées de chaque case dans un ordre aléatoire 

    VecteurPaires vecteurXY;

    // Création d'une matrice de Cases

    MatriceCases matrice(rows, vector<Case>(cols, Case(Entite(HERBE))));

    simulation(matrice, vecteurXY, rows, cols, loups, moutons, 500000);

    return 0;
}