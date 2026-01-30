#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <set>
#include <ctime>

using namespace std;

// Fonction pour générer une combinaison aléatoire de 4 chiffres différents
vector<int> genererCombinaison() {
    vector<int> chiffres = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // Mélanger et prendre les 4 premiers
    random_device rd;
    mt19937 gen(rd());
    shuffle(chiffres.begin(), chiffres.end(), gen);

    vector<int> combinaison(chiffres.begin(), chiffres.begin() + 4);
    return combinaison;
}

// Fonction pour afficher les indices
void afficherIndices(const vector<int>& combinaison) {
    cout << "Indices en debut de partie :" << endl;

    vector<int> indices;
    vector<int> indicesCopie;

    // Sélectionner 2 chiffres de la combinaison
    vector<int> combCopie = combinaison;
    random_device rd;
    mt19937 gen(rd());
    shuffle(combCopie.begin(), combCopie.end(), gen);
    indices.push_back(combCopie[0]);
    indices.push_back(combCopie[1]);
    indicesCopie.push_back(combCopie[0]);
    indicesCopie.push_back(combCopie[1]);

    // Sélectionner 2 chiffres qui ne sont PAS dans la combinaison
    vector<int> nonCombinaison;
    for (int i = 0; i < 10; i++) {
        if (find(combinaison.begin(), combinaison.end(), i) == combinaison.end()) {
            nonCombinaison.push_back(i);
        }
    }
    shuffle(nonCombinaison.begin(), nonCombinaison.end(), gen);
    indices.push_back(nonCombinaison[0]);
    indices.push_back(nonCombinaison[1]);

    // Mélanger tous les indices
    shuffle(indices.begin(), indices.end(), gen);

    // Afficher les indices
    for (int i = 0; i < indices.size(); i++) {
        if (find(indicesCopie.begin(), indicesCopie.end(), indices[i]) != indicesCopie.end()) {
            cout << "*** Indice " << (i + 1) << " : Le chiffre " << indices[i]
                << " est dans la combinaison ***" << endl;
        }
        else {
            cout << "*** Indice " << (i + 1) << " : Le chiffre " << indices[i]
                << " n'est pas dans la combinaison ***" << endl;
        }
    }
    cout << "*****************************************************************************" << endl;
}

// Fonction pour évaluer une tentative
pair<int, int> evaluerGuess(const vector<int>& combinaison, const vector<int>& guess) {
    int bienPlaces = 0;
    int malPlaces = 0;

    for (int i = 0; i < 4; i++) {
        if (guess[i] == combinaison[i]) {
            bienPlaces++;
        }
        else if (find(combinaison.begin(), combinaison.end(), guess[i]) != combinaison.end()) {
            malPlaces++;
        }
    }

    return make_pair(bienPlaces, malPlaces);
}

int main() {
    // Affichage du cadenas
    cout << "    +---+" << endl;
    cout << "  __|___|__ " << endl;
    cout << " /         \\" << endl;
    cout << "|    LOCK   |" << endl;
    cout << "|    0000   |" << endl;
    cout << " \\_________/" << endl;
    cout << "" << endl;

    cout << "Bienvenue dans le jeu du CADENAS ! Trouveras-tu la bonne combinaison pour l'ouvrir ?" << endl;
    cout << "Monsieur SERRES pense que non" << endl;
    cout << "Tu dois entrer des combinaisons de 4 chiffres differents (par exemple : 1234)" << endl;
    cout << "*****************************************************************************" << endl;

    vector<int> combinaison = genererCombinaison();
    int essaisRestants = 10;

    afficherIndices(combinaison);

    while (essaisRestants > 0) {
        string input;
        cout << "Entrez une combinaison de 4 chiffres (differents) > ";
        cin >> input;

        // Vérifier la validité de l'entrée
        if (input.length() != 4) {
            cout << "Veuillez entrer une combinaison valide de 4 chiffres differents > " << endl;
            continue;
        }

        bool valide = true;
        set<char> chiffresUniques;

        for (char c : input) {
            if (!isdigit(c)) {
                valide = false;
                break;
            }
            chiffresUniques.insert(c);
        }

        if (!valide || chiffresUniques.size() != 4) {
            cout << "Veuillez entrer une combinaison valide de 4 chiffres differents > " << endl;
            continue;
        }

        // Convertir l'entrée en vecteur d'entiers
        vector<int> guess;
        for (char c : input) {
            guess.push_back(c - '0');
        }

        pair<int, int> resultat = evaluerGuess(combinaison, guess);
        int bienPlaces = resultat.first;
        int malPlaces = resultat.second;

        cout << "> Nombre de chiffres bien places : " << bienPlaces << endl;
        cout << "> Nombre de chiffres mal places : " << malPlaces << "\n" << endl;

        essaisRestants--;

        if (bienPlaces == 4) {
            cout << "*****************************************************************************" << endl;
            cout << "BRAVO, vous avez trouve la combinaison correcte en " << (11 - essaisRestants) << " essais !" << endl;
            cout << "La combinaison correcte etait bien : ";
            for (int chiffre : combinaison) {
                cout << chiffre;
            }
            cout << endl;
            cout << "*****************************************************************************" << endl;
            break;
        }
    }

    if (essaisRestants == 0) {
        cout << "*****************************************************************************" << endl;
        cout << "PERDU. La combinaison correcte etait : ";
        for (int chiffre : combinaison) {
            cout << chiffre;
        }
        cout << endl;
        cout << "*****************************************************************************" << endl;
    }

    cout << "\nAppuyez sur Entree pour quitter...";
    cin.ignore();
    cin.get();

    return 0;
}
