from django.db import models


class Ingredient(models.Model):
    nom = models.CharField(max_length=50)

    def __str__(self):
        return self.nom


class Departement(models.Model):
    numero = models.IntegerField()
    prixm2 = models.IntegerField()

    def __str__(self):
        return f"Département {self.numero} à {self.prixm2}€ par m²"


class Prix(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    prix = models.IntegerField()

    def __str__(self):
        return (
            f"Ingrédient {self.ingredient} du département"
            f" {self.departement.numero} à {self.prix}€"
        )


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    quantite = models.IntegerField()

    def __str__(self):
        return f"Ingredient {self.ingredient.nom} quantité {self.quantite}"


class Machine(models.Model):
    nom = models.CharField(max_length=50)
    prix = models.IntegerField()


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


class Recette(models.Model):
    nom = models.CharField(max_length=50)
    action = models.ForeignKey(Action, on_delete=models.PROTECT)


class Usine(models.Model):
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    taille = models.IntegerField()
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    recettes = models.ForeignKey(Recette, on_delete=models.PROTECT)
    stocks = models.IntegerField()
