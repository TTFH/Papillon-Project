#include "server.h"

namespace https {
	Server::Server(const char* name) {
		app.loglevel(crow::LogLevel::Warning);
		app.server_name(name);
	}
	void Server::catchall(std::function<response(const request&)> callback) {
		app.catchall_route()(callback);
	}
	void Server::post(const std::string& path, std::function<response(const request&)> callback) {
		app.route_dynamic(path).methods(crow::HTTPMethod::Post)(callback);
	}
	void Server::listen(int port) {
		printf("Server running on %s:%d\n", app.bindaddr().c_str(), port);
		app.port(port).multithreaded().run();
	}
}

json_r parse(const std::string& s) {
	return crow::json::load(s);
}
