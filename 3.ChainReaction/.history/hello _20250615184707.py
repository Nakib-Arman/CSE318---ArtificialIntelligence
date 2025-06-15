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
player1 = "Human"
player2 = "AI"
rows, cols = 9, 6
cell_x, cell_y = (screen_x-700) // cols, (screen_y-100) // rows
grid_x = (screen_x-cols*cell_x) // 2
grid_y = (screen_y-rows*cell_y) // 2
cell_surface = pygame.Surface((cell_x,cell_y),pygame.SRCALPHA)

def update_details():
    global rows,cols,cell_x,cell_y,screen_x,screen_y,grid_x,grid_y,cell_surface,counts,colors,borders
    cell_x, cell_y = (screen_x-700) // cols, (screen_y-100) // rows
    grid_x = (screen_x-cols*cell_x) // 2
    grid_y = (screen_y-rows*cell_y) // 2
    cell_surface = pygame.Surface((cell_x,cell_y),pygame.SRCALPHA)
    counts = [[0 for _ in range(cols)] for _ in range(rows)]
    colors = [['W' for _ in range(cols)] for _ in range(rows)]
    borders = [['W' for _ in range(cols)] for _ in range(rows)]


# updating the grid
counts = [[0 for _ in range(cols)] for _ in range(rows)]
colors = [['W' for _ in range(cols)] for _ in range(rows)]
borders = [['W' for _ in range(cols)] for _ in range(rows)]
winner = "none"
def update_grid():
    global winner,counts,colors,borders
    counts.clear()
    colors.clear()
    borders.clear()
    with open("file.txt",'r') as file:
        lines = file.readlines()

    for line in lines:
        if line == player1:
            winner = player1
            break
        elif line == player2:
            winner = player2
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
    global rows,cols,colors,counts,player1,player2
    with open("file.txt",'w') as file:
        file.write(f"{player1} Move:\n")

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
    global rows,cols,counts,colors,borders
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
    global rows,cols
    for i in range (rows):
        for j in range (cols):
            if ((x>(grid_x + j*cell_x) and x<(grid_x + (j+1)*cell_x)) and (y>(grid_y + i*cell_y)) and y<(grid_y + (i+1)*cell_y)):
                return (i,j)
    return (-1,-1)


# creating the game ui
def load_ui():
    global rows,cols,cell_surface,grid_x,grid_y,cell_x,cell_y
    # background image
    screen.fill((0, 0, 0))
    screen.blit(background, (0, 0))

    settings_button = pygame.Rect(screen_x - 150, 20, 130, 40)
    pygame.draw.rect(screen, (50, 50, 50), settings_button, border_radius=10)
    pygame.draw.rect(screen, (255, 255, 255), settings_button, 2, border_radius=10)

    settings_text = pygame.font.SysFont(None, 30).render("Settings", True, (255, 255, 255))
    screen.blit(settings_text, settings_text.get_rect(center=settings_button.center))

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
    return settings_button


