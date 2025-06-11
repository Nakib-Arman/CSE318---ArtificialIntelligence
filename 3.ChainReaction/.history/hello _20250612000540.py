import pygame

pygame.init()

# Screen setup
screen_x,screen_y = 1200,900
screen = pygame.display.set_mode((screen_x, screen_y))
pygame.display.set_caption("Chain Reaction")

#background image setup
background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background, (screen_x, screen_y))
background.set_alpha(128)

# Grid setup
rows, cols = 9, 6
grid_x = (screen_x-cols*80) // 2
grid_y = (screen_y-rows*80) // 2
cell_surface = pygame.Surface((80,80),pygame.SRCALPHA)


running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    #background image
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))

    #Grid
    for i in range
    for i in range(rows + 1):
        pygame.draw.line(screen, (255,255,255),(grid_x, grid_y + i*80),(grid_x + cols*80, grid_y + i*80), 2)

    for i in range(cols + 1):
        pygame.draw.line(screen, (255,255,255),(grid_x + i*80, grid_y),(grid_x + i*80, grid_y + rows*80), 2)

    pygame.display.flip()

pygame.quit()
