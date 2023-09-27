# mysite/admin.py
from djongo.contrib import admin

from . import models

admin.site.register(models.Departement)
admin.site.register(models.Usine)
admin.site.register(models.Prix)
admin.site.register(models.Ingredient)
admin.site.register(models.QuantiteIngredient)
admin.site.register(models.Machine)
admin.site.register(models.Recette)
admin.site.register(models.Action)
