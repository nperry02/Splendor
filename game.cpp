/*
 * game.cpp
 * CS11 Splendor
 * game.cpp
 * Written by: Nate Perry
 * Date created: 12/1/2022
 * Purpose: game class and playes the game
 *
 */
 

#include "game.h"

    //makes vectors able to be used in all functions
    Vector mines;
    Vector transport;
    Vector vendors;
    Vector nobles; 

    //players
    Player *player_1 = new Player();
    Player *player_2 = new Player();

//constructor
Game::Game(string filename, string play_nobles){
   //store gem colors for easy reference in drawing functions 
   colors[0] = "white";
   colors[1] = "red";
   colors[2] = "pink";
   colors[3] = "blue";
   colors[4] = "green";
   colors[5] = "gold";

   //include nobles or not
        //changed to always be not (not doing extra credit)
   if(play_nobles == "true"){
        //switched to false
        this->play_nobles = false;
   }else{
        this->play_nobles = false;
   }

   //initialize the board
   for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }    

    //creates vectors and sets them up
    createVectors(filename);
    setUpGrid();
}

//createVectors
//input string filename
//goes through file and creates the decks
//3 made decks
void Game::createVectors(string filename){
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "Failed to open deck file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    //variables declaration
    string ro;
    infile >> ro >> ro >> ro >> ro >> ro >> ro >> ro >> ro >> ro;
    string type;
    int pres;
    string dis;
    int w, r, p, b, g;

    //loop through file, declaring cards into 3 diff vectors
    while(ro != "n"){
        infile >> pres >> dis >> w >> r >> p >> b >> g;
        //creates new card and puts it into a vector
        Card *card_p = new Card(pres, dis, w,r,p,b,g);
        if(ro =="m"){
            mines.push_back(card_p);
        } else if(ro == "t"){
            transport.push_back(card_p);
        } else if(ro == "v"){
            vendors.push_back(card_p);
        }
        infile >> ro;
    }
    infile.close();
}

//setUpGrid
// input: none
// takes the top cards of deck and puts them on grid
// sets up gem bank
// sets up the grid and gem_bank
void Game::setUpGrid(){

    //sets up vendors
    for (int i =0; i<4; i++){
        grid[0][i]=vendors.back();
        vendors.pop_back();
    }
    //sets up transport
    for (int i =0; i<4; i++){
        grid[1][i]=transport.back();
        transport.pop_back();
    }
    //sets up mines
    for (int i =0; i<4; i++){
        grid[2][i]=mines.back();
        mines.pop_back();
    }

    //set up gem bank
    for (int i =0; i < GEMS-1; i ++){
        gem_bank[i]=4;
    }
    gem_bank[5]=5;
}

Game::~Game() {
    //deletes the decks
    for (int i = 0; i < vendors.size(); i++){
        delete vendors.at(i);
    }
    for (int i = 0; i < mines.size(); i++){
        delete mines.at(i);
    }
    for (int i = 0; i < transport.size(); i++){
        delete transport.at(i);
    }
    for (int i = 0; i < nobles.size(); i++){
        delete nobles.at(i);
    }
    for (int i = 0; i < CARD_ROWS; i++){
        for (int j = 0; j < CARD_COLS; j++){
            delete  grid[i][j];
        }
    }
}

//main game loop
void Game::playGame(){
    bool game_over = false;
    bool player1_turn = true;
    int winner = 0; 
    bool quit = false;

    while(!game_over && !quit){
        //reset the screen and draw board
        clearBoard();
        screen_clear();
        screen_home();
        drawBoard();
    
        quit = queryLoop(player1_turn);

        game_over = checkGemsAndWinner(player1_turn, &winner);
        
        //change turns
        player1_turn = !player1_turn;
    } 

    if(winner == 1 || winner == 2){
        cout << "Congratulations Player " << winner << ": YOU WIN!!!";
    } else if (winner == 3){
        cout << "You losers tied - BORING!!!";
    }
}

