# June13UE4
Learning Project for UE4

This project is to figure out how to setup a Lobby system that allows changing of maps, modes.
Also faciltates multiple players, with player names, and different teams or spectators.

Maps can only have certain game modes, and team numbers and size. (Should always support spectators)

-----
Progress and Roadmap as OF f768d40bd02bb7b92a15e551e4d32685e6e43406
-----
1. Make sure Selected FMapInfo and make sure it's replicated to client for display purposes DONE
2. Make sure Widgets are removed on servertravel DONE
3. Allow host to change map and modes
4. Allow host to press start game, when everyone is readied DONE
5. Allow players to change teams DONE
6. Show teams/spectators based on selected map and mode. DONE
7. Should investigate potential issue where ALobbyPlayerState and ALobbyGameState have separate places that indicate a player's current team selection. As that could create conflicts, due to lag or weird edge cases