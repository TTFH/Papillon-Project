#include <map>
#include <string>
#include <stdio.h>
#include <stdexcept>

#include "src/server.h"

#define GREEN  "\x1b[92m"
#define NORMAL "\x1b[0m"

https::response ReturnOK(const https::request& req) {
	printf("> %s\n", req.url.c_str());
	json response_body = {
		{"result", "OK"}
	};
	https::response res(status::OK, response_body);
	res.set_header("Connection", "close");
	return res;
}

https::response ProcessPlayerRequest(const https::request& req) {
	json_r request_json = parse(req.body);
	std::string call = request_json["call"].s();
	printf("> %s | %s\n", req.url.c_str(), call.c_str());

	json response_body = {
		{"result", "OK"}
	};

	if (call == "getRecoveryInfo") {
		response_body = {
			{"result", "OK"},
			{"data", {
				{"recovery_id", 0}
			}}
		};
	} else if (call == "getNews") {
		response_body = {
			{"result", "OK"},
			{"data", {
				{"newsList", json::list{}}
			}}
		};
	} else if (call == "getRankingRegulation") {
		response_body = {
			{"result", "OK"},
			{"data", {
				{"regurations", json::list{
					{
						{"begin_time", ""},
						{"end_time", ""},
						{"ev_id", 1},
						{"ev_name", "TestRegulation"},
						{"info_begin_time", ""},
						{"interim_time", ""},
						{"long_event_name", "TestRegulationLong"},
						{"matching_regulation_id", 1},
						{"max_winner_rank", 1},
						{"mission_name", "MissionName"},
						{"present_items", json::list{
							json::object{
								{"rank", 1}
							}
						}},
						{"present_name_str", "PresentName"},
						{"ranking_rule_id", 1},
						{"ranking_type_name", "RankingTypeName"},
						{"receive_reward_time", 1},
						{"result_disp_time", ""},
						{"status", 0},
						{"target_aircrafts", json::list{}},
						{"target_missions", json::list{}},
						{"url_option", ""},
						{"use_original_aircraft_id", true}
					}
				}}
			}}
		};
	}
	https::response res(status::OK, response_body);
	res.set_header("Connection", "close");
	return res;
}

int main() {
	FILE* file = fopen("arrows.txt", "r");
	if (file != nullptr) {
		printf(GREEN);
		char line[256];
		while (fgets(line, sizeof(line), file))
			printf("%s", line);
		fclose(file);
		printf(NORMAL "\n");
	}

	https::Server app("dev-wind.siliconstudio.co.jp");
	app.post("/Wind/player", ProcessPlayerRequest);
	app.catchall(ReturnOK);
	app.listen(443);
	return 0;
}
