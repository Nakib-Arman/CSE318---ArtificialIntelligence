import pygame
import sys

pygame.init()

# Initial Setup
screen_x, screen_y = 400, 300
screen = pygame.display.set_mode((screen_x, screen_y))
pygame.display.set_caption("Set Grid Row")

# Colors and Fonts
WHITE = (255, 255, 255)
GRAY = (200, 200, 200)
DARK_GRAY = (50, 50, 50)
BLUE = (0, 120, 215)
font = pygame.font.SysFont(None, 40)

# Initial row count
rows = 9

# Button
button_rect = pygame.Rect(100, 120, 200, 60)

def draw_ui():
    screen.fill(WHITE)
    
    # Draw button
    pygame.draw.rect(screen, BLUE, button_rect)
    text = font.render(f"Rows: {rows}", True, WHITE)
    screen.blit(text, text.get_rect(center=button_rect.center))

    pygame.display.flip()

running = True
while running:
    draw_ui()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.MOUSEBUTTONDOWN:
            if button_rect.collidepoint(event.pos):
                rows += 1
                if rows > 15:
                    rows = 3  # Reset to minimum if too large

pygame.quit()
sys.exit()
