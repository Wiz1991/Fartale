template<typename T>
std::string toString(T value)
{
	std::ostringstream ss;
	ss << value;
	return ss.str();
}