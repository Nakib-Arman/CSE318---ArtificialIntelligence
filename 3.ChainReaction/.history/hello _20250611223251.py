import pygame

pygame.init()
screen = pygame.display.set_mode((800, 300))
pygame.display.set_caption("Pygame Test")

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
pygame.quit()
