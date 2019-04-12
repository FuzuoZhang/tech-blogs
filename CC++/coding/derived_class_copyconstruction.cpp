#include<cstdio>
#include<cmath>

class Point{
    public:
        Point(int xx, int yy):x(xx), y(yy){}
        Point(const Point &p);
        int getX(){return x;}
        int getY(){return y;}
    private:
        int x, y;
};

Point::Point(const Point &p){
            x = p.x;
            y = p.y;
}

class Line: public Point{
    public:
        Line(int x, int y);
        Line(Line &l);
        void show();
    private:
        double len;
};

Line::Line(int x, int y):Point(x,y){
            len = sqrt(x*x + y*y);
}

Line::Line(Line &l):Point(l){
            int x,y;
            x = l.getX();
            y = l.getY();
            len = sqrt(x*x + y*y);
}

void Line::show(){
    printf("x: %d, y: %d, len: %.2f\n", this->getX(), this->getY(), len);
}

int main(){
    Line l1(3,4);
    Line l2(l1);
    l1.show();
    l2.show();
    return 0;
}