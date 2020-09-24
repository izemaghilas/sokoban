"""
	point d'entrer de programme sokoban
	appel les methodes:
		instansiation de Stage
		showScene (class Stage)
		managerInstruction (class Stage)
	
"""
import pygame
from stagem import Stage

stage = Stage()
stage.showScene()

while stage.isOpen():
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			stage.close()
		if event.type == pygame.KEYDOWN:
			stage.managerInstruction(event)