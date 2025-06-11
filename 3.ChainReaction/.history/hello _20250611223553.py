import pygame

pygame.init()
screen = pygame.display.set_mode((1200, 900))
pygame.display.set_caption("Pygame Test")

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            break
pygame.quit()
