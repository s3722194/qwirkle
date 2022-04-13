

#include "Game.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <sstream>
#include <string>


#define EXIT_SUCCESS    0

#define USER_REPLACE 1
#define USER_PLACE 2
#define USER_SAVE 3


//finds what starting menu option the user selected
bool menuOption();

//shows the starting menu
void showMenu();

//creates new game
void newGame();

//loads a game
void loadGame();

//shows student info
void showInfo();

//validated the name of a player
bool validateName(const std::string& playerName);


Player* loadPlayer(std::string playerName, std::string playerScore, std::string playerHand);

// starts a new game
void startNewGame(std::string playerName1, std::string playerName2);

void startLoadedGame(Player* player1, Player* player2, Bag* bag, Board* board, Player* currPlayer);

// starts playing a game
void startGame(Game* game);


int main() {

   bool gameInProgress = false;
   if(gameInProgress==false)
   {
     //starts qwirkle
     showMenu();
     menuOption();

   }
   // delete gameInProgress;
   return EXIT_SUCCESS;
}

// Creates a new game
void startNewGame(std::string playerName1, std::string playerName2){
  Player* player1 = new Player(playerName1);
  Player* player2 = new Player(playerName2);

  Game* game= new Game(player1, player2);
  startGame(game);
}

//loads a game
void startLoadedGame(Player* player1, Player* player2, Bag* bag, Board* board, Player* currPlayer){
  Game* game = new Game(player1, player2, bag, board, currPlayer);
  startGame(game);

}

