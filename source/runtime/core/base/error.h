#pragma once

#include "runtime/core/base/macro.h"
#include "runtime/core/glad/glad.h"
#include <GLFW/glfw3.h>

inline void CheckError() {
	GLenum errorCode = glGetError();
	std::string error = "";
	if (errorCode != GL_NO_ERROR) {
		switch (errorCode)
		{
		case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:  error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
		default:
			error = "UNKNOWN";
			break;
		}
		LOG_FATAL(error.c_str())
	}
}

#ifdef _DEBUG
#define GL_CALL(func)  func; CheckError();
#else
#define GL_CALL(func)  func;
#endif 