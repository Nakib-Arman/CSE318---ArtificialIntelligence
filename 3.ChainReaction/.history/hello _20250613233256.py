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
grid_x = (screen_x-cols*80) // 2
grid_y = (screen_y-rows*80) // 2
cell_surface = pygame.Surface((80,80),pygame.SRCALPHA)

# storing the grid
grid = []
def get_latest_grid():
    with open("file.txt",'r') as file:
        lines = file.readlines()

    for line in lines:
        line = lines.strip()
        if

# drawing the orbs
orb_color1 = (200,0,0)
orb_border1 = (50,0,0)
orb_radius = 13
orb_color2 = (13,0,202)
orb_border2 = (10,4,107)

def print_orbs():
    pygame.draw.circle(screen, orb_color1, ((grid_x + 30),(grid_y+50)),orb_radius)
    pygame.draw.circle(screen, orb_border1, ((grid_x + 30),(grid_y+50)),orb_radius,1)
    pygame.draw.circle(screen, orb_color1, ((grid_x + 50),(grid_y+50)),orb_radius)
    pygame.draw.circle(screen, orb_border1, ((grid_x + 50),(grid_y+50)),orb_radius,1)
    pygame.draw.circle(screen, orb_color1, ((grid_x + 40),(grid_y+30)),orb_radius)
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
