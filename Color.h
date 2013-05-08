class Color {
public:
	float r, g, b;
	Color(int nr, int ng, int nb) {
		r = nr;
		g = ng;
		b = nb;
	}
	Color() {
		r = 0;
		b = 0;
		g = 0;
	}
	float get_r_float() {
        return r;
	}
	float get_g_float() {
        return g;
	}
	float get_b_float() {
        return b;
	}
	int get_r_int() {
        return (int)(r*255);
	}
	int get_g_int() {
        return (int)(g*255);
	}
	int get_b_int() {
        return (int)(b*255);
	}
	bool set_r(float nr) {
        if(nr >= 0.0 && nr <= 1.0) {
            r = nr;
            return true;
        }
        else {
            return false;
        }
	}
	bool set_g(float ng) {
        if(ng >= 0.0 && ng <= 1.0) {
            g = ng;
            return true;
        }
        else {
            return false;
        }
	}
	bool set_b(float nb) {
        if(nb >= 0.0 && nb <= 1.0) {
            b = nb;
            return true;
        }
        else {
            return false;
        }
	}
};
