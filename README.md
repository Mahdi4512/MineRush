# MineRush – Console Minesweeper Game (C++)

MineRush is a fully functional console-based **Minesweeper** game written in modern C++.  
The project includes safe input handling, recursive flood reveal, flagging, multiplayer mode,  
and a fully modular code structure to ensure stability and readability.

---

## 🎮 Features

✓ **Single-player & Multiplayer mode**  
✓ **Safe input system** (prevents infinite loops and invalid input crashes)  
✓ **Automatic flood reveal** for zero-value cells  
✓ **Flag toggling system**  
✓ **Win detection** when all safe cells are revealed  
✓ **Instant board refresh** after every action  
✓ **Shows all mines on game-over**  
✓ **Clear and modular code design**

---

## 🧩 How the Game Works

- The board contains hidden mines represented as `*` until revealed.  
- Revealing a mine (`M`) ends the game immediately.  
- You can place or remove flags (`F`) to mark suspected mines.  
- Revealing a `0` automatically expands nearby empty cells.  
- In multiplayer mode, players take turns until one triggers a mine or the board is cleared.

---

## 🛠️ How to Compile

Use **g++** to compile the game:

```bash
g++ Minerush.cpp -o MineRush
