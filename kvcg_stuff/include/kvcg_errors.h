/****************************************************
 *
 * KVCG Error Codes
 *
 ****************************************************/

#ifndef KVCG_ERROR_CODES_H
#define KVCG_ERROR_CODES_H


/**
 *
 * Definition of KVCG Errors
 *
 */
enum errNum: int {

KVCG_ESUCCESS = 0,
KVCG_EUNKNOWN = 1,
KVCG_EBADCONFIG = 10,
KVCG_EINVALID,
KVCG_EBADCONN,
KVCG_EBADMSG

};

/**
 *
 * Get human readable description of error code
 * returned from KVCG call.
 *
 * @param errnum - error code returned from KVCG call
 *
 * @return description of error
 *
 */
inline const char *kvcg_strerror(int errnum) {
    switch (errnum) {
        case KVCG_ESUCCESS: return "Success";
        case KVCG_EUNKNOWN: return "Unknown error";
        case KVCG_EBADCONFIG: return "Config file error";
        case KVCG_EINVALID: return "Invalid input";
        case KVCG_EBADCONN: return "Bad connection";
        case KVCG_EBADMSG: return "Bad message";
    }

    return "Undefined error";
}

#endif // KVCG_ERROR_CODES_H
