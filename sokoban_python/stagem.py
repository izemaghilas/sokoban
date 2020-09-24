"""
	la fenetre de programme sokoban
"""
import pygame
from pupeteerm import Puppeteer


class Stage():
	__WIDTH = 480
	__HEIGHT = 480
	__TITLE = "SOKOBAN"
	scene = None
	performing = True
	
	def __init__(self):
		pygame.init()
		self.scene = Puppeteer.createScene("menu",self.__WIDTH, self.__HEIGHT)
		pygame.display.set_caption(self.__TITLE)
		if not self.scene:
			self.performing = False
			print("Stage--> Failed to create a Scene")
		
	
	#montrer la scene
	def showScene(self): 
		self.scene.show()
		pygame.display.flip()
	
	#verifier si le stage est ouvert
	def isOpen(self):
		if self.performing:
			return True
		else:
			return False
	
	#fermer le stage
	def close(self):
		self.performing = False
		
		
	#gerer les instruction (evenement de clavier)
	def managerInstruction(self, instruction):
		Puppeteer.performInstruction(self.scene, instruction)
		self.showScene()