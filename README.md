# Filler
A competitive packing algorithm that seeks to beat all in the 42 game filler

<img src="https://media.giphy.com/media/3q1uejtiT7nBYAcEta/giphy.gif" />

In the turn-based game filler, two algorithms compete against each other to fill up the most space on a grid. Each player starts as a single square on the grid, and each turn a new shape is presented to each program, which must be placed according to the following rules:

1. The shape cannot go outside the boundaries of the grid.
2. The shape cannot overlap any of the enemy's squares.
3. The shape must overlap one (and only one) of your own squares.

Once a shape is placed, the squares its placed on belong to the program that placed it. The game ends for one player when a shape is presented to him that he cannot manage to place. The game then continues with only the other player playing, until the same happens for him.

The winner is the player who has placed the most pieces at the end.

The full pdf for the project can be read here.

<b>How to run the program</b>

go to resources and run ./filler_vm -p1 player_binary -p2 player_binary -f map_file

<b>The algorithm</b>

Undoubtedly the most effective method involves trying to smother the opponent so they are no longer able to put pieces.

While many students employed a heat map to tackle this task, I employed a simpler algorithm that actually proved more effective so far in my tests competing against other students.

My algorithm simply consisted of two behaviours:

Seek: If no piece can be placed that contacts an enemy piece, place a piece that will bring my territory closer to the enemy's centre.
Smother: If a piece can be placed in contact with an enemy's piece, determine which placement covers the most surface area of the enemy and place shape there.

Using only these two behaviours, the algorithm defeats easily all players supplied in the players folder and outperforms over students' so far I have played.

<b>Visualiser</b>

As a bonus, I created a visualiser using the basic minilibX library used at my school (Ecole 42), and epiTech. The library allows little more than creating a screen and putting pixels on it. Expanding on my project making wireframes with minilibX, I 
created the following visualiser:

It can run as so:

./filler_vm -p1 player_binary -p2 player_binary -f map_file | ./vis

<b>Learnings</b>

1. For the visualiser I learn about the advantages and disadvantages between dynamic arrays and linked lists. Initially I parsed all the information from the game into a single char array by reading each output of the game, and joining it to the current string by remallocing and copying. When strings were becoming millions of characters long, I naturally realised this method to be particularly inefficient, and I was having to recopy millions of characters each time I needed to add on just an extra hundred/thousand. Instead I used a linked list, where each node got a copy of the map at each point of output.

2. I learnt multithreading to transfer the contents of the linked list into one large char array. I had heard of multithreading before, and had been eager to get to grips with it. In this case, I split the list into two halves and one thread copied the first half into the char array, while simultaneously the other thread copied the rest into the second half of the char array. This had a noticeable effect on speed when playing with the larger maps, making the visualiser process the data and generate its results instantly.
