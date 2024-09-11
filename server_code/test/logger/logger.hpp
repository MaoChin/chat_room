#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>

// 对spdlog做二次封装：
// 1. 对外通过一个初始化的接口
// 2. 对打印内容进行封装，加上文件名和行号

namespace logger{
	// 全局的logger
	std::shared_ptr<spdlog::logger> g_logger;
	void initLogger(const bool is_release, const std::string& path, const int log_level){
		// 全局设置
		spdlog::flush_on((spdlog::level::level_enum)log_level);

		if(is_release){
			// release 模式，把日志打印到问价
			g_logger = spdlog::basic_logger_mt<spdlog::async_factory>("release_logger", path);
		}
		else{
			// debug 模式，就把日志打印到stdout
			g_logger = spdlog::stdout_color_mt<spdlog::async_factory>("debug_logger");
		}

		// 针对具体的logger设置
		g_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%t] [%-8l] %v");
		g_logger->set_level((spdlog::level::level_enum)log_level);
	}
}  // namespace logger


// 输入：因为spdlog的输出没有文件名和行号，所以再封装一下，加上打印文件名和行号
// logger的输出占位统一都是 {}
// __VA_ARGS__ 标识取到 ... 的可变参数，加上 ## 是为了防止没有可变参数时 __LINE__, 后面逗号的影响
#define LOG_DEBUG(format, ...) logger::g_logger->debug(std::string("[{}:{}] ") + format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(format, ...) logger::g_logger->info(std::string("[{}:{}] ") + format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(format, ...) logger::g_logger->warn(std::string("[{}:{}] ") + format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) logger::g_logger->error(std::string("[{}:{}] ") + format, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) logger::g_logger->critical(std::string("[{}:{}] ") + format, __FILE__, __LINE__, ##__VA_ARGS__)