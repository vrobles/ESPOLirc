from django.conf.urls import patterns, include, url
import sockets.views

urlpatterns = patterns('encuestas.formularios.urls',
	url(r'^$', sockets.views.Index.as_view(), name="index"),
	url(r'^conectar/$', sockets.views.Conectar, name="index"),
	url(r'^desconectar/$', sockets.views.Desconectar, name="index"),
)