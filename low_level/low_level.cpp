#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Classe représentant un département
class Departement {
public:
    Departement(int numero, int prixm2);
    Departement(json data);
    Departement(int id);

    friend std::ostream& operator << (std::ostream& out, const Departement& p);

private:
    int numero;
    float prixm2;
};

Departement::Departement(int numero, int prixm2) : numero(numero), prixm2(prixm2) {}

Departement::Departement(json data) : numero(data["numero"]), prixm2(data["prixm2"]) {}

Departement::Departement(int id) {
    std::cout << "Requete http http://localhost:8000/departement/ :" + std::to_string(id) << std::endl;
    std::string link = "http://localhost:8000/departement/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    numero = data["numero"];
    prixm2 = data["prixm2"];
}

std::ostream& operator << (std::ostream& out, const Departement& p) {
    return out << "Numero de Departement : " << p.numero << " / " << "Prix en m² : " << p.prixm2;
}

// Classe représentant un ingrédient
class Ingredient {
public:
    Ingredient(int id);
    std::string nom_Ingredient;
};

Ingredient::Ingredient(int id) {
    std::string link = "http://localhost:8000/ingredient/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    nom_Ingredient = data["nom"];
}

// ... (définitions similaires pour les autres classes)

int main() {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/departement/6"});
    json data = json::parse(r.text);
    std::cout << "Reponse HTTP :" << std::endl;
    std::cout << r.text << "\n";
    Departement d{6};
    std::cout << "d : " << d << std::endl;

    return 0;
}
