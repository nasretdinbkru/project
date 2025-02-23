#include "AppController.h"
AppController::AppController(std::shared_ptr<oatpp::web::mime::ContentMappers>& apiContentMappers)
	: oatpp::web::server::api::ApiController(apiContentMappers) {}
