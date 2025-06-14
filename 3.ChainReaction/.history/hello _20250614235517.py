import pygame
import subprocess

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

# updating the grid
counts = [[0 for _ in range(cols)] for _ in range(rows)]
colors = [['W' for _ in range(cols)] for _ in range(rows)]
borders = [['W' for _ in range(cols)] for _ in range(rows)]
winner = "none"
def update_grid():
    global winner
    counts.clear()
    colors.clear()
    borders.clear()
    with open("file.txt",'r') as file:
        lines = file.readlines()

    for line in lines:
        if line == "Human":
            winner = "Human"
            break
        elif line == "AI":
            winner = "AI"
            break

        row_counts = []
        row_colors = []
        row_borders = []
        if line.strip().endswith(":"):
            continue
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

# writing the grid to the file
def store_grid():
    with open("file.txt",'w') as file:
        file.write("Human Move:\n")

        for i in range(rows):
            for j in range(cols):
                file.write(str(counts[i][j]))
                if colors[i][j] == orb_color1:
                    file.write('R')
                elif colors[i][j] == orb_color2:
                    file.write('B')
                file.write(" ")
            file.write("\n")

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
    for i in range (rows):
        for j in range (cols):
            if ((x>(grid_x + j*cell_x) and x<(grid_x + (j+1)*cell_x)) and (y>(grid_y + i*cell_y)) and y<(grid_y + (i+1)*cell_y)):
                return (i,j)
    return (-1,-1)

# creating the game ui
def load_ui():
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

# game over menu
def game_over():

    
    msg_font = pygame.font.SysFont(None, 80)
    button_font = pygame.font.SysFont(None, 50)

    play_again_btn = pygame.Rect(screen_x // 2 - 150, screen_y // 2, 300, 60)
    quit_btn = pygame.Rect(screen_x // 2 - 150, screen_y // 2 + 80, 300, 60)

    while True:
        screen.fill((0, 0, 0))
        screen.blit(background, (0, 0))

        if (winner == 'Human'):
            text = msg_font.render("Congratulations, You've Won!", True, (255, 0, 0))
        elif (winner == 'AI'):
            text = msg_font.render("You've Lost!", True, (255, 0, 0))
        text_rect = text.get_rect(center=(screen_x // 2, screen_y // 2 - 100))
        screen.blit(text, text_rect)

        pygame.draw.rect(screen, (0, 128, 0), play_again_btn)
        play_again_text = button_font.render("Play Again", True, (255, 255, 255))
        play_again_text_rect = play_again_text.get_rect(center=play_again_btn.center)
        screen.blit(play_again_text, play_again_text_rect)
        
        pygame.draw.rect(screen, (128, 0, 0), quit_btn)
        quit_text = button_font.render("Quit", True, (255, 255, 255))
        quit_text_rect = quit_text.get_rect(center=quit_btn.center)
        screen.blit(quit_text, quit_text_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if play_again_btn.collidepoint(event.pos):
                    return  # Restart game
                elif quit_btn.collidepoint(event.pos):
                    pygame.quit()
                    exit()


running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            index_x, index_y = get_index(x,y)
            if index_x == -1 or index_y == -1:
                continue
            store_grid()
            try:
                subprocess.run(["./main",str(index_x),str(index_y)],check=True)
            except subprocess.CalledProcessError as e:
                print("Program failed:",e)
            update_grid()
            if winner != 'none':
                load_ui()
                game_over()

            load_ui()

            pygame.time.delay(1000)

            try:
                subprocess.run(["./main"],check=True)
            except subprocess.CalledProcessError as e:
                print("Program failed:",e)
            update_grid()
            if winner != 'none':
                load_ui()
                game_over()
    
    load_ui()

pygame.quit()