//queryLoop
//input boolean showing whose turn it is
//asks user question and calls functions
//returns bool if game is over (if quit game)
bool Game:: queryLoop(bool player1_turn){
    string ans = "";
    //ask question
    if(player1_turn){
        cout << "PLAYER 1, enter your next move: ";
    } else {
        cout << "PLAYER 2, enter your next move: ";
    }

    //goes through ansers continues loop if input not allowed
    bool check = false;
    while (check == false){
        cin >> ans;

        if(ans == "q"){
            return true;
        } else if(ans == "p2"){
            check = p2Query(player1_turn);
        } else if(ans == "p3"){
            check = p3Query(player1_turn);
        } else if(ans == "r"){
            check = rQuery(player1_turn);
        } else if(ans == "b"){
            check = bQuery(player1_turn); 
        } else if(ans == "br"){
            check = brQuery(player1_turn);
        } else{
            cout << "Invalid move - enter a valid move: ";
        }
    }
    return false;
}

//p2Query
//input: bool of whose turn it is
//sees if input is valid
//returns false is not valid, calls function + true is it is
bool Game::p2Query(bool player1_turn){
    //declare variables
    string g;
    cin >> g;
    int gem = getGemIndex(g);

    if (gem == -1){

        //if gem is not a real color
        cout << "Invalid move (invalid color) - enter a valid move: "; 
        return false;
    } 
    else if (gem_bank[gem]!=4){

        //if not 4 gems in bank
        cout << "Invalid move (unavailable gems) - enter a valid move: ";
        return false;
    } 
    else{

        //calls the function
        if(player1_turn){
            takeTwoGems(&player_1, gem);
        }
        else{
            takeTwoGems(&player_2, gem);
        }
        return true;
    }
}

//p3Query
//input: bool of whose turn it is
//sees if input is valid
//returns false is not valid, calls function + true is it is
bool Game::p3Query(bool player1_turn){
    //declare variables
    string threeColors[3];
    cin >> threeColors[0] >> threeColors[1] >> threeColors[2];
    int trioC[3];

    //test if each color is a real color
    for(int z = 0; z<3; z++){
        trioC[z] = getGemIndex(threeColors[z]);
        if (trioC[z] == -1){
            cout << "Invalid move (invalid color) - enter a valid move: "; 
            return false;
        }
    }
    //test if there is enough gems
    for(int z = 0; z<3; z++){
        if(gem_bank[trioC[z]]==0){
            cout << "Invalid move (unavailable gems) - enter a valid move: ";
            return false;
        } 
    }

    //calls function
    if(player1_turn){
        takeThreeGems(&player_1, trioC);
    }
    else{
        takeThreeGems(&player_2, trioC);
    }
    return true;
}

//rQuery
//input: bool of whose turn it is
//sees if input is valid
//returns false is not valid, calls function + true is it is
bool Game::rQuery(bool player1_turn){
    string typ;
    int plce;
    cin >> typ >> plce;
    //check if actual card type
    if(typ != "m" && typ != "t" && typ != "v"){
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        return false;
    }
    //check if actual column
    if(plce<1 || plce>4){
        cout << "Invalid move (invalid card column) - enter a valid move:";
        return false;
    }

    //calls function depending on player and if there is open space
    //if no open space return false
    if(player1_turn){
        if(player_1.getReserve(2)==nullptr){
            reserveCard(&player_1, typ, plce);
            return true;
        }
        cout << "Invalid move (reserve is already full) - enter a valid move: ";
        return false;
    }
    if(player_2.getReserve(2)==nullptr){
        reserveCard(&player_2, typ, plce);
        return true;
    }
    cout << "Invalid move (reserve is already full) - enter a valid move: ";
    return false;
}

