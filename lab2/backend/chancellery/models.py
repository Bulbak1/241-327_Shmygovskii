from django.db import models

# Create your models here.

class pen(models.Model):
    PEN_TYPES = [
        ('ballpoint', 'Шариковая'),
        ('gel', 'Гелевая'),
        ('fountain', 'Перьевая'),
        ('roller', 'Роллер'),
    ]

    name = models.CharField(max_length=200)
    price = models.DecimalField(max_digits=8, decimal_places=2)
    quantity = models.IntegerField()
    weight = models.FloatField()
    created_at = models.DateField()
    description = models.TextField()
    sku = models.CharField(max_length=50, unique=True)
    pen_type = models.CharField(max_length=20, choices=PEN_TYPES, default='ballpoint')