#ifndef UU_SPDR_H
#define UU_SPDR_H

/**
 * A tracing library
 */

#include "spdr-private.h"

#include <stddef.h> /* for size_t */

/**
 * Context for the library
 */
struct spdr_context_context;

/**
 * Buffer capacity
 */
struct spdr_capacity
{
	size_t count;
	size_t capacity;
};

/**
 * Reporting type.
 */
enum spdr_report_type
{
	SPDR_PLAIN_REPORT,
	SPDR_CHROME_REPORT,
};

/**
 * Initializes the library
 *
 * spdr will use the provided memory buffer for its memory
 * allocations.
 *
 * the size of the memory buffer will limit the number of events that
 * can be recorded at a time.
 *
 * @return 0 on success
 */
int spdr_init(struct spdr_context **context, void* buffer, size_t buffer_size);

/**
 * Shutdowns the library
 */
void spdr_deinit(struct spdr_context** context);

/**
 * Activates the recording of traces (off by default)
 */
void spdr_enable_trace(struct spdr_context *context, int traceon);

/**
 * Clears the log buffer to start anew
 */
void spdr_reset(struct spdr_context* context);

/**
 * Returns the current event count and total available capacity
 */
struct spdr_capacity spdr_capacity(struct spdr_context* context);

/**
 * Provide your own clock function.
 *
 * It must return a strictly monotonic series of numbers
 * representing elapsed microseconds.
 *
 * It must be thread-safe: it will be called concurrently
 * from multiple threads
 */
void spdr_set_clock_microseconds_fn(struct spdr_context *context,
		     unsigned long long (*clock_microseconds_fn)(void* user_data),
		     void *user_data);


/**
 * Provide your logging function if you want a trace stream to be produced.
 */
void spdr_set_log_fn(struct spdr_context *context,
		     void (*log_fn) (const char* line, void* user_data),
		     void *user_data);

/**
 * Report the traces which have been recorded so far, using the
 * provided log function.
 */
void spdr_report(struct spdr_context *context,
		 enum spdr_report_type report_type,
		 void (*print_fn) (const char* string, void* user_data),
		 void* user_data);


/**
 * Builds arguments of various types
 */
#define SPDR_INT(key, value)   UU_SPDR_INT(key, value)
#define SPDR_FLOAT(key, value) UU_SPDR_FLOAT(key, value)
#define SPDR_STR(key, value)   UU_SPDR_STR(key, value)



/* __ Instant events __ */

/**
 * An instant event
 */
#define SPDR_EVENT(spdr, cat, name)			\
	UU_SPDR_TRACE(spdr, cat, name, SPDR_EVENT)

/**
 * An instant event with one parameter
 */
#define SPDR_EVENT1(spdr, cat, name, arg0)			\
	UU_SPDR_TRACE1(spdr, cat, name, SPDR_EVENT, arg0)

/**
 * An instant event with two parameters
 */
#define SPDR_EVENT2(spdr, cat, name, arg0, arg1)		\
	UU_SPDR_TRACE2(spdr, cat, name, SPDR_EVENT, arg0, arg1)

/**
 * An instant event with two parameters
 */
#define SPDR_EVENT3(spdr, cat, name, arg0, arg1, arg2)		\
	UU_SPDR_TRACE3(spdr, cat, name, SPDR_EVENT, arg0, arg1, arg2)


/* __ Work slices __ */

/**
 * Begin a slice of work
 */
#define SPDR_BEGIN(spdr, cat, name)			\
	UU_SPDR_TRACE(spdr, cat, name, SPDR_BEGIN)

/**
 * Begin a slice of work, with one parameter.
 */
#define SPDR_BEGIN1(spdr, cat, name, arg0)			\
	UU_SPDR_TRACE1(spdr, cat, name, SPDR_BEGIN, arg0)

/**
 * Begin a slice of work, with two parameters
 */
#define SPDR_BEGIN2(spdr, cat, name, arg0, arg1)		\
	UU_SPDR_TRACE2(spdr, cat, name, SPDR_BEGIN, arg0, arg1)

/**
 * Begin a slice of work, with three parameters
 */
#define SPDR_BEGIN3(spdr, cat, name, arg0, arg1, arg2)			\
	UU_SPDR_TRACE3(spdr, cat, name, SPDR_BEGIN, arg0, arg1, arg2)

/**
 * End a slice of work
 */
#define SPDR_END(spdr, cat, name)			\
	UU_SPDR_TRACE(spdr, cat, name, SPDR_END)

/**
 * Mark the beginning and end of a scope
 *
 * Non standard. Only supported on select compilers.
 */
#define SPDR_SCOPE(spdr, cat, name)		\
	UU_SPDR_SCOPE_TRACE(spdr, cat, name)

#define SPDR_SCOPE1(spdr, cat, name, arg0)		\
	UU_SPDR_SCOPE_TRACE1(spdr, cat, name, arg0)

#define SPDR_SCOPE2(spdr, cat, name, arg0, arg1)		\
	UU_SPDR_SCOPE_TRACE2(spdr, cat, name, arg0, arg1)

#define SPDR_SCOPE3(spdr, cat, name, arg0, arg1, arg2)		\
	UU_SPDR_SCOPE_TRACE3(spdr, cat, name, arg0, arg1, arg2)


/* __ Counters __ */

/**
 * Track values over time.
 *
 * @param arg must be SPDR_INT or SPDR_FLOAT
 */
#define SPDR_COUNTER1(spdr, cat, name, arg0)	\
	UU_SPDR_TRACE1(spdr, cat, name, SPDR_COUNTER, arg0)

#define SPDR_COUNTER2(spdr, cat, name, arg0, arg1)			\
	UU_SPDR_TRACE2(spdr, cat, name, SPDR_COUNTER, arg0, arg1)

#define SPDR_COUNTER3(spdr, cat, name, arg0, arg1, arg2)			\
	UU_SPDR_TRACE3(spdr, cat, name, SPDR_COUNTER, arg0, arg1, arg2)

/* __ Metadata __ */

/**
 * Metadata.
 *
 * For instance to set the thread name:
 * @code
 * SPDR_METADATA1("thread_name", SPDR_STR("name", "My_Thread"))
 * @code
 *
 * chrome://tracing will then display this name rather than the tid of
 * the thread.
 */
#define SPDR_METADATA1(spdr, name, arg0)				\
	UU_SPDR_TRACE1(spdr, "__metadata", name, SPDR_METADATA, arg0)


#endif