# game over menu
def game_over():
    global screen_x,screen_y,player1,player2
    screen.blit(background, (0, 0))

    popup_width, popup_height = 500, 300
    popup_x = (screen_x - popup_width) // 2
    popup_y = (screen_y - popup_height) // 2
    popup_rect = pygame.Rect(popup_x, popup_y, popup_width, popup_height)

    msg_font = pygame.font.SysFont(None, 60)
    button_font = pygame.font.SysFont(None, 40)

    play_again_btn = pygame.Rect(popup_x + 50, popup_y + 180, 180, 50)
    quit_btn = pygame.Rect(popup_x + 270, popup_y + 180, 180, 50)

    while True:

        pygame.draw.rect(screen, (240, 240, 240), popup_rect, border_radius=15)
        pygame.draw.rect(screen, (255, 255, 255), popup_rect, 4, border_radius=15)

        if (winner == player1):
            if(player1 == "Human"):
                text = msg_font.render("Congratulations, You've Won!", True, (255, 0, 0))
            elif(player1 == "AI1"):
                text = msg_font.render("AI1 Has Won!\n",True, (255,0,0))
        elif (winner == player2):
            if(player2 == "AI"):
                text = msg_font.render("You've Lost!", True, (255, 0, 0))
            if(player2 == "AI2"):
                text = msg_font.render("AI2 Has Won!", True, (255, 0, 0))
        text_rect = text.get_rect(center=(screen_x // 2, popup_y + 80))
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
                    return

                elif quit_btn.collidepoint(event.pos):
                    pygame.quit()
                    exit()


# grid size change menu
def grid_size_menu():
    global rows,cols
    button_font = pygame.font.SysFont(None, 40)

    row_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 - 50, 300, 40)
    col_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 + 10, 300, 40)

    back_text = pygame.font.SysFont(None, 30).render("Back", True, (255, 255, 255))
    back_button = pygame.Rect(20, 20, 130, 40)

    while True:
        screen.fill((0, 0, 0, 180))
        screen.blit(background, (0, 0))

        pygame.draw.rect(screen, (240, 240, 240), row_rect)
        row_text = button_font.render(f"Rows: {rows}", True, (0, 0, 0))
        row_text_rect = row_text.get_rect(center=row_rect.center)
        screen.blit(row_text, row_text_rect)

        pygame.draw.rect(screen, (240, 240, 240), col_rect)
        col_text = button_font.render(f"Columns: {cols}", True, (0, 0, 0))
        col_text_rect = col_text.get_rect(center=col_rect.center)
        screen.blit(col_text, col_text_rect)

        pygame.draw.rect(screen, (50, 50, 50), back_button, border_radius=10)
        pygame.draw.rect(screen, (255, 255, 255), back_button, 2, border_radius=10)
        back_text_rect = back_text.get_rect(center=back_button.center)
        screen.blit(back_text, back_text_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if row_rect.collidepoint(event.pos):
                    rows += 1
                    if rows > 15:
                        rows = 3 
                elif col_rect.collidepoint(event.pos):
                    cols += 1
                    if cols >15:
                        cols = 3
                elif back_button.collidepoint(event.pos):
                    update_details()
                    return



# AI vs AI gameplay
def play_ai_vs_ai():
    global player1,player2,winner,counts,colors,borders,rows,cols

    while True:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()

        load_ui()

        store_grid()
        try:
            subprocess.run(["./main",str(rows),str(cols)],check=True)
        except subprocess.CalledProcessError as e:
            print("Program failed:",e)
        update_grid()
        load_ui()
        if winner != 'none':
            game_over()
            counts = [[0 for _ in range(cols)] for _ in range(rows)]
            colors = [['W' for _ in range(cols)] for _ in range(rows)]
            borders = [['W' for _ in range(cols)] for _ in range(rows)]                
            winner = "none"
            store_grid()
        pygame.time.delay(500)

        try:
            subprocess.run(["./main",str(rows),str(cols)],check=True)
        except subprocess.CalledProcessError as e:
            print("Program failed:",e)
        update_grid()
        load_ui()
        if winner != 'none':
            game_over()
            counts = [[0 for _ in range(cols)] for _ in range(rows)]
            colors = [['W' for _ in range(cols)] for _ in range(rows)]
            borders = [['W' for _ in range(cols)] for _ in range(rows)]                
            winner = "none"
            store_grid()
        pygame.time.delay(500)


# AI vs AI menu
def ai_vs_ai_menu():
    font = pygame.font.SysFont(None, 40)

    heuristics = ["Controlled Cell Difference", "Orb Count Difference", "Controlled Edge Cell Difference", "Edge Cell Orb Count Difference", "Critical Mass Proximity"]
    
    ai1_option = heuristics[1]  
    ai1_rect = pygame.Rect(150, screen_y // 2 - 50, 300, 40)

    ai2_option = heuristics[1]  
    ai2_rect = pygame.Rect(screen_x - 450, screen_y // 2 - 50, 300, 40)

    option_height = 40
    dropdown = False

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.MOUSEBUTTONDOWN:
                mx, my = event.pos
                if ai1_rect.collidepoint(mx, my):
                    dropdown_open = not dropdown_open  # Toggle dropdown
                elif dropdown_open:
                    for i, option in enumerate(heuristics):
                        option_rect = pygame.Rect(ai1_rect.x, ai1_rect.y + (i+1)*option_height, ai1_rect.width, option_height)
                        if option_rect.collidepoint(mx, my):
                            selected_option = option
                            dropdown_open = False
                            print(f"Selected Rows: {selected_option}")
                            break
                    else:
                        dropdown_open = False  # Clicked outside

        screen.fill((0, 0, 0, 180))
        screen.blit(background, (0, 0))

        pygame.draw.rect(pygame.display.set_mode(500,400), (200,200,200), ai1_rect)
        pygame.draw.rect(pygame.display.set_mode(500,400), (0,0,0), ai1_rect,2)

        selected_text = font.render(ai1_option, True, (0,0,0))
        screen.blit(selected_text, (ai1_rect.x + 10, ai1_rect.y + 5))

        if dropdown_open:
            for i, option in enumerate(heuristics):
                option_rect = pygame.Rect(ai1_rect.x, ai1_rect.y + (i+1)*option_height, ai1_rect.width, option_height)
                pygame.draw.rect(screen, (255,255,255), option_rect)
                pygame.draw.rect(screen, (BLACK), option_rect, 1)
                option_text = font.render(option, True, BLACK)
                screen.blit(option_text, (option_rect.x + 10, option_rect.y + 5))



# settings menu
def settings_menu():
    global player1,player2,counts,colors,borders,winner
    # font = pygame.font.SysFont(None, 80)
    button_font = pygame.font.SysFont(None, 40)

    new_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 - 140, 300, 40)
    grid_size_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 - 80, 300, 40)
    ai_vs_ai_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 -20, 300, 40 )
    multiplayer_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 + 40, 300, 40 )
    random_vs_ai_rect = pygame.Rect(screen_x // 2 - 150, screen_y // 2 + 100, 300, 40 )

    back_text = pygame.font.SysFont(None, 30).render("Back", True, (255, 255, 255))
    back_button = pygame.Rect(20, 20, 130, 40)

    while True:
        screen.fill((0, 0, 0, 180))
        screen.blit(background, (0, 0))

        pygame.draw.rect(screen, (0, 128, 0), new_rect)
        new_text = button_font.render("New Game", True, (255, 255, 255))
        new_text_rect = new_text.get_rect(center=new_rect.center)
        screen.blit(new_text, new_text_rect)

        pygame.draw.rect(screen, (0, 128, 0), grid_size_rect)
        grid_size_text = button_font.render("Grid Size", True, (255, 255, 255))
        grid_size_text_rect = grid_size_text.get_rect(center=grid_size_rect.center)
        screen.blit(grid_size_text, grid_size_text_rect)

        pygame.draw.rect(screen, (0, 128, 0), ai_vs_ai_rect)
        ai_vs_ai_text = button_font.render("Play AI vs AI", True, (255, 255, 255))
        ai_vs_ai_text_rect = ai_vs_ai_text.get_rect(center=ai_vs_ai_rect.center)
        screen.blit(ai_vs_ai_text, ai_vs_ai_text_rect)

        pygame.draw.rect(screen, (0, 128, 0), multiplayer_rect)
        multiplayer_text = button_font.render("Multiplayer", True, (255, 255, 255))
        multiplayer_text_rect = multiplayer_text.get_rect(center=multiplayer_rect.center)
        screen.blit(multiplayer_text, multiplayer_text_rect)

        pygame.draw.rect(screen, (0, 128, 0), random_vs_ai_rect)
        random_vs_ai_text = button_font.render("Random vs AI", True, (255, 255, 255))
        random_vs_ai_text_rect = random_vs_ai_text.get_rect(center=random_vs_ai_rect.center)
        screen.blit(random_vs_ai_text, random_vs_ai_text_rect)

        pygame.draw.rect(screen, (50, 50, 50), back_button, border_radius=10)
        pygame.draw.rect(screen, (255, 255, 255), back_button, 2, border_radius=10)
        back_text_rect = back_text.get_rect(center=back_button.center)
        screen.blit(back_text, back_text_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if new_rect.collidepoint(event.pos):
                    counts = [[0 for _ in range(cols)] for _ in range(rows)]
                    colors = [['W' for _ in range(cols)] for _ in range(rows)]
                    borders = [['W' for _ in range(cols)] for _ in range(rows)]
                    winner = "none"
                    store_grid()
                    return
                elif grid_size_rect.collidepoint(event.pos):
                    grid_size_menu()
                    continue
                elif ai_vs_ai_rect.collidepoint(event.pos):
                    player1 = "AI1"
                    player2 = "AI2"
                    play_ai_vs_ai()
                elif back_button.collidepoint(event.pos):
                    return
                

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:

            if settings_button.collidepoint(event.pos):
                settings_menu()
                continue
            
            x, y = event.pos
            index_x, index_y = get_index(x,y)
            if index_x == -1 or index_y == -1:
                continue
            store_grid()
            try:
                subprocess.run(["./main",str(rows),str(cols),str(index_x),str(index_y)],check=True)
            except subprocess.CalledProcessError as e:
                print("Program failed:",e)
            update_grid()
            if winner != 'none':
                settings_button = load_ui()
                game_over()
                counts = [[0 for _ in range(cols)] for _ in range(rows)]
                colors = [['W' for _ in range(cols)] for _ in range(rows)]
                borders = [['W' for _ in range(cols)] for _ in range(rows)]
                winner = "none"
                store_grid()

            settings_button = load_ui()

            pygame.time.delay(500)

            try:
                subprocess.run(["./main",str(rows),str(cols),str(index_x),str(index_y)],check=True)
            except subprocess.CalledProcessError as e:
                print("Program failed:",e)
            update_grid()
            if winner != 'none':
                settings_button = load_ui()
                game_over()
                counts = [[0 for _ in range(cols)] for _ in range(rows)]
                colors = [['W' for _ in range(cols)] for _ in range(rows)]
                borders = [['W' for _ in range(cols)] for _ in range(rows)]
                winner = "none"
                store_grid()


    
    settings_button = load_ui()

pygame.quit()