//bQuery
//input: bool of whose turn it is
//sees if input is valid
//returns false is not valid, calls function + true is it is
bool Game::bQuery(bool player1_turn){
    string typ;
    int plce;
    cin >> typ >> plce;

    //check if card type is valid
    if(typ != "m" && typ != "t" && typ != "v"){
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        return false;
    }
    //check if column is valid
    if(plce<1 || plce>4){
        cout << "Invalid move (invalid card column) - enter a valid move:";
        return false;
    }

    //call function
    bool pos;
    if(player1_turn){
        pos = buyCard(&player_1, typ, plce);
    }
    else{
        pos = buyCard(&player_2, typ, plce);
    }
    //if not enough gems
    if (pos == false){
        cout << "Invalid move (cannot afford card) - enter a valid move: ";
        return false;
    }     
    return true;
}

//brQuery
//input: bool of whose turn it is
//sees if input is valid
//returns false is not valid, calls function + true is it is
bool Game::brQuery(bool player1_turn){
    int plce;
    cin >> plce;

    //check if actual place
    if(plce<1 || plce>3){
        cout << "Invalid move (no card at that index) - enter a valid move:";
        return false;
    }
    bool pos;
    //depending on player, check if card at index, if so call function
    if(player1_turn){
        if(player_1.getReserve(plce-1)==nullptr){
            cout << "Invalid move (no card at that index) - enter a valid move:";
            return false;
        }
        pos = buyReserve(&player_1, plce);
    }
    else{
        if(player_2.getReserve(plce-1)==nullptr){
            cout << "Invalid move (no card at that index) - enter a valid move:";
            return false;
        }
        pos = buyReserve(&player_2, plce);
    }

    //if cannot afford card
    if (pos == false){
        cout << "Invalid move (cannot afford card) - enter a valid move: ";
        return false;
    }
    return true;
}

//checkGemsAndWinner
//input: bool for player turn, pointer to winner int
//sees if player has less than 10 gems and is anyone has 15 prestige
//returns if they won
bool Game::checkGemsAndWinner(bool player1_turn, int *winPoint){
    //get rid of gems if have too much
    bool totalGems = false;
    //continues loop until have 10 gems
    while(totalGems == false){
        if(player1_turn){
            totalGems = checkGemCount(&player_1, player1_turn);
        } else{
            totalGems = checkGemCount(&player_2, player1_turn);
        }
    }

    //if 2nd player turn
    //checks to see if anyone has over 15 prestige
    if(player1_turn==false){
        if(player_1.totalPrestige() >= 15){
            if(player_1.totalPrestige() == player_2.totalPrestige()){
                *winPoint=3;
                return true;
            }
            *winPoint=1;
            return true;
        } else if (player_2.totalPrestige() >= 15){
            *winPoint=2;
            return true;
        }
    }
    return false;
}

//takeTwoGems
//input: player pointer and index of gem
//takes 2 gems from bank and gives to player
//return nothing
void Game::takeTwoGems(Player *p, int gem){
    gem_bank[gem]=2;
    p->addGemCount(gem, 2);
}

//takeThreeGems
//input: player pointer and index of gem for all 3
//takes gems from the bank and gives to player
//return nothing
void Game::takeThreeGems(Player *p, int trioC[3]){
    for(int i = 0; i<3; i++){
        gem_bank[trioC[i]]= gem_bank[trioC[i]]-1;
        p->addGemCount(trioC[i], 1);
    }
}

//reserveCard
//input: player pointer, string of type of card, place of card int
//puts card in reserve and gets a new card
//nothing
void Game::reserveCard(Player *p, string typ, int plce){
    Card *c;
    //per type: puts card into reserve and replaces it on grid
    if(typ== "v"){
        c=grid[0][plce-1];
        p->setReserve(c);
        grid[0][plce-1]=vendors.back();
        vendors.pop_back();
    }
    else if(typ == "t"){
        c=grid[1][plce-1];
        p->setReserve(c);
        grid[1][plce-1]=transport.back();
        transport.pop_back();
    }
    else{
        c=grid[2][plce-1];
        p->setReserve(c);
        grid[2][plce-1]=mines.back();
        mines.pop_back();
    }
    //if there is gold gems give one to player
    if(gem_bank[5]>0){
        gem_bank[5]=gem_bank[5]-1;
        p->addGemCount(5, 1);
    }
}

