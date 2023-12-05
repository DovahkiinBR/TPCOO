#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Classe représentant un département
class Departement {
public:
    Departement(int numero, int prix_m2);
    Departement(json& data);
    Departement(int id);

    friend std::ostream& operator << (std::ostream& out, const Departement& p);

private:
    int numero_Departement;
    float prix_m2_Departement;
};

Departement::Departement(int numero, int prix_m2) : numero_Departement(numero), prix_m2_Departement(prix_m2) {}

Departement::Departement(json data) : numero_Departement(data["numero"]), prix_m2_Departement(data["prix_m2"]) {}

Departement::Departement(int id) {
    std::string link = "http://localhost:8000/departement/" + std::to_string(id);
    cpr::Response r  = cpr::Get(cpr::Url(link));
    json data = json::parse(r.text);
    numero_Departement = data["numero"];
    prix_m2_Departement = data["prix_m2"];
}

std::ostream& operator << (std::ostream& out, const Departement& p) {
    return out << "Numero de Departement : " << p.numero_Departement << " / " << "Prix en m² : " << p.prix_m2_Departement;
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
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/Departement/1"});
    json data = json::parse(r.text);
    std::cout << "Reponse HTTP :" << std::endl;
    std::cout << r.text << "\n";
    Departement d{1};
    std::cout << "d : " << d << std::endl;

    return 0;
}
