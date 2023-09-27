from django.db import models


class Ingredient(models.Model):
    nom = models.CharField(max_length=50)


class Departement(models.Model):
    numero = models.IntegerField(MinValueValidator=1, MaxValueValidator=100)
    prixm2 = models.IntegerField(MinValueValidator=1)


class Prix(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    prix = models.IntegerField(MinValueValidator=0)


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    quantite = models.IntegerField(MinValueValidator=0)


class Machine(models.Model):
    nom = models.CharField(max_length=50)
    prix = models.IntegerField(MinValueValidator=0)


class Action(models.Model):
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    commande = models.CharField(max_length=50)
    duree = models.IntegerField(MinValueValidator=0)
    action = models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
        blank=True,
        null=True,
        # related_name"+",
    )


class Recette(models.Model):
    nom = models.CharField(max_length=50)
    action = models.ForeignKey(Action, on_delete=models.PROTECT)


class Usine(models.Model):
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    taille = models.IntegerField(MinValueValidator=1)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    recettes = models.ForeignKey(Recette, on_delete=models.PROTECT)
    stocks = models.IntegerField(MinValueValidator=0)