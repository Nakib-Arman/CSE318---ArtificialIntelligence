import pygame

pygame.init()

# screen setup
screen_x,screen_y = 1200,900
screen = pygame.display.set_mode((screen_x, screen_y))
pygame.display.set_caption("Chain Reaction")

#b ackground image setup
background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background, (screen_x, screen_y))
background.set_alpha(128)

# grid setup
rows, cols = 9, 6
cell_x, cell_y = 80,80
grid_x = (screen_x-cols*cell_x) // 2
grid_y = (screen_y-rows*cell_y) // 2
cell_surface = pygame.Surface((cell_x,cell_y),pygame.SRCALPHA)

# storing the grid
counts = []
colors = []
borders = []
def update_grid():
    with open("file.txt",'r') as file:
        lines = file.readlines()

    for line in lines:
        line = lines.strip()
        if line.endswith(':'):
            continue
        row_counts = []
        row_colors = []
        row_borders = []
        for cell in line.split():
            if cell == '0':
                row_counts.append(0)
                row_colors.append('W')
                row_borders.append('W')
            else:
                row_counts.append(int(cell[0]))
                if cell[1] == 'R':
                    row_colors.append(orb_color1)
                    row_borders.append(orb_border1)
                else:
                    row_colors.append(orb_color2)
                    row_borders.append(orb_border2)
        counts.append(row_counts)
        colors.append(row_colors)
        borders.append(row_borders)

# drawing the orbs
orb_color1 = (200,0,0)
orb_border1 = (50,0,0)
orb_radius = grid_x // 6
orb_color2 = (13,0,202)
orb_border2 = (10,4,107)
def draw_orbs():
    for i in counts:
        for j in counts[i]:
            if counts[i][j] == 1:
                pygame.draw.circle(screen, rows[i][j], ((grid_x + 30),(grid_y+50)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((grid_x + 30),(grid_y+50)),orb_radius,1)
                pygame.draw.circle(screen, rows[i][j], ((grid_x + 50),(grid_y+50)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((grid_x + 50),(grid_y+50)),orb_radius,1)
                pygame.draw.circle(screen, rows[i], ((grid_x + 40),(grid_y+30)),orb_radius)
                pygame.draw.circle(screen, orb_border1, ((grid_x + 40),(grid_y+30)),orb_radius,1)


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
            cell_surface.fill((10,21,97,50))
            screen.blit(cell_surface, (grid_x + j*80,grid_y+i*80))
    
    for i in range(rows + 1):
        pygame.draw.line(screen, (255,255,255),(grid_x, grid_y + i*80),(grid_x + cols*80, grid_y + i*80), 2)

    for i in range(cols + 1):
        pygame.draw.line(screen, (255,255,255),(grid_x + i*80, grid_y),(grid_x + i*80, grid_y + rows*80), 2)

    print_orbs()

    pygame.display.flip()

pygame.quit()
