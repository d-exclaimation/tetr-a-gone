# Tetr-A-Gone (Group 207)

*Each time a player walks over a floor piece, it becomes unstable and eventually fall apart! Keep moving to stay alive*

By [Vincent ~ (vno16)](vno16@uclive.ac.nz) and [Natalie Kim (ski102)](ski102@uclive.ac.nz) (ENCE260 2022)


[[_TOC_]]

## Guide

### Brief

Players will be dropped above a map of 7x10 rectangular platform consisting of 70 floor tiles (each board show half of the entire map, players will be dropped on their half of the map). 

Each time a player moves out of a plaform tile, it will reduce the tile's durability by some amount.

Once the platform tile no longer has enough strength to hold itself together, it will be disintegrate and open a hole on the location.

If any of the two players moves into the hole or gets trapped with holes on all 4 sides, they will fall and loses the game. 

### Objective

Be the last player standing (last to fall) or make sure the other player falls before you.

### Setup 

Setup the funkits to have the IR receivers and transmitters facing each other.


<p align="center">
<img width="350" src="https://vincent-shared-files.netlify.app/images/funkits.jpg">
</p>

<small>Make sure the controls are either on the right or bottom side of the funkit from each player's point of view</small>

The display will be **the combined of the LED matrix displays on both board**.

Each player will start on their **bottom left corner**  of the LED display.


### Playing

- **Blinking light**: A player.
- **Constant light**: A hole.
- **No light**: A platform that is not broken yet.

You will start off on your side of the board at the bottom left corner (**blinking light**).

Move the navigation switch in any direction to move your player dot.

Each time you pass over a platform tile, it will slowly lose durability. Eventually, the platform tile will weaken and breakdown, becoming a hole and glowing (**constant light**).

You can move into the other player's side of board and vice versa. Each time the other player moves, you should see the blue LED on your board flash for a short period of time.

If any player falls (a player move into a hole (**constant light**) or is sorrounded by holes on all 4 sides), the game will end and will display a letter indicating who won (**W** for winner, **L** for loser). 

### Controls

- `NAVSWITCH_NORTH`: Move your player north (from your board point of view)
- `NAVSWITCH_SOUTH`: Move your player south (from your board point of view)
- `NAVSWITCH_EAST`: Move your player east (from your board point of view)
- `NAVSWITCH_WEST`: Move your player west (from your board point of view)

## Running on the FunKit

Clone the API and drivers code for the UC FunKit 4

```bash
git clone https://eng-git.canterbury.ac.nz/rmc84/ence260-ucfk4.git
```

Go to the assignment folder

```bash
cd ence260-ucfk4/assignment
```

Clone the project

```bash
git clone https://eng-git.canterbury.ac.nz/ence260-2022/group_207.git
```

Plug the UC FunKit 4 board through USB

<img width="200" src="https://support.usa.canon.com/library/attachments/ServiceWareImages/LDImages/SolutionAnswer/iP90/USBToPC.gif">

Start the game

```bash
make program
```


## Targets

#### Compile the project

```bash
  make
```

#### Clean the binary outputs

```bash
  make clean
```

#### Run the test code

```bash
  make test
```

#### Compile the project from scratch (clean compile)

```bash
  make fresh
```

#### Run the project on the UC FunKit 4

```bash
  make program
```

#### Run a cleaned build of the project on the UC FunKit 4

```bash
  make prod
```


## Authors

- [Vincent ~ (vno16)](vno16@uclive.ac.nz) 
    - [vincent ~ (vno16@cs19110bs.canterbury.ac.nz)](vno16@cs19110bs.canterbury.ac.nz) (*This is me (Vincent) who messed up by letting git automatically set the email when pushing my commits* `:)` )
- [Natalie Kim (ski102)](ski102@uclive.ac.nz)

## Acknowledgements

The game idea is heavily inspired from [Fall Guys' Hex-A-Gone](https://fallguysultimateknockout.fandom.com/wiki/Hex-A-Gone).
