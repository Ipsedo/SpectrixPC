//
// Created by samuel on 02/02/18.
//

#include <vector>

#include "res.h"
#include "string_utils.h"

using namespace std;

#define APP_NAME "SpectrixPC"

string getResFolder() {
	using namespace std;
	string this_file = __FILE__;
	vector<string> splittedPath = split(this_file, '/');

	while (splittedPath.back() != APP_NAME) {
		splittedPath.pop_back();
	}

	string res_path;
	for (auto &elt : splittedPath) {
		res_path += "/" + elt;
	}

	res_path += "/res";

	return res_path;
}

std::string getShaderFolder() {
	using namespace std;
	string this_file = __FILE__;
	vector<string> splittedPath = split(this_file, '/');

	while (splittedPath.back() != APP_NAME) {
		splittedPath.pop_back();
	}

	string res_path;
	for (auto &elt : splittedPath) {
		res_path += "/" + elt;
	}

	res_path += "/shaders";

	return res_path;
}