//buyCard
//input: player pointer, string of type of card, place of card int
//takes card off grid, and replaces gems used, and 
//gives player discount + prestige
//returns: bool if player has enough gems or not
bool Game::buyCard(Player *p, string typ, int plce){
    Card *c;
    int spt;
    //per type of card: take card being bough and put into pointer
    if(typ== "v"){
        c=grid[0][plce-1];
        spt = 0;
    } else if(typ == "t"){
        c=grid[1][plce-1];
        spt = 1;
    } else{
        c=grid[2][plce-1];
        spt = 2;
    }
    //card transaction of gems / false if not enough gems
    bool tr = buyCardTransaction(c, p);
    if(tr == false){
        return false;
    }
    //per type of card: switch out card on grid for new card
    delete grid[spt][plce-1];
    if(spt == 0){
        grid[spt][plce-1]=vendors.back();
        vendors.pop_back();
    } else if (spt == 1){
        grid[spt][plce-1]=transport.back();
        transport.pop_back();
    } else {
        grid[spt][plce-1]=mines.back();
        mines.pop_back();
    }
    return true;
}

//buyReserve
//input: player pointer,  place of card int
//takes card off reserve, and replaces gems used, and 
//gives player discount + prestige
//returns: bool if player has enough gems or not
bool Game::buyReserve(Player *p,  int plce){
    //pointer to card
    plce = plce - 1;
    Card *c = p->getReserve(plce);

    //card transaction of gems / false if not enough gems
    bool tr = buyCardTransaction(c, p);
    if(tr == false){
        return false;
    }

    //moves over resevre cards and makes last reserve nullptr
    delete p->getReserve(plce);
    for (int i = plce; i<2; i++){
        p->setReserveAt(p->getReserve(i+1), i);
    }
    p->setReserveAt(nullptr, 2);

    return true;
}

//buyCardTransaction
//input card and player pointer
//goes through gem cost to buy card and buys it
//returns false if not enough gems
bool Game::buyCardTransaction(Card *c, Player *p){
    //amount of gold gems needed
    int gemsNedded=0;
    //sees if player has enough gems
    for(int i = 0; i<5; i++){
        if(c->getPrice(i) != 0){
            if(c->getPrice(i) > (p->getDiscount(i) + p->getGemCount(i) )){
                gemsNedded = gemsNedded + c->getPrice(i) - (p->getDiscount(i) + p->getGemCount(i) );
            }
        }
    }
    if(gemsNedded > p->getGemCount(5)){
        return false;
    }
    //amount of gems needed to buy
    int extra;
    //goes though each gem and subtracts price from discount and gems of player
    for(int i = 0; i<5; i++){
        if(c->getPrice(i) != 0){
            if(c->getPrice(i) <= (p->getDiscount(i) + p->getGemCount(i) )){
                extra = c->getPrice(i) - p->getDiscount(i);
                if(extra > 0){
                    gem_bank[i] = gem_bank[i] + extra;
                    p->subGemCount(i, extra);
                }
            } else{
                gem_bank[i] = gem_bank[i] + p->getGemCount(i);
                p->subGemCount(i, p->getGemCount(i));
            }
        }
    }
    //substracts gold left and puts it into bank
    p->subGemCount(5, gemsNedded);
    gem_bank[5]= gem_bank[5] + gemsNedded;

    //sets player new discount and new prestige
    p->setDiscount(c->getDiscountIndex());
    p->addPrestige(c->getPrestige());
    return true;
}

