from django.conf.urls import patterns, include, url
from django.contrib import admin

urlpatterns = patterns('',
    # Examples:
    #url(r'^$', 'chat.views.home', name='home'),
    url(r'^chat/', include('sockets.urls')),

    url(r'^admin/', include(admin.site.urls)),
)
