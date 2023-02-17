#include <avr/io.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdio.h>

#include "speaker.c"

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define WDR() asm volatile("wdr"::)
#define NOP() asm volatile("nop"::)
#define RST() for(;;);

#define DDR    DDRB
#define PORT   PORTB
#define RS_PIN 0
#define RW_PIN 1
#define EN_PIN 2

// SPEAKER
typedef enum {
	A, As, B, C, Cs, D, Ds, Ee, F, Fs, G, Gs, A1, As1, B1, C1, Cs1, D1, Ds1, Ee1, F1, Fs1, G1, Gs1, Z
} Note;

typedef enum {
	W, HQ, H, Q, Ei
} Duration;

typedef struct {
	Note note;
	Duration duration;
} PlayingNote;

void play_note(const PlayingNote* note) {
	int i, k, wait;
	double f;
	k = 0;
	f = 0;
	wait = 0;
	switch (note->note) {
		case (A1):
		wait = 46;
		f = 110;
		break;
		case As1:
		wait = 42;
		f = 116.54;
		break;
		case B1:
		wait = 40;
		f = 123.47;
		break;
		case C1:
		wait = 38;
		f = 130.815;
		break;
		case Cs1:
		wait = 36;
		f = 138.59;
		break;
		case D1:
		wait = 34;
		f = 146.83;
		break;
		case Ds1:
		wait = 32;
		f = 155.565;
		break;
		case Ee1:
		wait = 30;
		f = 164.815;
		break;
		case F1:
		wait = 29;
		f = 174.615;
		break;
		case Fs1:
		wait = 28;
		f = 184.995;
		break;
		case G1:
		wait = 26;
		f = 196;
		break;
		case Gs1:
		wait = 24;
		f = 207.65;
		break;
		case A:
		wait = 23;
		f = 220.00;
		break;
		case As:
		wait = 21;
		f = 233.08;
		break;
		case B:
		wait = 20;
		f = 246.94;
		break;
		case C:
		wait = 19;
		f = 261.63;
		break;
		case Cs:
		wait = 18;
		f = 277.18;
		break;
		case D:
		wait = 17;
		f = 293.66;
		break;
		case Ds:
		wait = 16;
		f = 311.13;
		break;
		case Ee:
		wait = 15;
		f = 329.63;
		break;
		case F:
		wait = 14;
		f = 349.23;
		break;
		case Fs:
		wait = 14;
		f = 369.99;
		break;
		case G:
		wait = 13;
		f = 392.00;
		break;
		case Gs:
		wait = 12;
		f = 415.30;
		break;
		case Z:
		wait = 30;
		f = 166.66;
		break;
	}
	
	switch (note->duration) {
		case W:
		k = f;
		break;
		case HQ:
		k = 0.75 * f;
		break;
		case H:
		k = 0.5 * f;
		break;
		case Q:
		k = 0.25 * f;
		break;
		case Ei:
		k = 0.125 * f;
		break;
	}
	
	if (wait == 30) {
		for (i = 0; i < k; i++) {
			avr_wait2(wait*2);
		}
	}
	else {
		for (i = 0; i < k; i++) {
			SET_BIT(PORTB, 3);
			avr_wait2(wait);
			CLR_BIT(PORTB, 3);
			avr_wait2(wait);
		}
	}

}

void play_song(const PlayingNote song[], int length) {
	int i, k;
	for (i = 0; i < length; i++) {
		k = get_key();
		if (k == 2) {
			break;
		}
		play_note(&song[i]);
	}
}
