import cv2
import thread

WIDTH = 1920
BLACK = (0,0,0)
RED = (0, 0, 200)
BLUE = (200, 100, 0)

team1Name = 'Team 1'
team2Name = 'Team 2'

team1Score = 0
team2Score = 0

team1X = 125
team1Y = 850

team2X = WIDTH-325
team2Y = 850

exit = False

def printGuessy():
  print ' $$$$$$\\  $$\\   $$\\ $$$$$$$$\\  $$$$$$\\   $$$$$$\\  $$\\     $$\\ '
  print '$$  __$$\\ $$ |  $$ |$$  _____|$$  __$$\\ $$  __$$\\ \\$$\\   $$  |'
  print '$$ /  \\__|$$ |  $$ |$$ |      $$ /  \\__|$$ /  \\__| \\$$\\ $$  / '
  print '$$ |$$$$\\ $$ |  $$ |$$$$$\\    \\$$$$$$\\  \\$$$$$$\\    \\$$$$  /  '
  print '$$ |\\_$$ |$$ |  $$ |$$  __|    \\____$$\\  \\____$$\\    \\$$  /   '
  print '$$ |  $$ |$$ |  $$ |$$ |      $$\\   $$ |$$\\   $$ |    $$ |    '
  print '\\$$$$$$  |\\$$$$$$  |$$$$$$$$\\ \\$$$$$$  |\\$$$$$$  |    $$ |    '
  print ' \\______/  \\______/ \\________| \\______/  \\______/     \\__| '

def printChoccy():
  print ' $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\     $$\\ '
  print '$$  __$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ \\$$\\   $$  | '
  print '$$ /  \\__|$$ |  $$ |$$ /  $$ |$$ /  \\__|$$ /  \\__| \\$$\\ $$  /  '
  print '$$ |      $$$$$$$$ |$$ |  $$ |$$ |      $$ |        \\$$$$  /   '
  print '$$ |      $$  __$$ |$$ |  $$ |$$ |      $$ |         \\$$  /    '
  print '$$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |  $$\\ $$ |  $$\\     $$ |     '
  print '\\$$$$$$  |$$ |  $$ | $$$$$$  |\\$$$$$$  |\\$$$$$$  |    $$ |     '
  print ' \\______/ \\__|  \\__| \\______/  \\______/  \\______/     \\__| '

def ui():
  global team1Name
  global team2Name

  global team1Score
  global team2Score

  global team1X
  global team1Y

  global team2X
  global team2Y

  global exit

  for i in xrange(2):
    printGuessy()

  for i in xrange(2):
    printChoccy()

  while not exit:
    print '\n\n\n'
    print '1. team1Name: ' + team1Name
    print '2. team2Name: ' + team2Name
    print '3. team1Score: ' + str(team1Score)
    print '4. team2Score: ' + str(team2Score)
    print '5. team1X: ' + str(team1X)
    print '6. team1Y: ' + str(team1Y)
    print '7. team2X: ' + str(team2X)
    print '8. team2Y: ' + str(team2Y)

    userInput = raw_input('Choose a variable, refresh (any key) or quit (q)')

    try:
      if (userInput == '1'):
        team1Name = raw_input('Enter a new name for team 1:')

      elif (userInput == '2'):
        team2Name = raw_input('Enter a new name for team 2:')

      elif (userInput == '3'):
        team1Score = int(raw_input('Enter a new score for team 1:'))
      
      elif (userInput == '4'):
        team2Score = int(raw_input('Enter a new score for team 2:'))
      
      elif (userInput == '5'):
        team1X += int(raw_input('Enter a number to increment team1X by:'))

      elif (userInput == '6'):
        team1Y += int(raw_input('Enter a number to increment team1Y by:'))

      elif (userInput == '7'):
        team2X += int(raw_input('Enter a number to increment team2X by:'))

      elif (userInput == '8'):
        team2Y += int(raw_input('Enter a number to increment team2Y by:'))

      elif (userInput == 'q'):
        exit = True

      else:
        continue

    except ValueError:
      continue
    


thread.start_new_thread(ui, ())

cv2.namedWindow('opencv-show', cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
cv2.setWindowProperty('opencv-show', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)

cap = cv2.VideoCapture(1)

while not exit:
  ret, img = cap.read()
  img = cv2.resize(img, (1920, 1080))

  # Bordered Rectangles
  cv2.rectangle(img, (0, 790), (510, 1010), BLACK, -1, 8)
  cv2.rectangle(img, (WIDTH, 790), (WIDTH-510, 1010), BLACK, -1, 8)

  # Coloured Rectangles
  cv2.rectangle(img, (0, 800), (500, 1000), RED, -1, 8)
  cv2.rectangle(img, (WIDTH, 800), (WIDTH-500, 1000), BLUE, -1, 8)

  # Team Names
  cv2.putText(img, team1Name, (team1X, team1Y), cv2.FONT_HERSHEY_DUPLEX, 2, BLACK, 2)
  cv2.putText(img, team2Name, (team2X, team2Y), cv2.FONT_HERSHEY_DUPLEX, 2, BLACK, 2)

  # Team Scores
  cv2.putText(img, str(team1Score), (200, 950), cv2.FONT_HERSHEY_DUPLEX, 4, BLACK, 3)
  cv2.putText(img, str(team2Score), (WIDTH-300, 950), cv2.FONT_HERSHEY_DUPLEX, 4, BLACK, 3)

  cv2.imshow('opencv-show', img)

  key = cv2.waitKey(10)
  if key == 27:
    break

cv2.destroyAllWindows()
cv2.VideoCapture(0).release()
