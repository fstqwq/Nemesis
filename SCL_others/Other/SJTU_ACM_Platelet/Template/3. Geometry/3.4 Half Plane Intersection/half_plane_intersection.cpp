#include "point_and_line.cpp"
#include <algorithm>
#include <deque>
#include <vector>

bool quad(const point &p) {
    return sgn(p.y) > 0 || (sgn(p.y == 0) && sgn(p.x >= 0));
}
line pushLine(const line &l) {
    point delta = l.v().norm().turn90() * eps;
    return line(l.a - delta, l.b - delta);
}
bool sameDirection(const line &a, const line &b) {
    return parallel(a, b) && sgn(a.v() ^ b.v()) > 0;
}
bool operator <(const point &a, const point &b) {
    if (quad(a) != quad(b))
        return quad(a) < quad(b);
    else
        return sgn(a * b) > 0;
}
bool operator <(const line &a, const line &b) {
    if (sameDirection(a, b))
        return onLeft(a.a, b);
    else
        return a.v() < b.v();
}
bool check(const line &u, const line &v, const line &w) {
    return onLeft(intersect(u, v), w);
}

std::vector<point> half_plane_intersection(std::vector<line> l) {
    for (int i = 0; i < (int) l.size(); i++)
        l[i] = pushLine(l[i]);
    std::sort(l.begin(), l.end());
    std::deque<line> q;
    for (int i = 0; i < (int) l.size(); i++) {
        if (i && sameDirection(l[i], l[i - 1]))
            continue;
        while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i]))
            q.pop_back();
        while (q.size() > 1 && !check(q[1], q[0], l[i]))
            q.pop_front();
        q.push_back(l[i]);
    }
    while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0]))
        q.pop_back();
    while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1]))
        q.pop_front();
    std::vector<point> ans;
    for (int i = 0; i < (int) q.size(); i++)
        ans.push_back(intersect(q[i], q[(i + 1) % q.size()]));
    return ans;
}
