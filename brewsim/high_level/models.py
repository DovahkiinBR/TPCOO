from django.db import models


class Ingredient(models.Model):
    nom = models.CharField(max_length=50)

    def __str__(self):
        return self.nom

    def json(self):
        return {"nom": self.nom}


class Departement(models.Model):
    numero = models.IntegerField()
    prixm2 = models.IntegerField()

    def __str__(self):
        return f"Département {self.numero}"

    def json(self):
        return {"numero": self.numero, "prixm2": self.prixm2}


class Prix(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    prix = models.IntegerField()

    def __str__(self):
        return (
            f"Ingrédient {self.ingredient} du département"
            f" {self.departement.numero} à {self.prix}€"
        )

    def json(self):
        return {
            "ingredient": self.ingredient.id,
            "departement": self.departement.id,
            "prix": self.prix,
        }


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    quantite = models.IntegerField()

    def __str__(self):
        return f"{self.ingredient.nom} quantité {self.quantite}"

    def couts(self, departement):
        return (
            self.ingredient.prix_set.get(departement__numero=departement).prix
            * self.quantite
        )

    def json(self):
        return {"ingredient": self.ingredient.id, "quantite": self.quantite}


class Machine(models.Model):
    nom = models.CharField(max_length=50)
    prix = models.IntegerField()

    def __str__(self):
        return f"{self.nom}"

    def json(self):
        return {"nom": self.nom, "prix": self.prix}


class Action(models.Model):
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    commande = models.CharField(max_length=50)
    duree = models.IntegerField()
    action = models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
        blank=True,
        null=True,
        related_name="+",
    )

    def __str__(self):
        return f"{self.commande}"

    def json(self):
        return {
            "machine": self.machine.id,
            "ingredient": self.ingredient.id,
            "commande": self.commande,
            "duree": self.duree,
            "action": self.action.id,
        }


class Recette(models.Model):
    nom = models.CharField(max_length=50)
    action = models.ForeignKey(Action, on_delete=models.PROTECT)

    def __str__(self):
        return f"{self.nom}"

    def json(self):
        return {"nom": self.nom, "action": self.action.id}


class Usine(models.Model):
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    taille = models.IntegerField()
    machines = models.ManyToManyField(Machine)
    recettes = models.ManyToManyField(Recette)
    stocks = models.ManyToManyField(QuantiteIngredient)

    def __str__(self):
        return f"Usine du {self.departement}"

    def somme_machines(self):
        som = 0
        for i in self.machines.all():
            som = som + i.prix
        return som

    def somme_stocks(self):
        som = 0
        for i in self.stocks.all():
            som = som + i.couts(self.departement.numero)
        return som

    def costs(self):
        return (
            self.departement.prixm2 * self.taille
            + self.somme_machines()
            + self.somme_stocks()
        )

    def json(self):
        return {
            "departement": self.departement.id,
            "taille": self.taille,
            "machines": [m.id for m in self.machines.all()],
            "recettes": [r.id for r in self.recettes.all()],
            "stocks": [s.id for s in self.stocks.all()],
        }