// starts a game
void startGame(Game* game){
  bool playingGame=true;

  while(playingGame){

    Player* currentPlayer =game->getCurrentPlayer();

    std::cout<<std::endl;

    //prints out info the player

    // prints name
    std::cout<<currentPlayer->getName()<<" , it's your turn"<<std::endl;

    //prints scores
    std::cout<<"Score for "<<currentPlayer->getName()<<": "<<currentPlayer->getScore()<<std::endl;
    std::cout<<"Score for "<<game->getOtherPlayer()->getName()<<": "<<game->getOtherPlayer()->getScore()<<std::endl;
    std::cout<<std::endl;

    //prints board
    game->getBoard()->printBoard();

    //prints hand
    std::cout<<"Your hand is"<<std::endl;

    int index=0;
    while(index<currentPlayer->getHand()->size()){
      Tile* tile = currentPlayer->getHand()->get(index);
      std::cout <<tile->colour<< tile->shape<<",";
      index++;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    //deals with user input
    bool hasValidInput=false;
    std::string input="";

    // keeps asking user for input until it has valid input
    while(!hasValidInput){
      std::cout<<"> ";
      std::cin >> input;
      if(std::cin.eof()){
        std::cout<<"Goodbye"<<"\n";
        exit(0);
      }
      std::string type="";
      std::string tile="";
      std::stringstream userInput(input);
      std::getline( userInput, type );

      int foundInput=false;
      int inputType=0;
      int counter=1;

      while( userInput.good() || !foundInput){
        std::cin >> input;
        std::stringstream userInput(input);


        std::string word="";

        std::getline( userInput, word );


        // replaces a tile in the playres hand
        if(type.compare("replace")==0|| inputType==USER_REPLACE){
          inputType=USER_REPLACE;

          // uses the second word in the string, ie. the tile
          if(counter==1){

            // tries to replace the tile in the player's hand
            bool replaced= game->replaceTile(word);

            //if the tile is replaced
            if(replaced){
              hasValidInput =replaced;
            } else{
              std::cout<<"Tile couldn't be replaced"<<std::endl;
            }

            foundInput=true;
          }

          // places a tile on the board
        } else if (type.compare("place")==0 || inputType== USER_PLACE){


          inputType=USER_PLACE;

          // gets the tile from the second word
          if(counter==1){
            tile=word;


          // gets the row and column of th eboard from the 4th word
          } else if (counter ==3){

            //coverts the row char to int row, ie. 'A' to 0 etc.
            int row=word[0]-65;


            //converts the string of the column to an int
            //since a column can be two digits long, can't convert just the char
            //like above in the row , ie. "12" to 12
             std::stringstream intCol(word.substr(1,2));

             int col = 0;
             intCol >> col;



            //tries to add the tile onto the board
            bool isValid=game->addTileToBoard(tile, row, col);
            if(isValid){
              hasValidInput=true;
            }
            foundInput=true;
          }

          //saves the file of the current game state
        } else if (type.compare("save")==0 || inputType==USER_SAVE) {
          //TODO
          inputType=USER_SAVE;
          if(counter==1){

          }
          foundInput=true;

        } else {
          std::cout<<"Input is Invalid, try place or replace a tile"<<std::endl;
          foundInput=true;
          std::cin.clear();
        }
        //moves on to the next word
        counter++;

      }

    }
    // checks if the game has ended
    playingGame = !game->hasGameEnded();

    //changes who the current player is
    game->changeCurrentPlayer();


  }
  std::cout<<"Game has ended"<<std::endl;

}

// // starts a game
// void startGame(Game* game){
//   bool playingGame=true;
//
//   while(playingGame){
//
//     Player* currentPlayer =game->getCurrentPlayer();
//     std::cout<<std::endl;
//
//     //prints out info the player
//
//     // prints name
//     std::cout<<currentPlayer->getName()<<" , it's your turn"<<std::endl;
//
//     //prints scores
//     std::cout<<"Score for "<<currentPlayer->getName()<<": "<<currentPlayer->getScore()<<std::endl;
//     std::cout<<"Score for "<<game->getOtherPlayer()->getName()<<": "<<game->getOtherPlayer()->getScore()<<std::endl;
//     std::cout<<std::endl;
//
//     //prints board
//     game->getBoard()->printBoard();
//
//     //prints hand
//     std::cout<<"Your hand is"<<std::endl;
//
//     int index=0;
//     while(index<currentPlayer->getHand()->size()){
//       Tile* tile = currentPlayer->getHand()->get(index);
//       std::cout <<tile->colour<< tile->shape<<",";
//       index++;
//     }
//     std::cout<<std::endl;
//     std::cout<<std::endl;
//
//     //deals with user input
//     bool hasValidInput=false;
//     std::string input="";
//
//     // keeps asking user for input until it has valid input
//     while(!hasValidInput){
//       std::cout<<"> ";
//       std::cin.ignore();
//       std::cin.getLine(input)
//       if(std::cin.eof()){
//         std::cout<<"Goodbye"<<"\n";
//         exit(0);
//       }
//     //  std::string type="";
//       std::string tile="";
//       //std::stringstream userInput(input);
//       //std::getline( userInput, type );
//
//
//       //int inputType=0;
//
//       // while( userInput.good() || !foundInput){
//       //   std::cin >> input;
//       //   std::stringstream userInput(input);
//
//
//       //  std::string word="";
//
//         //std::getline( userInput, word );
//         std::cout<<"Line 163: Word: "<< input<<std::endl;
//         //replace A5
//         // replaces a tile in the playres hand
//         if(input.length()==11|| (input.substr(0,6)).compare("replace")==0){
//
//           // tries to replace the tile in the player's hand
//           bool replaced= game->replaceTile(input.substr(8,9));
//
//           //if the tile is replaced
//           if(replaced){
//             hasValidInput =replaced;
//           } else{
//             std::cout<<"Tile couldn't be replaced"<<std::endl;
//           }
//
//
//
//           //place R5 to A10
//           // places a tile on the board
//         } else if (input.length()>13 || (input.substr(0,4)).compare("place")==0){
//           std::cout<<"Line 167: Compare: "<< (input.substr(0,4)).compare("place")<<std::endl;
//
//           // gets the tile from the second word
//
//           tile=input.substr(6,7);
//           std::cout<<"Line 173: Tile: "<<tile<<std::endl;
//
//           //coverts the row char to int row, ie. 'A' to 0 etc.
//           int row=input[12]-65;
//           std::cout<<"Line 189: row: "<<row<<std::endl;
//
//           //converts the string of the column to an int
//           //since a column can be two digits long, can't convert just the char
//           //like above in the row , ie. "12" to 12
//           int col=0;
//           if(input.length()==15){
//             col= input[14];
//           } else if( input.length()==16){
//             std::stringstream intCol(input.substr(14,15));
//
//
//             intCol >> col;
//           }
//
//
//           std::cout<<"Line 191: col: "<<col<<std::endl;
//
//           //tries to add the tile onto the board
//           bool isValid=game->addTileToBoard(tile, row, col);
//           if(isValid){
//             hasValidInput=true;
//           }
//
//           //saves the file of the current game state
//         } else if (input.substr(0,3).compare("save")) {
//           //TODO
//
//           hasValidInput=true;
//         }
//         else {
//           std::cout<<"Input is Invalid, try place or replace at tile"<<std::endl;
//
//         }
//   }
//   // checks if the game has ended
//   playingGame = !game->hasGameEnded();
//
//   //changes who the current player is
//   game->changeCurrentPlayer();
//
//
// }
// std::cout<<"Game has ended"<<std::endl;
// }



void showMenu(){
  std::cout<<"\n";
  std::cout << "Welcome to Qwirkle!" << "\n";
  std::cout << "-------------------" << "\n";
  std::cout <<"Menu"<<"\n";
  std::cout <<"----"<<"\n";
  std::cout <<"1. New Game" << "\n";
  std::cout <<"2. Load Game" << "\n";
  std::cout <<"3. Show student information" << "\n";
  std::cout <<"4. Quit" << "\n";
  std::cout<<"\n";
}

bool menuOption(){
  // showMenu();
  bool gameInProgress;
  char input;

  std::cout<<"> ";
  std::cin >> input;
  if(std::cin.eof()){
    std::cout<<"Goodbye"<<"\n";
    exit(0);
  }


//if statement to look for input from user for menu function
  if(input=='1'){
    std::cout << "Creating A New Game" << "\n";
    gameInProgress = true;
    newGame();

  } else if (input=='2'){
    std::cout << "Loading The Game." << "\n";
    gameInProgress = true;
    loadGame();

  } else if (input=='3'){
    std::cout << "Show Student Information." << "\n";
    //displays student information and then returns to menu screen
    showInfo();
    menuOption();

  } else if (input=='4'){
    std::cout << "Quiting the menu" << "\n";
    //clears the screen with 50 end lines and exits the program without crashing
    std::cout << std::string(50, '\n' );
    exit(0);

  }else{
    while((input != '1') && (input !='2') &&(input !='3')&&(input!='4'))
    {
    std::cout << "Invalid Input"<< "\n";
    menuOption();
    std::cout<<"> ";
    std::cin >>input;
  }
  }

  return gameInProgress;
}

void newGame(){
  //generate a new game
  //player name variables
  std::string playerName1;
  std::string playerName2;
  std::cout << "Starting a New Game" << "\n";
  std::cout << "Enter a name for Player 1 (uppercase characters only): " << "\n";
  std::cout<<"> ";
  //player 1 name input
  std::cin >>playerName1;
  //while loop to check for validity to player name (name must be uppercase!)
  while(validateName(playerName1)==false){
    std::cout <<"Uppercase characters only for playername!" <<"\n";
    std::cout<<"> ";
    std::cin >>playerName1;
  }
    std::cout << "Enter a name for Player 2 (uppercase characters only): " << "\n";
    std::cout<<"> ";
    std::cin >>playerName2;
  //while loop to check for validity to player name (name must be uppercase!)
  while(validateName(playerName2)==false){
    std::cout <<"Uppercase characters only for playername!" <<"\n";
    std::cout<<"> ";
    std::cin >>playerName2;
  }
  if(!std::cin.fail()){
    std::cout << "Let's Play!" << "\n";
    std::cout <<"<normal gameplay continues from here>" <<"\n";
  }

  startNewGame(playerName1, playerName2);
}


void loadGame(){
  //LOADS THE GAME FROM HERE FOR ALL PLAYERS

  std::string filename;
  std::cout <<"Enter a filename: "<<"\n";
  std::cout <<"> ";
  std::cin >>filename;
  //checks if input contains EOF character (^D)
  if(std::cin.eof()){
    std::cout<<"Goodbye"<<"\n";
  } else{
    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.good()) {

      //determines what the file is reading in
      int item=1;
      Player* player1 =nullptr;
      Player* player2 =nullptr;
      Board* tileBoard =nullptr;
      Bag* newBag = new Bag();
      std::string playerName;
      std::string playerScore;
      std::string playerHand;

      std::string line;
      Player* currentPlayer=nullptr;
       while (!inFile.eof()) {
           std::getline(inFile, line);

         //reading in the player 1 name
          if(item==1){
            playerName=line;
          //std::cout<<"Read Player Name 1: "<<line<<std::endl;
            //reading in the player 1 score
          } else if (item==2){
            playerScore=line;
          // std::cout<<"Read Score : "<<line<<std::endl;
            //reading in the player 1 hand
          } else if(item==3){
            playerHand=line;
            player1= loadPlayer(playerName, playerScore, playerHand);


            //reading in the player 2 name
          } else if (item ==4){
            playerName=line;
        //   std::cout<<"Read Player Name 2: "<<line<<std::endl;

            // reading player 2 score
          } else if (item== 5){
            playerScore=line;
        //   std::cout<<"Read Score : "<<line<<std::endl;
            // reading player 2 hand
          } else if (item==6){
            playerHand=line;
            player2= loadPlayer(playerName, playerScore, playerHand);

            //reading in the board
          } else if (item==7){
            //std::cout<<"line 227:"<< line<<std::endl;
            std::getline(inFile, line);
           //std::cout<<"line 229: "<<line<<std::endl;
            std::getline(inFile, line);

            int col=0;
            int row=0;
            std::vector< std::vector<std::string>> boardVector;


            while(line[1]==' ' && !inFile.eof()){
              boardVector.push_back(std::vector<std::string>());
            // std::cout<<"lin 237: " <<line<<std::endl;

              if(line[1]==' '){
                col=0;
                std::stringstream boardRow(line);


                //splits the hand string into tiles
                while( boardRow.good() ){

                  std::string tile="";
                  getline( boardRow, tile, '|' );
                  if(col !=0){
              //     std::cout<<"line 252: "<<tile<<std::endl;
                    boardVector[row].push_back( tile );
                  }


              //    std::cout<<"line 254:" <<"Tile: "<< tile<<std::endl;

                // std::cout<< "line 256:"<<"Col "<< col<<std::endl;
                  col++;
                }
                std::getline(inFile, line);
              //  std::cout<<"line 260: "<<line<<std::endl;
                row++;

              }

            }
            col-=2;

            //creates board
            Tile*** board= new Tile**[row];
            for(int i = 0; i < row; i++){
              board[i] = new Tile*[col];
            }

            for(int i=0; i<row;i++){
              for(int j=0; j<col; j++){
                std::string tile=boardVector[i][j];
                if(tile[0]=='R' || tile[0]=='O' || tile[0]=='Y' || tile[0]=='G' || tile[0]=='B' || tile[0]=='P'){
              //   std::cout<<"Line: 275: "<<"colour: "<< tile[0]<< ", shape: "<< tile[1]<<std::endl;
                  Colour colour=tile[0];
                  Shape shape =tile[1] -'0';
                  board[i][j]= new Tile(colour, shape);
                }
              }
            }
            tileBoard = new Board(row, col);
            tileBoard->setBoard(board);
          // std::cout<<"line 287: print board"<< std::endl;
          //  tileBoard->printBoard();



            item++;
          }
          //reading in the Tile Bag
          if(item==8){

            std::stringstream bag(line);
            std::vector<std::string> bagVector;

            while( bag.good() )
            {
                std::string tile;
                getline( bag, tile, ',' );
                bagVector.push_back( tile );

                //std::cout<<"Line 303:"<<tile<<std::endl;
            }

            LinkedList* tileBag= new LinkedList();

            //for each of those tiles it adds the linkedlist
            for(std::string tile: bagVector){
              Colour colour=tile[0];
              Shape shape =tile[1] -'0';
              tileBag->addBack(new Tile(colour, shape));


            }
            newBag->setBag(tileBag);
          //  newBag->printBag();

            //reading in current player
          } else if(item ==9){
            currentPlayer=player1;
            if(player1->getName().compare(line)==0){
              currentPlayer=player1;
            } else{
              currentPlayer=player2;
            }

          }
          item++;
       }
       startLoadedGame(player1, player2, newBag, tileBoard, currentPlayer );
    } else{
      std::cout<<"Invalid File"<<std::endl;

      showMenu();
      menuOption();
    }



  }

  // board();
}

