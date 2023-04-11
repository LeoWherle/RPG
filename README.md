# RPG
- **Contributors:**
  - [Léo Wehrle - Rentmeister](https://github.com/leoWherle)
  - [Théodore Magna](https://github.com/TheodoreEpitech)
  - [Martin Sabatier](https://github.com/Nevi1)
  - [Nathanael Kimbembe-Croissant](https://github.com/Nathanael-Kimbembe)

## Language : C

## Libraries : CSFML - standart math library

## The only system calls allowed are the following ones:
 - malloc - free - memset
 - (s)rand - stat
 - (f)write - getline
 - (f)open - (f)read - (f)close
 - opendir - readdir - closedir

## Requirements :
  - gcc
  - make
  - graphical environnement

## REQUIREMENTS
  ### MANDATORY
    • The player needs to have characteristics
    • The player can fight enemies AND the characteristics impact the fights results
    • The player have an inventory which can contain a limited set of items
    • The player can earn experience by winning fights and/or accomplishing specific actions
    • The player can level up thanks to experience AND upgrading its characteristics
    • The game contains NPC
    • The game contains at least one quest
    • The game contains a how to play system at the very beginning
  ### TECHNICAL REQUIEREMENTS
    • A collision system including moving and static elements with different shapes.
    • Camera movements (zoom, translation, rotation).
    • 3D effects (depth scaling, isometric projection. . . ).
    • Buttons must have at least 3 differents state
    • Saving system
  ### MUST
    General
      • The window may be closed using events,
      • The windows may have differents mode :
        • Window mode
        • Full-screen mode
      • The windows may have differents resolutions, at least two (1920x1080, and an other)
      • The game manages inputs from the mouse click and keyboard,
      • The game contains animated sprites rendered thanks to sprite sheets,
      • Animations in your program are frame rate independent,
      • Animations and movements in your program are timed by clocks.
    Main menu
      • Must contain at least these options
      • Start the game
      • Resume game (grayed out if not possible)
      • Settings
      • Quit the game
      • The settings option must contain
      • Sound and music volume options
      • A window size and resolution options
    In game menu
      • Must be accessible by pressing the Escape key
      • Must contain at least these options
      • Character options
      • equipment and inventory management
      • characteristics management
      • Saving
      • Loading
      • Settings
      • the same that main menu
      • commands list
  ### SHOULD
    • Splash screen at the beginning
    • Command edit into the in game menu
    • As much information as possible about the game should be stored in a configuration file.
    • The game should have an advanced collision system to manage complex fighting.
    • The game should contains simple particle system :
    3
    • with at least 2 types of particle,
    • particle effects (changing colors, scaling, bouncing, fading) to simulate realistic environment
    (wind, fire, rain, snow. . . ).
    COULD
    • Have a skill tree, unlocking different abilities (active and passive).
    • Have a complete particle engine.
    • Use scripting to describe entities.
    • Have a map editor.


## How to use:

```
  $ make
  $ ./my_rpg
```