#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Classe représentant un département
class Departement {
public:
    Departement(int numero, int prixm2);
    Departement(int id);
    int numero;
    float prixm2;

    friend std::ostream& operator << (std::ostream& out, const Departement& p){ return out <<"Departement : " << p.numero << "prix au m² : " << p.prixm2;
    }
};

Departement::Departement(int id) {
    std::string link = "http://localhost:8000/departement/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    numero = data["numero"];
    prixm2 = data["prixm2"];
}



class Ingredient {
public:

    Ingredient(int id);
    std::string nom;

    friend std::ostream& operator << (std::ostream& out, const Ingredient& p){ return out <<"Ingredient : " << p.nom;
    }
};

Ingredient::Ingredient(int id) {
    std::string link = "http://localhost:8000/ingredient/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    nom = data["nom"];
}

class Prix {
public:

    Prix(int id);

    std::unique_ptr<Ingredient> ingredient;
    std::unique_ptr<Departement> departement;
    int prix;

    friend std::ostream& operator << (std::ostream& out, const Prix& p){ return out <<"Prix de l'ingredient " << *p.ingredient << " dans le " << p.departement->numero << " de : " << p.prix << " €.";
    }
};

Prix::Prix(int id) {
    std::string link = "http://localhost:8000/prix/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    departement = std::make_unique<Departement>(data["departement"]);
    ingredient = std::make_unique<Ingredient>(data["ingredient"]);
    prix = data["prix"];
}

class QuantiteIngredient {
public:

    QuantiteIngredient(int id);
    std::unique_ptr<Ingredient> ingredient;
    int quantite;

    friend std::ostream& operator << (std::ostream& out, const QuantiteIngredient& p){ return out <<"Nom de l' " << *p.ingredient << " quantite : " << p.quantite;
    }
};

QuantiteIngredient::QuantiteIngredient(int id) {
    std::string link = "http://localhost:8000/quantiteingredient/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    ingredient = std::make_unique<Ingredient>(data["ingredient"]);
    quantite = data["quantite"];
}

class Machine {
public:
    Machine(int id);
    std::string nom;
    int prix;

    friend std::ostream& operator << (std::ostream& out, const Machine& p){ return out <<"Nom de la machine :  " << p.nom << " et son prix : " << p.prix;
    }
};

Machine::Machine(int id) {
    std::string link = "http://localhost:8000/machine/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    nom = data["nom"];
    prix = data["prix"];

}

int main() {
    //Departement
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/departement/6"});
    json data = json::parse(r.text);
    Departement d{6};
    std::cout << "Departement d{selectionné}: " << d << std::endl;
    //Ingredient
    cpr::Response r2 = cpr::Get(cpr::Url{"http://localhost:8000/ingredient/12"});
    json data2 = json::parse(r2.text);
    Ingredient i{12};
    std::cout << "Ingredient i{selectionné}: " << i << std::endl;
    //Prix
    cpr::Response r3 = cpr::Get(cpr::Url{"http://localhost:8000/prix/7"});
    Prix p{7};
    std::cout << "Prix p{selectionné}: " << p << std::endl;
    // QuantiteIngredient
    cpr::Response r4 = cpr::Get(cpr::Url{"http://localhost:8000/quantiteingredient/8"});
    json data4 = json::parse(r4.text);
    QuantiteIngredient q{8};
    std::cout << "QuantiteIngredient q{selectionné}: " << q << std::endl;
    // Machine
    cpr::Response r5 = cpr::Get(cpr::Url{"http://localhost:8000/machine/8"});
    json data5 = json::parse(r5.text);
    Machine m{5};
    std::cout << "Machine q{selectionné}: " << m << std::endl;
    return 0;
}
