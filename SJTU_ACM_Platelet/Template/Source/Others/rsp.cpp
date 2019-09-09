register char *_sp __asm__("rsp");
int main() {
    const int size = 400 << 20; // 400 MB
    static char *sys, *mine(new char[size] + size - 4096);
    sys = _sp; _sp = mine;
    _main(); // main method
    _sp = sys;
    return 0;
}
