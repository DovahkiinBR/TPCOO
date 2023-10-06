#include <iostream>
#include <cpr/cpr.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
class Departement{

    int numero_;
    float prixm2_;
    json data_;
    int id_;

    public :

        Departement(int numero, float prixm2) : numero_{numero}, prixm2_{prixm2}{}
        construct1(json data) : data_{data}{}
        construct2(int id) : id_{id}{}

        friend std::ostream& operator<<(std::ostream& out, const Departement& D) {
        return out << D.numero_ << " / " << D.prixm2_;
        }
};

auto main()-> int{

    //std::cout << Departement{31, 20} << "\n";
    cpr::Response r  = cpr::Get(cpr::Url("http://localhost:8000/departement/6"));
    json j = json::parse(r.text);
    //std::string numero1 = j["numero"];
    //int prix = j["prixm2"];

    std::cout << j << std::endl;
    //std::cout << "Numero departement" << numero1 << std::endl;
return 0;
}
