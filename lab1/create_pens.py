import os
import django
import random
from datetime import date, timedelta

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'lab1.settings')
django.setup()

from chancellery.models import pen

names = ["Parker", "Erich Krause", "BIC", "Pilot", "Lamy", "Stabilo", "Schneider"]
types = ['ballpoint', 'gel', 'fountain', 'roller']

for i in range(1, 101):
    pen.objects.create(
        name=random.choice(names) + " " + str(random.randint(1, 10)),
        price=round(random.uniform(50, 500), 2),
        quantity=random.randint(0, 200),
        weight=round(random.uniform(8, 30), 1),
        created_at=date.today() - timedelta(days=random.randint(0, 365)),
        description="Test description " + str(i),
        sku=f"SKU-{i:04d}",
        pen_type=random.choice(types)
    )

print("100 pens created!")