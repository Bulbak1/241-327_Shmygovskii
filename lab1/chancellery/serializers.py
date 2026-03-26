from rest_framework import serializers
from .models import pen

class ChancellerySerializer(serializers.ModelSerializer):
    class Meta:
        model = pen
        fields = '__all__'