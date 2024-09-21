#include <gflags/gflags.h>
#include "logger.hpp"

// gflags 的使用
DEFINE_bool(is_release, false, "设置运行模式为debug还是release");
DEFINE_string(log_file_path, "", "设置release模式下日志输出文件");
DEFINE_int32(log_level, 1, "设置日志最低输出级别");

int main(int argc, char* argv[]){
	google::ParseCommandLineFlags(&argc, &argv, true);

	logger::initLogger(FLAGS_is_release, FLAGS_log_file_path, FLAGS_log_level);

	LOG_DEBUG("aaa, {}", "bbb");
	LOG_INFO("aaa, {}", "bbb");
	LOG_WARN("aaa, {}", "bbb");
	LOG_ERROR("aaa, {}", "bbb");
	LOG_FATAL("aaa, {}", "bbb");

	return 0;
}
