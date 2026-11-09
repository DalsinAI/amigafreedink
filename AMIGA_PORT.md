GNU FreeDink 109.6 for AmigaOS 3.x
==================================

GNU FreeDink, the free engine for Dink Smallwood (RTsoft, 1997), the
light-hearted top-down role-playing game: Dink the pig farmer leaves his
mother's house in Stonebrook to wander the land, fight, talk, cast magic
and take on the Cast. With freedink-data, the original game whose
non-free sounds and music were replaced with free ones. For AmigaOS 3.x on
a 68040 or 68060 with an FPU and an RTG screen, on OpenGPU's SDL 2.

Base: freedink_109.6.orig.tar.gz from Debian (sha256
5e0b35ac8f46d7bb87e656efd5f9c7c2ac1a6c519a908fc5b581e52657981002), with
Debian's patches (109.6-8) as the second commit. The game is Debian's
freedink-data_1.08.20190120.orig.tar.gz (sha256
715f44773b05b73a9ec9b62b0e152f3f281be1a1512fbaaa386176da94cffb9d), its
dink/ copied into the drawer by the Makefile's dist. SDL2_gfx 1.0.4 is
built in (amiga/SDL2_gfx, zlib licence). Branch team2/freedink-amiga.

Status: plays in the lab (Instance-45 on GFOpenUp 0.8.19, 6 November
2026): the splash, the title, Start, Dink's house (his mother, Dink walked
about, "This table must be bolted to the ground."), the status bar,
Escape and its menu, and Quit back to the Shell. Screenshots from that
run are in amiga/screenshots (freedink-title.png, freedink-house.png,
freedink-menu.png). No background music yet: the OpenGPU kit's
SDL2_mixer has no Ogg Vorbis, so the music is skipped; the sound effects
play (the lab is muted, so they were not heard there).


What you need
-------------

- A 68040 or 68060 with an FPU, AmigaOS 3.x, an RTG card (or the
  AmigaChrome lab).
- GFOpenUp 0.8.18 or later: LIBS:OpenGPU/SDL2.module, SDL2_image.module,
  SDL2_mixer.module and SDL2_ttf.module.
- About 90 MB on disk for the game.


How to play
-----------

Open the FreeDink icon, or run FreeDink from a Shell. It opens a 640x480
window (Alt+Return switches to the full screen). Click Start, or Continue
for a saved game. The cursor keys walk, Control attacks, Space talks and
looks, Shift casts magic, Return is the inventory, M the map and Escape the
menu (save, load, quit). ReadMe-upstream in the drawer is upstream's
README; doc/ has the game data's README, every replaced sound's and
tune's author and licence (README-REPLACEMENTS.txt and licenses/) and the
font's. The game is in the drawer's dink/; saved games and settings are
kept in user/.dink.


Building
--------

    make -f amiga/Makefile.amigaos -j2 dist

with GFOpenAmigaGCC 16.2.0-open4, the OpenNDK headers, the OpenGPU kit and
Debian's freedink-data unpacked (DINKDATA, see the Makefile's head). The
drawer is dist/FreeDink (and dist/FreeDink.info).


What was changed
----------------

- src/gfx.cpp, src/app.cpp: the software display only (the OpenGL 2
  renderer and glm are left out), in a window by default.
- src/freedink_main.cpp: main() first moves into the drawer and deals at
  exit with the screens OpenGPU's SDL2.module can leave after a full screen
  game (amiga/amiga_start.c and amiga/amiga_screens.c, from the Legend of
  Edgar port). $HOME is the drawer's user/ (amiga/amiga_env.c).
- amiga/amiga_rwops.c (-Wl,--wrap=SDL_RWFromFP): FreeDink hands its own
  open FILEs to SDL for its pictures, sounds and font; SDL2.module cannot
  use libnix's FILE, and the machine went down at the splash. The RWops
  now read through the program's own stdio.
- gnulib's getopt (gnulib/lib, amiga/gnulib/getopt.h): libnix's
  getopt_long_only never returned, so the game hung before its window.
- src/gfx_fonts.cpp: SDL2_ttf.module cannot read the Windows .fon system
  font; the system text uses FreeDink's Liberation Sans, as the dialog
  text does.
- src/io_util.cpp: file names only have their backslashes turned round
  (AmigaDOS names are not case-sensitive), as for upstream's web build.
- amiga/Makefile.amigaos builds src/Makefile.am's freedink with
  amiga/config.h for configure's (no gettext, no fontconfig); gnulib's
  xmalloc and hash; SDL2_gfx's rotozoom, primitives and framerate.
- amiga/stack.c: 1 MB of stack.


Licences
--------

GNU FreeDink: GPL 3 or later (COPYING.txt). The game (freedink-data): the
original Dink Smallwood data under RTsoft's zlib-style licence, its
replacement sounds and music under GPL, CC BY, CC BY-SA, Art Libre and
public domain, file by file in doc/README-REPLACEMENTS.txt and
doc/licenses (freedink-data's own COPYING is GPL 3). Liberation Sans: GPL with
the font exception (doc/README-fonts.txt).
SDL2_gfx: zlib licence (doc/COPYING-SDL2_gfx.txt). The Amiga files
(amiga/): the AmiCradle Team, GPL 3 or later; the icons are our
own GlowIcons (amiga/icons/art/freedink.svg).
