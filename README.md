# XOI

A CLI three-player score-based variant of naughts and crosses.

## Rules

- Take turns placing tokens (`X`, `O`, `I`), two at a time.
- Create special patterns of tokens to gain points (`X`, `O`, `I`), seen below.
- Patterns cannot share tokens.
- The game ENDS when the board is full or no more points can be gained.
- The player with the most points at the end of the game WINS!

### Pattern Types

```
//===========\\     //===========\\     //===========\\     //===========\\
|| X |   | X ||     ||   |   |   ||     ||   | I |   ||     ||   |   |   ||
||---|---|---||     ||---|---|---||     ||---|---|---||     ||---|---|---||
||   | X |   ||     || O | O |   ||     ||   | I |   ||     || I | I | I ||
||---|---|---||     ||---|---|---||     ||---|---|---||     ||---|---|---||
|| X |   | X ||     || O | O |   ||     ||   | I |   ||     ||   |   |   ||
\\===========//     \\===========//     \\===========//     \\===========//
    5 points            3 points            1 point             1 point
```
