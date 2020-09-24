"""
	gestion des sprites de programme

"""

import pygame

class Sprite():
	#la cartes des sprites de programme 
	__spritesMap = {
		"menu" : pygame.image.load("images/menu.png"),
		"editor" : pygame.image.load("images/fond.jpg"),
		"successmenu" : pygame.image.load("images/menu_reussite.jpg"),
		"background" : pygame.image.load("images/fond.jpg"),
		"wall" : pygame.image.load("images/mur.png"),
		"player" : pygame.image.load("images/joueur.jpg"),
		"box" : pygame.image.load("images/caisse.jpg"),
		"target" : pygame.image.load("images/objectif.png"),
		"boxok" : pygame.image.load("images/caisse_ok.jpg"),
	}

	def __init__(self, name, position):
		pygame.init()
		self.name = name
		self.position = position
		
	#recuperer un sprite selon un nom
	def getSurface(self, name):
		return self.__spritesMap[self.name]
	
	#dessiner un sprite sur la scene
	def draw(self, scene):
		sprite = self.__spritesMap[self.name]
		scene.blit(sprite.convert(), self.position)