"""
	definition des marionnettes gerer par le marionnettiste
	
"""
import pygame
from spritem import Sprite

"""
	class Mere des marionnettes
"""
class Puppet():
	width = 40  
	height = 40
	name = "" 
	position = None 
	sprite = None
	surface = None #l'objet pygame.Surface qui represente la marionnette
	
	def __init__(self):
		self.name = "puppet"
	
	#monter la marionnettes sur la scene	
	def show(self, scene):
		scene.blit(self.surface, self.position)
	
	#deplacer la marionnette en scene
	def move(self, scene, newposition):
		scene.removePuppet(self)
		self.setposition(newposition)
		scene.addPuppet(self)
	
	#mettre a jour la position de la marionnette
	def setposition(self, position):
		self.position = position
	
	#recuperer la position de la marionnette
	def getposition(self):
		return self.position
	
		
class Player(Puppet):
	def __init__(self, position):
		self.name = "player"
		self.position = position
		self.sprite = Sprite(self.name, self.position)
		self.surface = self.sprite.getSurface(self.name)
		self.ontarget = False
	
	#specifier si la marionnette(player) se retrouve sur le sprite "objectif"
	def setontarget(self, flag):
		self.ontarget = flag
	
	#savoir si la marionnette(player) se retrouve sur l'objectif
	def isontarget(self):
		return self.ontarget

class Box(Puppet):
	def __init__(self, position):
		self.name = "box"
		self.position = position
		self.sprite = Sprite(self.name, self.position)
		self.surface = self.sprite.getSurface(self.name)
	#changer l'apparence de la caisse quant elle se retrouve sur l'objectif
	def makeUP(self):
		self.name = "boxok"
		self.sprite = Sprite(self.name, self.position)
		self.surface = self.sprite.getSurface(self.name)