// CLOCK
typedef struct {
	char *location;
	int hour;
	int minute;
	int second;
} Time;


void init_time(Time *currentTime, int hour, int minute, int second, char *location) {
	currentTime->location = location;
	currentTime->hour = hour;
	currentTime->minute = minute;
	currentTime->second = second;
}

void check_time(Time *currentTime) {
	if (currentTime->second >= 60) {
		currentTime->second = 0;
		++currentTime->minute;
	}
	if (currentTime->second <= -1) {
		currentTime->second = 59;
		--currentTime->minute;
	}
	if (currentTime->minute >= 60) {
		currentTime->minute = 0;
		++currentTime->hour;
	}
	if (currentTime->minute <= -1) {
		currentTime->minute = 59;
		--currentTime->hour;
	}
	if (currentTime->hour >= 24) {
		currentTime->hour = 0;
	}
	if (currentTime->hour < 0) {
		currentTime->hour = 23;
	}
}

void advance_time(Time *currentTime) {
	++currentTime->second;
	check_time(currentTime);
}

void check_timer(Time *currentTime) {
	if (currentTime->second >= 60) {
		currentTime->second = 0;
		++currentTime->minute;
	}
	if (currentTime->minute >= 60) {
		currentTime->minute = 0;
		++currentTime->hour;
	}
	if (currentTime->second < 0) {
		currentTime->second = 59;
		--currentTime->minute;
	}
	if (currentTime->minute < 0) {
		currentTime->minute = 59;
		--currentTime->hour;
	}
	if (currentTime->hour < 0) {
		currentTime->hour = 0;
	}
}

void advance_timer(Time *currentTime) {
	--currentTime->second;
	check_timer(currentTime);
}

// Print clock
void print_clock(const Time *currentTime) {
	char buf[30];
	// Print location on top row.
	lcd_pos(0, 0);
	sprintf(buf, "%s", currentTime->location);
	lcd_puts2(buf);
	// Print time on bottom row.
	lcd_pos(1, 0);
	sprintf(buf, "%02d:%02d:%02d", currentTime->hour, currentTime->minute, currentTime->second);
	lcd_puts2(buf);
}

// Print clock with currently being configured section empty.
void print_empty(int cursor, const Time *currentTime) {
	char buf[30];
	
	switch (cursor) {
		case 1:
			lcd_pos(0, 0);
			sprintf(buf, "%s", currentTime->location);
			lcd_puts2(buf);
			lcd_pos(1, 0);
			sprintf(buf, "%s:%02d:%02d", "__", currentTime->minute, currentTime->second);
			lcd_puts2(buf);
			break;
		case 2:
			lcd_pos(0, 0);
			sprintf(buf, "%s", currentTime->location);
			lcd_puts2(buf);
			lcd_pos(1, 0);
			sprintf(buf, "%02d:%s:%02d", currentTime->hour, "__", currentTime->second);
			lcd_puts2(buf);
			break;
		case 3:
			lcd_pos(0, 0);
			sprintf(buf, "%s", currentTime->location);
			lcd_puts2(buf);
			lcd_pos(1, 0);
			sprintf(buf, "%02d:%02d:%s", currentTime->hour, currentTime->minute, "__");
			lcd_puts2(buf);
			break;
		}
}

void increase(int cursor, Time *currentTime) {
	switch (cursor) {
		case 1:
			++currentTime->hour;
			break;
		case 2:
			++currentTime->minute;
			break;
		case 3:
			++currentTime->second;
			break;
	}
	check_time(currentTime);
}

void decrease(int cursor, Time *currentTime) {
	switch (cursor) {
		case 1:
		--currentTime->hour;
		break;
		case 2:
		--currentTime->minute;
		break;
		case 3:
		--currentTime->second;
		break;
	}
	check_time(currentTime);
}