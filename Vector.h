class Vector {
public:
	double x, y;
	Vector(double nx, double ny) {
		x = nx;
		y = ny;
	}
	Vector() {
		x = 0;
		y = 0;
	}
	double get_x() {
	    return x;
	}
	double get_y() {
        return y;
	}
	void set_x(double nx) {
        x = nx;
	}
	void set_y(double ny) {
        y = ny;
	}
};

class VectorOP {
public:
    static Vector add(Vector a, Vector b) {
        Vector ret;
        //printf("Addiere: %f, %f und %f, %f", a.x, a.y, b.x, b.y);
        ret.x = a.x + b.x;
        ret.y = a.y + b.y;
        //printf(" -> %f, %f\n", ret.x, ret.y);
        return ret;
    }
    static Vector quad(Vector z) {
        Vector ret;
        //printf("Quadriere: %f, %f", z.x, z.y);
        ret.x = (z.x*z.x - z.y*z.y);
        ret.y = (z.x*z.y + z.y*z.x);
        //printf(" -> %f, %f\n", ret.x, ret.y);
        return ret;
    }
    static double absolut(Vector v) {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }
};
