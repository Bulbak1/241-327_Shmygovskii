from django.urls import path, include
from rest_framework.routers import DefaultRouter
from .views import ChancelleryViewSet

router = DefaultRouter()
router.register(r'pens', ChancelleryViewSet)

urlpatterns = [
    path('', include(router.urls)),
]