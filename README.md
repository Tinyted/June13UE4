# June13UE4
Learning Project for UE4

This project is to figure out how to setup a Lobby system that allows changing of maps, modes.
Also faciltates multiple players, with player names, and different teams or spectators.

Maps can only have certain game modes, and team numbers and size. (Should always support spectators)

-----
Progress and Roadmap as OF 862dca6cf9fea7a709a7df6f33a7a623f7342a50
-----
1. Need blueprint accessible way to show case current Players and their Names
2. Custom PlayerState to hold team info (use interface so it can be passed?)
3. Custom LobbyPlayerController for further customization on actions available to be performed
4. Find way to create available FMapInfo on server, then replicate to clients