class Rect {
    int x, y;
    unsigned int wd, hd;
    public:
    Rect(int x_a, int y_a, unsigned int wd_a, unsigned int hd_a) {
        x = x_a;
        y = y_a;
        wd = wd_a;
        hd = hd_a;
    }
    Rect() {
        x = 0;
        y = 0;
        wd = 1;
        hd = 1;
    }
    Rect(unsigned int a) {
        x = 0;
        y = 0;
        wd = a;
        hd = a;
    }
    void print_corner() {
        printf("(%d,%d)\n", x, y);
    }
    void print_sz() {
        printf("wd=%u hd=%u\n", wd, hd);
    }
    int area() {
        return wd * hd;
    }
    int perimeter() {
        return 2 * hd + 2 * wd;
    }
    bool intersect(Rect r) {
        return (x >= r.x - int(wd))&&(x <= r.x + int(r.wd))&&(y <= r.y + int(r.hd))&&(y >= r.y - int(hd));
    }
};
