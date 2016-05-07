UTIL_CPP_SRCS= \
	colour_conversion.cpp \
	console.cpp \
	io_util.cpp \
	lua_stack.cpp \
	lua_utf8.cpp \
	lua_util.cpp \
	posix_sleep.cpp \
	unicode_util.cpp \

UTIL_INCLUDE_SRCS= \
	centralised_log.h \
	colour_conversion.h \
	console.h \
	exception.h \
	intrinsics.h \
	io_util.h \
	lua_stack.h \
	lua_utf8.h \
	lua_util.h \
	lua_wrappers_common.h \
	math_util.h \
	portable_io.h \
	sleep.h \
	spline_table.h \
	unicode_util.h \

UTIL_INCLUDE_DIRS= \
	. \

UTIL_LDLIBS= \
	-lrt \

