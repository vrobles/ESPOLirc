from django.shortcuts import render
from django.core.urlresolvers import reverse
from django.http import HttpResponseRedirect,HttpResponse
from django.views.generic import ListView,TemplateView
from django.contrib.sessions.models import Session
import json
import datetime
import socket
from time import sleep
from threading import Thread

socket_principal = None

class ConexionThread(Thread):
	def __init__(self):
		super(ConexionThread, self).__init__()
	def run(self):
		host = 'localhost'    
		port = 7200# The same port as used by the server
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.connect((host, port))
		s.sendall(b'Hello, world2')
		#self.request.session.get('socket', s)
		global socket_principal
		socket_principal = s
		data = s.recv(1024)
		print('Received', repr(data))
		while socket_principal is not None:
			print socket_principal
			sleep(10)
		s.close()


class Index(TemplateView):
	template_name = 'index.html'
	def get_context_data(self, **kwargs):
		context = super(Index, self).get_context_data(**kwargs)
		return context

def Conectar(request):
	t = ConexionThread()
	t.start()
	return HttpResponse(1)

def Desconectar(request):
	global socket_principal
	socket_principal = None
	print socket_principal
	return HttpResponse(1)