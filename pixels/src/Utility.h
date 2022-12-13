#ifndef UTILITY__H
#define UTILITY__H

template <typename T>
T lerp(float alpha,T a, T b){
	return a*(1-alpha)+b*(alpha);
}

#endif
