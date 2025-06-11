import pygame

pygame.init()

#setting up the screen
screen = pygame.display.set_mode((1200,900))
pygame.display.set_caption("Chain Reaction")

#adding a background image
background = pygame.image.load("background.jpg")
background = pygame.transform.scale(background,(1200,900))
background.set_alpha(128)

# creating the grid
row,column = 9,6

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    #background image
    screen.fill((0,0,0))
    screen.blit(background,(0,0))
    pygame.display.flip()

    #Grid
    
    for i in range (row+1):
        pygame.draw.line(screen,(255,255,255),(0,row*60),(1200,row*60),2)