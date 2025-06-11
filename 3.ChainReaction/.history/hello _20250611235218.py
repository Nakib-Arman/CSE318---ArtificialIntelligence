import pygame

pygame.init()

# Screen setup
SCREEN_WIDTH, SCREEN_HEIGHT = 1200, 900
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Chain Reaction")

# Load background image
background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background, (SCREEN_WIDTH, SCREEN_HEIGHT))
background.set_alpha(128)

# Grid settings
rows, cols = 9, 6

# Total grid size
GRID_WIDTH = COLS * CELL_SIZE
GRID_HEIGHT = ROWS * CELL_SIZE

# Top-left corner of the grid (to center it)
GRID_X = (SCREEN_WIDTH - GRID_WIDTH) // 2
GRID_Y = (SCREEN_HEIGHT - GRID_HEIGHT) // 2

# Colors
GRID_COLOR = (255, 255, 255)  # white grid lines

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Draw background
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))

    # Draw grid
    for row in range(ROWS + 1):
        pygame.draw.line(screen, GRID_COLOR,
                         (GRID_X, GRID_Y + row * CELL_SIZE),
                         (GRID_X + GRID_WIDTH, GRID_Y + row * CELL_SIZE), 2)

    for col in range(COLS + 1):
        pygame.draw.line(screen, GRID_COLOR,
                         (GRID_X + col * CELL_SIZE, GRID_Y),
                         (GRID_X + col * CELL_SIZE, GRID_Y + GRID_HEIGHT), 2)

    pygame.display.flip()

pygame.quit()
