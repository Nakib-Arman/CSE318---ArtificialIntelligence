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
cell_x, cell_y = (screen_x-700) // cols, (screen_y-100) // rows
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
orb_radius = min(cell_x,cell_y) // 5
orb_color2 = (13,0,202)
orb_border2 = (10,4,107)
def draw_orbs():
    for i,row in enumerate(counts):
        for j,value in enumerate(row):
            orb_position_x = grid_x + j*cell_x
            orb_position_y = grid_y + i*cell_y
            if value == 0:
                continue
            if value == 1:
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2),(orb_position_y+cell_y // 2)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2),(orb_position_y+cell_y // 2)),orb_radius,1)
            if value == 2:
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2)),orb_radius,1)
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2)),orb_radius,1)
            if value == 3:
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius,1)
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius,1)
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2),(orb_position_y+cell_y // 2 - orb_radius + orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2),(orb_position_y+cell_y // 2 - orb_radius + orb_radius // 3)),orb_radius,1)
            if value == 4:
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius,1)
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2 + orb_radius - orb_radius // 3)),orb_radius,1)
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2 - orb_radius + orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 - orb_radius + orb_radius // 3),(orb_position_y+cell_y // 2 - orb_radius + orb_radius // 3)),orb_radius,1)
                pygame.draw.circle(screen, colors[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2 - orb_radius + orb_radius // 3)),orb_radius)
                pygame.draw.circle(screen, borders[i][j], ((orb_position_x + cell_x // 2 + orb_radius - orb_radius // 3),(orb_position_y+cell_y // 2 - orb_radius + orb_radius // 3)),orb_radius,1)

# handling mouse click event
def get_index(x,y):
    if ()

update_grid()

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            print(x)
            print(y)
            if((x>grid_x and x<grid_x+cell_x) and (y>grid_y and y<grid_y+cell_y)):
                print("(1,1)")

    # background image
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))

    # making the grid
    for i in range(rows):
        for j in range(cols):
            cell_surface.fill((10,21,97,50))
            screen.blit(cell_surface, (grid_x + j*cell_x,grid_y+i*cell_y))
    
    for i in range(rows + 1):
        pygame.draw.line(screen, (255,255,255),(grid_x, grid_y + i*cell_y),(grid_x + cols*cell_x, grid_y + i*cell_y), 2)

    for i in range(cols + 1):
        pygame.draw.line(screen, (255,255,255),(grid_x + i*cell_x, grid_y),(grid_x + i*cell_x, grid_y + rows*cell_y), 2)

    draw_orbs()

    pygame.display.flip()

pygame.quit()
