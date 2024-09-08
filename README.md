# MazeSolver

This project is a MazeSolver that aims to find a path through a maze. 
The objective is to have a user "program" an agent with instructions (conditions and operations to perform if those conditions are true), and for that agent to solve the maze.
It is also possible to find the shortest path through the maze (at the moment only with the A* algorithm).

## Demo

### Feature 1: Creating or editing a maze
- A maze can be loaded from a file or created by an user.
- The maze can be edited by user controls:
	- Left click turns a cell into a wall.
	- Right click turns a cell into an empty cell.
- A maze can be saved to a file to be loaded later.

https://github.com/user-attachments/assets/77ce1192-f2e3-42a1-b5e5-ce1e642b8e9c

### Feature 2: Finding the shortest path
 - The maze can be solved by an agent that follows the shortest path (currently using the A* algorithm).
   
https://github.com/user-attachments/assets/a746fc76-01d4-4f4d-9ab7-9e8690cd3139

 - It can also find the shortest path quickly in larger maps.

https://github.com/user-attachments/assets/c99331b9-df78-45e5-8fbb-bfece7daec2a

### Feature 3: Solving the maze with an "programmed" agent
 - The maze can be solved by an agent that follows a set of instructions that can be programmed by the user (currently hardcoded). Currently its instructions are too simple so it gets stuck in a loop very easily..

https://github.com/user-attachments/assets/89dfd441-d881-4494-a31e-8680cad589ad
