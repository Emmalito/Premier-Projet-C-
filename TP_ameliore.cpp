#include <iostream> 
#include <string>
#include <ctime> // Pour l'aléatoire
#include <cstdlib> // Pour l'aléatoire
#include <time.h> // Pour l'aléatoire
#include <ctype.h> //Mettre les str en majuscule 
#include <fstream> //Flux vers les fichiers

using namespace std;

void majuscule(string& chaine)
{
    // Fonction qui met un mot en majuscule
    for (int i = 0 ; i < chaine.size() ; i++)
    {
        chaine[i] = toupper(chaine[i]);
    }
}

int recommencer()
{
    //Fonction qui renvoie 1 pour 'oui' et 0 pour 'non'
    char reponse;
    cin >> reponse;
    reponse = toupper(reponse);
    switch (reponse)
    {
        case 'O':
            return 1;

        case 'N':
            break;
    
        default:
            recommencer();
            break;
    }

    return 0;    
}

string jouerSeul()
{
    //Fonction qui tire un mot aléatoire dans un dictionnaire
    string const nomFichier("dico.txt");
    ifstream dico(nomFichier.c_str());  //Ouverture du dictionnaire en lecture

    if (dico) 
    {
        srand(time(NULL));
        string motDico;
        int numeroMot;
        numeroMot = rand()%323577; //323577 est le nb de mot dans le dico

        while(numeroMot > 0)
        {
            dico >> motDico;
            numeroMot -= 1;
        }
        return motDico;
    } else
    {
        cout << "On ne trouve pas le dictionnaire de mot" << endl;
        return "";
    }
}


string saisie()
{
    //Fonction renvoyant le mot à deviner
    string mot("");
    int reponse;
    cout << "Jouez-vous seul ? (o/n) " << endl;
    reponse = recommencer();
    if (reponse == 0) 
    {
        cout << "Entrez le mot mystère" << endl;
        cin >> mot;
        majuscule(mot);
        return mot;
    } else
    {
        return jouerSeul();    
    } 
}


string melangeMot(string mot)
{
    //Fonction chiffrant un mot en mélangeant l'ordre de ses lettres
    int nbAleatoire(0);
    int nbLettre(mot.size());
    string motCode("");
    srand(time(0));
    
    for(int i = 0; i < nbLettre; i++)
    {
        nbAleatoire = rand() % mot.size(); //On choisit un nombre entre 0 et le nombre de lettre restant du mot
        motCode += mot[nbAleatoire]; 
        mot.erase(nbAleatoire,1); //On supprime la lettre
    }

    return motCode;        
}

int devine(string motMystere, int nbCoups = 5)
{
    //Fonction qui sert à vérifier si le joueur à trouver le mot chiffré
    string motDevine("");
    while(motDevine != motMystere and nbCoups > 0) //Tant que le mot n'est pas trouvé ou qu'il n'abandonne pas
    {
        cout << "Devinez le mot mystère ou entrez \"/\" pour quitter" << endl << "Il vous reste " << nbCoups << " coups" << endl;
        cin >> motDevine;
        if (motDevine == "/")
        {
            cout << "Vous avez abandonné LOOSER. Le mot était : " << motMystere << endl ;
            return 0;
        } else
        {
            majuscule(motDevine);
        }       
        nbCoups -= 1;       
        
    }
    if (motDevine == motMystere) 
    {
        cout << "Félicitation, vous avez deviné le mot mystère " << endl;
        return 0;
    } else
    {
        cout << "Vous n'avez pas réussi à trouver le mot mystère à temps. Le mot était \" " << motMystere << "\"" << endl;
        return 0;
    } 
}


int main()
{
    //Début - Récupération et chiffrage du mot mystère
    cout << "Bienvenue dans le jeu DEVINE-MOI " << endl << "Joueur 1 vous allez commencer." << endl;
    string motMyster("");
    motMyster = saisie();
    string motChiffre = melangeMot(motMyster);
    cout << "Le mot à déchiffrer est :  " << motChiffre << endl;
    cout << "Votre saisie sera automatiquement mis en majuscule" << endl;

    // Tentative de déchiffrage - Résultat du déchiffrage
    int resultat;
    resultat = devine(motMyster);

    // Recommencer ou pas
    int quitter;
    cout  << "Voulez-vous recommencer ? (o/n)" << endl;
    quitter = recommencer(); 
    if (quitter == 1) 
    {
        main();
    } else
    {
        cout << "Au revoir " << endl;
    }  
    
    return 0;
}
