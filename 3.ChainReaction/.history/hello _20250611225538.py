import pygame

pygame.init()

screen = pygame.display.set_mode((1200,900))
pygame.display.set_caption("Chain Reaction")
icon = pygame.image.load("chain-reaction.png")
pygame.display.set

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
