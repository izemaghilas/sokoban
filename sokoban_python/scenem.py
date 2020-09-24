"""
	scene pour le marionnistte

"""

import pygame


class Scene():
	__sprites = [] 
	__puppets = []
	__instructions = [] #list d'instruction reconnu par cette scene
	
	def __init__(self, act, width, height):
		self.act = act
		self.width = width 
		self.height = height
		self.surface = pygame.display.set_mode((self.width, self.height)) 
		self.__setInstructions()
	
	#recuperer la dimension d'une scene
	def getDimension(self):
		return (self.width, self.height)
	
	#recuperer l'objet surface de la scene (faciliter les blit)
	def getsurface(self):
		return self.surface
	
	#ajout d'un sprite a la liste des sprites
	def addSprite(self, sprite):
		if sprite:
			self.__sprites.append(sprite)
		
	#ajout d'une marionnette a la liste des marionnettes
	def addPuppet(self, puppet):
		if puppet :
			self.__puppets.append(puppet)
			
	#suppression d'une marionnette de la liste des marionnettes
	def removePuppet(self, puppet):
		if puppet:
			self.__puppets.remove(puppet)
	
	#specifier les instruction reconnues par la scene
	def __setInstructions(self):
		if self.act == "menu":
			self.__instructions.extend( (pygame.K_F1, pygame.K_F2, pygame.K_F3) )
		elif self.act == "successmenu":
			self.__instructions.extend( (pygame.K_F4, pygame.K_F3) )
		elif self.act == "level":
			self.__instructions.extend( (pygame.K_UP, pygame.K_DOWN, pygame.K_LEFT, pygame.K_RIGHT, pygame.K_F3) )
		elif self.act == "editor":
			self.__instructions.append(pygame.K_F3)
		else:
			self.__instructions = []
	
	#savoir si une instruction est reconnu par la scene
	def inInstructions(self, instruction):
		if instruction in self.__instructions:
			return True
		else:
			return False
			
	#specifier l'act de scene
	def setAct(self, act):
		self.act = act
		
	#recuperer l'act de scene
	def getAct(self):
		return self.act
	
	#netoyer la scene	
	def clearScene(self):
		self.__sprites.clear()
		self.__puppets.clear()
		self.name = ""
		
	#montrer la scene
	def show(self):
		for sprite in self.__sprites:
			sprite.draw(self.surface)
		if len(self.__puppets) > 0:
			for puppet in self.__puppets:
				puppet.show(self.surface)