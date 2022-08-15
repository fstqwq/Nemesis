int day_in_week(int year, int month, int day) {
    if (month == 1 || month == 2)
        month += 12, year--;
    int c = year / 100, y = year % 100, m = month, d = day;
    int ret = (y + y / 4 + c / 4 + 5 * c + 13 * (m + 1) / 5 + d + 6) % 7;
    return ret >= 0 ? ret : ret + 7;
}