Player* loadPlayer(std::string playerName, std::string playerScore, std::string playerHand){


  //convert score which is current a string to an int
  int score = std::stoi( playerScore );

  //hand into linked list
  std::stringstream hand(playerHand);
  std::vector<std::string> playerHandVector;

  //splits the hand string into tiles
  while( hand.good() )
  {
      std::string tile;
      getline( hand, tile, ',' );
      playerHandVector.push_back( tile );

    //  std::cout<<"line 357"<<tile<<std::endl;
  }

  LinkedList* handList= new LinkedList();

  //for each of those tiles it adds the linkedlist
  for(std::string tile: playerHandVector){
    Colour colour=tile[0];
    Shape shape =tile[1] -'0';
    handList->addBack(new Tile(colour, shape));

  }

  //creates a Player
  Player* player= new Player(playerName);
  player->setScore(score);
  player->setHand(handList);

  return player;
}

void showInfo(){
  //DISPLAYS PLAYER INFORMATION
  std::cout <<"---------------------------------" << "\n";
  std::cout <<"Name: Duc Chau" << "\n";
  std::cout <<"Student ID: S3656289" << "\n";
  std::cout <<"Email: S3656289@student.rmit.edu.au" << "\n";

  std::cout <<"Name: Ryan Atkinson" << "\n";
  std::cout <<"Student ID: S3646447 " << "\n";
  std::cout <<"Email: S3646447@student.rmit.edu.au" << "\n";

  std::cout <<"Name: Eleni Cook" << "\n";
  std::cout <<"Student ID: S3722194" << "\n";
  std::cout <<"Email: S3722194@student.rmit.edu.au" << "\n";
}


bool validateName(const std::string& playerName){
  for (const char c : playerName){
    if(!isalpha(c) || !isupper(c)){
      return false;
    }else{
      return true;
    }

  }
  return true;
}
