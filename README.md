## CustomBoardGamesApplication
"this was part of an assigment in OOP course under supervision of Dr Mohamed El Ramly, Factuly of Computers and Artificial Intelligence Cairo University"
a custom board Games application That contains 8 boardGames that is all based on the classic Tic Tac Toe Game But with some creative ideas.
the program has an ai using the MinMax algorithm in Game number 2 and 5.
me and my teammate members didn't have the time to implement an ai player for the rest of the games.
we tried to make a graphical user interface for the 8 games using dot net framework but we faced alot of problems when integrating the code logic in c++ with c# so we used IMGUI instead and made a gui for only game number 8 and 7. we may continue work on this project in the furture.

## how to play the games 
if you want to try it out in terminal (i recommend to try it in terminal thouh, since you may find some bugs we didn't find in gui),
all you have to do is just run the main file :D.
if you want to try it in gui, run the executable file in the BoardGamesGUI\BoardGames\Release path

for any questions about the gui code or anything alse, our emails is below feel free to contact us

* Mohamed Adel Kamal (email) raynowing007@gmail.com (made game number 2, 5 and 7 ,made ai for game 2 and 5)
* Mark Amir Samir (email) markamir415@gmail.com (made game number 1, 4, 8)
* Anton Zakaria Ezzat (email) antonzekoo@gmail.com ( made game number 3,6, made the gui using IMGUI)


## Games Discription 
## Game descriptions are taken from: https://www.whatdowedoallday.com/tic-tac-toe-variations/

1- Pyramic Tic-Tac-Toe
The game board is shaped like a pyramid. Five squares make the base, then three, then one. Players
take turns marking Xs and Os as in traditional tic-tac-toe. Winning: The first player to get three-in-a-row vertically, horizontally, or diagonally wins. See
two examples of winning positions, below.
![image](https://github.com/user-attachments/assets/408eed0f-f97f-4157-b492-4332fb4ee4e5)

2- Four-in-a-row
You will recognize four-in-a row as a two-dimensional version of the classic game, Connect Four. The game board consists of a 7 x 6 grid. Seven columns of six squares each. Instead of dropping
counters as in Connect Four, players mark the grid with Xs and Os as in tic-tac-toe. Rules: The first player places an X in the bottom square of any column. Taking turns, players make
their mark in any column, as long as it is in the lowest square possible. See image below for an
example of possible first six moves. Winning: The first player to get four-in-a-row vertically, horizontally, or diagonally wins.

![image](https://github.com/user-attachments/assets/9215bf0d-b155-46a6-b0fa-d6e9d03b9e98)

3- 5 x 5 Tic Tac Toe
This tic-tac-toe variation is played on a 5 x 5 grid. As in the traditional game, players are Xs or Os. Rules: Players take turns placing an X or an O in
one of the squares until all the squares except one
are filled. (Each player has 12 turns for a total of
24 squares.)
Winning: Count the number of three-in-a-rows
each player has. Sequences can be vertically, horizontally, or diagonally. Whoever has the most, wins. Can one mark be counted in more than one
three-in-a-row sequence? Decide ahead of time, yes or no. It is easier in implementation to allow
counting more than once.

![image](https://github.com/user-attachments/assets/1fa535aa-5912-4e44-bfa6-434bc9a13896)

4- Word Tic Tac Toe
Word Tic-tac-toe is an innovative twist on the classic Tic-
tac-toe game. Instead of using "X" or "O", players place
letters on a 3x3 grid to form valid words. This version
adds a linguistic challenge to the traditional game
mechanics. Players aim to form a valid word with the
letters they place on the board. Words can be formed
horizontally, vertically, or diagonally. Rules: Each player takes turns placing one letter on the
board. A player must try to form a valid word with each
move. Players can build upon existing letters to form words, provided that the resulting sequence is
a valid word. Winning: The game is won by forming a valid word horizontally, vertically, or diagonally. If the
board fills up without a valid word being formed, the game ends in a draw.

![image](https://github.com/user-attachments/assets/92f9a6ff-421d-47a1-b89d-c79a3fd4a089)

5- Numerical Tic-Tac-Toe
Numerical Tic-Tac-Toe offers a mathematical twist to
the classic Tic-Tac-Toe game. Instead of the traditional "X" and "O", players use numbers to add an element of
strategic calculation. The objective is to achieve a sum
of 15 with three numbers in a row, column, or diagonal. Rules: Player 1 typically starts and uses odd numbers
(1, 3, 5, 7, 9), while Player 2 uses even numbers (2, 4, 6, 8). Players alternate turns, placing one number in an
empty cell on the board. Each number can only be used
once. Winning: A player wins by placing three numbers in a row, column, or diagonal that add up to 15.


![image](https://github.com/user-attachments/assets/c22d35fa-e532-4fbf-809e-041c3234316b)


6- Misere Tic Tac Toe
Misere Tic Tac Toe, also known as Inverse Tic Tac Toe or Toe Tac Tic, is a unique twist on the
classic game. In this version, the objective is to avoid
getting three marks in a row. The game flips the traditional
win condition on its head, making every move a strategic
decision to prevent losing. Rules: The game is played on a standard 3x3 Tic-Tac-Toe
grid. The goal is to avoid placing three of your marks in a
row, column, or diagonal. The player who ends up with
three marks in a row loses the game. If all cells are filled
without either player aligning three marks in a row, the
game ends in a draw.

![image](https://github.com/user-attachments/assets/b23686e9-ca5a-401f-8148-5af892cdaa9c)

7- 4 x 4 Tic-Tac-Toe
4 x 4 Tic-Tac-Toe is an extended version of the classic game, played on a larger board with more
complex strategies. Each player has four tokens and aims to
align three tokens in a row to win. This game introduces new
movement rules and strategic depth to the traditional Tic-Tac- Toe. The game is played on a 4x4 grid. Each player has four
tokens. Tokens are placed in specific starting positions: two
tokens on opposite sides of the board for each player. (as shown in image).
Rules: Players alternate turns, moving one of their tokens to
an immediately adjacent open square. Tokens can be moved
horizontally or vertically but not diagonally. Tokens may not jump over other tokens. The goal is to
align three of your tokens in a row. This can be achieved
horizontally, vertically, or diagonally. Winning: The first player to get three tokens in a row wins
the game. The alignment alignment can be in any direction: horizontal, vertical, or diagonal.

![image](https://github.com/user-attachments/assets/ca200314-94ee-4996-9d9e-a63c22de6368)

![image](https://github.com/user-attachments/assets/092351b6-a6ca-4cb8-bd63-8360cd4ed458)


8- Ultimate Tic Tac Toe
Ultimate Tic Tac Toe is an expansion of the
classic game, where players engage in a meta- game of Tic Tac Toe within a 3x3 grid of
smaller Tic Tac Toe boards. The goal is to win
three smaller games in a row to claim victory
on the main board, adding layers of complexity
to the traditional game. The game is played on
a large 3x3 grid, where each cell contains a
smaller 3x3 Tic Tac Toe board. Rules: Player 1 starts by choosing any of the
nine smaller Tic Tac Toe boards to play on. Players alternate turns, playing Tic Tac Toe on
the smaller boards. The winner of each smaller
board claims that space on the main board. The
winner of the smaller board replaces that board
with their symbol (X or O) on the main board. Winning: The first player to win three smaller boards in a row on the main 3x3 grid wins the
Ultimate Tic Tac Toe game. The winning row on the main board can be horizontal, vertical, or
diagonal.

![image](https://github.com/user-attachments/assets/6151d4f7-0fbc-4449-8733-bd5b97b70fe5)








