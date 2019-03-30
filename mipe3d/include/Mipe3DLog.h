#pragma once

#include <cstdio>
#include <string>

// NOTE: for verbose logging (showing file, line number)
// #define MIPE3D_LOG_VERBOSE

// ---- internal helpers, not meant to be used by the client code ----

namespace mipe3d
{
	inline const char* _internal_to_c_str(const char* value)
	{
		return value;
	}
	inline const char* _internal_to_c_str(const std::string& value) 
	{
		return value.c_str();
	}
}

#ifdef MIPE3D_LOG_VERBOSE
#define _MIPE3D_LOG_INTERNAL(outputStream, message)	\
	fprintf(										\
		outputStream,								\
		"%s [%s, line %d]\n",						\
		mipe3d::_internal_to_c_str(message),		\
		__FILE__,									\
		__LINE__);
#else
#define _MIPE3D_LOG_INTERNAL(outputStream, message)	\
	fprintf(										\
		outputStream,								\
		"%s\n",										\
		mipe3d::_internal_to_c_str(message))
#endif

// ---- actual logging macros for client ----

#define MIPE3D_LOG(message)							\
	_MIPE3D_LOG_INTERNAL(stdout, message)	

#define MIPE3D_LOG_WARNING(message)					\
	_MIPE3D_LOG_INTERNAL(							\
		stdout,										\
		std::string("WARNING: ").append(			\
			mipe3d::_internal_to_c_str(message)		\
		)											\
	)

#define MIPE3D_LOG_ERROR(message)					\
	_MIPE3D_LOG_INTERNAL(							\
		stderr,										\
		std::string("ERROR: ").append(				\
			mipe3d::_internal_to_c_str(message)		\
		)											\
	)