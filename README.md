# June13UE4
Learning Project for UE4

This project is to figure out how to setup a Lobby system that allows changing of maps, modes.
Also faciltates multiple players, with player names, and different teams or spectators.

Maps can only have certain game modes, and team numbers and size. (Should always support spectators)

-----
Features done
-----
Change Teams
Ready System
Start system, that requires everyone to be ready and does a 5 second timer to server travel
Saving of custom TeamID data when server traveling

-----
TODOs
-----
1. Make sure Selected FMapInfo and make sure it's replicated to client for display purposes DONE (Need to double check with changing map feature)
2. Allow host to change map and modes
3. Make sure Players become spectators after server travel if they were on spectators team
4. Make sure after server travel, game only starts when all non-spectators have been connected.
3. Should investigate potential issue where ALobbyPlayerState and ALobbyGameState have separate places that indicate a player's current team selection. As that could create conflicts, due to lag or weird edge cases