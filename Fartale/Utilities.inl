template<typename T>
std::string toString(T value)
{
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

template<class T>
T operator~ (T a) { return (T)~(int)a; }
template<class T>
T operator| (T a, T b) { return (T)((int)a | (int)b); }
template<class T>
T operator& (T a, T b) { return (T)((int)a & (int)b); }
template<class T>
T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
template<class T>
T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
template<class T>
T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
template<class T>
T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }