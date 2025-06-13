import pygame

pygame.init()

# screen setup
screen_x, screen_y = 1200, 900
screen = pygame.display.set_mode((screen_x, screen_y))
pygame.display.set_caption("Chain Reaction")

# background image setup
background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background, (screen_x, screen_y))
background.set_alpha(128)

# grid setup
rows, cols = 9, 6
grid_x = (screen_x - cols * 80) // 2
grid_y = (screen_y - rows * 80) // 2
cell_surface = pygame.Surface((80, 80), pygame.SRCALPHA)

# Mock grid state with orb counts for demonstration (replace with your game state later)
orb_grid = [[0 for _ in range(cols)] for _ in range(rows)]
# For example purposes, populate some cells with orbs (1 to 3)
orb_grid[2][3] = 1
orb_grid[4][2] = 2
orb_grid[5][5] = 3

# Orb drawing function
def draw_orbs(cell_center, count, color):
    positions = []
    x, y = cell_center
    offset = 12

    if count == 1:
        positions = [(x, y)]
    elif count == 2:
        positions = [(x - offset, y), (x + offset, y)]
    elif count == 3:
        positions = [(x - offset, y + offset), (x, y - offset), (x + offset, y + offset)]

    # Draw lines between orbs
    for i in range(len(positions)):
        for j in range(i + 1, len(positions)):
            pygame.draw.line(screen, color, positions[i], positions[j], 2)

    # Draw orbs
    for pos in positions:
        pygame.draw.circle(screen, color, pos, 8)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # background image
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))

    # making the grid
    for i in range(rows):
        for j in range(cols):
            cell_surface.fill((10, 21, 97, 50))
            screen.blit(cell_surface, (grid_x + j * 80, grid_y + i * 80))

    for i in range(rows + 1):
        pygame.draw.line(screen, (255, 255, 255), (grid_x, grid_y + i * 80), (grid_x + cols * 80, grid_y + i * 80), 2)

    for i in range(cols + 1):
        pygame.draw.line(screen, (255, 255, 255), (grid_x + i * 80, grid_y), (grid_x + i * 80, grid_y + rows * 80), 2)

    # draw orbs (after grid so they appear on top)
    for i in range(rows):
        for j in range(cols):
            count = orb_grid[i][j]
            if count > 0:
                center = (grid_x + j * 80 + 40, grid_y + i * 80 + 40)
                draw_orbs(center, count, (255, 0, 0))  # red orbs

    pygame.display.flip()

pygame.quit()
