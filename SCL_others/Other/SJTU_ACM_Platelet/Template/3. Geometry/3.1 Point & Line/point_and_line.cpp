#include <cmath>

using num = long double;
const num eps = 1e-10;

num sqr(num x) {
    return x * x;
}
int sgn(num x) {
    return (x > eps) - (x < -eps);
}
int sgn(num x, num y) {
    return sgn(x - y);
}
struct point {
    num x, y;
    explicit point(num x = 0, num y = 0) : x(x), y(y) {
    }

    num len2() const {
        return sqr(x) + sqr(y);
    }
    num len() const {
        return std::sqrt(len2());
    }
    // counterclockwise rotate
    point turn90() const {
        return point(-y, x);
    }
    point norm() const {
        return point(x / len(), y / len());
    }

    friend bool operator ==(const point &a, const point &b) {
        return !sgn(a.x, b.x) && !sgn(a.y, b.y);
    }
    friend point operator +(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator -(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator *(const point &a, const num &b) {
        return point(a.x * b, a.y * b);
    }
    friend point operator /(const point &a, const num &b) {
        return point(a.x / b, a.y / b);
    }
    // det
    friend num operator *(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    // dot
    friend num operator ^(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
};
struct line {
    point a, b;
    explicit line(point a = point(), point b = point()) : a(a), b(b) {
    }

    point v() const {
        return b - a;
    }
    num len2() const {
        return v().len2();
    }
    num len() const {
        return v().len();
    }
};

// AB det AC
num det(const point &a, const point &b, const point &c) {
    return (b - a) * (c - a);
}
// AB dot AC
num dot(const point &a, const point &b, const point &c) {
    return (b - a) ^ (c - a);
}
num dis2(const point &a, const point &b) {
    return (b - a).len2();
}
num dis(const point &a, const point &b) {
    return (b - a).len();
}

bool onLine(const point &p, const line &l) {
    return sgn((l.a - p) * (l.b - p)) == 0;
}
bool onLeft(const point &p, const line &l) {
    return sgn(l.v() * (p - l.a)) > 0;
}
bool onSeg(const point &p, const line &l) {
    return onLine(p, l) && sgn(l.v() ^ (p - l.a)) >= 0 && sgn(l.v() ^ (p - l.b)) >= 0;
}
bool parallel(const line &a, const line &b) {
    return sgn(a.v() * b.v()) == 0;
}
point intersect(const line &a, const line &b) {
    num s1 = det(a.a, a.b, b.a);
    num s2 = det(a.a, a.b, b.b);
    return (b.a * s2 - b.b * s1) / (s2 - s1);
}
bool coincident(const line &a, const line &b) {
    return onLine(a.a, b) && onLine(a.b, b);
}
point projection(const point &p, const line &l) {
    return l.a + l.v() * ((p - l.a) ^ l.v()) / l.v().len2();
}
num dis(const point &p, const line &l) {
    return std::abs((p - l.a) * l.v()) / l.v().len();
}

int main() {
    return 0;
}
