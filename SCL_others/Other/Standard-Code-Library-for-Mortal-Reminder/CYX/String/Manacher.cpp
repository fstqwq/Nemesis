void Manacher(std::string s,int p[]) {
    std::string t = "$#";
    for (int i = 0; i < s.size(); i++) {
        t += s[i];
        t += "#";
    }
    int mx = 0, id = 0;
    for (int i = 1; i < t.size(); i++) {
        p[i] = mx > i ? std::min(p[2 * id - i], mx - i) : 1;
        while (i - p[i] >= 0 && i + p[i] < t.length() && t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
    }
}
