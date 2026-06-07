# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This repository is a **Touhou-style bullet curtain shooting game** (弹幕射击游戏) course project, built with **EasyX** graphics library in C++. It uses unpacked assets from **Touhou 17: Wily Beast and Weakest Creature** (東方鬼形獣, TH17) — including character sprites, backgrounds, bullet textures, and sound effects — to achieve an authentic look rather than simple geometric shapes.

The TH17 game data (~314MB) provides pre-extracted PNG textures (351 files) and WAV audio (68 files). A Visual Studio 2022 C++ project (`TouhouProject/`) is available as a build scaffold.

## Repository structure

```
TH17 东方鬼形兽/
├── ANM/          # Animation binaries (.anm) + extracted textures (ANM/ subdirectory: player, enemy, bullet, background, UI, face, front)
├── ECL/          # Enemy Control Language scripts (.ecl) — enemy AI/behavior data
├── MSG/          # Message files (.msg) — stage dialogue text (9 files per stage: a–i)
├── MUSIC/        # Sound effects (.wav, 68 files), format table (thbgm.fmt), composer comments (musiccmt.txt)
├── SHT/          # Shot/player definition data (.sht)
├── STD/          # Stage definition data (.std)
├── *.rpy         # Demo replay files
└── *.ver         # Version manifest files
TouhouProject/    # Visual Studio 2022 C++ console app project (v143 toolset, Win32/x64 targets)
```

## Phased development plan

The game is built incrementally across 10 stages. Each stage introduces new concepts and reuses assets from the unpacked TH17 data.

| Stage | Topic | Key assets involved |
|-------|-------|---------------------|
| 1 | Window init + player sprite display + keyboard movement | `player/pl00/pl00.png`, `se_select00.wav` |
| 2 | Double buffering + transparent blitting + frame rate control | Same as stage 1 |
| 3 | Player bullet system (single → spread) | `bullet/bullet1–5.png`, `bullet/beast*.png`, `se_tan00.wav` |
| 4 | Enemy spawning + basic movement | `enemy/enemy.png`, `enemy2.png`, `enemy5.png`, `enemy_b.png`, `enemy_g.png` |
| 5 | Collision detection (circle/rect for player, enemies, bullets) | — |
| 6 | Bullet pattern system (parsing `.ecl`-inspired data) | `ECL/` directory for reference patterns |
| 7 | Stage/scene management + scrolling backgrounds | `background/stage01–07/` |
| 8 | Score, lives, bomb system | `item.png`, `se_powerup.wav`, `se_pldead00.wav` |
| 9 | UI overlay + sound effect playback | `ascii/`, `front/lifebar.png`, `se_*.wav` files |
| 10 | Boss battles + spell card (符卡) system | `eff_*.png`, `face/enemy*/`, `se_cardget.wav` |

## Coding style

- **Teaching mode**: Do NOT write complete, runnable code for the user in one shot. Provide partial code snippets and explain the concepts — let the user write, extend, and debug themselves.
- **Language**: ALL responses must be in Simplified Chinese (简体中文). Technical terms (EasyX, GetAsyncKeyState, etc.) may remain in English. Code comments may be in Chinese or English.
- **Incremental review**: After the user completes each stage, review their code for issues (flickering, collision precision, performance) and suggest improvements.
- **Asset-first thinking**: When introducing a new feature, always point out which unpacked assets can be used before writing code.
- **Explanations before code**: For each new concept (double buffering, transparent blit, collision math, etc.), explain the "why" before showing the "how".

## Visual Studio project

Build targets: Debug/Release for both Win32 and x64.

```powershell
# Build (from TouhouProject directory)
msbuild TouhouProject.sln /p:Configuration=Debug /p:Platform=x64

# Open in Visual Studio
start TouhouProject.sln
```

The project (`TouhouProject/TouhouProject.vcxproj`) is a C++ console application. Source files include `main.cpp`.

## Game metadata

- **Game**: Touhou 17 ~ Wily Beast and Weakest Creature (東方鬼形獣)
- **Developer**: Team Shanghai Alice (ZUN)
- **Version**: 1.00b (from `th17_0100b.ver`)
- **Stages**: 7 stages (st01–st07), each with boss scripts (`*bs.ecl`, `*mbs.ecl`), stage data, and 9 dialogue files (a–i)
- **Sound effects**: 68 WAV files (se_*.wav) — includes shooting, hit, death, power-up, spell card, etc.
- **Replays**: 3 demo replays (demo1–demo3.rpy)
