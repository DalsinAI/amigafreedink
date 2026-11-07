/* A Shell gives 4 KB of stack; libnix's startup sets this much up instead.
 * The AmiCradle Team. GPL 3 or later, like FreeDink. */
unsigned long __stack = 1024 * 1024;
static const char version[] __attribute__((used)) = "$VER: FreeDink 109.6 Amiga (06.11.2026)";
