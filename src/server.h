#ifndef _SERVER_H
#define _SERVER_H

#define CROW_ENABLE_SSL
#define CROW_JSON_USE_MAP
#include "../lib/crow_all.h"

namespace https {
	typedef crow::request request;
	typedef crow::response response;

	class Server {
	private:
		crow::SimpleApp app;
	public:
		Server(const char* name);
		void catchall(std::function<response(const request&)> callback);
		void post(const std::string& path, std::function<response(const request&)> callback);
		void listen(int port);
	};
};

namespace status {
	const int OK = 200;
	const int BAD_REQUEST = 400;
	const int NOT_FOUND = 404;
};

using json = crow::json::wvalue;
using json_r = crow::json::rvalue;
json_r parse(const std::string& s);

#endif
