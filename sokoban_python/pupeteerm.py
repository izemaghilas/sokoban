"""
	Gerer la creation des scenes, deplacement des marionnetes et creation de labyrinth
	"marionnettiste"
	
"""
import math

import pygame
from scenem import Scene
from spritem import Sprite
from puppetm import Player, Box

class Puppeteer():
	__labyrinth = [] #matrice represent le labyrinth
	__acts = ["menu", "level", "successmenu", "editor"] #liste des actes des scenes
	__player = None 
	__boxes = [] 
	__levels = [] 
	__index = 0 #identifient d'un level
	__N = 0 #nombre d'element dans une ligne de labyrinth
	__W = 40 #largeur des sprites
	
	"""
		creation d'une scene
		appel la methode addSprite() (class Sprite) (instansiation Scene)
	
	"""
	def createScene(scene_act, w, h):
		if scene_act in Puppeteer.__acts:
			scene = Scene(scene_act, w, h)
			if scene_act == "level":
				Puppeteer.__generateLabyrinth(scene)
			else:
				#create a sprite and add it to scene's sprites list
				sprite = Sprite(scene_act, (0,0))
				scene.addSprite(sprite)
			return scene
		else:
			return None;
		
	"""
		gerer les instruction(evenments clavier )
		appel les methodes :
			createScene()
			__manipulatePuppet()
			__onPuppetFront()
			
			getAct() (class Scene)
			setAct() (class Scene)
 			clearScene() (class Scene)
			getposition() (class Puppet)
			
	"""
	def performInstruction(scene, instruction, w=480, h=480):
		if scene:
			act = scene.getAct()
			if scene.inInstructions(instruction.key):
				if instruction.key == pygame.K_F1:
					if act!="level" and act=="menu":
						scene.clearScene()
						scene.setAct("level")
						Puppeteer.createScene("level", w, h)
					
				if instruction.key == pygame.K_F2:
					if act != "editor" and act == "menu":
						scene.clearScene()
						scene.setAct("editor")
						Puppeteer.createScene("editor", w, h)
						
				if instruction.key == pygame.K_F3:
					if act != "menu":
						Puppeteer.__labyrinth.clear()
						Puppeteer.__player = None
						Puppeteer.__boxes.clear()
						Puppeteer.__index  = 0
						
						scene.clearScene()
						scene.setAct("menu")
						Puppeteer.createScene("menu", w, h)
						
				if instruction.key == pygame.K_F4:
					if act == "successmenu":
						Puppeteer.__index+=1
						
						scene.clearScene()
						scene.setAct("level")
						Puppeteer.createScene("level", w, h)
						
				if instruction.key == pygame.K_UP:
					if act == "level":
						if Puppeteer.__player:
							pos = Puppeteer.__player.getposition()
							x = pos[0]
							y = pos[1]
							y-=Puppeteer.__W
							if y >= 0:
								if Puppeteer.__onPuppetFront((x, y)) == "2":
									if (y-Puppeteer.__W) >=0:
										boxnewpos = (x, y-Puppeteer.__W)
										if Puppeteer.__manipulatePuppet(scene, "box", (x, y), boxnewpos):
											Puppeteer.__manipulatePuppet(scene, "player", pos, (x, y))
								else:
									Puppeteer.__manipulatePuppet(scene, "player", pos, (x, y))
								
								if len(Puppeteer.__boxes) == 0:
									scene.clearScene()
									scene.setAct("successmenu")
									Puppeteer.createScene("successmenu", w, h)
					
				if instruction.key == pygame.K_DOWN:
					if act == "level":
						if Puppeteer.__player:
							pos = Puppeteer.__player.getposition()
							x = pos[0]
							y = pos[1]
							y+=Puppeteer.__W
							if y <= scene.getDimension()[1]-Puppeteer.__W:
								if Puppeteer.__onPuppetFront((x, y)) == "2":
									if (y+Puppeteer.__W) <= scene.getDimension()[1]-Puppeteer.__W:
										boxnewpos = (x, y+Puppeteer.__W)
										if Puppeteer.__manipulatePuppet(scene, "box", (x, y), boxnewpos) :
											Puppeteer.__manipulatePuppet(scene, "player", pos, (x, y))
								else:
									Puppeteer.__manipulatePuppet(scene, "player", pos, (x, y))
								
								if len(Puppeteer.__boxes) == 0:
									scene.clearScene()
									scene.setAct("successmenu")
									Puppeteer.createScene("successmenu", w, h)
				
				if instruction.key == pygame.K_LEFT:
					if act == "level":
						if Puppeteer.__player:
							pos = Puppeteer.__player.getposition()
							x = pos[0]
							y = pos[1]
							x-=Puppeteer.__W
							if x >= 0:
								if Puppeteer.__onPuppetFront((x, y)) == "2":
									if (x-Puppeteer.__W) >=0:
										boxnewpos = (x-Puppeteer.__W, y)
										if Puppeteer.__manipulatePuppet(scene, "box",(x, y), boxnewpos):
											Puppeteer.__manipulatePuppet(scene, "player", pos, (x, y))
								else:
									Puppeteer.__manipulatePuppet(scene, "player", pos, (x, y))
								
								if len(Puppeteer.__boxes) == 0:
									scene.clearScene()
									scene.setAct("successmenu")
									Puppeteer.createScene("successmenu", w, h)
											
				if instruction.key == pygame.K_RIGHT:
					if act == "level":
						if Puppeteer.__player:
							pos = Puppeteer.__player.getposition()
							x = pos[0]
							y = pos[1]
							x+=Puppeteer.__W
							if x <= scene.getDimension()[0]-Puppeteer.__W:
								if Puppeteer.__onPuppetFront((x, y)) == "2":
									if (x+Puppeteer.__W) <= scene.getDimension()[0]-Puppeteer.__W:
										boxnewpos = (x+Puppeteer.__W, y)
										if Puppeteer.__manipulatePuppet(scene, "box",(x, y), boxnewpos):
											Puppeteer.__manipulatePuppet(scene, "player",pos,  (x,y))
								else:
									Puppeteer.__manipulatePuppet(scene, "player",pos,  (x,y))
								
								if len(Puppeteer.__boxes) == 0:
									scene.clearScene()
									scene.setAct("successmenu")
									Puppeteer.createScene("successmenu", w, h)
									
					
			else:
				print("Puppeteer--> Failed to perform instruction on specified scene")
		else:
			print("Puppeteer--> No Scene ")
	
	"""
		deplacer le joueur et les caisse
		appel les methodes:
			__onPuppetFront()
			__editLabyrinth()
			move() (class Puppet)
			getposition() (class Puppet) 
			setontarget() (class Player)
	"""
	def __manipulatePuppet(scene, puppet, formerpos, newpos, w=480, h=480):
		success = True
		if puppet == "player":
			onfront = Puppeteer.__onPuppetFront(newpos)
			if onfront == "1":
				Puppeteer.__player.setontarget(False)
				success = False
			elif onfront == "3":
				#edit labyrinth
				Puppeteer.__editLabyrinth("4", formerpos, newpos)
				Puppeteer.__player.move(scene, newpos)
				Puppeteer.__player.setontarget(True)
			else:
				#edit labyrinth
				Puppeteer.__editLabyrinth("4", formerpos, newpos)
				Puppeteer.__player.move(scene, newpos)
				Puppeteer.__player.setontarget(False)
				
		elif puppet == "box":
			box = None
			for b in Puppeteer.__boxes:
				bpos = b.getposition()
				if formerpos == bpos:
					box = b
					break
			if not box:
				success = False
			else:
				onfront = Puppeteer.__onPuppetFront(newpos)
				if onfront == "1" or onfront == "2":
					success = False
				if onfront == "3":
					Puppeteer.__boxes.remove(box)
					box.makeUP()
					box.move(scene, newpos)
					Puppeteer.__editLabyrinth("1", formerpos, newpos)
						
				if onfront == "0":
					Puppeteer.__editLabyrinth("2", formerpos, newpos)
					box.move(scene, newpos)
		else:
			success = False
			print("Puppeteer--> Failed to manipulate puppet ", puppet)
		return success
	
	#savoir c'est quoi l'element qui ce trouve devant une caisse et le joueur
	def __onPuppetFront(position):
		x = position[0]//Puppeteer.__W
		y = position[1]//Puppeteer.__W
		p = Puppeteer.__labyrinth[y][x]
		
		return p
		
	
	"""
		mettre a jour la matrice apres un deplacement
		appel la methode isontarget(class Puppet)
	"""
	
	def __editLabyrinth(puppet, formerpos, newpos):
		x_f = formerpos[0]//Puppeteer.__W
		y_f = formerpos[1]//Puppeteer.__W
		
		x_n = newpos[0]//Puppeteer.__W
		y_n = newpos[1]//Puppeteer.__W
		if puppet == "4":
			if Puppeteer.__player.isontarget():
				Puppeteer.__labyrinth[y_f][x_f] = "3"
				Puppeteer.__labyrinth[y_n][x_n] = puppet
			else:
				Puppeteer.__labyrinth[y_f][x_f] = "0"
				Puppeteer.__labyrinth[y_n][x_n] = puppet
		else:
			Puppeteer.__labyrinth[y_f][x_f] = "0"
			Puppeteer.__labyrinth[y_n][x_n] = puppet
		
	
	"""
		generer la representation graphique d'un labyrinth a partir d'une matrice
		appel les methodes:
			__setMatrix
			addPuppet (class Scene)
			addSprite (class Scene)
	"""
	def __generateLabyrinth(scene):
		if Puppeteer.__setMatrix():
			SIZE = len(Puppeteer.__labyrinth)
			#create background
			scene.addSprite(Sprite("background", (0,0)))
			for y in range(0, SIZE):
				for x in range(0, Puppeteer.__N):
					s = Puppeteer.__labyrinth[y][x]
					if s == "0":
						continue
					if s == "1":
						scene.addSprite(Sprite("wall", (x*Puppeteer.__W,y*Puppeteer.__W)))
					if s == "2":
						box = Box((x*Puppeteer.__W,y*Puppeteer.__W))
						Puppeteer.__boxes.append(box)
						scene.addPuppet(box)
						
					if s == "3":
						scene.addSprite(Sprite("target", (x*Puppeteer.__W,y*Puppeteer.__W)))
					if s == "4":
						Puppeteer.__player = Player((x*Puppeteer.__W,y*Puppeteer.__W))
						scene.addPuppet(Puppeteer.__player)
						
		else:
			Puppeteer.__labyrinth.clear()
			Puppeteer.__player = None
			Puppeteer.__boxes.clear()
			Puppeteer.__index  = 0
			
			print("Puppeteer--> Failed to generate Labyrinth")
	
	"""
		creation d'une matrice a partir d'un niveau (representer par une chaine de caracteres)
		appel la methode __getLevel() 
	"""
	def __setMatrix():
		success = True
		try:
			level = Puppeteer.__getLevel()
			if level != "":
				SIZE = len(level)
				Puppeteer.__N = int(math.sqrt(SIZE))
				if Puppeteer.__N == 12:
					lvl_index = 0
					while(lvl_index<SIZE):
						row = []
						for i in range(lvl_index, Puppeteer.__N+lvl_index):
							row.append(level[i])
						lvl_index+=Puppeteer.__N
						Puppeteer.__labyrinth.append(row)
						row = []
				else:
					success = False
			else:
				success = False
				print("Puppeteer--> Failed to set Matrix from empty level, check file structure")
		except:
			success = False
		
		return success
		
	"""
		recuperation d'un niveau a partir d'une liste de niveau
		appel la methode __readLevels() 
	"""
	def __getLevel():
		level = ""
		if len(Puppeteer.__levels) == 0:
			if Puppeteer.__readLevels():
				if Puppeteer.__index < len(Puppeteer.__levels): 
					level = Puppeteer.__levels[Puppeteer.__index]
				else:
					level = ""
			else:
				level = ""
		else:
			if Puppeteer.__index < len(Puppeteer.__levels): 
					level = Puppeteer.__levels[Puppeteer.__index]
			else:
				level = ""
			
		return level
	
	"""
		chargement des niveaux a partir de fichier niveaux.txt
	"""
	def __readLevels(file = "fichiers/niveaux.txt"):
		success = True
		try:
			with open(file, "r", encoding="utf-8") as lvl:
				lines = lvl.readlines()
				for line in lines:
					Puppeteer.__levels.append(line)
		except:
			success = False
			print("Puppeteer--> Failed to read from file ", file)
		
		return success