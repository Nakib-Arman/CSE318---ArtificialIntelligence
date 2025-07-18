import pygame

pygame.init()

# Screen setup
screen_x,screen_y = 1200
screen = pygame.display.set_mode((1200, 900))
pygame.display.set_caption("Chain Reaction")

# Load background image
background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background, (SCREEN_WIDTH, SCREEN_HEIGHT))
background.set_alpha(128)

# Grid settings
rows, cols = 9, 6
GRID_X = (SCREEN_WIDTH - cols*80) // 2
GRID_Y = (SCREEN_HEIGHT - rows*80) // 2


running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Draw background
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))

    # Draw grid
    for row in range(rows + 1):
        pygame.draw.line(screen, (255,255,255),(GRID_X, GRID_Y + row*80),(GRID_X + cols*80, GRID_Y + row*80), 2)

    for col in range(cols + 1):
        pygame.draw.line(screen, (255,255,255),(GRID_X + col*80, GRID_Y),(GRID_X + col*80, GRID_Y + rows*80), 2)

    pygame.display.flip()

pygame.quit()
