# June13UE4
Learning Project for UE4

This project is to figure out how to setup a Lobby system that allows changing of maps, modes.
Also faciltates multiple players, with player names, and different teams or spectators.

Maps can only have certain game modes, and team numbers and size. (Should always support spectators)

-----
How to use/run project after downloading/cloning?
-----
Right click June13.uproject and press Generate Visual Studios Project files. 
Open June13.sln and build June13.

-----
Features done
-----
1. Change Teams
2. Ready System
3. Start system, that requires everyone to be ready and does a 5 second timer to server travel
4. Saving of custom TeamID data when server traveling
5. Change Maps
6. Players are on the corresponding team/spectator after seamless travel
7. Game only starts when all players have been connected.

-----
TODOs
-----
1. Should investigate potential issue where ALobbyPlayerState and ALobbyGameState have separate places that indicate a player's current team selection. As that could create conflicts, due to lag or weird edge cases
2. Unify LobbyGameState and TWGameState, since they have very similar stuff