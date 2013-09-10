#ifndef _TRANSAPI_H
#define _TRANSAPI_H

#include "../libnetconf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* maximal number of input arguments every defined RPC can have */
#ifndef MAX_RPC_INPUT_ARGS
#define MAX_RPC_INPUT_ARGS 64
#endif

/**
 * @ingroup transapi
 * @brief Enum specifying states of node in document
 */
typedef enum
{
	XMLDIFF_ERR = -1 /**< Error while creating XML difftree. */,
	XMLDIFF_NONE = 0 /**< Last operation did not cause any change in configuration. */,
	XMLDIFF_ADD = 1 /**< Element was added to configuration. */,
	XMLDIFF_REM = 2 /**< Element was removed from configuration. */,
	XMLDIFF_MOD = 4/**< Element was modified. */,
	XMLDIFF_CHAIN = 8/**< Some of children of element was modified/added/removed. */
} XMLDIFF_OP;

/**
 * @ingroup transapi
 * @brief Structure binding location in configuration XML data and function callback applying changes.
 */
struct transapi_data_callbacks {
	int callbacks_count;
	void * data;
	struct {
		char * path;
		int (*func)(XMLDIFF_OP, char *, void **);
	} callbacks[];
};


/**
 * @ingroup transapi
 * @brief Structure binding location in configuration XML data and function callback processing RPC message.
 */
struct transapi_rpc_callbacks {
        int callbacks_count;
        struct {
                char * name;
                int arg_count;
        		nc_reply * (*func)(char *[]);
                char * arg_order[MAX_RPC_INPUT_ARGS];
        } callbacks[];
};

#ifdef __cplusplus
}
#endif

#endif
