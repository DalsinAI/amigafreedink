/* SDL_RWFromFP for GNU FreeDink on AmigaOS (-Wl,--wrap=SDL_RWFromFP).
 * FreeDink opens its pictures, sounds, fonts and packed sprite files with
 * the program's own stdio and hands the FILE to SDL; OpenGPU's SDL2.module
 * cannot use libnix's FILE, and the first picture (the splash) took the
 * machine down. Here the RWops' calls are the program's own stdio.
 * After the Team's amiga_rwops.c for SDL 1.2 (Holotz's Castle, Abe).
 * The AmiCradle Team. GPL 3 or later, like FreeDink. */
#include <stdio.h>
#include <SDL.h>

static Sint64 SDLCALL rw_size(SDL_RWops *rw)
{
	FILE *f = (FILE *)rw->hidden.unknown.data1;
	long here = ftell(f), end;
	if (here < 0 || fseek(f, 0, SEEK_END) != 0)
		return -1;
	end = ftell(f);
	fseek(f, here, SEEK_SET);
	return end;
}

static Sint64 SDLCALL rw_seek(SDL_RWops *rw, Sint64 offset, int whence)
{
	FILE *f = (FILE *)rw->hidden.unknown.data1;
	int w = whence == RW_SEEK_CUR ? SEEK_CUR : whence == RW_SEEK_END ? SEEK_END : SEEK_SET;
	if (fseek(f, (long)offset, w) != 0)
		return SDL_SetError("fseek failed");
	return ftell(f);
}

static size_t SDLCALL rw_read(SDL_RWops *rw, void *ptr, size_t size, size_t maxnum)
{
	if (size == 0 || maxnum == 0)
		return 0;
	return fread(ptr, size, maxnum, (FILE *)rw->hidden.unknown.data1);
}

static size_t SDLCALL rw_write(SDL_RWops *rw, const void *ptr, size_t size, size_t num)
{
	if (size == 0 || num == 0)
		return 0;
	return fwrite(ptr, size, num, (FILE *)rw->hidden.unknown.data1);
}

static int SDLCALL rw_close(SDL_RWops *rw)
{
	int r = 0;
	if (rw) {
		if (rw->hidden.unknown.data2)	/* autoclose */
			r = fclose((FILE *)rw->hidden.unknown.data1) == 0 ? 0 : -1;
		SDL_FreeRW(rw);
	}
	return r;
}

SDL_RWops *__wrap_SDL_RWFromFP(FILE *fp, SDL_bool autoclose)
{
	SDL_RWops *rw;
	if (!fp) {
		SDL_SetError("SDL_RWFromFP: no file");
		return NULL;
	}
	rw = SDL_AllocRW();
	if (!rw)
		return NULL;
	rw->size = rw_size;
	rw->seek = rw_seek;
	rw->read = rw_read;
	rw->write = rw_write;
	rw->close = rw_close;
	rw->type = SDL_RWOPS_UNKNOWN;
	rw->hidden.unknown.data1 = fp;
	rw->hidden.unknown.data2 = (void *)(long)autoclose;
	return rw;
}
