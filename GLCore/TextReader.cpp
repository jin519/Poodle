#include "TextReader.h"
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

namespace GLCore
{
	string TextReader::read(const string_view& path)
	{
		ifstream fin(path.data());
		assert(fin);

		ostringstream oss;
		oss << fin.rdbuf();

		return oss.str();
	}
}