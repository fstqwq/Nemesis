number f(number x) {
    return /* Take circle area as example */ std::sqrt(1 - x * x) * 2;
}
number simpson(number a, number b) {
    number c = (a + b) / 2;
    return (f(a) + f(b) + 4 * f(c)) * (b - a) / 6;
}
number integral(number a, number b, number eps) {
    number c = (a + b) / 2;
    number mid = simpson(a, b), l = simpson(a, c), r = simpson(c, b);
    if (std::abs(l + r - mid) <= 15 * eps)
        return l + r + (l + r - mid) / 15;
    else
        return integral(a, c, eps / 2) + integral(c, b, eps / 2);
}
