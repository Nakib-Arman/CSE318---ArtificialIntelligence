import pygame

pygame.init()

screen = pygame.display.set_mode((1200,900))
pygame.display.set_caption("Chain Reaction")

background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background,(1200,900))
background.set_alpha(128)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    screen.blit(background,(0,0))
    pygame.display.flip()