# letdown

An Undertale-inspired indie RPG built from scratch for the Sony PSP.

The entire game targets the original PSP-1000 hardware — 333 MHz MIPS, 32 MB RAM, 480x272 screen. No emulator safety nets. If it doesn't run on real silicon, it doesn't ship.

## Tech Stack

| Layer | Choice |
|---|---|
| **Language** | C++17 |
| **SDK** | [PSPSDK](https://github.com/pspdev/pspsdk) (unofficial open-source PSP toolchain) |
| **Graphics / Audio** | [OSLib](https://github.com/pspdev/oslib) (oldschool PSP multimedia library) |
| **Build** | CMake, cross-compiled via `psp-gcc` |
| **Target** | EBOOT.PBP — runs on real PSP hardware or PPSSPP |

## Hardware Constraints

This is the box everything has to fit inside:

- **CPU** — MIPS R4000 @ 333 MHz (often underclocked to 222 MHz to save battery)
- **RAM** — 32 MB main + 4 MB VRAM
- **GPU** — Sony custom, hardware T&L, ~33M poly/sec
- **Screen** — 480x272 TFT LCD
- **Storage** — Memory Stick Pro Duo (up to 32 GB)
- **Audio** — Hardware stereo

## Project Structure

```
psp-game/
├── CMakeLists.txt          # builds ELF, generates EBOOT.PBP
├── src/
│   ├── main.cpp            # PSP boot, OSLib init, enters game loop
│   ├── engine/             # reusable subsystems
│   │   ├── memory/         # pool & stack allocators (no malloc at runtime)
│   │   ├── assets/         # image & sound cache
│   │   ├── input/          # d-pad, buttons, analog stick
│   │   ├── graphics/       # renderer, sprites, animation
│   │   ├── cutscene/       # scripted sequences
│   │   └── core/           # game loop, scene stack
│   └── game/               # game-specific logic
│       ├── dialogue/        # branching dialogue system
│       ├── world/           # tile maps, player, NPCs
│       └── scenes/          # title screen, overworld, etc.
└── assets/
    ├── sprites/
    ├── audio/
    └── dialogue/
```

Everything is stubbed — compiles clean, zero real logic. Every function body you'll fill in yourself.

## Building

Requires the [pspdev](https://github.com/pspdev/pspdev) toolchain installed and on your `PATH`.

```bash
cd psp-game
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$PSPDEV/psp/share/pspdev.cmake ..
make
```

This produces `EBOOT.PBP` — drop it into `ms0:/PSP/GAME/letdown/` on your Memory Stick, or load it in PPSSPP.

## Devlog

I'm writing about the process of building a full game inside these constraints:
**[devlog](https://letdown.dev/log)** *(coming soon)*

Turns out making something good on a 333 MHz processor with 32 megs of RAM teaches you more about game dev than any modern engine ever will.

## License

TBD
