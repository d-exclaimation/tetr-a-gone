
# Tetr-A-Gone (Group 207)

*Floor pieces break slowly when you walk on them - keep moving and survive longest*

By [Vincent ~ (vno16)](vno16@uclive.ac.nz) and [Natalie Kim (ski102)](ski102@uclive.ac.nz) (ENCE260 2022)

## Guide

### Brief

Both players will be dropped above many square platforms, 7x10 to be precise (each board show half of the entire map, players will be dropped on their half of the map). 

When any player moved away from a platform, it will reduce its strength by some amount.

If a platform no longer have enough strength to hold itself together, it will be broken and open a hole on that location.

When a player moved into a hole or got trapped with holes from all 4 sides, they fall and lose the game. 

### Objective

Be last player standing (last to fall) or make sure the other player fell before you.

### Setup 

Setup the funkits to have the IR receivers and transmitters facing each other.

![Facing each other](https://www.tomrizzi.com/images/ucfk5.png)

<small>Make sure the controls are either on the right or bottom side of the funkit from each player point of view</small>

The display will be **the combined of the LED matrix displays on both board**.

Each player will start on their **bottom corner**  of the LED display.


### Playing

- **Blinking light**: A player.
- **Constant light**: A hole.
- **No light**: A platform that is not broken yet.

You will start off on your side of the board at the bottom corner (**blinking light**).

Move the navigation switch in any directions to move your player.

The previous platform where you were before will slowly lose strength. If it is broken, it will be a hole and glow (**constant light**).

You can move into the other player side of board and vice versa. Each time the other player moves, you should see the blue LED on your board flash for a short period of time.

If any player fell (a player move into a hole (**constant light**) or is sorrounded by holes on all 4 sides), the game will end and shown a letter indicating who won (**W** for winner, **L** for loser). 

### Controls

- `NAVSWITCH_*`
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

![Plug the USB cable](https://support.usa.canon.com/library/attachments/ServiceWareImages/LDImages/SolutionAnswer/iP90/USBToPC.gif)

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