//checkGemCount
//input player pointer and bool for player turn
//checks the amount of gems the player has
//if over 10 make player get rid of some
//return true if less or = to 10 gems
bool Game::checkGemCount(Player *p, bool player1_turn){
    //finds amount of gems player has, if less than 11 return true
    int tot = 0;
    for(int i = 0; i <GEMS; i++){
        tot = tot + p->getGemCount(i);
    }
    if (tot <= 10){
        return true;
    }
    //creates board
    clearBoard();
    screen_clear();
    screen_home();
    drawBoard();

    if(player1_turn){
        cout << "PLAYER 1, you have more than 10 gems! Name one gem you would like to return: ";
    } else{
        cout << "PLAYER 2, you have more than 10 gems! Name one gem you would like to return: ";
    }
    string nC;
    cin >> nC;
    while(nC != "white" && nC != "red" && nC != "pink" && nC != "blue" && nC != "green" && nC != "gold"){
        cout << "Invalid color. Name one gem you would like to return: ";
        cin >> nC;
    }
    //gets rid of chosen gem
    int a = getGemIndex(nC);
    p->subGemCount(a, 1);
    gem_bank[a]=gem_bank[a]+1;
    return false;
}

//getGemIndex
//input: string of gem
//finds index of that gem name
//return int
int Game::getGemIndex(string g){
    //goes through gems until finds it index
    for (int i = 0; i < GEMS-1; i++){
        if(colors[i]==g){
            return i;
        }
    }
    return -1;
}



//Get the gem color associated with the given index 
string Game::indexToColor(int index){
    return colors[index];
}

//draw all of the elements onto the game board
void Game::drawBoard(){
    int vpos = 0;
    int hpos = 1;

    //draw the card decks
    if(!vendors.empty()){
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if(!transport.empty()){
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if(!mines.empty()){
        drawDeck(vpos, hpos, "Mines");
    }

    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for(int i = 0; i < CARD_ROWS; i++){
        for(int j = 0; j < CARD_COLS; j++){
            if(grid[i][j] != nullptr){
                drawCard(vpos, hpos, grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            int index = (i * 2) + j;
            if(gem_bank[index] > 0){
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }
    
    //draw players
    drawPlayer(vpos + 1, 1, &player_1);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), &player_2);

    //draw nobles
    if(play_nobles){
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for(int i = 0; i < NUM_NOBLES; i++){
            if(nobles.at(i) != nullptr){
                drawNoble(vpos, hpos, nobles.at(i));
            }
            vpos += CARD_HEIGHT + 1;
        }
    }

    //print out the finished board
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            if(board_color[i][j] != "white"){
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
   } 
   cout << endl; 
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card *c){
    string top    = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank  = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < 5; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for(int i = 0; i < GEMS-1; i++){
        int price = c->getPrice(i);
        if(price > 0){
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p){
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if(hpos < 10){
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    }else{
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for(int i = 0; i < GEMS-1; i++){
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if(bonus >= 10){
            length += 1;
        }
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    int different_gems = GEMS;
    for(int i = 0; i < different_gems; i++){
        int gems = p->getGemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for(int i = 0; i < 3; i++){
        Card *c = p->getReserve(i);
        if(c == nullptr){
            drawDeck(vpos, hpos, "");
        }else{
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for(int i = 0; i < length; i++){
        board[vpos + (CARD_HEIGHT/2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color){
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for(int i = 0; i < GEMS; i++){
        int length = gem_image[i].length();
        for(int j = 0; j < length; j++){
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card *c){
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for(int i = 0; i < length; i++){
        board[vpos][hpos + i] = top[i];

        if(i == 8 || i == 9){
            board_color[vpos + 1][hpos + i] = c->getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for(int j = 2; j < CARD_HEIGHT; j++){
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = c->getPrestige() + 48;
    board_color[vpos + 2][hpos + 8] = c->getGemColor();
    board_color[vpos + 2][hpos + 9] = c->getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c->getGemColor();
    board_color[vpos + 1][hpos + 9] = c->getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for(int i = 0; i < GEMS-1; i++){
        int price = c->getPrice(i);
        if(price > 0){
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }

}

//clear the board display
void Game::clearBoard(){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++){
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
   }  
}
