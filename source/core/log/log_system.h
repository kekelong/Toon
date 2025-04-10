#pragma once

#include <spdlog/spdlog.h>

#include <cstdint>
#include <stdexcept>

namespace Toon
{

	class LogSystem final
	{
	public:
		enum class LogLevel : uint8_t
		{
			debug,
			info,
			warn,
			error,
			fatal
		};

	public:
		LogSystem();
		~LogSystem();
		template<typename... TARGS>
		void log(LogLevel level, const char* format, TARGS&&... args)
		{
			switch (level)
			{
			case LogLevel::debug:
				m_logger->debug(format, std::forward<TARGS>(args)...);
				break;
			case LogLevel::info:
				m_logger->info(format, std::forward<TARGS>(args)...);
				break;
			case LogLevel::warn:
				m_logger->warn(format, std::forward<TARGS>(args)...);
				break;
			case LogLevel::error:
				m_logger->error(format, std::forward<TARGS>(args)...);
				break;
			case LogLevel::fatal:
				m_logger->critical(format, std::forward<TARGS>(args)...);
				fatalCallback(format, std::forward<TARGS>(args)...);
				break;
			default:
				break;
			}
		}

		template<typename... TARGS>
		void fatalCallback(const char* format, TARGS&&... args)
		{
			const std::string format_str = fmt::format(format, std::forward<TARGS>(args)...);
			throw std::runtime_error(format_str);
		}

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};

} // namespace Toon