# Super Mario Galaxy 2 PathFinder
Suggests an optimal speedrun path for Super Mario Galaxy 2 based on individual star times

## Why Super Mario Galaxy 2?
Super Mario Galaxy 2 speedruns consist of travelling to systems, beating a galaxy, collecting stars, and travelling to the next galaxy until you can beat the final Bowser boss battle, all as quickly as possible of course. Unlike most speedruns SMG2 has very discrete levels and there are many paths that are possible to take to beat the game. For novices at speedrunning this game, following pre-designed strategies may not be optimal because some movement and glitches are challenging to perform and taking an easier route may make a galaxy so much slower that is advantageous to replace that galaxy in the optimal path with another. This program allows novices to establish their times with each level in the game and then chooses an optimal path for them, just to make things a bit easier. I want to be one of these novices and this sounds more fun than planning routes by hand.

Even for experienced runners, pathing can change when new tech is found. If suddenly an experienced runner's IL time is a whole minute faster due to new tech, the whole route may change. This program just prevents you from having to establish the route by hand.

Keep in mind that this is only for any% speedruns, otherwise you must beat every galaxy in the game, so pathing around difficult galaxies is impossible.

## How does(/will) it work?
The program takes into account, IL times (and any extra time incurred when beating certain levels, such as being forced to meet new ship members), how long it takes to travel between galaxies on the overworld map, and which stars are available at any given time in the path. By greedily choosing which star will take the shortest amount of time from the last star completed, the program can build the (hopefully) quickest path which is unique to the runner using it.
