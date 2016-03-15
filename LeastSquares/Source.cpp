#include "Twin.h"

std::vector<double> gvec(Twin&);
void dvec(Twin&, const std::vector<double>&);
void regress(Twin&, const std::vector<double>& x, const std::vector<double>& y);

int main() {

	Twin t("Least Squares");
	std::vector<double> x;
	std::vector<double> y;

	do {

		t.println("Enter the first element of the vector x.");
		t.println("Example: 1.2");
		t.display();

		x = gvec(t);

		t.println("Enter the first element of the vector y.");
		t.println("Example: 1.2");
		t.display();

		y = gvec(t);

		if (x.size() != y.size()) {
			t.println("Vectors must have same dimension.");
			t.println();
		}

	} while (x.size() != y.size());

	regress(t, x, y);

	return EXIT_SUCCESS;

}

void regress(Twin& t, const std::vector<double>& x, const std::vector<double>& y) {

	double sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0, sumy2 = 0, st = 0, sr = 0;
	int n = x.size();

	for (int i = 0; i < n; i++) {

		sumx += x[i];
		sumy += y[i];
		sumxy += x[i] * y[i];
		sumx2 += x[i] * x[i];
		sumy2 += y[i] * y[i];

	}

	double xm = sumx / n;
	double ym = sumy / n;
	double a1 = (n*sumxy - sumx*sumy) / (n*sumx2 - sumx*sumx);
	double r = (n*sumxy - sumx*sumy) / (pow(n*sumx2 - sumx*sumx, .5) * pow(n*sumy2 - sumy*sumy, .5));
	double a0 = ym - a1*xm;

	for (int i = 0; i < n; i++) {

		st += pow(y[i] - ym, 2);
		sr += pow(y[i] - a1*x[i] - a0, 2);

	}

	double syx = pow(sr / (n - 2), .5);
	double r2 = (st - sr) / st;

	t.println("n = ");
	t.print(n);
	t.println("a1 = ");
	t.print(a1);
	t.println("a0 = ");
	t.print(a0);
	t.println("syx = ");
	t.print(syx);
	t.println("r2 = ");
	t.print(r2);
	t.println("r = ");
	t.print(r);
	t.println();
	t.println("Press enter to continue.");
	t.display();

	std::cin.ignore(1000, '\n');
	std::cin.clear();

	std::vector<double> yf;

	for (auto&& i : x) yf.push_back(a0 + a1*i);

	t.println("Vector x:");
	t.println();
	dvec(t, x);
	t.println();
	t.println("Press enter to continue.");
	t.display();
	std::cin.ignore(1000, '\n');
	std::cin.clear();

	t.println("Vector y:");
	t.println();
	dvec(t, y);
	t.println();
	t.println("Press enter to continue.");
	t.display();
	std::cin.ignore(1000, '\n');
	std::cin.clear();

	t.println("Vector yf:");
	t.println();
	dvec(t, yf);
	t.println();
	t.println("Press enter to continue.");
	t.display();
	std::cin.ignore(1000, '\n');
	std::cin.clear();

}

std::vector<double> gvec(Twin& t) {

	std::vector<double> b;
	double in;
	std::string input;

	std::getline(std::cin, input);
	std::stringstream iss(input);
	iss >> in;
	b.push_back(in);

	while (true) {

		t.println("Vector:");
		t.println();
		dvec(t, b);
		t.println("Enter the next element.");
		t.println("Enter 'x' to save and continue.");
		t.display();

		std::getline(std::cin, input);
		std::stringstream iss(input);
		iss >> in;

		if (input == "x" || input == "X") return b;
		else b.push_back(in);

	}
}

void dvec(Twin& t, const std::vector<double>& vec) {

	for (auto&& i : vec) {
		t.println("[ ");
		t.print(i);
		t.print(" ]");
	}

	t.println();
}