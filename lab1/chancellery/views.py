from django.shortcuts import render

# Create your views here.

from rest_framework import viewsets
from .models import pen
from .serializers import ChancellerySerializer

class ChancelleryViewSet(viewsets.ModelViewSet):
    queryset = pen.objects.all().order_by('id')
    serializer_class = ChancellerySerializer