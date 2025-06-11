import pygame

pygame.init()

# Grid settings
ROWS, COLS = 6, 9
CELL_SIZE = 60
WIDTH, HEIGHT = COLS * CELL_SIZE, ROWS * CELL_SIZE

# Pygame setup
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Pygame Grid")

# Colors
WHITE = (255, 255, 255)
GRAY = (200, 200, 200)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(WHITE)

    # Draw vertical lines
    for col in range(COLS + 1):
        pygame.draw.line(screen, GRAY, (col * CELL_SIZE, 0), (col * CELL_SIZE, HEIGHT), 2)

    # Draw horizontal lines
    for row in range(ROWS + 1):
        pygame.draw.line(screen, GRAY, (0, row * CELL_SIZE), (WIDTH, row * CELL_SIZE), 2)

    pygame.display.flip()

pygame.quit()
