#define DEPTH 50
#define Ne 2
#define Nl 2
#define Nc 3
#define Ns 4
#include <iostream>
#include <cmath>
using namespace std;

template <class X, int N, int K>
class SinSum {
public:
	enum { go = (K + 1 != N) };
	static inline double sum() {
		return 1 - X::var * X::var / (2 * K + 2) / (2 * K + 3) * SinSum<X, N * go, (K + 1) * go>::sum();
	}
};

template <class X>
class SinSum<X, 0, 0> {
public:
	static inline double sum() {
		return 1;
	}
};

template <class X, int N>
class Sine {
public:
	static inline double sin() {
		return X::var * SinSum<X, N, 0>::sum();
	}
};

template<class X, int N, int K>
class cosSum {
public:
	enum { go = (K + 1 != N) };
	static inline double sum() {
		return 1 - X::var*X::var / (K * 2 - 1) / (K * 2)*cosSum<X, N*go, (K + 1)*go>::sum();
	}
};


template <class X>
class cosSum<X, 0, 0> {
public:
	static inline double sum() {
		return 1;
	}
};

template <class X, int N>
class Cos {
public:
	static inline double cos() {
		return cosSum<X, N, 1>::sum();
	}
};



template <class X, int N, int K>
class logSum {
public:
	enum { go = (K + 1 != N) };
	static inline double sum() {
		return X::var / (K + 1)*logSum<X, N*go, (K + 1)*go>::sum();
	}
};

template <class X>
class logSum<X, 0, 0> {
public:
	static inline double sum() {
		return 1;
	}
};

template <class X, int N>
class Logarithm {
public:
	static inline double log() {
		return static_cast<double>(X::var - 1)*logSum<X, N, 1>::sum();
	}
};

template<class X, int N, int K>
class expSum {
public:
	enum { go = (N + 1 != K) };
	static inline const double sum() {
		return 1 + X::var / K * expSum<X, N*go, (K + 1)*go>::sum();
	}

};
template<class X>
class expSum<X, 0, 0> {
public:
	static inline const double sum() {
		return 0;
	}
};

template<class X, int N>
class Exponenta {
public:
	static inline const double exp() {
		return expSum<X, N, 1>::sum();
	}
};

class variable {
public:
	static double var;
};
double variable::var = 0.5;

int main() {
	for (int i = 0; i < Ne; i++){
	variable::var = Exponenta<variable, DEPTH>::exp();
	}
	for (int i = 0; i < Nl; i++) {
		variable::var = Logarithm<variable, DEPTH>::log();
	}
	for (int i = 0; i < Nc; i++) {
		variable::var = Cos<variable, DEPTH>::cos();
	}
	for (int i = 0; i < Ns; i++) {
		variable::var = Sine<variable, DEPTH>::sin();
	}

	double result = sin(sin(sin(sin(cos(cos(cos(log(log(exp(exp(0.5)))))))))));

	cout << "Methaprogram: " << variable::var << endl;
	cout << "Library func: " << result << endl;
	cout << "Error: " << abs(result - variable::var) << endl;
	system("pause");
	return 0;
}
