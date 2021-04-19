# LineDraw

This is the university project for the Algorithms&Data Structures I course in UFAZ. It is a paint like app that has many useful functions like line draws, undo operations, point disposition, line selection and etc. The project is mainly focused on implementation of stacks, vector calculus as well as usage of OpenGL.

## Prerequisites

You need:
* C Compiler
* OpenGL/GLUT library <br>
  For Ubuntu:
  ```
  sudo apt-get install freeglut3-dev
  ```
  
## Instructions

When the program is launched, we only have a white window with no vertices and no edges.

Pressing the `Esc` key exits the program.

There are two modes : 
1. **Create mode** - for creating new vertexes
2. **Edit mode** - to make edits of existing vertexes


**In Create mode** : 
* Each time the user makes a left mouse click, a new vertex is added at the position of the click.
* The selected vertex is always the most recent one.
* Each time the user presses the `Backspace` key, the last vertex is removed.
* Pressing the `Enter` key switches to edit mode.

**In Edit mode** :
* Clicking near a vertex selects that vertex and unselects everything else.
* Clicking near an edge selects that edge and unselects everything else.
* When a vertex is selected, the `arrow` keys move the selected vertex in the corresponding direction.
* When a vertex is selected, the `backspace` key removes the selected vertex. The new selected vertex is one of the neighbors of the removed vertex.
* When an edge is selected, pressing `i` (as in insert) inserts a new vertex at the middle of the selected edge.
* Pressing `n` (as in new) switches back to create mode.
* If the number of vertices is smaller than 2, then the system automatically switches to create mode.

## Usage
1. Compile the source code with the makefile: `make` or  `make linedraw`
2. Run the `./linedraw <width> <height>`
3. (Optional) Run `make clean` to clean the object files.
