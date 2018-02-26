#include <iostream>
#include <thread>
#include <cv.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include <highgui.h>

#define WIDTH 1920
#define HEIGHT 1080

#define BLACK cv::Scalar(0,0,0)
#define RED cv::Scalar(0,0,200)
#define BLUE cv::Scalar(200,100,0)

bool exitProgram = false;

std::string team1Name = "Team 1";
std::string team2Name = "Team 2";
int team1Score = 0;
int team2Score = 0;

int team1X = 125;
int team2X = WIDTH-325;

int team1Y = 850;
int team2Y = 850;


void draw()
{
  cv::namedWindow("opencv-show", CV_WINDOW_NORMAL || CV_WINDOW_FREERATIO);    //Create window
  cv::setWindowProperty("opencv-show", CV_WINDOW_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  cv::moveWindow("opencv-show", 0, 0);
  cv::VideoCapture capture(CV_CAP_ANY);  //Capture using any camera connected to your system
  while(!exitProgram) //Create infinte loop for live streaming
  {
    cv::Mat frame;
    capture >> frame; //Create image frames from capture
    // Resize to make full screen
    cv::resize(frame, frame, cv::Size(1920, 1080), 0, 0, CV_INTER_LINEAR);

    // Text Rectangles
    // Borders
    cv::rectangle(frame, cv::Point(0, 790), cv::Point(510, 1010), BLACK, -1, 8);
    cv::rectangle(frame, cv::Point(WIDTH, 790), cv::Point(WIDTH-510, 1010), BLACK, -1, 8);
    // Coloured rectangles
    cv::rectangle(frame, cv::Point(0, 800), cv::Point(500, 1000), RED, -1, 8);
    cv::rectangle(frame, cv::Point(WIDTH, 800), cv::Point(WIDTH-500, 1000), BLUE, -1, 8);

    // Team Names
    cv::putText(frame, team1Name, cv::Point(team1X, team1Y), cv::FONT_HERSHEY_DUPLEX, 1, BLACK, 2, CV_AA);
    cv::putText(frame, team2Name, cv::Point(team2X, team2Y), cv::FONT_HERSHEY_DUPLEX, 1, BLACK, 2, CV_AA);

    // Team Scores
    cv::putText(frame,
                std::to_string(team1Score),
                cv::Point(200, 950),
                cv::FONT_HERSHEY_DUPLEX,
                4,
                cv::Scalar(0, 0, 0),
                3,
                CV_AA);

    cv::putText(frame,
                std::to_string(team2Score),
                cv::Point(WIDTH-300, 950),
                cv::FONT_HERSHEY_DUPLEX,
                4,
                cv::Scalar(0, 0, 0),
                3,
                CV_AA);

    // Scores
    cv::imshow("opencv-show", frame);   //Show image frames on created window
    //Quit with esc
    if(cv::waitKey(10) == 27 ) break;
  }
  capture.release(); //Release capture.
  cv::destroyAllWindows(); //Destroy Window
}

void printGuessy()
{
  std::cout << " $$$$$$\\  $$\\   $$\\ $$$$$$$$\\  $$$$$$\\   $$$$$$\\  $$\\     $$\\ " << std::endl
            << "$$  __$$\\ $$ |  $$ |$$  _____|$$  __$$\\ $$  __$$\\ \\$$\\   $$  |" << std::endl
            << "$$ /  \\__|$$ |  $$ |$$ |      $$ /  \\__|$$ /  \\__| \\$$\\ $$  / " << std::endl
            << "$$ |$$$$\\ $$ |  $$ |$$$$$\\    \\$$$$$$\\  \\$$$$$$\\    \\$$$$  /  " << std::endl
            << "$$ |\\_$$ |$$ |  $$ |$$  __|    \\____$$\\  \\____$$\\    \\$$  /   " << std::endl
            << "$$ |  $$ |$$ |  $$ |$$ |      $$\\   $$ |$$\\   $$ |    $$ |    " << std::endl
            << "\\$$$$$$  |\\$$$$$$  |$$$$$$$$\\ \\$$$$$$  |\\$$$$$$  |    $$ |    " << std::endl
            << " \\______/  \\______/ \\________| \\______/  \\______/     \\__| " << std::endl;
}

void printChoccy()
{
  std::cout << " $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\     $$\\ " << std:: endl
            << "$$  __$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ \\$$\\   $$  | " << std::endl
            << "$$ /  \\__|$$ |  $$ |$$ /  $$ |$$ /  \\__|$$ /  \\__| \\$$\\ $$  /  " << std::endl
            << "$$ |      $$$$$$$$ |$$ |  $$ |$$ |      $$ |        \\$$$$  /   " << std::endl
            << "$$ |      $$  __$$ |$$ |  $$ |$$ |      $$ |         \\$$  /    " << std::endl
            << "$$ |  $$\\ $$ |  $$ |$$ |  $$ |$$ |  $$\\ $$ |  $$\\     $$ |     " << std::endl
            << "\\$$$$$$  |$$ |  $$ | $$$$$$  |\\$$$$$$  |\\$$$$$$  |    $$ |     " << std::endl
            << " \\______/ \\__|  \\__| \\______/  \\______/  \\______/     \\__| " << std::endl;
}

int getInt()
{
  int newScore;
  std::cin >> newScore;

  while(std::cin.fail())
  {
    std::cout << "Error parsing num" << std::endl;
    std::cout << "Enter a value:" << std::endl;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> newScore;
  }

  return newScore;
}

void userInterface()
{
  for (int i : {1, 2})
  {
    printGuessy();
  }

  for (int i : {1, 2})
  {
    printChoccy();
  }

  std::string input;
  std::vector<std::string> acceptedInputs = {"1",
                                             "2",
                                             "3",
                                             "4",
                                             "5",
                                             "6",
                                             "7",
                                             "8",
                                             "r",
                                             "q"};
  while (!exitProgram)
  {
    std::cout << std::endl << std::endl;

    std::cout << "1. team1Name: " << team1Name << std::endl;
    std::cout << "2. team2Name: " << team2Name << std::endl;
    std::cout << "3. team1Score: " << team1Score << std::endl;
    std::cout << "4. team2Score: " << team2Score << std::endl;
    std::cout << "5. team1X: " << team1X << std::endl;
    std::cout << "6. team1Y: " << team1Y << std::endl;
    std::cout << "7. team2X: " << team2X << std::endl;
    std::cout << "8. team2Y: " << team2Y << std::endl;

    std::cout << "Choose a variable (1-4), refresh (r) or quit (q)" << std::endl;
    std::getline(std::cin, input);

    bool inputIsCorrect = std::find(acceptedInputs.begin(), acceptedInputs.end(), input) != acceptedInputs.end();
    if (inputIsCorrect)
    {
      std::cout << "Input: " << input << std::endl;
      if (input == "1")
      {
        std::cout << "Enter a new name for team 1:" << std::endl;
        std::getline(std::cin, team1Name);
      }
      else if (input == "2")
      {
        std::cout << "Enter a new name for team 2:" << std::endl;
        std::getline(std::cin, team2Name);
      }
      else if (input == "3")
      {
        std::cout << "Enter a new score for team 1:" << std::endl;
        team1Score = getInt();
      }
      else if (input == "4")
      {
        std::cout << "Enter a new score for team 2:" << std::endl;
        team2Score = getInt();
      }
      else if (input == "5")
      {
        std::cout << "Enter a number to increment team1X by:" << std::endl;
        team1X += getInt();
      }
      else if (input == "q")
      {
        exitProgram = true;
      }
      else if (input == "r")
      {
        continue;
      }
    }
  }
}

int main()
{
  std::thread ui (userInterface);
  std::thread camera (draw);

  ui.join();
  camera.join();

  std::cout << "Shutdown successful" << std::endl;
  return 0;
}
