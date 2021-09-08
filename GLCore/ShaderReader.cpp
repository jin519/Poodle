#include "ShaderReader.h"
#include <fstream>
#include <sstream>
#include "TextReader.h"
#include <stack>
#include <cassert>
#include <regex>

using namespace std;
using namespace filesystem;
using namespace std;

namespace GLCore
{
	string ShaderReader::read(const string_view& path)
	{
		return __preprocess(path, false);
	}

	string ShaderReader::__preprocess(const path &srcPath, const bool recursive)
	{
		static const regex
			includeDirectiveRegex	{ R"_(^[ \t]*#include[ \t]+"(.*)"[ \t]*$)_" },
			extensionDirectiveRegex	{ R"_(^[ \t]*#extension[ \t]+\w+[ \t]*:[ \t]*\w*[ \t]*$)_" },
			versionDirectiveRegex	{ R"_(^[ \t]*#version[ \t]+\d+[ \t]+\w*[ \t]*$)_" };

		const path sourceParentPath{ srcPath.parent_path() };
		string retVal{ TextReader::read(srcPath.string()) };

		smatch matched;
		
		// #include directive processing

		while (regex_search(retVal, matched, includeDirectiveRegex))
		{
			const path includedPath{ matched.str(1ULL) };

			if (!includedPath.has_filename())
				throw runtime_error{ "Invalid #include syntax" };

			retVal.replace(
				matched.position(), matched.length(),
				__preprocess(sourceParentPath / includedPath, true));
		}

		if (recursive)
			return retVal;

		// #extension directive processing

		vector<string> extensionStrList;
		while (regex_search(retVal, matched, extensionDirectiveRegex))
		{
			extensionStrList.emplace_back(move(matched.str()));
			retVal.erase(matched.position(), matched.length());
		}

		if (!extensionStrList.empty())
		{
			size_t insertionPos {};
			if (regex_search(retVal, matched, versionDirectiveRegex))
				insertionPos = (matched.position() + matched.length());

			for (const string &extensionStr : extensionStrList)
				retVal.insert(insertionPos, "\n" + extensionStr);
		}

		return retVal;
	}
}