from json import dumps

from django.http import HttpResponse
from django.views.generic import DetailView

from .models import Departement


class DepartementDetailView(DetailView):
    model = Departement

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))
